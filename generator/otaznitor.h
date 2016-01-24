#ifndef OTAZNITOR_H
#define OTAZNITOR_H

class Sektor;

// Otaznítor
class Otaznitor
{
  public:
    Otaznitor(Sektor* s);
    void nasekej_otazniky();
    void nasekej_mince();

  private:
    Sektor* nas_sektor;
    int w,h;

    void rada_otazniku(int x, int y);

    int vymysli_pocet();
    bool uprav_pozici_p1(int x, int &y);
    bool uprav_pozici_p2(int x, int &y);
    bool uprav_pozici(int &x, int &y);
    bool zkontroluj_3(int x, int y);
    bool zkontroluj_levy_kraj(int x, int y);
    bool zkontroluj_pravy_kraj(int x, int y);
    bool zkontroluj_pozici(int x, int y);

};

#endif // OTAZNITOR_H
