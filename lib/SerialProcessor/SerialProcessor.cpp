#include <Arduino.h>
#include <ArduinoLog.h>
#include "SerialProcessor.h"
#include "Buffer.h"

void processLine();
void printCmdList(Command* list);

SerialProcessor::SerialProcessor(Stream* serial) {
    _serial = serial;
    processPtr = &this->processCommands;
}

/** --- checkSerial()
 * If a character is available it is read into the buffer, and if it is \n then processLine() is called
*/
void SerialProcessor::checkSerial() {
    if (read()) processLine();
}

bool SerialProcessor::read() {
    if (_serial.available()) {
        char c = _serial.read();

        // if CR the check if next is LF or change to LF to signal eol
        if (c == '\r') {
            if (_serial.peek() == '\n') {
                _serial.read();
            }
            c='\n';
        }

        if (c == '\n') {
            return true; // end of line
        }
        else {
            _buffer.AddChar(c);
        }
    }
    return false;
}

/** --- processLine
 * Called after a complete line is read - calls whatever function processPtr is pointing at.
 * Initially processPtr points to the inbuilt processCommands() function, but when a command
 * is recognised this is updated to point to the user supplied callback for that command.
*/
void SerialProcessor::processLine() {
    processPtr();
}

/** --- processCommands
 * Default command processor for top level commands.
 * Calls the user supplied callback for the command.
*/
void SerialProcessor::processCommands() {
    // walk through commandList and compare to start of buffer
    // if found, call the callback for that command with the buffer as a parameter
    Log.trace("processCommands" CR);
    Command* current = this->commandList;

}

/** --- registerCommand
 * Adds a command to the commands linked list
*/
void SerialProcessor::registerCommand(const char* command, void(*callback)(Buffer*)) {
    struct Command *cmd = new Command {command, callback, NULL};
    if (commandList == NULL) {
        commandList = cmd;
    }
    else {
        Command* current = commandList;
        while (current->next != NULL ) {
            current = current->next;
            }
        current->next = cmd;
        current = cmd;
    }
}

void printCmdList(Command* list){
    Command* current = list;
    int i = 0;
    do {
        Log.trace(F("'%s' [%X] [%X]" CR), current->cmdString, current->handler, current->next);
        current = current->next;
        delay(50);
    } while (current != NULL && i++ < 10);
}

void SerialProcessor::setLineProcessor(void (*lineProcessor)(char *))
{
}

void SerialProcessor::resetLineProcessor()
{
}

void SerialProcessor::debug() {
    processPtr();
    /*
    char str[80];
    char c;
    int i = 0;
    do {
        c = _buffer.GetNext();
        str[i++] = c;
        //Log.trace("[%c,%d]", c,i);
    } while (c != '\0');

    Log.trace("Buffer: %s" CR, str);
    _buffer.Clear();*/
}
