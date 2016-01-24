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

#include "../level/sektor.h"
#include "../level/tilemap.h"

#include "../tema/dlazdickoraj.h"

void gen_ledove_pozadi(Sektor *s) {
  LedovePozadi lp(s);
}

void gen_lesni_podlaha(Sektor *s) {
  LesniPodlaha lp(s, PoleDlazdic::led);
  lp.generuj();
}

void gen_jeskyne1(Sektor *s) {
  LesniPodlaha lp(s, PoleDlazdic::led);
  lp.min_y = s->intact2->vyska/2 + 3;
  Strop st(s, PoleDlazdic::led);
  st.max_y = s->intact2->vyska/2 - 1;
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
  Zlej z(s);
  z.nasekej_zlejsky();
}

void gen_ryby(Tilemap *tm) {
  Rybator r(tm);
  r.nasekej_ryby();
}
