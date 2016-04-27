#include "pozadi.h"

#include <stdio.h>
#include <iostream>
#include <cstdlib>

#include "random.h"
#include "generator.h"

#include "../level/barva.h"
#include "../level/level.h"
#include "../level/sektor.h"
#include "../level/tilemap.h"

#include "../tema/tema.h"
#include "../tema/tematicke_hodnoty.h"

#include <sstream>

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

enum druhy_castic {
  DCsnih,
  DCdest,
  DCmraky,
  DCduchove,
  DCcastice
};

const std::string pocasicka[DCcastice] = {"snow", "rain", "clouds", "ghosts"};

void pocasi(Sektor* s, druhy_castic druh, int zpos) {
  s->blbosti += "(particles-" + pocasicka[druh] + " (z-pos " + patch::to_string(zpos) + "))\n";
}

void snih(Sektor* s) {
  pocasi(s, DCsnih, -120);
  pocasi(s, DCsnih,  120);
}

void dest(Sektor* s) {
  pocasi(s, DCdest, -120);
  pocasi(s, DCdest,  120);
}

void dest_se_snehem(Sektor* s) {
  pocasi(s, DCsnih, -120);
  pocasi(s, DCdest,  120);
}

void duchovno(Sektor* s) {
  pocasi(s, DCduchove, -120);
  pocasi(s, DCduchove,  120);
}

void mraky(Sektor* s) {
  pocasi(s, DCmraky, -120);
}

void mlha(Sektor* s) {
  s->blbosti += "    (gradient\n";
  s->blbosti += "      (top_color 1 1 1 0)\n";
  s->blbosti += "      (bottom_color 1 1 1 1)\n";
  s->blbosti += "      (direction \"vertical_sector\")\n";
  s->blbosti += "      (layer 200))\n";
}

void bourkovnik(Sektor* s) {
  double interval = nahodne_d(20) + 3;
  s->blbosti += "(thunderstorm (interval " + patch::to_string(interval) + "))\n";
}

void bourka(Sektor* s) {
  bourkovnik(s);
  bourkovnik(s);
  dest(s);
}

void pozadi(Sektor *s, std::string horni, std::string stredni, std::string dolni, int z_pos, double rychlost) {
  s->blbosti += "    (background (image-top \"images/background/" + horni + "\")\n";
  s->blbosti += "      (image \"images/background/" + stredni + "\")\n";
  s->blbosti += "      (image-bottom \"images/background/" + dolni + "\")\n";
  s->blbosti += "      (speed " + patch::to_string(rychlost) + ")\n";
  s->blbosti += "      (z-pos " + patch::to_string(z_pos) + "))\n";
}

void pozadi(Sektor *s, std::string horni, std::string stredni, std::string dolni) {
  pozadi(s, horni, stredni, dolni, -200, 0.5);
}

void gradient(Sektor *s, Barva horni, Barva dolni) {
  s->blbosti += "    (gradient\n";
  s->blbosti += "      (top_color" + horni.zblbni() + ")\n";
  s->blbosti += "      (bottom_color" + dolni.zblbni() + "))\n";
}

const std::string ledove_hudby[3] = {"voc-daytime.ogg","voc-daytime2.ogg","chipdisko.ogg"};
const std::string lesni_hudby[2] = {"forest.ogg","forest2.ogg"};
const std::string podzemni_hudby[3] = {"cave.ogg","voc-dark.ogg","clavelian_march.ogg"};
const std::string duchove_hudby[4] = {"greatgigantic.ogg","wisphunt.ogg","ghostforest.ogg","ghostforest2.ogg"};

void vymysli_hudbu(Sektor *s) {
  int r;

  switch (s->tema) {
    case TemaSektoru::Thrad:
      switch (s->level->tema.biom) {
        case TemaLevelu::Tles:
        case TemaLevelu::Tducholes:
        case TemaLevelu::Tdzungle:
          s->hudba = "darkforestkeep.ogg";
          break;
        case TemaLevelu::Tledovec:
        case TemaLevelu::Tkrystaly:
        default:
          s->hudba = "fortress.ogg";
          break;
      }
      return;
    case TemaSektoru::Tbunkr:
    case TemaSektoru::Tmistnost:
      s->hudba = "bonuscave.ogg";
      return;
    default:
      break;
  }

  switch (s->level->tema.vyskopis) {
    case TemaLevelu::Tnebe:
      s->hudba = "airship_remix.ogg";
      return;
    case TemaLevelu::Tpodzemi:
      r = nahodne(3);
      s->hudba = podzemni_hudby[r];
      return;
    default:
      break;
  }

  switch (s->level->tema.biom) {
    case TemaLevelu::Tledovec:
    case TemaLevelu::Tkrystaly:
      r = nahodne(3);
      s->hudba = ledove_hudby[r];
      return;
    case TemaLevelu::Tles:
      r = nahodne(2);
      s->hudba = lesni_hudby[r];
      return;
    case TemaLevelu::Tducholes:
      r = nahodne(4);
      s->hudba = duchove_hudby[r];
      return;
    case TemaLevelu::Tdzungle:
      s->hudba = "forest3.ogg";
      return;
    default:
      break;
  }
}

void vymysli_pozadi(Sektor *s) {
  if (s->level->tema.vyskopis == TemaLevelu::Tpodzemi) {
    switch (s->level->tema.biom) {
      case TemaLevelu::Tledovec:
        pozadi(s, "cave2.jpg", "cave2.jpg", "cave2.jpg");
        break;
      case TemaLevelu::Tles:
      case TemaLevelu::Tducholes:
      case TemaLevelu::Tdzungle:
        s->blbosti += "    (background (image-top \"images/tiles/forest/underground/background1.png\")\n";
        s->blbosti += "      (image \"images/tiles/forest/underground/background1.png\")\n";
        s->blbosti += "      (image-bottom \"images/tiles/forest/underground/background1.png\")\n";
        s->blbosti += "      (speed 0.5)\n";
        s->blbosti += "      (z-pos -200))\n";
        break;
      default:
        break;
    }
  } else {
    if (TemaLevelu::potreba_gradient[s->level->tema.biom] &&
        !(s->level->tema.biom == TemaLevelu::Tledovec && s->level->tema.vyskopis == TemaLevelu::Thory)) {
      gradient(s, TemaLevelu::denni_svetlo[s->level->tema.denni_doba].horni,
          TemaLevelu::denni_svetlo[s->level->tema.denni_doba].dolni);
    }
    switch (s->level->tema.biom) {
      case TemaLevelu::Tledovec:
        if (s->level->tema.vyskopis != TemaLevelu::Tnebe) {
          if (s->level->tema.vyskopis == TemaLevelu::Thory) {
            pozadi(s, "bluemountain-top.png", "bluemountain-middle.png", "bluemountain-bottom.png");
          } else {
            gen_ledove_pozadi(s);
          }
        }
        break;
      case TemaLevelu::Tles:
        if (s->level->tema.vyskopis == TemaLevelu::Tnebe) {
          pozadi(s, "BlueRock_Forest/blue-top.jpg", "BlueRock_Forest/blue-top.jpg",
                 "BlueRock_Forest/blue-top.jpg");
        } else  {
          pozadi(s, "BlueRock_Forest/blue-top.jpg", "BlueRock_Forest/blue-middle.jpg",
                 "BlueRock_Forest/blue-bottom.jpg");
        }
        break;
      case TemaLevelu::Tducholes:
        if (s->level->tema.vyskopis == TemaLevelu::Tnebe) {
          pozadi(s, "BlueRock_Forest/blue-top.jpg", "BlueRock_Forest/blue-top.jpg",
                 "BlueRock_Forest/blue-top.jpg");
        } else  {
          pozadi(s, "ghostforest.jpg", "ghostforest.jpg", "ghostforest.jpg");
        }
        break;
      case TemaLevelu::Tdzungle:
        if (s->level->tema.vyskopis == TemaLevelu::Tnebe) {
          pozadi(s, "BlueRock_Forest/blue-top.jpg", "BlueRock_Forest/blue-top.jpg",
                 "BlueRock_Forest/blue-top.jpg");
        } else  {
          pozadi(s, "BlueRock_Forest/blue-top.jpg", "BlueRock_Forest/rolling-middle.jpg",
                 "BlueRock_Forest/rolling-bottom.jpg");
        }
        break;
      default:
        break;
    }
  }
}

void vymysli_osvetleni(Sektor *s) {
  if (s->level->tema.vyskopis == TemaLevelu::Tpodzemi) {
    s->osvetleni = TemaLevelu::denni_svetlo[TemaLevelu::Tpulnoc].svetlo;
  } else {
    s->osvetleni = TemaLevelu::denni_svetlo[s->level->tema.denni_doba].svetlo;
  }
}

void vymysli_pocasi(Sektor *s) {
  bool venku = true;
  if (s->level->tema.vyskopis == TemaLevelu::Tpodzemi || s->tema == TemaSektoru::Tvenku) {
    venku = false;
  }
  switch (s->level->tema.pocasi) {
    case TemaLevelu::Tbourka:
      if (venku) {
        bourka(s);
      }
      break;
    case TemaLevelu::Tdest:
      if (venku) {
        dest(s);
      }
      break;
    case TemaLevelu::Tdest_se_snehem:
      if (venku) {
        dest_se_snehem(s);
      }
      break;
    case TemaLevelu::Tjasno:
      break;
    case TemaLevelu::Tduchovno:
      duchovno(s);
      break;
    case TemaLevelu::Tmlha:
      mlha(s);
      break;
    case TemaLevelu::Tsnih:
      if (venku) {
        snih(s);
      }
      break;
  }
}
