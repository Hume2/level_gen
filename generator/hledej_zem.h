#ifndef HLEDEJ_ZEM_H
#define HLEDEJ_ZEM_H

class Sektor;

class HledejZem {
  public:
    enum Zpusob{VOLNY, PRAZDNY};

    HledejZem(Sektor* s_, Zpusob zp_);
    Sektor* s;
    Zpusob zp;

    bool hledej_zem(int x, int &y, int sirka=1);
    bool hledej_strop(int x, int &y, int sirka=1);

  private:
    bool je_volno(int x1, int x2, int y1, int y2);

    bool najdi_pozici_dole(int x, int &y, int sirka);
    bool najdi_pozici_nahore(int x, int &y, int sirka);
    bool inv_najdi_pozici_dole(int x, int &y, int sirka);
    bool inv_najdi_pozici_nahore(int x, int &y, int sirka);
};

#endif // HLEDEJ_ZEM_H
