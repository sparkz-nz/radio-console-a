#ifndef SERIALPROCESSOR_H
#define SERIALPROCESSOR_H

#include <Arduino.h>
#include <ArduinoLog.h>
#include "Buffer.h"

struct Command {
    const char* cmdString;
    void(*handler)(Buffer*);
    Command* next;
};

class CommandLineProcessor {
    public:
        virtual void processLine(Buffer* buffer);
    private:
}

class SerialProcessor : CommandLineProcessor {
    public:
        SerialProcessor(Stream* serial);
        //SerialProcessor(Serial_& serial) : _serial(serial), processPtr(&processCommands) {};
        void checkSerial();
        bool read();
        void debug();
        void registerCommand(const char* command, void(*callback)(Buffer*));
        void setLineProcessor(void (*lineProcessor)(char*));
        void resetLineProcessor();


    private:
        Buffer _buffer;
        Stream *_serial;
        CommandLineProcessor * processCommands();
        //static void processCommands();
        CommandLineProcessor processLine();
        //void(*processPtr)();
        Command* commandList = NULL;

        class CmdProc : CommandLineProcessor {
            public:
                void processLine(Buffer* buffer);
        };

        CmdProc* cmdProc;

};



struct KeyPtr {
    char kkey[10];
};

#endif