#include "pokladac_svahu.h"

#include "../level/tilemap.h"
#include "../tema/dlazdicky.h"

#define N50  til->nahoru_50
#define N100 til->nahoru_100
#define N200 til->nahoru_200
#define D50  til->dolu_50
#define D100 til->dolu_100
#define D200 til->dolu_200
#define M50  til->inv_nahoru_50
#define M100 til->inv_nahoru_100
#define M200 til->inv_nahoru_200
#define E50  til->inv_dolu_50
#define E100 til->inv_dolu_100
#define E200 til->inv_dolu_200
#define N65 til->nahoru_0_50
#define N56 til->nahoru_50_0
#define N51 til->nahoru_50_100
#define N15 til->nahoru_100_50
#define D65 til->dolu_0_50
#define D56 til->dolu_50_0
#define D51 til->dolu_50_100
#define D15 til->dolu_100_50

#define X0 x
#define X1 x+1
#define X2 x+2
#define X3 x+3

#define Y0 y
#define Y1 y+1
#define Y2 y+2
#define Y3 y+3

#define CUR (til->curani_svahu)&&curak

PokladacSvahu::PokladacSvahu(Tilemap* tm_, SadaDlazdic* til_, bool curak_):
  tm(tm_),
  til(til_),
  curak(curak_)
{
}

void PokladacSvahu::dolu50(int x, int y) {
  // _____ 0
  // @@@@@ 1 2 ______
  // @@@@@ 3 4 @@@@@@
  tm->poloz_blok(D50[1], X0, Y0);
  tm->poloz_blok(D50[2], X1, Y0);
  tm->poloz_blok(D50[3], X0, Y1);
  tm->poloz_blok(D50[4], X1, Y1);

  if (CUR) {
    if (tm->bloky[x][y-1] == 0) {
      tm->poloz_blok(D50[0], x, y-1);
    }
    tm->poloz_blok(D50[0], x+2, y);
  } else {
    tm->poloz_blok(D50[0], x, y-1);
  }
}

void PokladacSvahu::dolu100(int x, int y) {
  // ______ 0
  // @@@@@@ 1 ______
  // @@@@@@ 2 @@@@@@
  tm->poloz_blok(D100[1], X0, Y0);
  tm->poloz_blok(D100[2], X0, Y1);

  if (CUR) {
    tm->poloz_blok(D100[0], x+1, y);
  } else {
    tm->poloz_blok(D100[0], x, y-1);
  }
}

void PokladacSvahu::dolu200(int x, int y) {
  // ______ 0
  // @@@@@@ 1
  // @@@@@@ 2 ______
  // @@@@@@ 3 @@@@@@
  tm->poloz_blok(D200[1], X0, Y0);
  tm->poloz_blok(D200[2], X0, Y1);
  tm->poloz_blok(D200[3], X0, Y2);

  if (CUR) {
    tm->poloz_blok(D200[0], x+1, y+1);
  } else {
    tm->poloz_blok(D200[0], x, y-1);
  }
}

void PokladacSvahu::nahoru50(int x, int y) {
  //       0 ____
  //____ 1 2 @@@@
  //@@@@ 3 4 @@@@
  tm->poloz_blok(N50[1], X0, Y0);
  tm->poloz_blok(N50[2], X1, Y0);
  tm->poloz_blok(N50[3], X0, Y1);
  tm->poloz_blok(N50[4], X1, Y1);

  if (CUR) {
    tm->poloz_blok(N50[0], x+1, y-1);
    if (tm->bloky[x-1][y] == 1045) {
      tm->poloz_blok(N50[0], x-1, y);
    }
  } else {
    tm->poloz_blok(N50[0], x+1, y-1);
  }
}

void PokladacSvahu::nahoru100(int x, int y) {
  //     0 ____
  //____ 1 @@@@
  //@@@@ 2 @@@@
  tm->poloz_blok(N100[1], X0, Y0);
  tm->poloz_blok(N100[2], X0, Y1);

  tm->poloz_blok(N100[0], x, y-1);
  if (CUR) {
    tm->poloz_blok(N100[0], x-1, y);
  }
}

void PokladacSvahu::nahoru200(int x, int y) {
  //     0 ____
  //     1 @@@@
  //____ 2 @@@@
  //@@@@ 3 @@@@
  tm->poloz_blok(N200[1], X0, Y0);
  tm->poloz_blok(N200[2], X0, Y1);
  tm->poloz_blok(N200[3], X0, Y2);

  tm->poloz_blok(N200[0], X0, y-1);
  if (CUR) {
    tm->poloz_blok(N200[0], x-1, y+1);
  }
}

void PokladacSvahu::nahoru0_50(int x, int y){
  //         0 ____
  //____ 1 2 3 @@@@
  //@@@@ 4 5 6 @@@@
  tm->poloz_blok(N65[0], x+2, y-1);

  tm->poloz_blok(N65[1], X0, Y0);
  tm->poloz_blok(N65[2], X1, Y0);
  tm->poloz_blok(N65[3], X2, Y0);
  tm->poloz_blok(N65[4], X0, Y1);
  tm->poloz_blok(N65[5], X1, Y1);
  tm->poloz_blok(N65[6], X2, Y1);
}

void PokladacSvahu::nahoru50_0(int x, int y) {
  //       0 1 ____
  //____ 2 3 4 @@@@
  //@@@@ 5 6 7 @@@@
  tm->poloz_blok(N56[0], x+1, y-1);
  tm->poloz_blok(N56[1], x+2, y-1);

  tm->poloz_blok(N56[2], X0, Y0);
  tm->poloz_blok(N56[3], X1, Y0);
  tm->poloz_blok(N56[4], X2, Y0);
  tm->poloz_blok(N56[5], X0, Y1);
  tm->poloz_blok(N56[6], X1, Y1);
  tm->poloz_blok(N56[7], X2, Y1);
}

void PokladacSvahu::nahoru50_100(int x, int y){
  //         0 ____
  //       1 2 @@@@
  //     3 4 5 @@@@
  //@@@@ 6 7 8 @@@@
  tm->poloz_blok(N51[0], x+2, y-1);

  tm->poloz_blok(N51[1], X1, Y0);
  tm->poloz_blok(N51[2], X2, Y0);
  tm->poloz_blok(N51[3], X0, Y1);
  tm->poloz_blok(N51[4], X1, Y1);
  tm->poloz_blok(N51[5], X2, Y1);
  tm->poloz_blok(N51[6], X0, Y2);
  tm->poloz_blok(N51[7], X1, Y2);
  tm->poloz_blok(N51[8], X2, Y2);
}

void PokladacSvahu::nahoru100_50(int x, int y) {
  //         0 ____
  //     1 2 3 @@@@
  //     4 5 6 @@@@
  //@@@@ 7 8 9 @@@@
  tm->poloz_blok(N15[0], x+2, y-1);

  tm->poloz_blok(N15[1], X0, Y0);
  tm->poloz_blok(N15[2], X1, Y0);
  tm->poloz_blok(N15[3], X2, Y0);
  tm->poloz_blok(N15[4], X0, Y1);
  tm->poloz_blok(N15[5], X1, Y1);
  tm->poloz_blok(N15[6], X2, Y1);
  tm->poloz_blok(N15[7], X0, Y2);
  tm->poloz_blok(N15[8], X1, Y2);
  tm->poloz_blok(N15[9], X2, Y2);
}

void PokladacSvahu::dolu0_50(int x, int y) {
  // ______ 0 1
  // @@@@@@ 2 3 4 ______
  // @@@@@@ 5 6 7 @@@@@@
  tm->poloz_blok(D65[0], x, y-1);
  tm->poloz_blok(D65[1], x+1, y-1);

  tm->poloz_blok(D65[2], X0, Y0);
  tm->poloz_blok(D65[3], X1, Y0);
  tm->poloz_blok(D65[4], X2, Y0);
  tm->poloz_blok(D65[5], X0, Y1);
  tm->poloz_blok(D65[6], X1, Y1);
  tm->poloz_blok(D65[7], X2, Y1);
}

void PokladacSvahu::dolu50_0(int x, int y){
  // ______ 0
  // @@@@@@ 1 2 3 ______
  // @@@@@@ 4 5 6 @@@@@@
  tm->poloz_blok(D56[0], x, y-1);

  tm->poloz_blok(D56[1], X0, Y0);
  tm->poloz_blok(D56[2], X1, Y0);
  tm->poloz_blok(D56[3], X2, Y0);
  tm->poloz_blok(D56[4], X0, Y1);
  tm->poloz_blok(D56[5], X1, Y1);
  tm->poloz_blok(D56[6], X2, Y1);
}

void PokladacSvahu::dolu50_100(int x, int y) {
  // ______ 0
  // @@@@@@ 1 2 3
  // @@@@@@ 4 5 6 ______
  // @@@@@@ 7 8 9 @@@@@@
  tm->poloz_blok(D51[0], x, y-1);

  tm->poloz_blok(D51[1], X0, Y0);
  tm->poloz_blok(D51[2], X1, Y0);
  tm->poloz_blok(D51[3], X2, Y0);
  tm->poloz_blok(D51[4], X0, Y1);
  tm->poloz_blok(D51[5], X1, Y1);
  tm->poloz_blok(D51[6], X2, Y1);
  tm->poloz_blok(D51[7], X0, Y2);
  tm->poloz_blok(D51[8], X1, Y2);
  tm->poloz_blok(D51[9], X2, Y2);
}

void PokladacSvahu::dolu100_50(int x, int y) {
  // ______ 0
  // @@@@@@ 1 2
  // @@@@@@ 3 4 5 ______
  // @@@@@@ 6 7 8 @@@@@@
  tm->poloz_blok(D15[0], x, y-1);

  tm->poloz_blok(D15[1], X0, Y0);
  tm->poloz_blok(D15[2], X1, Y0);
  tm->poloz_blok(D15[3], X0, Y1);
  tm->poloz_blok(D15[4], X1, Y1);
  tm->poloz_blok(D15[5], X2, Y1);
  tm->poloz_blok(D15[6], X0, Y2);
  tm->poloz_blok(D15[7], X1, Y2);
  tm->poloz_blok(D15[8], X2, Y2);
}

void PokladacSvahu::inv_dolu50(int x, int y) {
  // @@@@@@ 0 1 @@@@@@
  //        2 3 @@@@@@
  tm->poloz_blok(E50[0], X0, Y0);
  tm->poloz_blok(E50[1], X1, Y0);
  tm->poloz_blok(E50[2], X0, Y1);
  tm->poloz_blok(E50[3], X1, Y1);
}

void PokladacSvahu::inv_dolu100(int x, int y) {
  // @@@@@@ 0 @@@@@@
  //        1 @@@@@@
  tm->poloz_blok(E100[0], X0, Y0);
  tm->poloz_blok(E100[1], X0, Y1);
}

void PokladacSvahu::inv_dolu200(int x, int y) {
  // @@@@@@ 0 @@@@@@
  //        1 @@@@@@
  //        2 @@@@@@
  tm->poloz_blok(E200[0], X0, Y0);
  tm->poloz_blok(E200[1], X0, Y1);
  tm->poloz_blok(E200[2], X0, Y2);
}

void PokladacSvahu::inv_nahoru50(int x, int y) {
  // @@@@@@ 0 1 @@@@@@
  // @@@@@@ 2 3
  tm->poloz_blok(M50[0], X0, Y0);
  tm->poloz_blok(M50[1], X1, Y0);
  tm->poloz_blok(M50[2], X0, Y1);
  tm->poloz_blok(M50[3], X1, Y1);
}

void PokladacSvahu::inv_nahoru100(int x, int y) {
  // @@@@@@ 0 @@@@@@
  // @@@@@@ 1
  tm->poloz_blok(M100[0], X0, Y0);
  tm->poloz_blok(M100[1], X0, Y1);
}

void PokladacSvahu::inv_nahoru200(int x, int y) {
  // @@@@@@ 0 @@@@@@
  // @@@@@@ 1
  // @@@@@@ 2
  tm->poloz_blok(M200[0], X0, Y0);
  tm->poloz_blok(M200[1], X0, Y1);
  tm->poloz_blok(M200[2], X0, Y2);
}
