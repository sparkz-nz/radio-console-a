#include <Arduino.h>
#include "Keyboard.h"

/*
struct keycode {
    char keyName[6];
    byte keyValue;
};

const keycode kc_LC PROGMEM = {"LC\0", KEY_LEFT_CTRL};
const keycode kc_LS PROGMEM = {"LS\0", KEY_LEFT_SHIFT};
const keycode kc_LA PROGMEM = {"LA\0", KEY_LEFT_ALT};
const keycode kc_LG PROGMEM = {"LG", KEY_LEFT_GUI};
const keycode kc_RC PROGMEM = {"RC", KEY_RIGHT_CTRL};
const keycode kc_RS PROGMEM = {"RS", KEY_RIGHT_SHIFT};
const keycode kc_RA PROGMEM = {"RA", KEY_RIGHT_ALT};
const keycode kc_RG PROGMEM = {"RG", KEY_RIGHT_GUI};
const keycode kc_END PROGMEM = {"END", 0};
*/

const char s_LC[] PROGMEM = "LC\0";
const char s_LS[] PROGMEM = "LS\0";
const char s_LA[] PROGMEM = "LA\0";
const char s_LG[] PROGMEM = "LG";
const char s_RC[] PROGMEM = "RC";
const char s_RS[] PROGMEM = "RS";
const char s_RA[] PROGMEM = "RA";
const char s_RG[] PROGMEM = "RG";
const char s_END[] PROGMEM = "END";

const byte kc_LC PROGMEM = KEY_LEFT_CTRL;
const byte kc_LS PROGMEM = KEY_LEFT_SHIFT;
const byte kc_LA PROGMEM = KEY_LEFT_ALT;
const byte kc_LG PROGMEM = KEY_LEFT_GUI;
const byte kc_RC PROGMEM = KEY_RIGHT_CTRL;
const byte kc_RS PROGMEM = KEY_RIGHT_SHIFT;
const byte kc_RA PROGMEM = KEY_RIGHT_ALT;
const byte kc_RG PROGMEM = KEY_RIGHT_GUI;
const byte kc_END PROGMEM = 0;



const char* const stringTable[] PROGMEM = {s_LC, s_LS, s_LA, s_LG, s_RC, s_RS, s_RA, s_RG, s_END};
const byte keycodeTable[] PROGMEM = {kc_LC, kc_LS, kc_LA, kc_LG, kc_RC, kc_RS, kc_RA, kc_RG, kc_END};