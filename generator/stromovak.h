#ifndef STROMOVAK_H
#define STROMOVAK_H

#include "hledej_zem.h"

class Sektor;

class Stromovak
{
  public:
    Stromovak(Sektor* s_);
    Sektor* s;
    HledejZem hz;

    void nasekej_stromy();

  private:
    void strom(int x, int y);
    void strom1(int x, int y);
    void strom2(int x, int y);
    void strom3(int x, int y);
    void strom4(int x, int y);

    void prvkovnik(BLOK f, int x, int y, int w, int h);

    const int kmen = 4;
    const int listi = 2;
};

#endif // STROMOVAK_H
