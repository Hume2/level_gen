#ifndef GENERATOR_H
#define GENERATOR_H

class Sektor;
class Tilemap;

void gen_ledove_pozadi(Sektor* s);
void gen_jeskyne1(Sektor* s);
void gen_lesni_podlaha(Sektor* s);

void gen_otazniky(Sektor* s);

void gen_start(Sektor* s, int x, int y);
void gen_cil(Sektor* s, int x, int y);
void gen_ulozovaky(Sektor *s);
void gen_zlejsky(Sektor *s);

void gen_ryby(Tilemap *tm);
void gen_stromy(Sektor *s);

#endif //GENERATOR_H
