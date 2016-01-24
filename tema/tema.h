#ifndef TEMA_H
#define TEMA_H

namespace TemaLevelu {

  enum Biom{
    Tledovec,
    Tles,
    Tkrystaly,
    Tdzungle,
    Tducholes
  }; //6 celkem

  enum Vyskopis{
    Trovina,
    Tparhorkatina,
    Tvrchovina,
    Thory,
    Tpodzemi,
    Tnebe
  }; //6 celkem

  enum Struktura{
    Tteren,
    Thrad,
    Tzricenina,
    Tvesnice
  }; //4 celkem

  enum Pocasi{
    Tjasno,
    Tdest,
    Tdest_se_snehem,
    Tsnih,
    Tbourka,
    Tduchovno,
    Tmlha
  }; //7 celkem

  enum DenniDoba{
    Tpulnoc,
    Tnoc,
    Trozbresk,
    Trano,
    Tdopoledne,
    Tpoledne,
    Todpoledne,
    Tpredvecer,
    Tvecer,
    Tpozde_vecer
  }; //10 celkem

  enum Hrani{
    T1D,   //1D, začátek vlevo, konec vpravo, jen jedna cesta
    T1_5D, //1,5D, začátek vlevo, konec vpravo, více cest
    T2D,   //2D, cochcárna
    T2_5D, //2_5D, dveřovaná
    T3D,   //3D, jako ve hře Fez
    T3_5D  //3_5D, jako ve hře Fez + dveřovaná
  }; //5 celkem

  struct Tema{
    Biom biom;
    Vyskopis vyskopis;
    Struktura struktura;
    Pocasi pocasi;
    DenniDoba denni_doba;
    Hrani hrani;
  }; //50400 kombinací

}

namespace TemaSektoru {

  enum Tema{
    Tvenku,
    Tmistnost,
    Thrad,
    Tbunkr
  };

}

#endif // TEMA_H
