#include <Callables.h>

void printTime() {
    Serial.println(millis());
}
VoidCallableVoid printTime_callable = VoidCallableVoid((VoidFunctionVoid)printTime);

void printTimeToStream(Stream* stream) {
    stream->println(millis());
}
VoidCallableAny printTimeToStream_callable = VoidCallableAny((VoidFunctionAny)printTimeToStream);

void setup() {
    Serial.begin(115200);
}

void loop() {
    printTime_callable.invoke();
    printTimeToStream.invoke(&Serial);
}