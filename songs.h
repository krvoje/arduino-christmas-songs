#define NUM_SONGS 10

struct Song
{
    char *soprano;
    char *alto;
    char *tenor;
    char *bass;
};

const char adeste_fideles_soprano[] PROGMEM = "2a4a2ea4be2c#*bc#*d*4c#*2ba4a2g#f#g#abc#*4g#2f#1e8e4e*2d*c#*4d*c#*2bc#*ab2g#1f#12e2aag#ab4a2ec#*c#*bc#*d*4c#*2bc#*d*c#*ba4g#2ad*4c#*3b1a6a\0";
const char adeste_fideles_alto[] PROGMEM = "2e4e2ec#4ee2eeef#4e2ec#c#d#ed#eeee4e3d#1e8e4e1f#g#2af#g#4a2eef#f#4e2e2x8xxx6x2a1f#g#2aed#4e2ef#4e3e1c#6c#\0";
const char adeste_fideles_tenor[] PROGMEM = "2c#*4c#*2aa4g#b2abaa4a2g#a4a2bbec#g#f#4b3a1g#8g#4c#*2d*e*4d*e*2e*ac#*d*3b1a2g#x8xxx6x2e*d*e*bb4baa3g#1a6a\0";
const char adeste_fideles_bass[] PROGMEM = "2A4A2c#A4eg#2ag#ad4e2ef#4f#2eBBAG#A4B3B1e8e4c#*2ba4ba2g#af#d4e2wx8xxx6x2abag#f#2edc#d4e3e1A6A\0";

const char mehki_snezek_soprano[] PROGMEM =
    "1Gdgb Gdgb Gdgb GBgd* Acf#d* cdc*f# bGdg 4x 1gGBd GCga Gdbd* GBgb F#df#b cdaf# GBdg 4x|1Gdgb Bdf#b Begb Bdgd* Acf#d* cdc*f# Gdbg GBdg 1Gdbd GCga Gdbd* GBgb F#df#b cdaf# GBdg 4x| 2d*gab 1e*g#2d* 1c*e2b 2c*eab 1d*f#2c* 1bd2a 2bdga 1c*e2b 1ac2g 2aF#A1ef# 8d 1gBaA bGc*e bGdg aF#A1cd 2d*gab 1e*g#2d* 1c*e2b 2c*eab 1d*f#2c* 1bd2a 2bdga 1c*e2b 1ac2g 2aF#A 1f#e 8d 2gBaA bGc*e bGdg aF#A1cd 1GABd 6g \0";

const char first_noel_soprano[] PROGMEM =
    "1ag3f1gab'4c*1d*e*2f*e*d*4c*1d*e*2f*e*d*c*d*e*f*c*b'4a1ag3f1gab'4c*1d*e*2f*e*d*4c*1d*e*2f*e*d*c*d*e*f*c*b'4a2ag4f2f*4e*2e*3d*1e*2d*6c*2f*e*d*c*d*e*f*c*b'4a\0";
const char first_noel_alto[] PROGMEM =
    "1ag3c1c2ffee3d1e2a4e1eg2ag2b'afgc*ed4c1ag3c1c2fgab'3d*1c*2b'3g1a21b'g2c*c*b'fb'gafg4f1fe4c2f4g2a4b'2f6g2d*ab'e1fgcd2afe4f\0";
const char first_noel_tenor[] PROGMEM =
    "1ag3a1b'2b'4c*2b'4a2b'3a1f2b'a1gf2d*3c*1b'2c*bag4f2a4a2b'4c*2c*4d*2d*6e*1c*d*2e*d*c*b'1c*b'2fab'4a\0";
const char first_noel_bass[] PROGMEM =
    "1ag2gfd4c2c4d2f3e1d2cf1ed2defg3f1e2B4c2e4d2B4e2e4B2f6g2aef1ag2fc1ce2fe4c2c4f2d4c2A4B2d3e1d2cdcBABcFAG4c\0";

const char jingle_bells_soprano[] PROGMEM =
    "2dbag6d1dd2dbag4ex2ec*ba8f#2d*d*c*a4bx2dbag8d2dbag4e2xeec*bad*d*d*d*e*d*c*agx4d*2bb4b2bb4b2bd*3g1a4bx2c*c*3c*1c*2c*bb1bb2baab4a2d*xbb4b2bb4b2bd*3g1a4bx2c*c*3c*1c*2c*bb1bb2d*d*c*ag6x\0";
const char jingle_bells_alto[] PROGMEM =
    "2dddd6d1dd2dddd4cx2ceee8d2f#f#f#f#4gx2dddd8d2dddd4c2xcceeef#f#f#f#f#f#f#f#4dx2gg4g2gg4g2gg3d1f#4gx2ee3e1e2egg1gg2gf#f#e6f#2x2gg4g2gg4g2gg3d1f#4gx2ee3e1e2egg1gg2f#gf#ag6x\0";
const char jingle_bells_tenor[] PROGMEM =
    "2bbbb6b1bb2bbbb4gx2gggg8c*2c*c*ad*4d*x2bbbb8b2bbbb4g2xgggggaaaac*c*c*c*4bx2d*d*4d*2d*d*4d*2d*d*3b1c*4d*x2c*c*3c*1c*2c*d*d*1d*d*2c#*c#*c#*c#*6d*2x2d*d*4d*2d*d*4d*2d*d*3b1c*4d*x2c*c*3c*1c*2c*d*d*1d*d*2abac*d*6x\0";
const char jingle_bells_bass[] PROGMEM =
    "2gggg6g1gg2gggg4cx2cccc8d2dddd4gx2gggg8g2gggg4c2xcccccdddddddd4gx2gg4g2gg4g2gg3g1g4gx2cc3c1c2ggg1gg2aaaa6d2x2gg4g2gg4g2gg3g1g4gx2cc3c1c2ggg1gg2ddddg6x\0";

const char silent_night_soprano[] PROGMEM =
    "3f1g2f6d3f1g2f6d4c*2c*6a4b'2b'6f4g2g3b'1a2g3f1g2f6d4g2g3b'1a2g3f1g2f6d4c*2c*3e'*1c*2a6b'd*2b'fd3f1e'2c8B'x\0";
const char silent_night_alto[] PROGMEM =
    "3d1e'2d6B'3d1e'2d6B'4e'2e'6e'4d2d6d4e'2e'3g1f2e'3d1e'2d6B'4e'2e'3g1f2e'3d1e'2d6B'4f2f3f1f2f6ff2B'fB'3A1A2A8B'x\0";
const char silent_night_tenor[] PROGMEM =
    "4f2f6f4f2f6f4a2a6c*4b'2b'6b'4b'2b'4b'2b'3b'1b'2b'6b'4b'2b'3b'1b'2b'3b'1b'2b'6b'4a2a3a1a2e'*6e'*b'4f2f3f1f2f8dx\0";
const char silent_night_bass[] PROGMEM =
    "4B'2B'6B'4B'2B'6B'4f2f6f4B'2B'6B'4e'2e'4e'2e'3B'1B'2B'6B'4e'2e'3e'1e'2e'3B'1B'2B'6B'4f2f3f1f2f6b'b'4d2B3F1F2F8Bx\0";

const char veselje_ti_navjescujem_soprano[] PROGMEM =
    "2ad*c#*b3a1b2ag1f#ef#g2ac#8d2ad*c#*b3a1b2ag1f#ef#g2ac#8d2f#aeef#aeea1ab2agf#1f#g2f#ea1ab2agf#1f#g2f#e3f#1g2f#e4de3f#1g2f#e8d\0";
const char veselje_ti_navjescujem_alto[] PROGMEM =
    "2f#1f#g2agf#gf#e2dcde2c#c#8A2f#1f#g2agf#gf#e2dcde2c#c#8A2f#d#Bc#f#d#Bc#ddc#edddc#ddc#edddc#3d1d2c#c#4B2Bc#3d1d2c#c#8A\0";
const char veselje_ti_navjescujem_tenor[] PROGMEM =
    "2d*aabc#*c#*1d*c#*2bbb3a1g8f#2d*aabc#*c#*1d*c#*2bbb3a1g8f#2a1ba2ga2a1ba2ga2f#1f#g2aa2a1ab2aa2f#1f#g2aaabba3a1b2ag4f#2ga3a1b2ag8f#\0";
const char veselje_ti_navjescujem_bass[] PROGMEM =
    "2ddf#gae1dd#2e2beaA8d2ddf#gae1dd#2e2beaA8d1dc#2Be1Ac#dc#2BeAf#f#Ac#dd1df#2addAc#1dc2BG#A3d1d2AA#4B2eA3d1G2AA8d\0";

const char u_to_vrijeme_godista_soprano[] PROGMEM =
    "4f2c4d2c4d2e4f2x4f2c4d2c4d2e4f2x2fga4b'2b'b'ag4a2xagf4g2ggfe4f2xfga4b'2b'b'ag4a2xagf4g2ggfe4f2x\0";
const char u_to_vrijeme_godista_alto[] PROGMEM =
    "6xx4B'2B4A2x4A2A4B'2B'4B'2B'4A2x6xx4B'2B4A2x4A2A4B'2B'4B'2B'4A2x2dcfgfe4d2e4f2x4c2d4B'2B'4c2c4f2x\02dcfgfe4d2e4f2x4c2d4B'2B'4c2c4f2x\0";

const char we_wish_you_a_merry_christmas_soprano[] PROGMEM =
    "3f1f4b'2b'c*b'a4gggc*2c*d*c*b'4affd*2d*e'*d*c*4b'g2ff4gc*a8b'4fb'b'b'8a4ab'ag8f4c*d*2c*c*b'b'4f*f2ff4gc*a8b'\0";
const char we_wish_you_a_merry_christmas_alto[] PROGMEM =
    "3f1f4f2de'ff4e'B'gg2efgg4fccd2f#gaa4gd2ffe'gf8f4ff2de'fg8a4f#gfe8f4a2ff#f#gg4af2ff4e'gf8f\0";
const char we_wish_you_a_merry_christmas_tenor[] PROGMEM =
    "3f1f4f2ffb'b'4b'gbc*2ggc*c*4c*aaa2aad*d*4d*b'2b'b'4b'e'*c*8d*2f*e'*d*c*b'c*d*e'*8f*4agc*2c*b'8a4f*f*2c*c*d*e'*4f*a2b'b'4b'2e'*d*4c*8d*\0";
const char we_wish_you_a_merry_christmas_bass[] PROGMEM =
    "3f1f4d2B'B'dd4e'e'ge2cce'e'4ffaf#2ddff4gg2dd4e'cf8B4fb'b'B'8f4dgc*c8f4fb'2aagg4f2fe'dd4e'cf8B'\0";

const char chessnuts_roasting_on_an_open_fire[] PROGMEM =
    "2e'e'*1d*c*b'a'gg6g2e'c*b'a'gf8e'x2e'e'1ffe'f2gb'c*3d*1c*2bb1d'*c*b'a'4b'1b'a'gf2e'e'*1d*c*b'a'gg6g2e'c*1b'a'gf8e'2e'e'f1e'f2gb'c*3d*1c*b'gc*b'3a'1e'4e'1xe'de'5d'*1c*b'a4b'1xe'de'd'*cd'*c*d'*c*b'a'4b'1xe'de'bb'3c*1b'a'g'5a'1g'a'g'f3f1ff2fff6f1xg2e'e'*2d*c*b'a'gg4g1xg2e'c*b'a'gf6e'1xd2e'1de'2f1e'f2g1b'c*2d*1e'*c*2b'4e'2f4e'x\0";

const char santa_claus_is_coming_to_town_soprano[] PROGMEM =
    "1fde'2f3f1f1ga2b'4b'1de'2fff1gf2e'4e'2dfB'dc4e'2A8B'\0";

const Song ALL_SONGS[NUM_SONGS] PROGMEM = {
    {
        // Adeste Fideles
        adeste_fideles_soprano,
        adeste_fideles_alto,
        adeste_fideles_tenor,
        adeste_fideles_bass,
    },
    {
        // Mehki snežek
        mehki_snezek_soprano,
    },
    {
        // First Noel
        first_noel_soprano,
        first_noel_alto,
        first_noel_tenor,
        first_noel_bass,
    },
    {
        // Jingle Bells
        jingle_bells_soprano,
        jingle_bells_alto,
        jingle_bells_tenor,
        jingle_bells_bass,
    },
    {
        // Silent Night
        silent_night_soprano,
        silent_night_alto,
        silent_night_tenor,
        silent_night_bass,
    },
    {
        // Veselje ti navješčujem
        veselje_ti_navjescujem_soprano,
        veselje_ti_navjescujem_alto,
        veselje_ti_navjescujem_tenor,
        veselje_ti_navjescujem_bass,
    },
    {
        // U to vrijeme godišta
        u_to_vrijeme_godista_soprano,
        u_to_vrijeme_godista_alto,
    },
    {
        // We Wish You a Merry Christmas
        we_wish_you_a_merry_christmas_soprano,
        we_wish_you_a_merry_christmas_alto,
        we_wish_you_a_merry_christmas_tenor,
        we_wish_you_a_merry_christmas_bass,
    },
    {
        // Chestnuts Roasting on an Open Fire
        chessnuts_roasting_on_an_open_fire,
    },
    {
        // Santa Claus is Coming to Town
        santa_claus_is_coming_to_town_soprano,
    },
};