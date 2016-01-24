#ifndef POZADI_H
#define POZADI_H

#include <string>

class Barva;
class Sektor;

void snih(Sektor* s);
void dest(Sektor* s);
void mraky(Sektor* s);
void dest_se_snehem(Sektor* s);
void duchovno(Sektor* s);
void mlha(Sektor* s);
void bourka(Sektor* s);

void gradient(Sektor* s, Barva horni, Barva dolni);
void pozadi(Sektor* s, std::string horni, std::string stredni, std::string dolni);

void vymysli_hudbu(Sektor* s);
void vymysli_pozadi(Sektor* s);
void vymysli_osvetleni(Sektor* s);
void vymysli_pocasi(Sektor* s);

#endif // POZADI_H
