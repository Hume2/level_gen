#ifndef PREKAZITOR_H
#define PREKAZITOR_H

#include "../tema/dlazdicky.h"

class Sektor;

//Překážítor
class Prekazitor
{
  public:
    Prekazitor(Sektor* s_, int* X_, int* Y_, SadaDlazdic til_, int max_x_, int min_y_);

    ///Vyrobí překážku :D
    bool prekazka();

  private:

    enum TypPrekazky {
      DIRA,
      TRAMPOSKA,
      PARKUR,
      PISKACOJUMP,
      TYPY_PREKAZEK
    };

    Sektor* s;
    int* X;
    int* Y;

  public:
    int max_x, min_y;

  private:

    SadaDlazdic til;

    bool dira();
    bool tramposka();
    bool parkur();
    bool piskacojump();

    void nahodny_skok(int &x, int &y, int max_dx = 11);
    void nahorovak(int dh);
    void dolovak(int dh);
    void stredovak(int l);
    void uber_nahorovak();
    void uber_dolovak();
    void ostruvek();
    void piskac();
    void zakaz(int x1, int x2, int y1, int y2);

    bool uprav_smer(bool &sm, int h);

};

#endif // PREKAZITOR_H
