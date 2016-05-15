#include "../level/sektor.h"
#include "../level/tilemap.h"

#include "stromovak.h"

#include "random.h"

Stromovak::Stromovak(Sektor* s_):
  s(s_),
  hz(s_, HledejZem::VOLNY)
{
}

void Stromovak::strom(int x, int y) {
  hz.hledej_zem(x, y);
  s->bkgrd->poloz_blok(360, x, y);
}

void Stromovak::nasekej_stromy() {
  for (int i = s->intact2->sirka/8; i; i--) {
    strom(nahodne(s->intact2->sirka), 0);
  }
}
