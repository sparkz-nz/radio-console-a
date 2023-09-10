#include <Arduino.h>
#include <ArduinoLog.h>
#include <SerialProcessor.h>




class ConfigCmdProcessor : public CommandLineProcessor {
    public:
        ConfigCmdProcessor(SerialProcessor *serialProc) : CommandLineProcessor(serialProc) {}

        void processLine(Buffer* buffer) {
            Log.trace(F("configCmdProcessor::processLine buffer='%s'" CR), buffer->getBuffer());
            
            // when all done reset processor 
            if (buffer->atEnd()) {
                serProc->resetLineProcessor();
                Log.trace(F("configCmdProcessor::processLine - buffer empty, resetting back to cmdProc" CR));
                }
        };
};

class SaveCmdProcessor : public CommandLineProcessor {
    public:
        SaveCmdProcessor(SerialProcessor *serialProc) : CommandLineProcessor(serialProc) {}

        void initProcess(Buffer* buffer) override {
            Log.trace(F("Saving to %s and returning to cmdProc" CR), buffer->getBuffer() + buffer->getIndex());
            serProc->resetLineProcessor();
        }

        void processLine(Buffer* buffer) {
            Log.trace(F("SaveCmdProcessor::processLine buffer='%s'" CR), buffer->getBuffer());
            // when all done reset processor 
            if (buffer->atEnd()) {
                serProc->resetLineProcessor();
                Log.trace(F("SaveCmdProcessor::processLine - buffer empty, resetting back to cmdProc" CR));
                }
        }
};