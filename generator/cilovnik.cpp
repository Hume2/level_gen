#include <stdio.h>
#include <iostream>
#include <cstdlib>

#include "cilovnik.h"

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

Cilovnik::Cilovnik(Sektor *s_) :
  nas_sektor(s_),
  hl(s_, HledejZem::VOLNY)
{
}

void Cilovnik::udelej_cil(int x, int y) {
  uprav_pozici(x, y);
  udelej_tyc(x-1, y, nas_sektor->bkgrd);
  udelej_tyc(x+1, y, nas_sektor->frgrd);
  if (nas_sektor->level->tema.hrani == TemaLevelu::T3D ||
      nas_sektor->level->tema.hrani == TemaLevelu::T3_5D) {
    udelej_end_seq(x, y, "fireworks");
  } else {
    udelej_end_seq(x, y, "endsequence");

    if (nas_sektor->level->tema.hrani == TemaLevelu::T2D ||
             nas_sektor->level->tema.hrani == TemaLevelu::T2_5D) {
      return;
    }
    if (nas_sektor->tema != TemaSektoru::Tvenku) {
      return;
    }
    if (nas_sektor->level->tema.vyskopis == TemaLevelu::Tpodzemi ||
        nas_sektor->level->tema.vyskopis == TemaLevelu::Tnebe) {
      return;
    }

    hledej_trasu(x, y);

    switch (nas_sektor->level->tema.biom) {
      case TemaLevelu::Tledovec:
        udelej_iglu(x, y);
        break;
      case TemaLevelu::Tles:
      case TemaLevelu::Tdzungle:
        udelej_strom(x, y);
        break;
      case TemaLevelu::Tducholes:
        udelej_budku(x, y);
        break;
      case TemaLevelu::Tkrystaly:
        break;
    }
  }
}

void Cilovnik::udelej_iglu(int x, int y) {
  udelej_end_seq(x+4, y, "stoptux");

  y -= 5;
  Objekt* obj = new Objekt("decal", x*32, y*32);
  obj->blbosti = "(layer 100)(sprite \"images/tiles/goal/exitfg.png\")";
  nas_sektor->objekty.push_back(obj);

  x -= 3;
  obj = new Objekt("decal", x*32, y*32);
  obj->blbosti = "(layer -100)(sprite \"images/tiles/goal/exitbg.png\")";
  nas_sektor->objekty.push_back(obj);
}

void Cilovnik::udelej_budku(int x, int y) {
  udelej_end_seq(x+2, y, "stoptux");

  y -= 3;
  Objekt* obj = new Objekt("decal", x*32, y*32);
  obj->blbosti = "(layer 100)(sprite \"images/tiles/forest/exit/outhouse.png\")";
  nas_sektor->objekty.push_back(obj);
}

void Cilovnik::udelej_strom(int x, int y) {
  //1632 1633 1634 1635 +4
  int a,b;
  BLOK t = 1632;
  for (b = y-6; b <= y; b++) {
    for (a = x-1; a <= x+2; a++) {
      BKGRD(t, a, b);
      t++;
    }
    t += 3;
  }

  //1643 1644 1645 1656 (+11) -> 1650 +5
  t = 1636;
  for (b = y-4; b < y; b++) {
    for (a = x-1; a <= x+1; a++) {
      FRGRD(t, a, b);
      t++;
    }
    FRGRD(t+10, a, b);
    t += 4;
  }
  FRGRD(1666, x+1, y);
  FRGRD(1677, x+2, y);

  x+=3;
  FRGRD(1664, x  , y-2);
  FRGRD(1665, x+1, y-2);
  t = 1671;
  for (b = y-1; b <= y; b++) {
    for (a = x; a <= x+2; a++) {
      FRGRD(t, a, b);
      t++;
    }
    t += 4;
  }

  udelej_end_seq(x+1, y, "stoptux");
}

void Cilovnik::hledej_trasu(int &x, int &y) {
  najdi_pozici_dole(x, y);
  x += 15;
}

void Cilovnik::najdi_pozici_dole(int x, int &y) {
  hl.hledej_zem(x, y);
}

void Cilovnik::najdi_pozici_nahore(int x, int &y) {
  hl.hledej_strop(x, y);
}

void Cilovnik::udelej_end_seq(int x, int y, std::string seq) {
  int y1 = y-1;
  while (nas_sektor->je_blok_volny(x,y1) && y1 >= 0) {
    y1--;
  }
  while (nas_sektor->je_blok_volny(x,y) && y < nas_sektor->intact->vyska) {
    y++;
  }
  y--;
  int h = (y-y1+1) * 32;
  Objekt* obj = new Objekt("sequencetrigger", x*32, y1*32);
  obj->blbosti = "(width 32) (height " + patch::to_string(h) + ") (sequence \"" + seq + "\")";
  nas_sektor->objekty.push_back(obj);

  nas_sektor->obdelniky.push_back(Obdelnik(x-5, y-5, x+25, y));
}

void Cilovnik::udelej_tyc(int x, int y, Tilemap *tm) {

  int h = 0;
  int y_ = y-1;
  while (nas_sektor->je_blok_volny(x,y_) && h<10) {
    tm->poloz_blok(129, x, y);
    y = y_;
    y_--;
    h++;
  }
  tm->poloz_blok(130, x, y);
}

void Cilovnik::udelej_start(int x, int y) {
  uprav_pozici(x, y);
  y--;

  Objekt* obj = new Objekt("spawnpoint", x*32, y*32);
  obj->jmeno = "main";
  nas_sektor->objekty.push_back(obj);

  nas_sektor->obdelniky.push_back(Obdelnik(x, y-5, x+5, y+2));
}

bool Cilovnik::ulozovak(int x, int y) {
  uprav_pozici(x, y);
  y-=2;

  if (nas_sektor->je_povoleno(x,y)) {
    Objekt* obj = new Objekt("firefly", x*32, y*32);
    nas_sektor->objekty.push_back(obj);

    nas_sektor->obdelniky.push_back(Obdelnik(x-2, y-5, x+2, y+2));
    return true;
  } else {
    return false;
  }
}

void Cilovnik::nasekej_ulozovaky() {
  int pocet = nas_sektor->intact2->sirka / 250;
  for (int i = pocet; i; i--) {
    int st = i*250 - 1;
    if (!ulozovak(st, nahodne(nas_sektor->intact2->vyska))) {
      for (int j = 100; j; j--) {
        if (ulozovak(signed_xp_rand(10) + st, nahodne(nas_sektor->intact2->vyska))) {
          break;
        }
      }
    }
  }
}

void Cilovnik::uprav_pozici(int x, int &y) {
  if (nas_sektor->je_blok_volny(x,y)) {
    y++;
    najdi_pozici_dole(x,y);
  } else {
    y--;
    najdi_pozici_nahore(x,y);
  }
}
