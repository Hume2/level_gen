#ifndef STROP_H
#define STROP_H

#include <string>
#include <stdio.h>
#include <vector>

class PokladacSvahu;
class Sektor;
class Tilemap;

#include "../tema/dlazdicky.h"

class Strop {
  public:
    Strop(Sektor* sektor, const SadaDlazdic til_);
    void generuj();

    int w, h, stred, x;
    int trr;
    int min_y, max_y, min_x, max_x;

  private:
    Sektor* nas_sektor;

    /*enum Stoupani{
      minus_blbec = 0,
      minus200 = 1,
      minus100 = 2,
      minus50 = 3,
      plus0 = 4,
      plus50 = 5,
      plus100 = 6,
      plus200 = 7,
      plus_blbec = 8
    };*/

    enum Akce{
      Astredovak,
      Anahorovak,
      Adolovak,
      Astoupej,
      Aklesej
    };

    int stoupani;
    bool bylo_stoupani;
    bool byl_nahorovak;
    bool byl_dolovak;

    SadaDlazdic til;

    void stredovak(int x1, int x2);
    void stredovak();
    void nahorovak();
    void svahovak(int cko);
    void dolovak();
    void sloupek();
    void nahoru50();
    void nahoru100();
    void nahoru200();
    void dolu50();
    void dolu100();
    void dolu200();

    PokladacSvahu* ps;
};

#endif // STROP_H
