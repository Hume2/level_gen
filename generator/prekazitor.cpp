#include <math.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <cstdlib>

#include "prekazitor.h"

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

Prekazitor::Prekazitor(Sektor* s_, int* X_, int* Y_, SadaDlazdic til_, int max_x_, int min_y_) :
  s(s_),
  X(X_),
  Y(Y_),
  til(til_),
  max_x(max_x_),
  min_y(min_y_)
{
}

void Prekazitor::nahodny_skok(int &x, int &y) {
  int dy = nahodne(5) - 2;
  int dx = nahodne(7) + 3;
  if ((dy < 0) && (dx >= 10)) {
    dy = -dy;
    dx = 11;
  } else if ((dy == -2) && (dx >= 9)) {
    dy = -3;
    dx = 7;
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
    *X = x2;
    *Y = y2;
    if (nahodne(3) == 0 || x2 >= max_x) {
      break;
    }
    ostruvek();
    x2 = *X;
    nahodny_skok(x2, y2);
  }
  if (zacato) {
    uber_nahorovak();
    (*X)++;
  }
  return zacato;
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
  }
}
