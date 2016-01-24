#ifndef SMER_H
#define SMER_H

enum Smer{
  NAHORU,
  VPRAVO,
  DOLU,
  VLEVO,
  DOPREDU,
  DOZADU
};

enum SmerS{
  sNAHORU  = 0x01,
  sVPRAVO  = 0x02,
  sDOLU    = 0x04,
  sVLEVO   = 0x08,
  sDOPREDU = 0x10,
  sDOZADU  = 0x20
};

#endif // SMER_H
