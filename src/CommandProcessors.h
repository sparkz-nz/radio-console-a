#include <Arduino.h>
#include <ArduinoLog.h>
#include <SerialProcessor.h>




class ConfigCmdProcessor : public CommandLineProcessor {
    public:
        ConfigCmdProcessor(SerialProcessor *serialProc) : CommandLineProcessor(serialProc) {}

        void processLine(Buffer* buffer) {
            Log.trace(F("configCmdProcessor::processLine buffer='%s'" CR), buffer->getBuffer());
            
            // when all done reset processor 
            if (buffer->AtEnd()) {
                sp->resetLineProcessor();
                Log.trace(F("configCmdProcessor::processLine - buffer empty, resetting back to cmdProc" CR));
                }
        };
};
