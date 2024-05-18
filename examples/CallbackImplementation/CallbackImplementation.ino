#include <Callables.h>

#define BAUDRATE 115200

class SomeClass
{
public:
    void streamReceived() {
        //Do anything...
    }
};

void myFunction() {
    //Do anything...
}

SomeClass instance;

//Both derive from abstract class Invokable. Get these by reference for support for either.
Function<void> streamReceivedGlobalFunction = Function_Infered(myFunction);
Method<SomeClass, void> streamReceivedSomeClassMethod = Method_Infered(&instance, &SomeClass::streamReceived);

void setup() {
    Serial.begin(BAUDRATE);
}

void loop() {
    if (Serial.available())
    {
        if (invokable_verify(&streamReceivedGlobalFunction))
            streamReceivedGlobalFunction.invoke();
        if (invokable_verify(&streamReceivedSomeClassMethod))
            streamReceivedSomeClassMethod();
    }
}