#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <stdio.h>
#include <vector>

#include "../tema/tema.h"

class Sektor;

class Level
{
  public:
    Level();
    ~Level();

    TemaLevelu::Tema tema;

    std::string jmeno;
    std::string autor;

    std::vector<Sektor*> sektory;

    int vyska,sirka;

    int poradi;

    void vysav(FILE* f);

};

#endif // LEVEL_H
