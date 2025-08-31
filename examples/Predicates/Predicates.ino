#include <Callables.h>

#define BAUDRATE 115200

// Say that a `Predicate` is just any invokable that may take any args but returns bool, is reference for easier use.
template <typename... Args>
using Predicate = Invokable<bool, Args...>&;

bool c_isupper(char c)
{
    if ('A' <= c && c <= 'Z')
        return true;
    return false;
}

bool c_islower(char c)
{
    if ('a' <= c && c <= 'z')
        return true;
    return false;
}

//Chose whether you want to use c_isupper, c_islower or your own predicate that takes in one char
Predicate<char> predicate = Predicate<char>(c_isupper);

//Name of predicate, for printing purposes
String predicateName = "c_isupper"; 

void setup() {
    Serial.begin(BAUDRATE);
}

void loop() {
    while (Serial.available()) {
        int read = Serial.read();

        //Make sure we actually read a character!
        if (read == EOF)
            break;

        char c = (char)read;
        Serial.print("Using predicate ");
        Serial.print(predicateName);
        Serial.print(" on character ");
        Serial.print(c);
        Serial.print(" returns: ");
        Serial.println(predicate(c));
    }
}
