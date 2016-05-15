#ifndef CILOVNIK_H
#define CILOVNIK_H

#include <string>

#include "hledej_zem.h"

class Sektor;
class Tilemap;

class Cilovnik
{
  public:
    Cilovnik(Sektor* s_);

    void udelej_cil(int x, int y);
    void udelej_start(int x, int y);
    bool ulozovak(int x, int y);
    void nasekej_ulozovaky();

  private:
    Sektor* nas_sektor;
    HledejZem hl;

    void najdi_pozici_dole(int x, int &y);
    void najdi_pozici_nahore(int x, int &y);
    void uprav_pozici(int x, int &y);
    void hledej_trasu(int &x, int &y);
    void udelej_tyc(int x, int y, Tilemap* tm);
    void udelej_end_seq(int x, int y, std::string seq);
    void udelej_iglu(int x, int y);
    void udelej_strom(int x, int y);
    void udelej_budku(int x, int y);
};

#endif // CILOVNIK_H
