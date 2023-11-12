#include <Callables.h>

void printTime() {
    Serial.println(millis());
}

void printTimeToStream(Stream* stream) {
    stream->println(millis());
}

void setup() {
    Serial.begin(115200);
}

void loop() {
    Function<void> printTimeFunc = Function<void>(printTime);
    Function<void, Stream*> printTimeToStreamFunc = Function<void, Stream*>(printTimeToStream);

    if (printTimeFunc.valid())
        printTimeFunc.invoke();

    if (printTimeToStreamFunc)
        printTimeToStreamFunc(&Serial);
}