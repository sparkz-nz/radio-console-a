#include <Arduino.h>
#include <ArduinoLog.h>
#include "SerialProcessor.h"
#include "Buffer.h"

void printCmdList(Command* list);

SerialProcessor::SerialProcessor(Stream* serial):
    _serial(serial) {
        cmdProc.sp = this;
        resetLineProcessor();
}

/** --- checkSerial()
 * If a character is available it is read into the buffer
 * If end of line, then process the line with the current line processor
*/
void SerialProcessor::checkSerial() {
    if (read()) {
        currentLineProc->processLine(&_buffer);
        _buffer.Clear();
    }
}

/** --- read
 * reads a character if available into the buffer, returns true on newline 
*/
bool SerialProcessor::read() {
    if (_serial->available()) {
        char c = _serial->read();

        // if CR the check if next is LF or change to LF to signal eol
        if (c == '\r') {
            if (_serial->peek() == '\n') {
                _serial->read();
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

/** --- CmdProc::processLine
 * Default command processor for top level commands.
 * Calls the user supplied callback for the command.
*/
void CmdProc::processLine(Buffer *buffer) {
    // walk through commandList and compare to start of buffer
    // if found, call the callback for that command with the buffer as a parameter
    Log.trace(F("CmdProc::processCommands - buffer: '%s'" CR), buffer->getBuffer());
    if (buffer->GetNext() == 'c') {
        Log.trace(F("Found 'c', switching to config" CR));
        sp->setLineProcessor(sp->commandList->processor);
    }
};

/** --- registerCommand
 * Adds a command to the commands linked list
*/
void SerialProcessor::registerCommand(const char* command, CommandLineProcessor* cmdLineProc) {
    struct Command *cmd = new Command {command, cmdLineProc, NULL};
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
        Log.trace(F("'%s' [%X]" CR), current->cmdString, current->next);
        current = current->next;
        delay(50);
    } while (current != NULL && i++ < 10);
}

void SerialProcessor::setLineProcessor(CommandLineProcessor* lineProc) {
    currentLineProc = lineProc;
}

void SerialProcessor::resetLineProcessor() {
    currentLineProc = (CommandLineProcessor*)&cmdProc;
    Log.trace(F("currentLineProcessor has been reset to cmdProc" CR));
}

void SerialProcessor::debug() {

    Log.trace("debug - Buffer: %s" CR, _buffer.getBuffer());
    _buffer.Clear();
}
