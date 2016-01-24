#ifndef OBDELNIK_H
#define OBDELNIK_H

struct Obdelnik {
  int x1,y1,x2,y2;

  Obdelnik(int x1_, int y1_, int x2_, int y2_):
    x1(x1_),
    y1(y1_),
    x2(x2_),
    y2(y2_)
  {}
};

#endif // OBDELNIK_H
