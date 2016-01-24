#include <stdio.h>
#include <string>
#include <math.h>

#include "tocitko.h"

#include "../level/objekt.h"
#include "../level/sektor.h"

void tocitko(Sektor *s, std::string jmeno, std::string blbosti, float x, float y, int n, int m, float r, float cas, float f, bool chaos) {
  int X = x*32, Y = y*32, R = r*32;
  double uhel1 = 2*M_PI / n;
  double uhel2 = uhel1 * m;
  double u1 = f, u2;
  double x_, y_;
  for (int i = n; i; i--, u1 += uhel1) {
    Objekt *obj = new Objekt(jmeno, X, Y);
    obj->blbosti = blbosti + "(running #t)";
    obj->cesta.chaos = chaos;
    u2 = u1;
    for (int j = n; j; j--, u2 += uhel2) {
      x_ = cos(u2) * R;
      y_ = sin(u2) * R;
      obj->cesta.uzly.push_back(Uzel(X + x_, Y + y_, cas));
    }
    s->objekty.push_back(obj);
  }
}
