#ifndef SEKTOR_H
#define SEKTOR_H

#include <string>
#include <stdio.h>
#include <vector>

#include "barva.h"
#include "../tema/tema.h"
#include "../obdelnik.h"

class Level;
class Objekt;
class Tilemap;

class Sektor
{
  public:
    Sektor(Level *l, std::string jmeno_);
    ~Sektor();

    Level* level;
    TemaSektoru::Tema tema;

    std::string jmeno;
    std::string hudba;
    Barva osvetleni;
    std::string blbosti;
    Tilemap* bkgrd;
    Tilemap* intact;
    Tilemap* intact2;
    Tilemap* frgrd;

    std::vector<Objekt*> objekty;
    std::vector<Tilemap*> tilemapy;
    std::vector<Obdelnik> obdelniky;

    int tajnych_chodeb;

    bool je_blok_volny(int x, int y);
    bool je_obdelnik_volny(int x1, int x2, int y1, int y2);
    bool je_obdelnik_prazny(int x1, int x2, int y1, int y2);
    bool je_povoleno(int x, int y);

    void vysav(FILE *f);
    void posun_objekty(int x, int y);
};

#endif // SEKTOR_H
