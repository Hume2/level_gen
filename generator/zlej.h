#ifndef ZLEJ_H
#define ZLEJ_H

#include <string>

#include "hledej_zem.h"

#include "../tema/zlejsci.h"

class Objekt;
class Sektor;
class Tilemap;

class Zlej
{
  public:
    Zlej(Sektor* s_, const double *pocty_);
    virtual void nasekej_zlejsky();

  private:
    Sektor* nas_sektor;
    HledejZem hl;
    bool tvrda_zem;
    const double* pocty;

    bool najdi_pozici_dole(int x, int &y);
    bool najdi_pozici_nahore(int x, int &y);
    bool inv_najdi_pozici_dole(int x, int &y);
    bool inv_najdi_pozici_nahore(int x, int &y);
    bool uprav_pozici(int x, int &y);
    bool uprav_horni_pozici(int x, int &y);

    int vymysli_pocet();

    Objekt* umisti(int x, int y, Zlejsci typ);

    void bezny_zlejsek(int x, int y, Zlejsci typ);
    void litac(int x, int y, Zlejsci typ);
    void skokan(int x, int y, Zlejsci typ);
    void rampouch(int x, int y, Zlejsci typ);
};

#endif // ZLEJ_H
