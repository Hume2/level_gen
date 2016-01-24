#ifndef DLAZDICKORAJ_H
#define DLAZDICKORAJ_H

#include "dlazdicky.h"

namespace PoleDlazdic {

  const SadaDlazdic les = {
    true, // jsou svahy
    true, // čúrání svahů
    true, // je svah 50%
    true, // je svah 100%
    true, // je svah 200%
    false,// je horní svah
    false,// je svahový přechod
    true, // lze nahorovákovat
    true, // lze dolovákovat
    true, // jsou pidischody
    // konvexní
    {1000, 1001, 1003,
     1004, 1005, 1007,
     1008, 1009, 1011,
     1016, 1017, 1019},

    // konkávní
    {1009, 1009,
     1035, 1034,
     1041, 1040},

    // pidischody
    {1036, 1037},

    // dolu 50%
    {1061,
     1065, 1066,
     1069, 1070},

    // dolu 100%
    {1046,
     1048,
     1050},

    // dolu 200%
    {1052,
     1054,
     1056,
     1058},

    // nahoru 50%
    {      1060,
     1063, 1064,
     1067, 1068},

    // nahoru 100%
    {1045,
     1047,
     1049},

    // nahoru 200%
    {1051,
     1053,
     1055,
     1057},

    // na nic:
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0},
    {0,0},
    {0,0,0},
    {0,0,0,0},
    {0,0},
    {0,0,0}
  };

  const SadaDlazdic led = {
    true, // jsou svahy
    false,// čúrání svahů
    true, // je svah 50%
    true, // je svah 100%
    true, // je svah 200%
    true, // je horní svah
    true, // je svahový přechod
    true, // lze nahorovákovat
    true, // lze dolovákovat
    true, // jsou pidischody
    // konvexní
    { 7,  8,  9,
     13, 14, 15,
     10, 11, 12,
     16, 17, 18},

    // konkávní
    {30, 31,
     21, 22,
     20, 23},

    // pidischody
    {114, 113},

    // dolu 50%
    {1827,
     1831, 1832,
     1835, 1836},

    // dolu 100%
    {1838,
     1840,
     1842},

    // dolu 200%
    {1844,
     1846,
     1848,
     1850},

    // nahoru 50%
    {      1826,
     1829, 1830,
     1833, 1834},

    // nahoru 100%
    {1837,
     1839,
     1841},

    // nahoru 200%
    {1843,
     1845,
     1847,
     1849},

    // nahoru 0% -> 50%
    {            1826,
     2921, 2922, 1830,
     2923, 2924, 1834},

    // nahoru 50% -> 0%
    {      2909, 2910,
     1829, 2911, 2912,
     1833, 1834,   11},

    // nahoru 50% -> 100%
    {            3150,
           3153, 3154,
     1829, 3157, 3158,
     1833, 1834,   11},

    // nahoru 100% -> 50%
    {            1826,
     3141, 3142, 1830,
     3145, 3146, 1834,
     3148,   11,   11},

    // dolu 50% -> 0%
    {1827,
     1831, 2917, 2918,
     1835, 2919, 2920},

    // dolu 0% -> 50%
    {2913, 2914,
     2915, 2916, 1832,
       11, 1835, 1836},

    // dolu 100% -> 50%
    {3149,
     3151, 3152,
     3155, 3156, 1832,
       11, 1835, 1836},

    // dolu 50% -> 100%
    {1827,
     1831, 3139, 3140,
     1835, 3143, 3144,
       11,   11, 3147},

    // inv dolu 50%
    {2925, 2926,
        0, 2928},

    // inv dolu 100%
    {2933,
     2934},

    // inv dolu 200%
    {2937,
     2938,
     2939},

    // inv nahoru 50%
    {2929, 2930,
     2931,    0},

    // inv nahoru 100%
    {2935,
     2936},

    // inv nahoru 200%
    {2940,
     2941,
     2942}

  };
}

#endif // DLAZDICKORAJ_H
