#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include "KeyMap.h"

#define LEFTSHIFT  0b00100000
#define LEFTCTRL   0b00010000
#define LEFTALT    0b00001000
#define RIGHTSHIFT 0b00000100
#define RIGHTCTRL  0b00000010
#define RIGHTALT   0b00000001

#define NUMENCODERS 4
#define NUMSWITCHES 8
#define NUMMODES    5

#define EEPROM_CONFIG_ADDR 0x300


struct SwitchConfig {
  char character;
  byte modifiers;
};

struct Mode {
  SwitchConfig encoders[NUMENCODERS];
  SwitchConfig switches[NUMSWITCHES];
};

class Configuration {
  public:
    Mode Modes[NUMMODES];
    void Save();
    void Recall();
    void ReadFromSerial();
    void ClearConfig();

  private:
    enum SwitchTypes {
      Switch, Encoder
    };
    void AddConfig(SwitchTypes switchType);

};

#endif