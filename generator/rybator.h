#ifndef RYBATOR_H
#define RYBATOR_H

class Tilemap;

// Rybátor
class Rybator
{
  public:
    Rybator(Tilemap* tm_);

    void nasekej_ryby();

  private:
    Tilemap* tm;
    int w, h;

    int vymysli_pocet();
};

#endif // RYBATOR_H
