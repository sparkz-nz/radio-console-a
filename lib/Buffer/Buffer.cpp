#include <Arduino.h>
#include <ArduinoLog.h>
#include "Buffer.h"

Buffer::Buffer() {
    Clear();
}

void Buffer::Clear() {
    _buffer[0] = '\0';
    _index = 0;
    _end = 0;
}

void Buffer::AddChar(char c) {
    if (_end < BUFFERSIZE) {
        _buffer[_end] = c;
        _buffer[++_end] = '\0';
    }
}

char Buffer::GetNext() {
    if (_buffer[_index] != '\0') {
        return _buffer[_index++];
    }
    return '\0';
}

char Buffer::GetFirst() {
    _index = 0;
    return GetNext();
}