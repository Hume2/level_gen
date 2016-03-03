#ifndef ZLEJSCI_H
#define ZLEJSCI_H

#include <string>

enum Zlejsci{
  ANGRYSTONE, BOUNCINGSNOWBALL, CAPTAINSNOWBALL, DART, DARTTRAP, DISPENSER, FISH, FLAME, FLYINGSNOWBALL, GHOSTFLAME, GHOSTTREE, GOLDBOMB, HAYWIRE, ICEFLAME, IGEL, JUMPY, KAMIKAZESNOWBALL, KUGELBLITZ, LIVEFIRE, LIVEFIRE_ASLEEP, LIVEFIRE_DORMANT, MOLE, MOLE_ROCK, MRBOMB, MRCANDLE, MRICEBLOCK, MRTREE, OWL, PLANT, POISONIVY, SHORT_FUSE, SSPIKY, SKYDIVE, SKULLYHOP, SMARTBALL, SMARTBLOCK, SNAIL, SNOWBALL, SNOWMAN, SPIDERMITE, SPIKY, STALACTITE, STUMPY, TOAD, TOTEM, WALKINGLEAF, WILLOWISP, YETI, YETI_STALACTITE, ZEEKLING,
  ZLEJSCI
};

enum TypZlejska {
  TZ_LETOUN,
  TZ_CHODEC,
  TZ_PADAC,
  TZ_SPICI,
  TZ_SKOKAN,
  TZ_JINY
};

const int pocet_zlejsku = (int)ZLEJSCI;

const TypZlejska typy_zlejsku[ZLEJSCI] =
//ANGRYSTONE,   BOUNCINGSNOWBALL,   CAPTAINSNOWBALL,   DART,   DARTTRAP,   DISPENSER,   FISH,   FLAME,   FLYINGSNOWBALL,   GHOSTFLAME,   GHOSTTREE,   GOLDBOMB,   HAYWIRE,   ICEFLAME,   IGEL,   JUMPY,   KAMIKAZESNOWBALL,   KUGELBLITZ,   LIVEFIRE,   LIVEFIRE_ASLEEP,   LIVEFIRE_DORMANT,   MOLE,   MOLE_ROCK,   MRBOMB,   MRCANDLE,   MRICEBLOCK,   MRTREE,   OWL,   PLANT,   POISONIVY,   SHORT_FUSE,   SSPIKY,   SKYDIVE,   SKULLYHOP,   SMARTBALL,   SMARTBLOCK,   SNAIL,   SNOWBALL,   SNOWMAN,   SPIDERMITE,   SPIKY,   STALACTITE,   STUMPY,   TOAD,   TOTEM,   WALKINGLEAF,   WILLOWISP,   YETI,   YETI_STALACTITE,   ZEEKLING,
 {TZ_CHODEC,    TZ_CHODEC,          TZ_CHODEC,    TZ_LETOUN,    TZ_JINY,     TZ_JINY,TZ_JINY,TZ_SKOKAN,TZ_SKOKAN,       TZ_SKOKAN,    TZ_JINY,     TZ_CHODEC,  TZ_CHODEC, TZ_SKOKAN,TZ_CHODEC,TZ_SKOKAN,TZ_CHODEC,         TZ_LETOUN,    TZ_CHODEC,  TZ_SPICI,          TZ_JINY,          TZ_CHODEC, TZ_LETOUN,  TZ_CHODEC,TZ_CHODEC,  TZ_CHODEC,   TZ_CHODEC,TZ_LETOUN,TZ_CHODEC,TZ_CHODEC,TZ_CHODEC,    TZ_SPICI, TZ_LETOUN, TZ_CHODEC,   TZ_CHODEC,   TZ_CHODEC,   TZ_CHODEC,TZ_CHODEC,  TZ_CHODEC, TZ_SKOKAN,   TZ_CHODEC, TZ_PADAC,    TZ_CHODEC,TZ_CHODEC,TZ_CHODEC,TZ_CHODEC,  TZ_LETOUN,   TZ_JINY, TZ_PADAC,         TZ_LETOUN};

const std::string nazvy_zlejsku[ZLEJSCI] =
//ANGRYSTONE,   BOUNCINGSNOWBALL,   CAPTAINSNOWBALL,   DART,   DARTTRAP,   DISPENSER,   FISH,   FLAME,   FLYINGSNOWBALL,   GHOSTFLAME,   GHOSTTREE,   GOLDBOMB,   HAYWIRE,   ICEFLAME,   IGEL,   JUMPY,   KAMIKAZESNOWBALL,   KUGELBLITZ,   LIVEFIRE,   LIVEFIRE_ASLEEP,   LIVEFIRE_DORMANT,   MOLE,   MOLE_ROCK,   MRBOMB,   MRCANDLE,   MRICEBLOCK,   MRTREE,   OWL,   PLANT,   POISONIVY,   SHORT_FUSE,   SSPIKY,   SKYDIVE,   SKULLYHOP,   SMARTBALL,   SMARTBLOCK,   SNAIL,   SNOWBALL,   SNOWMAN,   SPIDERMITE,   SPIKY,   STALACTITE,   STUMPY,   TOAD,   TOTEM,   WALKINGLEAF,   WILLOWISP,   YETI,   YETI_STALACTITE,   ZEEKLING,
 {"angrystone", "bouncingsnowball", "captainsnowball", "dart", "darttrap", "dispenser", "fish", "flame", "flyingsnowball", "ghostflame", "ghosttree", "goldbomb", "haywire", "iceflame", "igel", "jumpy", "kamikazesnowball", "kugelblitz", "livefire", "livefire_asleep", "livefire_dormant", "mole", "mole_rock", "mrbomb", "mrcandle", "mriceblock", "mrtree", "owl", "plant", "poisonivy", "short_fuse", "sspiky", "skydive", "skullyhop", "smartball", "smartblock", "snail", "snowball", "snowman", "spidermite", "spiky", "stalactite", "stumpy", "toad", "totem", "walkingleaf", "willowisp", "yeti", "yeti_stalactite", "zeekling"};

const double ledovi_zlejsci[ZLEJSCI] =
//ANGRYSTONE, BOUNCINGSNOWBALL, CAPTAINSNOWBALL, DART, DARTTRAP, DISPENSER, FISH, FLAME, FLYINGSNOWBALL, GHOSTFLAME, GHOSTTREE, GOLDBOMB, HAYWIRE, ICEFLAME, IGEL, JUMPY, KAMIKAZESNOWBALL, KUGELBLITZ, LIVEFIRE, LIVEFIRE_ASLEEP, LIVEFIRE_DORMANT, MOLE, MOLE_ROCK, MRBOMB, MRCANDLE, MRICEBLOCK, MRTREE, OWL, PLANT, POISONIVY, SHORT_FUSE, SSPIKY, SKYDIVE, SKULLYHOP, SMARTBALL, SMARTBLOCK, SNAIL, SNOWBALL, SNOWMAN, SPIDERMITE, SPIKY, STALACTITE, STUMPY, TOAD, TOTEM, WALKINGLEAF, WILLOWISP, YETI, YETI_STALACTITE, ZEEKLING,
 {         0,              300,             100,    0,        0,         0,    0,     0,            150,          0,         0,       50,     400,      150,    0,   200,               10,          0,        0,               0,                0,    0,         0,    500,        0,        700,      0,   0,     0,         0,        250,      0,       0,         0,      1000,        700,     0,     1000,     100,          0,   500,       1000,      0,    0,     0,           0,         0,    0,               0,        0};

const double lesni_zlejsci[ZLEJSCI] =
//ANGRYSTONE, BOUNCINGSNOWBALL, CAPTAINSNOWBALL, DART, DARTTRAP, DISPENSER, FISH, FLAME, FLYINGSNOWBALL, GHOSTFLAME, GHOSTTREE, GOLDBOMB, HAYWIRE, ICEFLAME, IGEL, JUMPY, KAMIKAZESNOWBALL, KUGELBLITZ, LIVEFIRE, LIVEFIRE_ASLEEP, LIVEFIRE_DORMANT, MOLE, MOLE_ROCK, MRBOMB, MRCANDLE, MRICEBLOCK, MRTREE, OWL, PLANT, POISONIVY, SHORT_FUSE, SSPIKY, SKYDIVE, SKULLYHOP, SMARTBALL, SMARTBLOCK, SNAIL, SNOWBALL, SNOWMAN, SPIDERMITE, SPIKY, STALACTITE, STUMPY, TOAD, TOTEM, WALKINGLEAF, WILLOWISP, YETI, YETI_STALACTITE, ZEEKLING,
 {         2,                0,               0,    0,        0,         0,    0,     0,              0,         20,         0,       50,     400,        0,  200,     0,                0,          0,        0,               0,                0,    0,         0,    500,        0,          0,    400,  50,    10,      1000,        250,      0,       0,        10,         0,          0,   600,        0,       0,        200,     0,          0,    200,  200,     0,        1000,         0,    0,               0,      200};

const double ducholesni_zlejsci[ZLEJSCI] =
//ANGRYSTONE, BOUNCINGSNOWBALL, CAPTAINSNOWBALL, DART, DARTTRAP, DISPENSER, FISH, FLAME, FLYINGSNOWBALL, GHOSTFLAME, GHOSTTREE, GOLDBOMB, HAYWIRE, ICEFLAME, IGEL, JUMPY, KAMIKAZESNOWBALL, KUGELBLITZ, LIVEFIRE, LIVEFIRE_ASLEEP, LIVEFIRE_DORMANT, MOLE, MOLE_ROCK, MRBOMB, MRCANDLE, MRICEBLOCK, MRTREE, OWL, PLANT, POISONIVY, SHORT_FUSE, SSPIKY, SKYDIVE, SKULLYHOP, SMARTBALL, SMARTBLOCK, SNAIL, SNOWBALL, SNOWMAN, SPIDERMITE, SPIKY, STALACTITE, STUMPY, TOAD, TOTEM, WALKINGLEAF, WILLOWISP, YETI, YETI_STALACTITE, ZEEKLING,
 {         4,                0,               0,    0,        0,         0,    0,     0,              0,        150,         0,       50,     400,        0,  200,     0,                0,          0,        0,               0,                0,    0,         0,    500,        0,          0,    200,  50,   210,      1000,        250,      0,       0,       400,         0,          0,   600,        0,       0,        600,     0,          0,    400,  600,     0,        1000,         0,    0,               0,       50};

#endif // ZLEJSCI_H
