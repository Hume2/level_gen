#include <math.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <ctime>

#include "generator.h"

#include "cilovnik.h"
#include "ledove_pozadi.h"
#include "lesni_podlaha.h"
#include "otaznitor.h"
#include "rybator.h"
#include "strop.h"
#include "zlej.h"

#include "../level/level.h"
#include "../level/sektor.h"
#include "../level/tilemap.h"

#include "../tema/dlazdickoraj.h"
#include "../tema/zlejsci.h"

SadaDlazdic spravna_sada(Sektor *s) {
  switch (s->level->tema.biom) {
    case TemaLevelu::Tledovec:
    case TemaLevelu::Tkrystaly:
      return PoleDlazdic::led;
    case TemaLevelu::Tles:
    case TemaLevelu::Tdzungle:
      return PoleDlazdic::les;
    case TemaLevelu::Tducholes:
      return PoleDlazdic::ducholes;
  }
}

const double* spravni_zlejsci(Sektor *s) {
  switch (s->level->tema.biom) {
    case TemaLevelu::Tledovec:
    case TemaLevelu::Tkrystaly:
      return ledovi_zlejsci;
    case TemaLevelu::Tles:
    case TemaLevelu::Tdzungle:
      return lesni_zlejsci;
    case TemaLevelu::Tducholes:
      return ducholesni_zlejsci;
  }
}

void gen_ledove_pozadi(Sektor *s) {
  LedovePozadi lp(s);
}

void gen_lesni_podlaha(Sektor *s) {
  LesniPodlaha lp(s, spravna_sada(s));
  lp.generuj();
}

void gen_jeskyne1(Sektor *s) {
  LesniPodlaha lp(s, spravna_sada(s));
  lp.set_min_y(s->intact2->vyska/2 + 3);
  Strop st(s, PoleDlazdic::led);
  st.max_y = s->intact2->vyska/2 - 2;
  lp.generuj();
  st.generuj();
}

void gen_start(Sektor *s, int x, int y) {
  Cilovnik c(s);
  c.udelej_start(x, y);
}

void gen_cil(Sektor *s, int x, int y) {
  Cilovnik c(s);
  c.udelej_cil(x, y);
}

void gen_ulozovaky(Sektor *s) {
  Cilovnik c(s);
  c.nasekej_ulozovaky();
}

void gen_otazniky(Sektor *s) {
  Otaznitor o(s);
  o.nasekej_otazniky();
  o.nasekej_mince();
}

void gen_zlejsky(Sektor *s) {
  Zlej z(s, spravni_zlejsci(s));
  z.nasekej_zlejsky();
}

void gen_ryby(Tilemap *tm) {
  Rybator r(tm);
  r.nasekej_ryby();
}
