#include "objekt.h"

using namespace std;

Objekt::Objekt(string typ_, int x_, int y_) :
  typ(typ_),
  jmeno(""),
  x(x_),
  y(y_),
  barva(256,256,256,256),
  ma_barvu(false),
  blbosti(""),
  cesta()
{
}

void Objekt::vysav(FILE* f) {
  fprintf(f, "    (");
  fputs(typ.c_str(), f);
  if (!cesta.uzly.size()) {
    fprintf(f, "\n      (x %d)\n      (y %d)\n", x, y);
  }
  fputs(blbosti.c_str(), f);
  if (jmeno.size()) {
    fprintf(f, "\n      (name \"");
    fputs(jmeno.c_str(), f);
    fprintf(f, "\")");
  }
  if (ma_barvu) {
    fprintf(f, "\n      (color ");
    barva.vysav(f);
    fprintf(f, ")");
  }
  cesta.vysav(f);
  fprintf(f, "\n    )");
}

void Objekt::posun(int x_, int y_) {
  x += x_;
  y += y_;
}
