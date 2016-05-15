#include <string>
#include <stdio.h>
#include <iostream>

#include "sektor.h"

#include "level.h"
#include "objekt.h"
#include "tilemap.h"

#include "../generator/generator.h"
#include "../generator/pozadi.h"

#include "../tema/tema.h"

using namespace std;

Sektor::Sektor(Level *l, std::string jmeno_) :
  level(l),
  tema(TemaSektoru::Tvenku),
  jmeno(jmeno_),
  hudba(""),
  osvetleni(256,256,256,256),
  blbosti(""),
  bkgrd(),
  intact(),
  intact2(),
  frgrd(),
  objekty(),
  tilemapy(),
  obdelniky(),
  tajnych_chodeb(0)
{
  bkgrd = new Tilemap(l->sirka, l->vyska, false);
  bkgrd->z_pos = -100;
  intact = new Tilemap(l->sirka, l->vyska, true);
  intact->z_pos = 0;
  intact2 = new Tilemap(l->sirka, l->vyska, true);
  intact2->z_pos = 51;
  frgrd = new Tilemap(l->sirka, l->vyska, false);
  frgrd->z_pos = 100;

  vymysli_osvetleni(this);
  if (level->tema.vyskopis == TemaLevelu::Tpodzemi) {
    gen_jeskyne1(this);
  } else {
    gen_lesni_podlaha(this);
  }
  gen_start(this, 0, 0);
  gen_cil(this, level->sirka-25, 1);
  gen_ulozovaky(this);
  gen_otazniky(this);
  gen_zlejsky(this);
  gen_ryby(intact2);
  vymysli_pocasi(this);
  vymysli_hudbu(this);
  vymysli_pozadi(this);
}

Sektor::~Sektor() {
  for (vector<Objekt*>::iterator i = objekty.begin(); i != objekty.end(); i++) {
    Objekt* obj = *i;
    delete (obj);
  }
  for (vector<Tilemap*>::iterator i = tilemapy.begin(); i != tilemapy.end(); i++) {
    Tilemap* tm = *i;
    delete (tm);
  }
  delete bkgrd;
  delete intact;
  delete intact2;
  delete frgrd;
}

void Sektor::vysav(FILE *f) {
  fprintf(f, "  (sector\n    (camera (mode \"normal\"))\n    (name \"");
  fputs(jmeno.c_str(), f);
  fprintf(f, "\")\n    (music \"music/");
  fputs(hudba.c_str(), f);
  fprintf(f, "\")\n    (ambient-light ");
  osvetleni.vysav(f);
  fprintf(f, ")\n");
  fputs(blbosti.c_str(), f);
  fprintf(f, "\n");
  for (vector<Objekt*>::iterator i = objekty.begin(); i != objekty.end(); i++) {
    Objekt* obj = *i;
    obj->vysav(f);
  }
  if (intact->lze_sloucit(intact2)) {
    intact2->sluc_s(intact);
    intact->viditelny = false;
  }
  bkgrd->vysav(f);
  intact->vysav(f);
  intact2->vysav(f);
  frgrd->vysav(f);
  for (vector<Tilemap*>::iterator i = tilemapy.begin(); i != tilemapy.end(); i++) {
    Tilemap* tm = *i;
    tm->vysav(f);
  }
  fprintf(f, "\n  )");
}

void Sektor::posun_objekty(int x, int y) {
  for (vector<Objekt*>::iterator i = objekty.begin(); i != objekty.end(); i++) {
    Objekt* obj = *i;
    obj->posun(x, y);
  }
}

bool Sektor::je_blok_volny(int x, int y) {
  if (x < 0 || y < 0 || x >= level->sirka || y >= level->vyska) {
    return false;
  }
  if (intact2->je_blok_pevny(x, y)) {
    return false;
  }
  for (vector<Tilemap*>::iterator i = tilemapy.begin(); i != tilemapy.end(); i++) {
    Tilemap* tm = *i;
    if (tm->je_blok_pevny(x, y) && tm->pevny) {
      return false;
    }
  }
  return true;
}

bool Sektor::je_obdelnik_prazny(int x1, int x2, int y1, int y2) {
  if (!bkgrd->je_obdelnik_prazdny(x1, x2, y1, y2) ||
      !intact->je_obdelnik_prazdny(x1, x2, y1, y2) ||
      !intact2->je_obdelnik_prazdny(x1, x2, y1, y2) ||
      !frgrd->je_obdelnik_prazdny(x1, x2, y1, y2)) {
    return false;
  }
  for (vector<Tilemap*>::iterator i = tilemapy.begin(); i != tilemapy.end(); i++) {
    Tilemap* tm = *i;
    if (!tm->je_obdelnik_prazdny(x1, x2, y1, y2)) {
      return false;
    }
  }
  return true;
}

bool Sektor::je_obdelnik_volny(int x1, int x2, int y1, int y2) {
  if (!intact2->je_obdelnik_pevny(x1, x2, y1, y2)) {
    return false;
  }
  for (vector<Tilemap*>::iterator i = tilemapy.begin(); i != tilemapy.end(); i++) {
    Tilemap* tm = *i;
    if (!tm->je_obdelnik_pevny(x1, x2, y1, y2) && tm->pevny) {
      return false;
    }
  }
  return true;
}

bool Sektor::je_povoleno(int x, int y) {
  //std::cout << "x" << x << " y" << y << std::endl;
  for (vector<Obdelnik>::iterator i = obdelniky.begin(); i != obdelniky.end(); i++) {
    Obdelnik o = *i;
    //std::cout << "1x" << o.x1 << " 1y" << o.y1 << " 2x" << o.x2 << " 2y" << o.y2 << std::endl;
    if (x >= o.x1 && x <= o.x2 && y >= o.y1 && y <= o.y2) {
      //std::cout << "nn" << std::endl;
      return false;
    }
  }
  //std::cout << "jj" << std::endl;
  return true;
}
