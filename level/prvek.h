#ifndef PRVEK_H
#define PRVEK_H

#include <stdio.h>
#include <vector>

#include "../smer.h"
#include "tilemap.h"

class Prvek
{
  public:
    Prvek();

    int vyska,sirka;
    BLOK** bloky;

    SmerS pevne_smery;
    int polopevne_smery[4]; // Jak daleko je poslední pevný bod od vrcholu.
    /*   * -> -> *
     *   V       V
     *   V       V
     *   * -> -> *
     */

    std::vector<Prvek*> doporucene[4];
};

#endif // PRVEK_H
