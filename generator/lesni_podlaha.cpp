#include <math.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <ctime>

#include "lesni_podlaha.h"

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

void LesniPodlaha::stredovak(int x1, int x2) {
  int stred_ = stred-1;
  nas_sektor->intact2->obdelnik(K[1],x1,x2,stred_,stred_);
  nas_sektor->intact2->obdelnik(K[4],x1,x2,stred,stred);
  nas_sektor->intact2->obdelnik(S,x1,x2,stred+1,h);
}

void LesniPodlaha::stredovak() {
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
  byla_prekazka = false;
}

void LesniPodlaha::nahorovak() {
  int dh = exp_rand(trr,3) + 1;
  int novy_stred = stred - dh;
  if (novy_stred < min_y) {
    stredovak();
    return;
  }

  nas_sektor->intact2->poloz_blok(K[0], x, novy_stred-1);
  if (dh == 1) {
    nas_sektor->intact2->poloz_blok(P[0], x, novy_stred);
  } else {
    nas_sektor->intact2->poloz_blok(K[3], x, novy_stred);
    nas_sektor->intact2->obdelnik(K[6], x, x, novy_stred+1, stred-2);
    nas_sektor->intact2->poloz_blok(V[3], x, stred-1);
  }
  nas_sektor->intact2->poloz_blok(V[5], x, stred);
  nas_sektor->intact2->obdelnik(S, x, x, stred+1, h);
  stred = novy_stred;
  bylo_stoupani = false;
  byl_nahorovak = true;
  byl_dolovak = false;
  byla_prekazka = false;
  x++;
}

void LesniPodlaha::dolovak() {
  int dh = exp_rand(trr,3) + 1;
  int novy_stred = stred + dh;
  if (novy_stred > max_y) {
    stredovak();
    return;
  }

  nas_sektor->intact2->poloz_blok(K[2], x, stred-1);
  if (dh == 1) {
    nas_sektor->intact2->poloz_blok(P[1], x, stred);
  } else {
    nas_sektor->intact2->poloz_blok(K[5], x, stred);
    nas_sektor->intact2->obdelnik(K[8], x, x, stred+1, novy_stred-2);
    nas_sektor->intact2->poloz_blok(V[2], x, novy_stred-1);
  }
  nas_sektor->intact2->poloz_blok(V[4], x, novy_stred);
  nas_sektor->intact2->obdelnik(S, x, x, novy_stred+1, h);
  stred = novy_stred;
  bylo_stoupani = false;
  byl_nahorovak = false;
  byl_dolovak = true;
  byla_prekazka = false;
  x++;
}

void LesniPodlaha::dolu50() {
  nas_sektor->intact2->obdelnik(S,x,x+2,stred+2,h);
  ps->dolu50(x,stred);
  x+=2;
  stred++;
}

void LesniPodlaha::dolu100() {
  nas_sektor->intact2->obdelnik(S,x,x,stred+2,h);
  ps->dolu100(x,stred);
  x++;
  stred++;
}

void LesniPodlaha::dolu200() {
  nas_sektor->intact2->obdelnik(S,x,x,stred+3,h);
  ps->dolu200(x,stred);
  x++;
  stred+=2;
}

void LesniPodlaha::nahoru50() {
  nas_sektor->intact2->obdelnik(S,x,x+2,stred+1,h);
  stred--;
  ps->nahoru50(x,stred);
  x+=2;
}

void LesniPodlaha::nahoru100() {
  nas_sektor->intact2->obdelnik(S,x,x,stred+1,h);
  stred--;
  ps->nahoru100(x,stred);
  x++;
}

void LesniPodlaha::nahoru200() {
  nas_sektor->intact2->obdelnik(S,x,x,stred+1,h);
  stred-=2;
  ps->nahoru200(x,stred);
  x++;
}

void LesniPodlaha::nahoru0_50() {
  nas_sektor->intact2->obdelnik(S,x,x+2,stred+1,h);
  stred--;
  ps->nahoru0_50(x,stred);
  x+=3;
}

void LesniPodlaha::nahoru50_0() {
  nas_sektor->intact2->obdelnik(S,x,x+2,stred+1,h);
  stred--;
  ps->nahoru50_0(x,stred);
  x+=3;
}

void LesniPodlaha::nahoru50_100() {
  nas_sektor->intact2->obdelnik(S,x,x+2,stred+1,h);
  stred-=2;
  ps->nahoru50_100(x,stred);
  x+=3;
}

void LesniPodlaha::nahoru100_50() {
  nas_sektor->intact2->obdelnik(S,x,x+2,stred+1,h);
  stred-=2;
  ps->nahoru100_50(x,stred);
  x+=3;
}

void LesniPodlaha::dolu0_50() {
  nas_sektor->intact2->obdelnik(S,x,x+2,stred+1,h);
  ps->dolu0_50(x,stred);
  stred++;
  x+=3;
}

void LesniPodlaha::dolu50_0() {
  nas_sektor->intact2->obdelnik(S,x,x+2,stred+1,h);
  ps->dolu50_0(x,stred);
  stred++;
  x+=3;
}

void LesniPodlaha::dolu50_100() {
  nas_sektor->intact2->obdelnik(S,x,x+2,stred+1,h);
  ps->dolu50_100(x,stred);
  stred+=2;
  x+=3;
}

void LesniPodlaha::dolu100_50() {
  nas_sektor->intact2->obdelnik(S,x,x+2,stred+1,h);
  ps->dolu100_50(x,stred);
  stred+=2;
  x+=3;
}

void LesniPodlaha::svahovak(int cko) {
  if (cko == 0 ) {
    cko = 1;
  }
  if (cko == 8) {
    cko = 7;
  }

  switch (cko) {
    case 1:
      if (stred - (til.je_svahovy_prechod ? 6 : 4) < min_y && til.je_svah_200) {
        return;
      } else {
        nahoru200();
      }
      break;
    case 2:
      if (stred - (til.je_svahovy_prechod ? 4 : 2) < min_y && til.je_svah_100) {
        return;
      } else {
        if (til.je_svahovy_prechod && stoupani == 3) {
          nahoru50_100();
        } else {
          nahoru100();
        }
      }
      break;
    case 3:
      if (stred - (til.je_svahovy_prechod ? 2 : 1) < min_y && til.je_svah_50) {
        return;
      } else {
        if (!til.je_svahovy_prechod || stoupani == 3) {
          nahoru50();
        } else if (stoupani == 4) {
          nahoru0_50();
        } else {
          nahoru100_50();
        }
      }
      break;
    case 4:
      if (til.je_svahovy_prechod && stoupani != 4) {
        if (stoupani == 3) {
          nahoru50_0();
        } else {
          dolu50_0();
        }
      }
      stoupani = 4;
      bylo_stoupani = false;
      byl_nahorovak = false;
      byl_dolovak = false;
      byla_prekazka = false;
      return;
      break;
    case 5:
      if (stred + (til.je_svahovy_prechod ? 2 : 1) > max_y && til.je_svah_50) {
        return;
      } else {
        if (!til.je_svahovy_prechod || stoupani == 6) {
          dolu50();
        } else if (stoupani == 4) {
          dolu0_50();
        } else {
          dolu100_50();
        }
      }
      break;
    case 6:
      if (stred + (til.je_svahovy_prechod ? 4 : 2) > max_y && til.je_svah_100) {
        return;
      } else {
        if (til.je_svahovy_prechod && stoupani == 5) {
          dolu50_100();
        } else {
          dolu100();
        }
      }
      break;
    case 7:
      if (stred + (til.je_svahovy_prechod ? 6 : 4) > max_y && til.je_svah_200) {
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
  byla_prekazka = false;
}

LesniPodlaha::LesniPodlaha(Sektor* sektor, const SadaDlazdic til_) :
  w(sektor->intact->sirka),
  h(sektor->intact->vyska),
  stred(),
  x(),
  trr(TemaLevelu::hornatost[sektor->level->tema.vyskopis]),
  min_y(15),
  max_y(h-6),
  min_x(5),
  max_x(w-30),
  nas_sektor(sektor),
  stoupani(4),
  bylo_stoupani(false),
  byl_nahorovak(false),
  byl_dolovak(false),
  byla_prekazka(false),
  til(til_),
  ps(new PokladacSvahu(nas_sektor->intact2, &til, true)),
  pr(new Prekazitor(nas_sektor, &x, &stred, til_, max_x, min_y))
{
  if (til.je_svahovy_prechod) {
    trr *= 1.8;
  }
}

void LesniPodlaha::generuj() {
  int s = (min_y + max_y)/2;
  stred = s;
  stredovak(0,min_x);
  x = min_x + 1;
  double codal[6];
  while (x < max_x) {
    codal[Astredovak] = 20/trr;
    codal[Anahorovak] = trr;
    codal[Adolovak] = trr;
    codal[Astoupej] = stoupani > 4 ? trr*trr : sqrt(trr);
    codal[Aklesej] = stoupani < 4 ? trr*trr : sqrt(trr);
    codal[Aprekazej] = trr/5;
    if (stred < s) {
      double coef = (s-stred)/h;
      codal[Adolovak] += coef;
      codal[Aklesej] += coef;
    }
    if (stred > s) {
      double coef = (stred-s)/h;
      codal[Anahorovak] += coef;
      codal[Astoupej] += coef;
    }
    if (byl_dolovak) {
      codal[Anahorovak] = 0;
    }
    if (bylo_stoupani) {
      codal[Anahorovak] = 0;
      codal[Adolovak] = 0;
      codal[Aprekazej] = 0;
    }
    if (byla_prekazka) {
      codal[Aprekazej] = 0;
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
      case Aprekazej:
        if (pr->prekazka()) {
          bylo_stoupani = false;
          byl_dolovak = false;
          byl_nahorovak = false;
          byla_prekazka = true;
        }
        break;
      default:
        break;
    }
  }
  stredovak(x,w);
}

void LesniPodlaha::set_max_x(int n) {
  max_x = n;
  pr->max_x = n;
}

void LesniPodlaha::set_max_y(int n) {
  max_y = n;
}

void LesniPodlaha::set_min_x(int n) {
  min_x = n;
}

void LesniPodlaha::set_min_y(int n) {
  min_y = n;
  pr->min_y = n;
}
