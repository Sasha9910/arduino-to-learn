#include <Arduino.h>

String letters[] = { "a", "b", "c"};
float values[3];

void setup() {
    Serial.begin(9600);
    while(!Serial);
}

void loop() {
    for(int i = 0; i < 3; i++) {
        Serial.println(String("Introduce ") + letters[i] + ":");
        while(Serial.available() == 0);
        values[i] = Serial.readStringUntil('\n').toFloat();
        while(Serial.available() > 0) Serial.read();
    }
    for (int i = 0; i < 3; i++) {
        sqrtValues(values[i]);
    }
    Serial.println("Type 'exit' to stop or press Enter to insert new values.");
    String order = Serial.readStringUntil('\n');
    if (order == "exit") { break; }
    while(Serial.available() > 0) Serial.read();
}

float sqrtValues(float number) {
    if (number < 0) {
        Serial.println("Cannot compute square root of a negative number");
    }
    float result = sqrt(number);
    Serial.print("Square root: ");
    Serial.println(result, 2);
    return result;
}