#ifndef OBJEKT_H
#define OBJEKT_H

#include <string>
#include <stdio.h>

#include "barva.h"
#include "cesta.h"

class Objekt
{
  public:
    Objekt(std::string typ_, int x_, int y_);

    std::string typ;
    std::string jmeno;
    int x,y;
    Barva barva;
    bool ma_barvu;
    std::string blbosti;
    Cesta cesta;

    virtual void vysav(FILE* f);
    virtual void posun(int x_, int y_);
};

#endif // OBJEKT_H
