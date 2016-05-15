#include "../level/sektor.h"
#include "../level/tilemap.h"

#include "hledej_zem.h"

HledejZem::HledejZem(Sektor *s_, Zpusob zp_) :
  s(s_),
  zp(zp_)
{

}

/*
bool Zlej::uprav_pozici(int x, int &y) {
  if (nas_sektor->je_blok_volny(x,y)) {
    y++;
    if (!najdi_pozici_dole(x,y)) {
      return false;
    }
  } else {
    y--;
    if (!inv_najdi_pozici_nahore(x,y)) {
      return false;
    }
  }
  y--;
  hl.hledej_zem(x, y);

  return nas_sektor->je_povoleno(x,y);
}

bool Zlej::uprav_horni_pozici(int x, int &y) {
  if (nas_sektor->je_blok_volny(x,y)) {
    y--;
    if (!najdi_pozici_nahore(x,y)) {
      return false;
    }
  } else {
    y++;
    if (!inv_najdi_pozici_dole(x,y)) {
      return false;
    }
  }

  hl.hledej_strop(x, y);

  return nas_sektor->je_povoleno(x,y);
}*/

bool HledejZem::hledej_zem(int x, int &y, int sirka) {
  sirka--;
  if (s->je_blok_volny(x,y)) {
    y++;
    return !najdi_pozici_dole(x,y, sirka);
  } else {
    y--;
    return !inv_najdi_pozici_nahore(x,y, sirka);
  }
}

bool HledejZem::hledej_strop(int x, int &y, int sirka) {
  sirka--;
  if (s->je_blok_volny(x,y)) {
    y--;
    return !najdi_pozici_nahore(x,y, sirka);
  } else {
    y++;
    return !inv_najdi_pozici_dole(x,y, sirka);
  }
}

bool HledejZem::je_volno(int x1, int x2, int y1, int y2) {
  switch (zp) {
    case VOLNY:
      return s->je_obdelnik_volny(x1, x2, y1, y2);
    case PRAZDNY:
      return s->je_obdelnik_prazny(x1, x2, y1, y2);
  }
}

bool HledejZem::najdi_pozici_dole(int x, int &y, int sirka) {
  while (je_volno(x, x+sirka, y, y) && y < s->intact->vyska) {
    y++;
  }
  y--;
  return y < s->intact->vyska;
}

bool HledejZem::inv_najdi_pozici_nahore(int x, int &y, int sirka) {
  while (!je_volno(x, x+sirka, y, y) && y >= 0) {
    y--;
  }
  return y > 1;
}

bool HledejZem::inv_najdi_pozici_dole(int x, int &y, int sirka) {
  while (!je_volno(x, x+sirka, y, y) && y < s->intact->vyska) {
    y++;
  }
  y--;
  return y < s->intact->vyska;
}

bool HledejZem::najdi_pozici_nahore(int x, int &y, int sirka) {
  while (je_volno(x, x+sirka, y, y) && y >= 0) {
    y--;
  }
  return y > 1;
}
