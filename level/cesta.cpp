#include "cesta.h"

Uzel::Uzel(float x_, float y_, float cas_) :
  x(x_),
  y(y_),
  cas(cas_)
{

}

void Uzel::vysav(FILE *f) {
  fprintf(f, "        (node");
  fprintf(f, "\n          (x %f)\n          (y %f)\n          (time %f)", x, y, cas);
  fprintf(f, "\n        )");
}

Cesta::Cesta() :
  uzly(),
  chaos(false)
{
  uzly.clear();
}

void Cesta::vysav(FILE *f) {
  if (uzly.size()) {
    fprintf(f, "      (path\n");
    if (chaos) {
      fprintf(f,"        (mode \"unordered\")");
    } else {
      fprintf(f,"        (mode \"circular\")");
    }
    for (std::vector<Uzel>::iterator i = uzly.begin(); i != uzly.end(); i++) {
      Uzel* u = &(*i);
      u->vysav(f);
    }
    fprintf(f, "\n      )");
  }
}

void Cesta::oddo(int x1, int y1, int x2, int y2, float cas) {
  uzly.push_back(Uzel(x1, y1, cas));
  uzly.push_back(Uzel(x2, y2, cas));
}

void Cesta::bod(int x, int y) {
  uzly.push_back(Uzel(x, y, 1));
}
