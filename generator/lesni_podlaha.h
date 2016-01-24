#ifndef LESNI_PODLAHA_H
#define LESNI_PODLAHA_H

#include <string>
#include <stdio.h>
#include <vector>

class PokladacSvahu;
class Prekazitor;
class Sektor;
class Tilemap;

#include "../tema/dlazdicky.h"

class LesniPodlaha {
  public:
    LesniPodlaha(Sektor* sektor, const SadaDlazdic til_);
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
      Aklesej,
      Aprekazej
    };

    int stoupani;
    bool bylo_stoupani;
    bool byl_nahorovak;
    bool byl_dolovak;
    bool byla_prekazka;

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
    void nahoru0_50();
    void nahoru50_0();
    void nahoru50_100();
    void nahoru100_50();
    void dolu0_50();
    void dolu50_0();
    void dolu50_100();
    void dolu100_50();

    PokladacSvahu* ps;
    Prekazitor *pr;

};

#endif // LESNI_PODLAHA_H
