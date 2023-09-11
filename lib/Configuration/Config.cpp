#include <Arduino.h>
#include <ArduinoLog.h>
#include <EEPROM.h>
#include <Buffer.h>
#include <Config.h>


enum SwitchTypes {
    None, Switch, Encoder
};

struct TokenizedLine {
    SwitchTypes switchType;
    int switchNumber;
    SwitchResponse response[2];
};

void FlushUntilEOL();
char ParseKeycode(char c);
char parseEscapeSequence(Buffer* buffer);
TokenizedLine tokenizeLine(Buffer* buffer);

void Configuration::save() {
  EEPROM.put(EEPROM_CONFIG_ADDR, modes);
}

void Configuration::recall() {
  EEPROM.get(EEPROM_CONFIG_ADDR, modes);
}

void Configuration::processLine(Buffer *buffer) {
    if (buffer->atEnd()) {
        Log.error(F("Config line processor - no data" CR));
        return;
    }

    tokenizeLine(buffer);


}

void Configuration::clearConfig() {

}

TokenizedLine tokenizeLine(Buffer* buffer) {
    TokenizedLine result;

    // first character - switch type s or e
    switch (buffer->getNext()) {
        case 's':
        case 'S':
            result.switchType = Switch;
            Log.trace(F("Found s" CR));
            break;

        case 'e':
        case 'E':
            result.switchType = Encoder;
            Log.trace(F("Found e" CR));
            break;
        
        default:
            result.switchType = None;
            Log.error(F("Invalid switch type in line '%s'" CR), buffer->getBuffer());
            return result;
    }

    // next one or two chars - switch number
    if (isdigit(buffer->peekNext())) {
        result.switchNumber = buffer->parseInt();
        Log.trace(F("Found number %d" CR), result.switchNumber);
    }
    else {
        result.switchType = None;
        Log.error(F("Invalid switch number in line '%s'" CR), buffer->getBuffer());
        return result;
    }
    
    // expect : next
    if (buffer->getNext() != ':') {
        result.switchType = None;
        Log.error(F("Expected : in line '%s'" CR), buffer->getBuffer());
        return result;
    }

    // next is the char or an escape sequence
    char c = buffer->getNext();
    if (c == '\\') c = parseEscapeSequence(buffer);
    Log.trace(F("character %X" CR), c);
    

    return result;
}

char parseEscapeSequence(Buffer* buffer) {
    int startIndex = buffer->getIndex();
    char nextChar;
    // walk the buffer looking for '\'
    do {
        nextChar = buffer->getNext();
    } while (nextChar != '\\' && nextChar != '\0');

    if (nextChar == '\0') return nextChar;

    
}

char searchStringTable(char* charBuf, int len) {
    int i = 0;
    int val = -1;
    bool found = false;
    do {
        found = (strncmp_P(charBuf, (const char*)pgm_read_word(&(stringTable[i])), len) == 0);
        val = pgm_read_byte(&keycodeTable[i]);
        if (found) {
            Log.trace(F("Found string in string table at index %d, keycode %X" CR), i, val);
        }
    } while (!found && val != 0);
    return val;
}


void parseAction(Buffer* buffer) {
    char* start = buffer->getBuffer() + buffer->getIndex();
    Log.trace(F(""));
}




// old implememntation

void AddConfig(SwitchTypes switchType) {
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