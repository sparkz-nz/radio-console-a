#ifndef BUFFER_H
#define BUFFER_H

#include <Arduino.h>
#include <ArduinoLog.h>

#define BUFFERSIZE 80

class Buffer {
    public:
        Buffer();
        void AddChar(char c);
        char GetNext();
        char GetFirst();
        int ParseInt();
        void Clear();
        bool AtEnd();
        char* getBuffer();
        bool Delete();

    private:
        char _buffer[BUFFERSIZE + 1];
        int _index = 0;
        int _end = 0;

};


#endif