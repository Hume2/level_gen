#include <stdio.h>
#include <iostream>

#include "barva.h"

#include <sstream>

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

Barva::Barva() :
  cervena(0),
  zelena(0),
  modra(0),
  alfa(1)
{
}

Barva::Barva(float c, float z, float m, float a) :
  cervena(c),
  zelena(z),
  modra(m),
  alfa(a)
{
}

void Barva::vysav(FILE *f) {
  if (alfa == 256) {
    fprintf(f, "%f %f %f", cervena/256, zelena/256, modra/256);
  } else {
    fprintf(f, "%f %f %f %f", cervena/256, zelena/256, modra/256, alfa/256);
  }
}

std::string Barva::zblbni() {
  std::string result = " " + patch::to_string(cervena/256) + " " + patch::to_string(zelena/256) + " " + patch::to_string(modra/256);

  if (alfa != 256) {
    result += " " + patch::to_string(alfa/256);
  }

  return result;
}
