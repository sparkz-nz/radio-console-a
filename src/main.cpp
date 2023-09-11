#include <Arduino.h>
#include <ArduinoLog.h>
#include "Keyboard.h"
#include <Config.h>
#include <SerialProcessor.h>
#include "CommandProcessors.h"

#define SERIAL_BAUD 9600

char buffer[6];
Configuration config;
SerialProcessor sp(&Serial);
ConfigCmdProcessor configCmdProc(&sp);
SaveCmdProcessor saveCmdProc(&sp);

void printMsg();
void test();

void setup() {
  Serial.begin(SERIAL_BAUD);
  while (!Serial);
  Log.begin(LOG_LEVEL_VERBOSE, &Serial, false);
  Log.trace("Starting..." CR);

  sp.registerCommand("config", &configCmdProc);
  sp.registerCommand("save", &saveCmdProc);

  test();
}

void loop() {

  sp.checkSerial();

}

/*
  int i = 0;
  byte val = 0;

  do {
    Log.trace("Starting loop" CR);
    Log.trace("... %s" CR);
    strcpy_P(buffer, (const char*)pgm_read_word(&(stringTable[i])));
    val = pgm_read_byte(&keycodeTable[i]);
    Log.trace("buffer %s, value %X" CR, buffer, val);
    i++;
  } while (val > 0 || i < 3);

*/

void printMsg() {
  Log.trace("I got called" CR);
}

void test() {
  Buffer buf;
  buf.addString("s1:aLS");
  Log.trace(F("Testing '%s'" CR), buf.getBuffer());

  config.processLine(&buf);

}
