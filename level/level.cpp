#include <string>
#include <stdio.h>
#include <iostream>

#include "level.h"

#include "sektor.h"

#include "../generator/random.h"

#include "../tema/tematicke_hodnoty.h"

using namespace std;

Level::Level() :
  tema(),
  jmeno(""),
  autor(""),
  sektory(),
  vyska(36),
  sirka(473),
  poradi(-1)
{
  tema.biom = (TemaLevelu::Biom)nahodne(5);
  tema.denni_doba = (TemaLevelu::DenniDoba)nahodne(10);
  tema.hrani = TemaLevelu::T1D;
  tema.pocasi = (TemaLevelu::Pocasi)nahodne(7);
  tema.struktura = TemaLevelu::Tteren;
  tema.vyskopis = TemaLevelu::Tparhorkatina;//(TemaLevelu::Vyskopis)nahodne(6);
  vyska = std::max(36, TemaLevelu::hornatost[tema.vyskopis] * 12);
  Sektor* hlavni = new Sektor(this, "main");
  sektory.push_back(hlavni);
}

Level::~Level() {
  for (vector<Sektor*>::iterator i = sektory.begin(); i != sektory.end(); i++) {
    Sektor* s = *i;
    delete (s);
  }
}

void Level::vysav(FILE* f) {
  fprintf(f, "(supertux-level\n  (version 2)\n  (name \"");
  if (poradi >= 0) {
    fprintf(f, "Level %d", poradi);
    if (jmeno.size()) {
      fprintf(f, ": ");
    }
  }
  fputs(jmeno.c_str(), f);
  fprintf(f, "\")\n  (author \"");
  fputs(autor.c_str(), f);
  fprintf(f, "\")\n  (license \"GPL 2+ / CC-by-sa 3.0\")\n");
  for (vector<Sektor*>::iterator i = sektory.begin(); i != sektory.end(); i++) {
    Sektor* s = *i;
    s->vysav(f);
  }
  fprintf(f, "\n)");
}
