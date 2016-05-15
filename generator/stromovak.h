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
};

#endif // STROMOVAK_H
