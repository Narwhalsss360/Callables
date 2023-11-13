#include <Callables.h>

#define BAUDRATE 115200

String transformCharacters(const String& string, Invokable<char, char>& transformer) {
    String result;
    for (int i = 0; i < string.length(); i++) {
        result += transformer(string[i]);
    }
    return result;
}

//Function that takes in a character and transforms into its uppercase form.
char c_toupper(char character)
{
    return toupper(character);
}

//Function that takes in a character and transforms into its other case form.
char swapCase(char character)
{
    if ('A' <= character && character <= 'Z')
        return character + 32;
    else if ('a' <= character && character <= 'z')
        return character - 32;
    return character;
}

//Function invokable
Function<char, char> swapCase_Function = Function<char, char>(swapCase);

void setup() {
    Serial.begin(BAUDRATE);
    String myString = F("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.");

    String result = transformCharacters(myString, invokable_get(c_toupper));
    Serial.println(result);

    result = transformCharacters(myString, swapCase_Function);
    Serial.println(result);
}

void loop() {

}