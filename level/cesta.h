#ifndef CESTA_H
#define CESTA_H

#include <string>
#include <stdio.h>
#include <vector>

class Uzel
{
  public:
    Uzel(float x_, float y_, float cas_);

    float x, y;
    float cas;

    void vysav(FILE *f);
};

class Cesta
{
  public:
    Cesta();

    std::vector<Uzel> uzly;
    bool chaos;

    void vysav(FILE *f);

    void oddo(int x1, int y1, int x2, int y2, float cas);
    void bod(int x, int y);
};

#endif // CESTA_H
