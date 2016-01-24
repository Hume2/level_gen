#include <math.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <ctime>

#include "level/level.h"

using namespace std;

string int_to_str(int x) {
  if (x == 0) {
    return "  0";
  }

  string result = "";
  int zb;
  while (x) {
    zb = x % 10;
    x = ( x-zb ) / 10;
    result.insert(result.begin(), '0' + zb);
  }
  return result;
}

int str_to_int(string s) {
  int result = 0;
  while (s.length()) {
    result *= 10;
    result += s[0] - '0';
    s.erase(s.begin(),s.begin()+1);
  }
  return result;
}

int main(int argc, char** arg) {
  srandom(time(0));

  int lvlc = 100;
  if (argc > 1) {
    lvlc = str_to_int(arg[1]);
  }

  if (lvlc == 1) {
    FILE *f = fopen("out.stl","w");
    Level kolo;
    kolo.autor = "Hume2";
    kolo.jmeno = "Humeho sranda kolo";
    kolo.poradi = 1;
    kolo.vysav(f);
    fclose(f);
  } else {
    for (int i = 1; i <= lvlc; i++) {
      string filename = "tt_reborn/level" + int_to_str(i) + ".stl";
      FILE *f = fopen(filename.c_str(),"w");
      Level kolo;
      kolo.autor = "Hume2";
      //kolo.jmeno = "Very level, such long, wow";
      kolo.poradi = i;
      kolo.vysav(f);
      fclose(f);
      cout << "Vygenerována úroveň č." << i << endl;
    }
  }
  return 0;
}
