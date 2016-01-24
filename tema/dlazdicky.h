#ifndef DLAZDICKY_H
#define DLAZDICKY_H

typedef unsigned short int BLOK;

struct SadaDlazdic{
  bool jsou_svahy;
  bool curani_svahu;
  bool je_svah_50;
  bool je_svah_100;
  bool je_svah_200;
  bool je_horni_svah;
  bool je_svahovy_prechod;
  bool lze_nahorovakovat;
  bool lze_dolovakovat;
  bool jsou_pidischody;

  /*   00_ _01_ _02
   *  003X X04X X05
   *  006@ @07@ @08
   *  @09@ @10@ @11
   */
  BLOK konvexni[12];

  /* @00@ @01@
   * @02_ _03@
   * @04X X05@
   */
  BLOK konkavni[6];

  /* 00X X01
   */
  BLOK pidischody[2];

  // _____ 0
  // @@@@@ 1 2 ______
  // @@@@@ 3 4 @@@@@@
  BLOK dolu_50[5];

  // ______ 0
  // @@@@@@ 1 ______
  // @@@@@@ 2 @@@@@@
  BLOK dolu_100[3];

  // ______ 0
  // @@@@@@ 1
  // @@@@@@ 2 ______
  // @@@@@@ 3 @@@@@@
  BLOK dolu_200[4];

  //       0 ____
  //____ 1 2 @@@@
  //@@@@ 3 4 @@@@
  BLOK nahoru_50[5];

  //     0 ____
  //____ 1 @@@@
  //@@@@ 2 @@@@
  BLOK nahoru_100[3];

  //     0 ____
  //     1 @@@@
  //____ 2 @@@@
  //@@@@ 3 @@@@
  BLOK nahoru_200[4];

  //         0 ____
  //____ 1 2 3 @@@@
  //@@@@ 4 5 6 @@@@
  BLOK nahoru_0_50[7];

  //       0 1 ____
  //____ 2 3 4 @@@@
  //@@@@ 5 6 7 @@@@
  BLOK nahoru_50_0[8];

  //         0 ____
  //       1 2 @@@@
  //     3 4 5 @@@@
  //@@@@ 6 7 8 @@@@
  BLOK nahoru_50_100[9];

  //         0 ____
  //     1 2 3 @@@@
  //     4 5 6 @@@@
  //@@@@ 7 8 9 @@@@
  BLOK nahoru_100_50[10];

  // ______ 0
  // @@@@@@ 1 2 3 ______
  // @@@@@@ 4 5 6 @@@@@@
  BLOK dolu_50_0[7];

  // ______ 0 1
  // @@@@@@ 2 3 4 ______
  // @@@@@@ 5 6 7 @@@@@@
  BLOK dolu_0_50[8];

  // ______ 0
  // @@@@@@ 1 2
  // @@@@@@ 3 4 5 ______
  // @@@@@@ 6 7 8 @@@@@@
  BLOK dolu_100_50[9];

  // ______ 0
  // @@@@@@ 1 2 3
  // @@@@@@ 4 5 6 ______
  // @@@@@@ 7 8 9 @@@@@@
  BLOK dolu_50_100[10];

  // @@@@@@ 0 1 @@@@@@
  //        2 3 @@@@@@
  BLOK inv_dolu_50[4];

  // @@@@@@ 0 @@@@@@
  //        1 @@@@@@
  BLOK inv_dolu_100[2];

  // @@@@@@ 0 @@@@@@
  //        1 @@@@@@
  //        2 @@@@@@
  BLOK inv_dolu_200[3];

  // @@@@@@ 0 1 @@@@@@
  // @@@@@@ 2 3
  BLOK inv_nahoru_50[4];

  // @@@@@@ 0 @@@@@@
  // @@@@@@ 1
  BLOK inv_nahoru_100[2];

  // @@@@@@ 0 @@@@@@
  // @@@@@@ 1
  // @@@@@@ 2
  BLOK inv_nahoru_200[3];
};

// Windows 8 je sračka!!!
// Windows 10 je sračka a spajwer!!!!
// Fejzbug má IQ -9!

#endif // DLAZDICKY_H
