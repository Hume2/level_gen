#ifndef LEDOVE_POZADI_H
#define LEDOVE_POZADI_H

#include <string>
#include <stdio.h>
#include <vector>

class Sektor;
class Tilemap;

class LedovePozadi {
  public:
    LedovePozadi(Sektor* sektor);

  private:
    int w, h, stred;
    float trr;
    int min_y, max_y;
    int var_chance;
    Tilemap* bloky;
    Sektor* nas_sektor;

    void udelej_tilemap(int zpos, float speed, int til);
    void vydlazdickuj(int til);
    void sloupek(int x, int til, int min_y, int max_y);
    void var_sloupek(int x, int til, int min_y, int max_y);
    void nahorovak(int x, int start, int til, int plus);
    void dolovak(int x, int start, int til, int minus);
    void stredovak(int x, int start, int til);
};

#endif // LEDOVE_POZADI_H
