#ifndef TILEMAP_H
#define TILEMAP_H

#include <string>
#include <stdio.h>
#include <vector>

#include "../tema/dlazdicky.h"

class Cesta;

class Tilemap
{
  public:
    Tilemap(int sirka_, int vyska_, bool pevny_);
    ~Tilemap();

    int vyska,sirka;
    BLOK** bloky;
    int z_pos;
    float rychlost;
    bool pevny;
    std::string blbosti;
    std::string jmeno;
    bool viditelny;
    Cesta* cesta;

    void vysav(FILE* f);
    std::string zblbni();

    void pojmenuj(std::string zaklad, int cislo);

    // Bomben fest und idioten sicher :DDDDD
    void poloz_blok(BLOK blok, int x, int y);
    void obdelnik(BLOK blok, int x1, int x2, int y1, int y2);
    void ram_obdelnik(BLOK* blok, int x1, int x2, int y1, int y2);

    // Tato funkce si neověřuje, zda-li jdou sloučit.
    void sluc_s(Tilemap* t);

    bool je_prazdny();
    bool lze_sloucit(Tilemap* t);
    bool je_blok_pevny(BLOK b);
    bool je_blok_pevny(int x, int y);
};

#endif // TILEMAP_H
