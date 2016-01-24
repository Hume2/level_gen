#include <math.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <ctime>

int nahodne(int max) {
  int result = rand()%max;
  if (result < 0) {
    result *= -1;
  }
  return result;
}

double nahodne_d(double max) {
  return static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * max;
}

int exp_rand(int xp) {
  int p = 0;
  while (nahodne(xp) > 1) {
    p++;
  }
  return p;
}

int exp_rand(int xp, int max) {
  int p = 0;
  while (nahodne(xp) > 1 && p < max) {
    p++;
  }
  return p;
}

int signed_xp_rand(int xp) {
  bool zn = nahodne(2);
  int p = exp_rand(xp);
  return zn ? p : -p;
}

int signed_xp_rand(int xp, int max) {
  bool zn = nahodne(2);
  int p = exp_rand(xp, max);
  return zn ? p : -p;
}

int nahodne_vyber(const double *pole, int pocet) {
  double soucet = 0;
  for (int i = pocet - 1; i >= 0; i--) {
    soucet += pole[i];
  }
  double r = nahodne_d(soucet);
  int j = 0;
  do {
    r -= pole[j];
  } while ((r >= 0) && (++j < pocet));
  return j;
}
