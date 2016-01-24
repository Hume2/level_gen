#ifndef TEMATICKE_HODNOTY_H
#define TEMATICKE_HODNOTY_H

#include "tema.h"
#include "../level/barva.h"

namespace TemaLevelu {

  struct Osvetleni{
    Barva horni;
    Barva dolni;
    Barva svetlo;
  };

  const Osvetleni denni_svetlo[10] = {
    {{  0,  0,  0,256},{  0,  0,128,256},{ 64, 64, 64,256}}, // půlnoc
    {{  0,  0,  0,256},{  0,  0,128,256},{ 64, 64, 64,256}}, // noc
    {{  0, 80,256,256},{256,200,100,256},{150,128,128,256}}, // rozbřesk
    {{  0, 80,256,256},{256,220,192,256},{256,220,192,256}}, // ráno
    {{  0, 80,256,256},{256,256,256,256},{256,256,256,256}}, // dopoledne
    {{100,200,256,256},{256,256,256,256},{256,256,256,256}}, // poledne
    {{  0, 80,256,256},{256,256,256,256},{256,256,256,256}}, // odpoledne
    {{  0, 80,256,256},{256,220,192,256},{256,220,192,256}}, // předvečer
    {{  0, 80,256,256},{256,200,100,256},{150,128,128,256}}, // večer
    {{  0,  0,  0,256},{  0,  0,128,256},{ 64, 64, 64,256}}  // pozdě večer
  };

  const bool potreba_gradient[6] = {
    true,  //ledovec
    false, //les
    true,  //krystaly
    false, //džungle
    false  //ducholes
  };

  const int hornatost[6] = {
    3, //rovina
    4, //pahorkatina
    6, //vrchovina
    8, //hory
    3, //podzemí
    3  //nebe
  };
}

namespace TemaSektoru {

  const bool potreba_gradient[4] = {
    true,  //venku
    false, //místnost
    true,  //hrad
    false  //bunkr
  };
}

#endif // TEMATICKE_HODNOTY_H
