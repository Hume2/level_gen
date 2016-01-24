#ifndef POKLADAC_SVAHU_H
#define POKLADAC_SVAHU_H

class Tilemap;
struct SadaDlazdic;

class PokladacSvahu
{
  public:
    PokladacSvahu(Tilemap* tm_, SadaDlazdic* til_, bool curak_);

    void nahoru50(int x, int y);
    void nahoru100(int x, int y);
    void nahoru200(int x, int y);

    void dolu50(int x, int y);
    void dolu100(int x, int y);
    void dolu200(int x, int y);


    void inv_nahoru50(int x, int y);
    void inv_nahoru100(int x, int y);
    void inv_nahoru200(int x, int y);

    void inv_dolu50(int x, int y);
    void inv_dolu100(int x, int y);
    void inv_dolu200(int x, int y);

    void nahoru0_50(int x, int y);
    void nahoru50_0(int x, int y);
    void nahoru50_100(int x, int y);
    void nahoru100_50(int x, int y);
    void dolu0_50(int x, int y);
    void dolu50_0(int x, int y);
    void dolu50_100(int x, int y);
    void dolu100_50(int x, int y);

  private:
    Tilemap* tm;
    SadaDlazdic* til;
    bool curak;
};

#endif // POKLADAC_SVAHU_H
