#include "tilemap.h"

#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>

#include <sstream>

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

using namespace std;

Tilemap::Tilemap(int sirka_, int vyska_, bool pevny_) :
  sirka(sirka_),
  vyska(vyska_),
  bloky(),
  z_pos(0),
  rychlost(1),
  pevny(pevny_),
  blbosti(""),
  viditelny(true)
{
  bloky = new BLOK*[sirka];
  for (int x = sirka-1; x >= 0; x--) {
    bloky[x] = new BLOK[vyska];
    for (int y = vyska-1; y >= 0; y--) {
      bloky[x][y] = 0;
    }
  }
}

Tilemap::~Tilemap() {
  for (int i = sirka-1; i >= 0; i--) {
    delete[] bloky[i];
  }
  delete[] bloky;
}

void Tilemap::vysav(FILE *f) {
  if (je_prazdny()) {
    return;
  }

  fprintf(f, "    (tilemap\n      (width %d)\n      (height %d)\n", sirka, vyska);
  fprintf(f, "      (z-pos %d)\n      (speed %f)\n      (speed-y %f)\n", z_pos, rychlost, rychlost);
  fprintf(f, "      (solid #");
  if (pevny) {
    fprintf(f, "t");
  } else {
    fprintf(f, "f");
  }
  fprintf(f, ")\n");
  fputs(blbosti.c_str(), f);
  fprintf(f, "\n      (tiles");
  for (int y = 0; y < vyska; y++) {
    for (int x = 0; x < sirka; x++) {
      fprintf(f, " %d", bloky[x][y]);
    }
  }
  fprintf(f, ")\n    )\n");
}

string Tilemap::zblbni() {
  if (je_prazdny()) {
    return "";
  }

  string result = "    (tilemap\n      (width ";
  result += patch::to_string(sirka);
  result += ")\n      (height ";
  result += patch::to_string(vyska);
  result += ")\n      (z-pos ";
  result += patch::to_string(z_pos);
  result += ")\n      (solid #";
  if (pevny) {
    result += 't';
  } else {
    result += 'f';
  }

  string r = patch::to_string(rychlost);
  result += ")\n      (speed "+r+")\n      (speed-y "+r+")\n";
  result += blbosti + "\n      (tiles";

  for (int y = 0; y < vyska; y++) {
    for (int x = 0; x < sirka; x++) {
      result += " " + patch::to_string(bloky[x][y]);
    }
  }

  result += "))\n";

  return result;
}

void Tilemap::poloz_blok(BLOK blok, int x, int y) {
  if (x >= 0 && y >= 0 && x < sirka && y < vyska) {
    bloky[x][y] = blok;
  }
}

void Tilemap::obdelnik(BLOK blok, int x1, int x2, int y1, int y2) {
  if (x1 < 0) {
    x1 = 0;
  }
  if (y1 < 0) {
    y1 = 0;
  }
  if (x2 >= sirka) {
    x2 = sirka - 1;
  }
  if (y2 >= vyska) {
    y2 = vyska - 1;
  }

  for (int y = y1; y <= y2; y++) {
    for (int x = x1; x <= x2; x++) {
      bloky[x][y] = blok;
    }
  }
}

void Tilemap::ram_obdelnik(BLOK *blok, int x1, int x2, int y1, int y2) {
  poloz_blok(blok[0],x1,y1);
  obdelnik(blok[1],x1+1,x2-1,y1,y1);          //  +--+--+--+
  poloz_blok(blok[2],x2,y1);                  //  | 0| 1| 2|
  obdelnik(blok[3],x1,x1,y1+1,y2-1);          //  +--+--+--+
  obdelnik(blok[4],x1+1,x2-1,y1+1,y2-1);      //  | 3| 4| 5|
  obdelnik(blok[5],x2,x2,y1+1,y2-1);          //  +--+--+--+
  poloz_blok(blok[6],x1,y2);                  //  | 6| 7| 8|
  obdelnik(blok[7],x1+1,x2-1,y2,y2);          //  +--+--+--+
  poloz_blok(blok[8],x2,y2);
  //std::cout << "x1:" << x1 << " y1:" << y1 << " x2:" << x2 << " y2:" << y2 << std::endl;
}

bool Tilemap::je_prazdny() {
  if (!viditelny) {
    return true;
  }
  for (int y = 0; y < vyska; y++) {
    for (int x = 0; x < sirka; x++) {
      if (bloky[x][y]) {
        return false;
      }
    }
  }
  return true;
}

bool Tilemap::lze_sloucit(Tilemap *t) {
  if (vyska != t->vyska || sirka != t->sirka) {
    return false;
  }
  if (rychlost != t->rychlost) {
    return false;
  }

  for (int y = 0; y < vyska; y++) {
    for (int x = 0; x < sirka; x++) {
      if (bloky[x][y] && t->bloky[x][y]) {
        return false;
      }
    }
  }
  return true;
}

void Tilemap::sluc_s(Tilemap *t) {
  for (int y = 0; y < vyska; y++) {
    for (int x = 0; x < sirka; x++) {
      if (bloky[x][y] == 0) {
        bloky[x][y] = t->bloky[x][y];
      }
    }
  }
}

namespace Tilemap_bl{

const int pocet = 54;
const BLOK bloky[pocet] = {0, 1000, 1001, 1002, 1061, 1066, 1046, 1052, 1063, 1060, 1045, 1051,
      7, 8, 9, 16, 17, 18, 1827, 1832, 1838, 1844, 1829, 1826, 1837, 1843, 2921, 2922, 2909, 2910,
      3153, 3150, 3141, 3142, 2917, 2918, 2913, 2914, 3149, 3152, 3139, 3140, 2925, 2928, 2933, //45
      2934, 2938, 2939, 2930, 2931, 2935, 2936, 2941, 2942};

}

bool Tilemap::je_blok_pevny(BLOK b) {
  for (int i = 0; i < Tilemap_bl::pocet; i++) {
    if (b == Tilemap_bl::bloky[i]) {
      return false;
    }
  }
  return true;
}

bool Tilemap::je_blok_pevny(int x, int y) {
  if (x < 0 || y < 0 || y >= vyska || x >= sirka) {
    return false;
  } else {
    return je_blok_pevny(bloky[x][y]);
  }
}
