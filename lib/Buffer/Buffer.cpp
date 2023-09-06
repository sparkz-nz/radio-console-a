#include <Arduino.h>
#include <ArduinoLog.h>
#include "Buffer.h"

Buffer::Buffer() {
    Clear();
}

void Buffer::Clear() {
    _buffer[0] = '\0';  // pointer to start of buffer array
    _index = 0;         // current position for reading through
    _end = 0;           // index of null terminator
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

char* Buffer::getBuffer() {
    return _buffer;
}

bool Buffer::AtEnd() {
    return (_buffer[_index] == NULL);
}

bool Buffer::Delete() {
    if (_end > 0) {
        _buffer[--_end] = '\0';
        return true;
    }
    return false;
}

int Buffer::SetIndex(int index) {
    if (index <= _end) {
        _index = index;
    }
    else {
        _index = _end;
    }
    return _index;
}

char Buffer::PeekNext() {
    return(_buffer[_index]);
}

int Buffer::GetIndex() {
    return _index;
}