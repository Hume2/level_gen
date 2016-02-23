#include <math.h>
#include <sstream>
#include <stdio.h>
#include <string>
#include <iostream>
#include <cstdlib>

#include "prekazitor.h"

#include "../level/cesta.h"
#include "../level/level.h"
#include "../level/objekt.h"
#include "../level/sektor.h"
#include "../level/tilemap.h"
#include "random.h"

#include "../tema/dlazdicky.h"
#include "../tema/tematicke_hodnoty.h"

#include "pokladac_svahu.h"

#define S til.konvexni[7]
#define K til.konvexni
#define V til.konkavni
#define P til.pidischody

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

Prekazitor::Prekazitor(Sektor* s_, int* X_, int* Y_, SadaDlazdic til_, int max_x_, int min_y_) :
  s(s_),
  X(X_),
  Y(Y_),
  til(til_),
  max_x(max_x_),
  min_y(min_y_)
{
}

void Prekazitor::nahodny_skok(int &x, int &y, int max_dx) {
  int dy = nahodne(5) - 2;
  int dx = nahodne(7) + 3;
  if ((dy < 0) && (dx >= 10)) {
    dy = -dy;
    dx = 11;
  } else if ((dy == -2) && (dx >= 9)) {
    dy = -3;
    dx = 7;
  }
  if (dx > max_dx) {
    dx = max_dx;
  }
  x += dx;
  int y2 = y + dy;
  if (y2 >= min_y && y2 < s->intact2->vyska) {
    y = y2;
  }
}

void Prekazitor::uber_dolovak() {
  s->intact2->poloz_blok(K[2], *X, (*Y)-1);
  s->intact2->poloz_blok(K[5], *X, *Y);
  s->intact2->obdelnik(K[8], *X, *X, (*Y)+1, s->intact2->vyska);
}

void Prekazitor::uber_nahorovak() {
  s->intact2->poloz_blok(K[0], *X, (*Y)-1);
  s->intact2->poloz_blok(K[3], *X, *Y);
  s->intact2->obdelnik(K[6], *X, *X, (*Y)+1, s->intact2->vyska);
}

void Prekazitor::zakaz(int x1, int x2, int y1, int y2) {
  Obdelnik o(x1, y1, x2, y2);
  s->obdelniky.push_back(o);
}

void Prekazitor::stredovak(int l) {
  int X2 = *X + l;
  int Y2 = *Y-1;
  s->intact2->obdelnik(K[1],*X,X2,Y2,Y2);
  s->intact2->obdelnik(K[4],*X,X2,*Y,*Y);
  s->intact2->obdelnik(S,*X,X2,*Y+1,s->intact2->vyska);
  *X += l;
}

void Prekazitor::nahorovak(int dh) {
  int Y2 = *Y - dh;

  s->intact2->poloz_blok(K[0], *X, Y2-1);
  if (dh == 1) {
    s->intact2->poloz_blok(P[0], *X, Y2);
  } else {
    s->intact2->poloz_blok(K[3], *X, Y2);
    s->intact2->obdelnik(K[6], *X, *X, Y2+1, *Y-2);
    s->intact2->poloz_blok(V[3], *X, *Y-1);
  }
  s->intact2->poloz_blok(V[5], *X, *Y);
  s->intact2->obdelnik(S, *X, *X, *Y+1, s->intact2->vyska);
  (*X)++;
  *Y = Y2;
}

void Prekazitor::dolovak(int dh) {
  int Y2 = *Y + dh;

  s->intact2->poloz_blok(K[2], *X, *Y-1);
  if (dh == 1) {
    s->intact2->poloz_blok(P[1], *X, *Y);
  } else {
    s->intact2->poloz_blok(K[5], *X, *Y);
    s->intact2->obdelnik(K[8], *X, *X, *Y+1, Y2-2);
    s->intact2->poloz_blok(V[2], *X, Y2-1);
  }
  s->intact2->poloz_blok(V[4], *X, Y2);
  s->intact2->obdelnik(S, *X, *X, Y2+1, s->intact2->vyska);
  (*X)++;
  *Y = Y2;
}

void Prekazitor::ostruvek() {
  BLOK bloky[9] = {K[3], K[4], K[5], K[6], K[7], K[8], K[9], K[10], K[11]};
  int x2 = *X + 1 + exp_rand(4,6);
  int y2 = *Y + 1 + exp_rand(4,4);
  s->intact2->ram_obdelnik(bloky, *X, x2, *Y, y2);
  s->intact2->poloz_blok(K[0], *X, (*Y)-1);
  s->intact2->obdelnik(K[1], (*X)+1, x2-1, (*Y)-1, (*Y)-1);
  s->intact2->poloz_blok(K[2], x2, (*Y)-1);
  //std::cout << "před:" << *X;
  *X = x2;
  //std::cout << " po:" << *X << std::endl;
}

void Prekazitor::piskac() {
  Objekt* obj;
  if (s->level->tema.biom == TemaLevelu::Tledovec) {
    obj = new Objekt("flyingsnowball",(*X)*32,(*Y)*32);
  } else {
    obj = new Objekt("spidermite",(*X)*32,(*Y)*32);
  }
  s->objekty.push_back(obj);
}

void Prekazitor::secretarea(int x, int y, Tilemap* tm) {
  tm->cesta->bod(x*32, y*32);
  Objekt* obj = new Objekt("secretarea", x*32, y*32);
  obj->blbosti = "(width " + patch::to_string(tm->sirka*32) + ")\n";
  obj->blbosti += "(height " + patch::to_string(tm->vyska*32) + ")\n";
  obj->blbosti += "(fade-tilemap \"" + tm->jmeno + "\")\n";
  s->objekty.push_back(obj);
  int x2 = x + tm->sirka - 1;
  int y2 = y + tm->vyska - 1;
  for (int i = x+1; i < x2; i++) {
    for (int j = y; j < y2; j++) {
      if (nahodne(2)) {
        s->intact->poloz_blok(44, i, j);
      }
    }
  }
  zakaz(x, x2 + 1, y, y2 + 1);
}

bool Prekazitor::uprav_smer(bool &sm, int h) {
  if (sm) {
    if (*Y + h >= s->intact2->vyska) {
      sm = !sm;
      if (*Y - h < min_y) {
        return false;
      }
    }
  } else {
    if (*Y - h < min_y) {
      sm = !sm;
      if (*Y + h >= s->intact2->vyska) {
        return false;
      }
    }
  }
  return true;
}

bool Prekazitor::dira() {
  if (*X > max_x - 13) {
    return false;
  }
  int x1 = *X;
  uber_dolovak();
  nahodny_skok(*X, *Y);
  uber_nahorovak();
  (*X)++;
  int x2 = *X;

  zakaz(x1, x2, 0, s->intact2->vyska);

  return true;
}

bool Prekazitor::tramposka() {
  bool sm = nahodne(2);
  int h = nahodne(8) + 5;

  if (!uprav_smer(sm, h)) {
    return false;
  }

  if (sm) {
    dolovak(h);
    stredovak(1);
    Objekt *o = new Objekt("trampoline", ((*X)-1)*32, ((*Y)-1)*32);
    o->blbosti = "(portable #f)";
    s->objekty.push_back(o);
  } else {
    stredovak(1);
    Objekt *o = new Objekt("trampoline", ((*X)-1)*32, ((*Y)-1)*32);
    o->blbosti = "(portable #f)";
    s->objekty.push_back(o);
    nahorovak(h);
  }
  return true;
}

bool Prekazitor::parkur() {
  bool zacato = false;
  int x2 = *X, y2 = *Y;
  nahodny_skok(x2, y2);
  while (x2 < max_x) {
    if (!zacato) {
      uber_dolovak();
      zacato = true;
    }
    zakaz(*X, x2, 0, s->intact2->vyska);
    *X = x2;
    *Y = y2;
    if (nahodne(3) == 0 || x2 >= max_x) {
      break;
    }
    ostruvek();
    x2 = *X;
    nahodny_skok(x2, y2);
    if (x2 >= max_x) {
      (*X)++;
    }
  }
  if (zacato) {
    uber_nahorovak();
    (*X)++;
  }
  return zacato;
}

bool Prekazitor::piskacojump() {
  bool zacato = false;
  int x2 = *X, y2 = *Y;
  int x1 = x2;
  nahodny_skok(x2, y2);
  while (x2 < max_x) {
    if (!zacato) {
      uber_dolovak();
      zacato = true;
    }
    *X = x2;
    *Y = y2;
    if (nahodne(3) == 0 || x2 >= max_x || y2 >= s->intact2->vyska-5) {
      break;
    }
    piskac();
    nahodny_skok(x2, y2, 5);
  }
  if (zacato) {
    uber_nahorovak();
    (*X)++;
    zakaz(x1, *X, 0, s->intact2->vyska);
  }
  return zacato;
}

bool Prekazitor::pneumatic() {
  int rezerva1 = (*Y) - min_y;
  int rezerva2 = s->intact2->vyska - (*Y) - 1;
  int rezerva = std::min(rezerva1, rezerva2);
  if (rezerva < 5) {
    return false;
  }
  int max_d = std::min(rezerva, 12) - 5;
  int dy = 5 + exp_rand(10, max_d);
  int y_pn = *Y;
  int nove_y = y_pn + dy;

  Objekt *o = new Objekt("rock", (*X)*32, ((*Y)-1)*32);
  s->objekty.push_back(o);

  while (*Y < nove_y) {
    dolovak( std::min(nove_y - (*Y), 4) );
  }
  o = new Objekt("pneumatic-platform", (*X)*32, y_pn*32);
  o->blbosti = "(sprite \"images/objects/platforms/small.sprite\")";
  s->objekty.push_back(o);
  stredovak(4);
  nahorovak(2*dy);
  return true;
}

bool Prekazitor::bodlaky() {
  if ((*X) + 7 > max_x) {
    return false;
  }
  stredovak(3);
  int x_ = *X;
  int d = nahodne(7) + 1;
  if ((x_ + d + 3) > max_x) {
    d = max_x - x_ - 3;
  }
  stredovak(d);
  s->intact->obdelnik(295, x_, *X, (*Y)-1, (*Y)-1);
  zakaz(x_-1, (*X)+1, (*Y)-5, *Y);
  stredovak(3);
  return true;
}

bool Prekazitor::tajna_chodba() {
  bool sm = !(nahodne(2));
  if (!uprav_smer(sm, 4)) {
    return false;
  }
  int delka = exp_rand(6, max_x-(*X)-4) + 3;
  if (delka < 3) {
    return false;
  }

  Tilemap* tm = new Tilemap(delka, 4, false);
  tm->pojmenuj("secretTM",s->tajnych_chodeb);
  tm->z_pos = 200 + s->tajnych_chodeb;
  tm->cesta = new Cesta();
  float x, y;
  if (sm) {
    dolovak(4);
    stredovak(delka);
    s->intact2->obdelnik(K[1] , (*X)-delka-1, (*X)-3, (*Y)-5, (*Y)-5);
    s->intact2->obdelnik(K[4] , (*X)-delka-1, (*X)-3, (*Y)-4, (*Y)-4);
    s->intact2->obdelnik(K[10], (*X)-delka-1, (*X)-3, (*Y)-3, (*Y)-3);
    s->intact2->poloz_blok(K[2] , (*X)-2, (*Y)-5);
    s->intact2->poloz_blok(K[5] , (*X)-2, (*Y)-4);
    s->intact2->poloz_blok(K[11], (*X)-2, (*Y)-3);
    s->intact2->poloz_blok(V[0], (*X)-delka-1, (*Y)-3);

    tm->obdelnik(S, 0, tm->sirka-2, 0, tm->vyska-1);
    tm->obdelnik(K[8], tm->sirka-1, tm->sirka-1, 0, tm->vyska-3);
    tm->poloz_blok(V[2], tm->sirka-1, tm->vyska-2);
    tm->poloz_blok(V[4], tm->sirka-1, tm->vyska-1);
    x = (*X)-delka-1;
    y = (*Y)-3;
  } else {
    stredovak(delka);
    nahorovak(4);
    s->intact2->poloz_blok(K[0], (*X)-delka, (*Y)-1);
    s->intact2->poloz_blok(K[3], (*X)-delka, *Y);
    s->intact2->poloz_blok(K[9], (*X)-delka, (*Y)+1);
    s->intact2->obdelnik(K[1] , (*X)-delka+1, *X, (*Y)-1, (*Y)-1);
    s->intact2->obdelnik(K[4] , (*X)-delka+1, *X, *Y, *Y);
    s->intact2->obdelnik(K[10], (*X)-delka+1, *X, (*Y)+1, (*Y)+1);
    s->intact2->poloz_blok(V[1], (*X)-1, (*Y)+1);

    tm->obdelnik(S, 1, tm->sirka-1, 0, tm->vyska-1);
    tm->obdelnik(K[6], 0, 0, 0, tm->vyska-3);
    tm->poloz_blok(V[3], 0, tm->vyska-2);
    tm->poloz_blok(V[5], 0, tm->vyska-1);
    x = (*X)-delka;
    y = (*Y)+1;
  }
  secretarea(x, y, tm);
  stredovak(1);
  s->tilemapy.push_back(tm);
  s->tajnych_chodeb++;
  return true;
}

bool Prekazitor::prekazka() {
  TypPrekazky typ = (TypPrekazky)nahodne((int)TYPY_PREKAZEK);
  switch (typ) {
    case DIRA:
      return dira();
    case TRAMPOSKA:
      return tramposka();
    case PARKUR:
      return parkur();
    case PISKACOJUMP:
      return piskacojump();
    case PNEUMATIC:
      return pneumatic();
    case BODLAKY:
      return bodlaky();
    case TAJNA_CHODBA:
      return tajna_chodba();
    default:
      return false;
  }
}
