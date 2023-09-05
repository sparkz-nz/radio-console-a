#include <Arduino.h>
#include <ArduinoLog.h>
#include <EEPROM.h>
#include "Config.h"

void FlushUntilEOL();
char ParseKeycode(char c);

void Configuration::Save() {
  EEPROM.put(EEPROM_CONFIG_ADDR, Modes);
}

void Configuration::Recall() {
  EEPROM.get(EEPROM_CONFIG_ADDR, Modes);
}

void Configuration::ReadFromSerial() {
    if (!Serial.available()) {
        Log.error(F("Reading configuration from serial - no data available" CR));
        return;
    }

    int lineNo, charNo;

    while (Serial.available()) {
        char c = Serial.read();
        lineNo++; charNo++;

        switch (c) {
            case 'c': // Clear current configuration
            case 'C':
                ClearConfig();
                break;
            
            case 's': // switch definition
            case 'S':
                break;

            case 'e': // encoder definition
            case 'E':
                break;

            default:
                Log.error(F("Configuration.ReadFromSerial line %d character %d '%c'" CR), lineNo, charNo, c);
                break;
        }

    }
    Log.trace(F("[ReadFromSerial] No more serial available" CR));

}

void Configuration::ClearConfig() {

}

void Configuration::AddConfig(SwitchTypes switchType) {
    int numSwitches;
    char switchChar;
    if (switchType == Switch) {
        numSwitches = NUMSWITCHES;
        switchChar = 'S';
    }
    else {
        numSwitches = NUMENCODERS;
        switchChar = 'E';
    }

    // get the switch number
    int switchNumber = Serial.parseInt(SKIP_NONE);
    if (switchNumber < 1 || switchNumber > numSwitches) {
        Log.error(F("Invalid switch number %c%d" CR), switchChar, switchNumber);
        FlushUntilEOL();
        return;
    }

    // next char should be a :
    if (Serial.read() != ':') {
        Log.error(F("Expected ':' after switch identifier %c%d" CR), switchChar, switchNumber);
        FlushUntilEOL();
        return;
    }

    // next char is a key or '\'
    char c = Serial.read();
    switch (c) {
        case '\0': // timed out
            Log.error(F("Timed out after ':'" CR));
            return;
        case '\\': // macro string to follow
            c = ParseKeycode(c);
            if (c == '\0') {
                FlushUntilEOL();
                return;
            }
            break;
    }

    Log.trace(F("Keycode %X" CR), c);

    //char keyChar = Serial.read();
    //if (keyChar != ',') //Keyboard.press('A');


}

void FlushUntilEOL() {
    while (Serial.available()) {
        char b = Serial.read();
        if (b == '\n') break;
    }
}

char ParseKeycode(char c) {
    return '\0';
}