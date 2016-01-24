#include <math.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <ctime>

#include "ledove_pozadi.h"

#include "../level/level.h"
#include "../level/sektor.h"
#include "../level/tilemap.h"
#include "random.h"

#include "../tema/tematicke_hodnoty.h"

using namespace std;

void LedovePozadi::sloupek(int x, int til, int min_y, int max_y) {
  bloky->obdelnik(til,x,x,min_y,max_y-1);
}

void LedovePozadi::var_sloupek(int x, int til, int min_y, int max_y) {
  for (int y = min_y+1; y < max_y; y++) {
    bloky->poloz_blok(til+5,x,y);
    int p = nahodne(100);
    if (p <= var_chance) {
      bloky->poloz_blok(til+97,x,y);
      p = nahodne(10);
      if (p <= 1) {
        bloky->poloz_blok(til+96,x,y);
      }
    }
  }
}

void LedovePozadi::nahorovak(int x, int start, int til, int plus) {
  var_sloupek(x, til, start, h);
  bloky->poloz_blok(til+11,x,start);
  sloupek(x, til+4, start-plus, start);
  bloky->poloz_blok(til+1,x,start-plus);
}

void LedovePozadi::dolovak(int x, int start, int til, int minus) {
  var_sloupek(x, til, start+minus, h);
  bloky->poloz_blok(til+10,x,start+minus);
  sloupek(x, til+6, start, start+minus);
  bloky->poloz_blok(til+3,x,start);
}

void LedovePozadi::stredovak(int x, int start, int til) {
  var_sloupek(x, til, start, h);
  bloky->poloz_blok(til+2,x,start);
}

void LedovePozadi::vydlazdickuj(int til) {
  int vyska = stred;
  for (int x = 0; x <= w; x++) {
    int p = exp_rand(trr);
    bool zn = nahodne(2);

    /*while (nahodne(trr) > 1) {
      p++;
    }*/

    if (zn) {
      if (vyska+p >= max_y) {
        p = 0;
      } else {
        dolovak(x,vyska,til,p);
        vyska += p;
      }
    } else {
      if (vyska-p < min_y) {
        p = 0;
      } else {
        nahorovak(x,vyska,til,p);
        vyska -= p;
      }
    }
    if (p == 0) {
      stredovak(x,vyska,til);
      continue;
    }
  }
}

void LedovePozadi::udelej_tilemap(int zpos, float speed, int til) {
  bloky = new Tilemap(w,h,false);
  bloky->rychlost = speed;
  bloky->z_pos = zpos;
  vydlazdickuj(til);
  nas_sektor->blbosti += bloky->zblbni();
  delete bloky;
  bloky = NULL;
}

LedovePozadi::LedovePozadi(Sektor* sektor) :
  w(sektor->intact->sirka),
  h(sektor->intact->vyska),
  stred(h/2),
  trr(TemaLevelu::hornatost[sektor->level->tema.vyskopis] * 1.8),
  min_y(12),
  max_y(h-12),
  var_chance(1),
  bloky(NULL),
  nas_sektor(sektor)
{
  udelej_tilemap(-130, 0.5, 148);
  var_chance = 4;
  udelej_tilemap(-170, 0.2, 160);
}
