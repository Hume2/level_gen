#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <math.h>

#include "otaznitor.h"

#include "random.h"
#include "tocitko.h"

#include "../level/level.h"
#include "../level/objekt.h"
#include "../level/sektor.h"
#include "../level/tilemap.h"

#include "../tema/tema.h"

Otaznitor::Otaznitor(Sektor *s):
  nas_sektor(s),
  w(s->intact->sirka),
  h(s->intact->vyska)
{
}

int Otaznitor::vymysli_pocet() {
  int pocet;
  if (nas_sektor->level->tema.hrani == TemaLevelu::T1D && nas_sektor->tema != TemaSektoru::Thrad) {
    pocet = w / 10;
  } else {
    pocet = (w / 10) * (h / 20);
  }
  return pocet;
}

bool Otaznitor::uprav_pozici_p1(int x, int &y) {
  int y1 = y, y2 = y;
  int citac1 = 6, citac2 = 7;
  bool break1 = false, break2 = false;
  while (! (break1 && break2)) {
    if (!break1) {
      if (y1 >= h) {
        break1 = true;
      } else {
        if (nas_sektor->je_blok_volny(x,y1)) {
        citac1 --;
        } else {
          citac1 = 6;
        }
        if (citac1 == 0) {
          y = y1 - 3;
          return true;
        }
        y1++;
      }
    }
    if (!break2) {
      if (y2 < 0) {
        break2 = true;
      } else {
        if (nas_sektor->je_blok_volny(x,y2)) {
          citac2 --;
        } else {
          citac2 = 7;
        }
        if (citac2 == 0) {
          y = y2 + 3;
          return true;
        }
        y2--;
      }
    }
  }
  return false;
}

bool Otaznitor::uprav_pozici_p2(int x, int &y) {
  if ( uprav_pozici_p1(x, y) ) {
    while (y < h) {
      if (!nas_sektor->je_blok_volny(x, y)) {
        break;
      }
      y++;
    }
    if (y >= h) {
      return false;
    }
      y -= 4;
    return nas_sektor->je_povoleno(x,y);
  } else {
    return false;
  }
}

bool Otaznitor::uprav_pozici(int &x, int &y) {
  if ( uprav_pozici_p2(x, y) ) {
    if ( !nas_sektor->je_blok_volny(x-1, y) ) {
      if (nas_sektor->je_blok_volny(x+1, y) &&
          nas_sektor->je_blok_volny(x+2, y)) {
        x++;
        return true;
      } else {
        return false;
      }
    } else {
      return true;
    }
  } else {
    return false;
  }
}

void Otaznitor::nasekej_otazniky() {
  int pocet = vymysli_pocet();
  int i;

  for (i = pocet; i; i--) {
    int x = nahodne(w), y = nahodne(h);
    if (uprav_pozici(x, y)) {
      rada_otazniku(x, y);
    }
  }
}

void Otaznitor::nasekej_mince() {
  int pocet = vymysli_pocet();
  int i;

  for (i = pocet; i; i--) {
    int x = nahodne(w), y = nahodne(h);
    if (uprav_pozici_p2(x, y)) {
      y+= nahodne(3);
      if (nahodne(50)) {
        nas_sektor->intact->poloz_blok(44, x, y);
      } else {
        int n = std::max(signed_xp_rand(5) + 5, 2);
        int m = nahodne(n - 1) + 1;
        int r = std::max(signed_xp_rand(3) + 5, 1);
        double f = nahodne_d(6);
        double h = cos(M_PI / n);
        double t = nahodne_d(2) + 1;
        t *= sin(M_PI / n * m) * r/4;
        tocitko(nas_sektor, "coin", "", x, y-h, n, m, r, t, f, !nahodne(n));
      }
    }
  }
}

bool Otaznitor::zkontroluj_3(int x, int y) {
  bool nahore1 = nas_sektor->je_blok_volny(x, y-1);
  bool nahore2 = nas_sektor->je_blok_volny(x, y-2);
  bool uprostred = nas_sektor->je_blok_volny(x, y);
  bool dole1 = nas_sektor->je_blok_volny(x, y+1);
  bool dole2 = nas_sektor->je_blok_volny(x, y+2);
  return nahore1 && nahore2 && dole1 && dole2 && uprostred;
}

bool Otaznitor::zkontroluj_pozici(int x, int y) {
  bool nahore1 = nas_sektor->je_blok_volny(x, y-1);
  bool nahore2 = nas_sektor->je_blok_volny(x, y-2);
  bool nahore3 = nas_sektor->je_blok_volny(x, y-3);

  bool dole1 = nas_sektor->je_blok_volny(x, y+1);
  bool dole2 = nas_sektor->je_blok_volny(x, y+2);
  bool dole3 = nas_sektor->je_blok_volny(x, y+3);
  bool dole4 = nas_sektor->je_blok_volny(x, y+4);

  bool blokove_podminky = nahore1 && nahore2 && nahore3 && dole1 && dole2 && dole3 && !dole4 &&
      zkontroluj_pravy_kraj(x, y);

  return blokove_podminky && nas_sektor->je_povoleno(x,y);
}

bool Otaznitor::zkontroluj_levy_kraj(int x, int y) {
  return zkontroluj_3(x-1, y);
}

bool Otaznitor::zkontroluj_pravy_kraj(int x, int y) {
  return zkontroluj_3(x+1, y);
}

const BLOK otazniky[7] = {83, 102, 103, 128, 140, 2947, 2948};
const double o_sance[7] = {100, 7, 0.2, 0.2, 7, 1, 1};

void Otaznitor::rada_otazniku(int x, int y) {
  if (!zkontroluj_levy_kraj(x, y)) {
    return;
  }

  bool bedny = nahodne(2);
  bool mam_bednu = nahodne(2);

  while (zkontroluj_pozici(x,y) && nahodne(5)) {
    if (mam_bednu) {
      if (nahodne(3) > 1) {
        if (nas_sektor->level->tema.biom == TemaLevelu::Tledovec) {
          nas_sektor->intact2->poloz_blok(78, x, y);
        } else if (nas_sektor->level->tema.biom == TemaLevelu::Tducholes) {
          nas_sektor->intact2->poloz_blok(3159, x, y);
        } else {
          nas_sektor->intact2->poloz_blok(77, x, y);
        }
      } else {
        nas_sektor->intact2->poloz_blok(77, x, y);
      }
    } else {
      BLOK ot = nahodne_vyber(o_sance, 7);
      if (ot == 5 && nas_sektor->level->tema.vyskopis == TemaLevelu::Tpodzemi) {
        ot = 6;
      }
      nas_sektor->intact2->poloz_blok(otazniky[ot], x, y);
    }
    x++;
    if (bedny) {
      mam_bednu = !mam_bednu;
    }
  }
}
