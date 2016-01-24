#ifndef BARVA_H
#define BARVA_H

#include <stdio.h>
#include <string>

class Barva
{
  public:
    Barva();
    Barva(float c, float z, float m, float a);

    float cervena, zelena, modra, alfa;

    void vysav(FILE *f);
    std::string zblbni();
};

#endif // BARVA_H
