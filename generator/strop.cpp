#include <math.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <ctime>

#include "strop.h"

#include "../level/level.h"
#include "../level/sektor.h"
#include "../level/tilemap.h"
#include "random.h"

#include "../tema/dlazdicky.h"
#include "../tema/tematicke_hodnoty.h"

#include "pokladac_svahu.h"
#include "prekazitor.h"

#define S til.konvexni[7]
#define K til.konvexni
#define V til.konkavni
#define P til.pidischody

using namespace std;

void Strop::stredovak(int x1, int x2) {
  int stred_ = stred-1;
  nas_sektor->intact2->obdelnik(K[10],x1,x2,stred,stred);
  nas_sektor->intact2->obdelnik(S,x1,x2,0,stred_);
}

void Strop::stredovak() {
  int x2 = exp_rand(20/trr);
  if (x2 == 0) {
    return;
  }
  if (x2) {
    stredovak(x,x+x2-1);
  }
  x += x2;
  bylo_stoupani = false;
  byl_nahorovak = false;
  byl_dolovak = false;
}

void Strop::dolovak() {
  int dh = exp_rand(trr,3) + 1;
  int novy_stred = stred + dh;
  if (novy_stred > max_y) {
    stredovak();
    return;
  }

  nas_sektor->intact2->poloz_blok(K[9], x, novy_stred);
  if (dh > 1) {
    nas_sektor->intact2->obdelnik(K[6], x, x, stred+1, novy_stred-1);
  }
  nas_sektor->intact2->poloz_blok(V[1], x, stred);
  nas_sektor->intact2->obdelnik(S, x, x, 0, stred-1);
  stred = novy_stred;
  bylo_stoupani = false;
  byl_nahorovak = false;
  byl_dolovak = true;
  x++;
}

void Strop::nahorovak() {
  int dh = exp_rand(trr,3) + 1;
  int novy_stred = stred - dh;
  if (novy_stred < min_y) {
    stredovak();
    return;
  }

  nas_sektor->intact2->poloz_blok(K[11], x, stred);
  if (dh > 1) {
    nas_sektor->intact2->obdelnik(K[8], x, x, novy_stred+1, stred-1);
  }
  nas_sektor->intact2->poloz_blok(V[0], x, novy_stred);
  nas_sektor->intact2->obdelnik(S, x, x, 0, novy_stred-1);
  stred = novy_stred;
  bylo_stoupani = false;
  byl_nahorovak = true;
  byl_dolovak = false;
  x++;
}

void Strop::dolu50() {
  nas_sektor->intact2->obdelnik(S,x,x+1,0,stred-1);
  ps->inv_dolu50(x,stred);
  x+=2;
  stred++;
}

void Strop::dolu100() {
  nas_sektor->intact2->obdelnik(S,x,x,0,stred-1);
  ps->inv_dolu100(x,stred);
  x++;
  stred++;
}

void Strop::dolu200() {
  nas_sektor->intact2->obdelnik(S,x,x,0,stred-1);
  ps->inv_dolu200(x,stred);
  x++;
  stred+=2;
}

void Strop::nahoru50() {
  nas_sektor->intact2->obdelnik(S,x,x+1,0,stred-2);
  stred--;
  ps->inv_nahoru50(x,stred);
  x+=2;
}

void Strop::nahoru100() {
  nas_sektor->intact2->obdelnik(S,x,x,0,stred-2);
  stred--;
  ps->inv_nahoru100(x,stred);
  x++;
}

void Strop::nahoru200() {
  nas_sektor->intact2->obdelnik(S,x,x,0,stred-3);
  stred-=2;
  ps->inv_nahoru200(x,stred);
  x++;
}

void Strop::svahovak(int cko) {
  if (cko == 0 ) {
    cko = 1;
  }
  if (cko == 8) {
    cko = 7;
  }

  switch (cko) {
    case 1:
      if (stred - 4 < min_y || !til.je_svah_200) {
        return;
      } else {
        nahoru200();
      }
      break;
    case 2:
      if (stred - 2 < min_y || !til.je_svah_100) {
        return;
      } else {
        nahoru100();
      }
      break;
    case 3:
      if (stred - 1 < min_y || !til.je_svah_50) {
        return;
      } else {
        nahoru50();
      }
      break;
    case 4:
      stoupani = 4;
      bylo_stoupani = false;
      byl_nahorovak = false;
      byl_dolovak = false;
      return;
      break;
    case 5:
      if (stred + 1 > max_y || !til.je_svah_50) {
        return;
      } else {
        dolu50();
      }
      break;
    case 6:
      if (stred + 2 > max_y || !til.je_svah_100) {
        return;
      } else {
        dolu100();
      }
      break;
    case 7:
      if (stred + 4 > max_y || !til.je_svah_200) {
        return;
      } else {
        dolu200();
      }
      break;
    default:
      break;
  }
  stoupani = cko;
  byl_dolovak = false;
  byl_nahorovak = false;
  bylo_stoupani = true;
}

Strop::Strop(Sektor* sektor, const SadaDlazdic til_) :
  w(sektor->intact->sirka),
  h(sektor->intact->vyska),
  stred(),
  x(),
  trr(TemaLevelu::hornatost[sektor->level->tema.vyskopis]),
  min_y(4),
  max_y(h-6),
  min_x(5),
  max_x(w-30),
  nas_sektor(sektor),
  stoupani(4),
  bylo_stoupani(false),
  byl_nahorovak(false),
  byl_dolovak(false),
  til(til_),
  ps(new PokladacSvahu(nas_sektor->intact2, &til, true))
{
  trr *= 1.8;
}

void Strop::generuj() {
  int s = (min_y + max_y)/2;
  stred = s;
  stredovak(0,min_x);
  x = min_x + 1;
  double codal[5];
  while (x < max_x) {
    codal[Astredovak] = 20/trr;
    codal[Anahorovak] = trr;
    codal[Adolovak] = trr;
    codal[Astoupej] = stoupani > 4 ? trr*trr : sqrt(trr);
    codal[Aklesej] = stoupani < 4 ? trr*trr : sqrt(trr);
    if (stred > s) {
      double coef = (s-stred)/h;
      codal[Adolovak] += coef;
      codal[Aklesej] += coef;
    }
    if (stred < s) {
      double coef = (stred-s)/h;
      codal[Anahorovak] += coef;
      codal[Astoupej] += coef;
    }
    if (byl_nahorovak) {
      codal[Adolovak] = 0;
    }
    if (bylo_stoupani) {
      codal[Anahorovak] = 0;
      codal[Adolovak] = 0;
    }
    int a = nahodne_vyber(codal, 6);
    switch (a) {
      case Astredovak:
        if (bylo_stoupani) {
          svahovak(stoupani);
        } else {
          stredovak();
        }
        break;
      case Anahorovak:
        nahorovak();
        break;
      case Adolovak:
        dolovak();
        break;
      case Astoupej:
        svahovak(stoupani - 1);
        break;
      case Aklesej:
        svahovak(stoupani + 1);
        break;
      default:
        break;
    }
  }
  stredovak(x,w);
}
