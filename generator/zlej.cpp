#include <stdio.h>
#include <iostream>
#include <cstdlib>

#include "zlej.h"

#include "random.h"

#include "../level/level.h"
#include "../level/objekt.h"
#include "../level/sektor.h"
#include "../level/tilemap.h"

#include "../tema/dlazdicky.h"
#include "../tema/tematicke_hodnoty.h"

#include <sstream>

#define BKGRD nas_sektor->bkgrd->poloz_blok
#define FRGRD nas_sektor->frgrd->poloz_blok

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

Zlej::Zlej(Sektor *s_, const double* pocty_) :
  nas_sektor(s_),
  tvrda_zem(nas_sektor->tema != TemaSektoru::Tvenku),
  pocty(pocty_)
{
}

bool Zlej::najdi_pozici_dole(int x, int &y) {
  while (nas_sektor->je_blok_volny(x,y) && y < nas_sektor->intact->vyska) {
    y++;
  }
  return y < nas_sektor->intact->vyska;
}

bool Zlej::inv_najdi_pozici_nahore(int x, int &y) {
  while (!nas_sektor->je_blok_volny(x,y) && y >= 0) {
    y--;
  }
  y++;
  return y > 1;
}

bool Zlej::inv_najdi_pozici_dole(int x, int &y) {
  while (!nas_sektor->je_blok_volny(x,y) && y < nas_sektor->intact->vyska) {
    y++;
  }
  return y < nas_sektor->intact->vyska;
}

bool Zlej::najdi_pozici_nahore(int x, int &y) {
  while (nas_sektor->je_blok_volny(x,y) && y >= 0) {
    y--;
  }
  y++;
  return y > 1;
}

bool Zlej::uprav_pozici(int x, int &y) {
  if (nas_sektor->je_blok_volny(x,y)) {
    y++;
    if (!najdi_pozici_dole(x,y)) {
      return false;
    }
  } else {
    y--;
    if (!inv_najdi_pozici_nahore(x,y)) {
      return false;
    }
  }
  y--;

  return nas_sektor->je_povoleno(x,y);
}

bool Zlej::uprav_horni_pozici(int x, int &y) {
  if (nas_sektor->je_blok_volny(x,y)) {
    y--;
    if (!najdi_pozici_nahore(x,y)) {
      return false;
    }
  } else {
    y++;
    if (!inv_najdi_pozici_dole(x,y)) {
      return false;
    }
  }

  return nas_sektor->je_povoleno(x,y);
}

int Zlej::vymysli_pocet() {
  int pocet;
  if (nas_sektor->level->tema.hrani == TemaLevelu::T1D && nas_sektor->tema != TemaSektoru::Thrad) {
    pocet = nas_sektor->intact->sirka / 10;
  } else {
    pocet = (nas_sektor->intact->sirka / 10) * (nas_sektor->intact->vyska / 20);
  }
  return pocet;
}

void Zlej::nasekej_zlejsky() {
  int pocet = vymysli_pocet();
  int i;

  for (i = pocet; i; i--) {
    int x = nahodne(nas_sektor->intact->sirka), y = nahodne(nas_sektor->intact->vyska);
    if (!nas_sektor->je_povoleno(x, y)) {
      continue;
    }
    Zlejsci typ = (Zlejsci)nahodne_vyber(pocty, pocet_zlejsku);
    switch (typy_zlejsku[typ]) {
      case TZ_CHODEC:
        bezny_zlejsek(x, y, typ);
        break;
      case TZ_LETOUN:
        litac(x, y, typ);
        break;
      case TZ_SKOKAN:
        skokan(x, y, typ);
        break;
      case TZ_PADAC:
        rampouch(x, y, typ);
        break;
      default:
        break;
    }
  }
}

#if 0

const char* zlejsci[10] = {"snowball","smartball","jumpy","mriceblock","smartblock","mrbomb","haywire","spiky","bouncingsnowball","captainsnowball"};
double sance[10] = {10,10,2,7,7,5,4,5,3,1};

#endif

Objekt* Zlej::umisti(int x, int y, Zlejsci typ) {
  Objekt* obj = new Objekt(nazvy_zlejsku[typ], x*32, y*32);
  nas_sektor->objekty.push_back(obj);
  return obj;
}

void Zlej::bezny_zlejsek(int x, int y, Zlejsci typ) {
  if (uprav_pozici(x, y)) {
    umisti(x, y, typ);
  }
}

void Zlej::rampouch(int x, int y, Zlejsci typ) {
  if (uprav_horni_pozici(x, y)) {
    umisti(x, y, typ);
  }
}

void Zlej::litac(int x, int y, Zlejsci typ) {
  if (nas_sektor->je_blok_volny(x, y)) {
    umisti(x, y, typ);
  }
}

void Zlej::skokan(int x, int y, Zlejsci typ) {
  if (uprav_pozici(x, y)) {
    int y2 = y-1;
    najdi_pozici_nahore(x, y2);
    if (y - y2 >= 5) {
      umisti(x, y-3, typ);
    }
  }
}
