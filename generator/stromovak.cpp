#include "../level/sektor.h"
#include "../level/tilemap.h"

#include "stromovak.h"

#include "random.h"

Stromovak::Stromovak(Sektor* s_):
  s(s_),
  hz(s_, HledejZem::VOLNY)
{
}

void Stromovak::prvkovnik(BLOK f, int x, int y, int w, int h) {
  for (int Y = y; Y < y + h; Y++) {
    for (int X = x; X < x + w; X++) {
      s->bkgrd->poloz_blok(f, X, Y);
      f++;
    }
  }
}

void Stromovak::strom(int x, int y) {
  switch (nahodne(4)) {
    case 0:
      strom1(x, y);
      break;
    case 1:
      strom2(x, y);
      break;
    case 2:
      strom3(x, y);
      break;
    case 3:
      strom4(x, y);
      break;
    default:
      break;
  }
}

void Stromovak::strom1(int x, int y) {
  //hz.hledej_zem(x, y, 2);
  if (!s->bkgrd->je_obdelnik_prazdny(x, x+1, 0, y)) return;
  y--;
  while ((nahodne(kmen) > 0 || !s->je_blok_volny(x, y)) && y > -4) {
    prvkovnik(1303, x, y, 2, 2);
    y -= 2;
  }
  prvkovnik(1299, x, y, 2, 2);
  while (nahodne(listi) > 0 && y > -4) {
    y -= 2;
    prvkovnik(1295, x, y, 2, 2);
  }
  prvkovnik(1287, x, y-4, 2, 4);
}

void Stromovak::strom2(int x, int y) {
  //hz.hledej_zem(x, y, 2);
  if (!s->bkgrd->je_obdelnik_prazdny(x-1, x+2, 0, y)) return;
  y--;
  while ((nahodne(kmen) > 0 || !s->je_blok_volny(x, y)) && y > -4) {
    s->bkgrd->poloz_blok(1272, x, y);
    s->bkgrd->poloz_blok(1273, x+1, y);
    s->bkgrd->poloz_blok(1276, x, y+1);
    s->bkgrd->poloz_blok(1277, x+1, y+1);
    y -= 2;
  }
  x--;
  prvkovnik(1263, x, y, 4, 2);
  while (nahodne(listi) > 0 && y > -4) {
    y -= 2;
    prvkovnik(1255, x, y, 4, 2);
  }
  prvkovnik(1239, x, y-4, 4, 4);
}

void Stromovak::strom3(int x, int y) {
  //hz.hledej_zem(x, y, 4);
  if (!s->bkgrd->je_obdelnik_prazdny(x-2, x+3, 0, y)) return;
  y--;
  while ((nahodne(kmen) > 0 || !s->je_blok_volny(x, y)) && y > -4) {
    s->bkgrd->poloz_blok(1217, x, y);
    s->bkgrd->poloz_blok(1218, x+1, y);
    s->bkgrd->poloz_blok(1223, x, y+1);
    s->bkgrd->poloz_blok(1224, x+1, y+1);
    y -= 2;
  }
  x -= 2;
  prvkovnik(1203, x, y, 6, 2);
  while (nahodne(listi) > 0 && y > -4) {
    y -= 2;
    prvkovnik(1191, x, y, 6, 2);
  }
  prvkovnik(1167, x, y-4, 6, 4);
}

void Stromovak::strom4(int x, int y) {
  //hz.hledej_zem(x, y, 4);
  if (!s->bkgrd->je_obdelnik_prazdny(x-2, x+5, 0, y)) return;
  y--;
  while ((nahodne(kmen) > 0 || !s->je_blok_volny(x, y)) && y > -4) {
    prvkovnik(1137, x, y, 4, 1);
    prvkovnik(1145, x, y+1, 4, 1);
    y -= 2;
  }
  x -= 2;
  prvkovnik(1119, x, y, 8, 2);
  while (nahodne(listi) > 0 && y > -4) {
    y -= 2;
    prvkovnik(1103, x, y, 8, 2);
  }
  prvkovnik(1071, x, y-4, 8, 4);
}

void Stromovak::nasekej_stromy() {
  for (int i = s->intact2->sirka/4; i; i--) {
    strom(nahodne(s->intact2->sirka), s->intact2->vyska-1);
  }
}
