#include <Arduino.h>

String letters[] = { "a", "b", "c"};
float values[3];


void setup() {
    Serial.begin(9600);
    while(!Serial);
    for(int i = 0; i < 3; i++) {
        Serial.println(String("Introduce ") + letters[i] + ":");
        while(Serial.available() == 0);
        values[i] = Serial.readStringUntil('\n').toFloat();
        while(Serial.available() > 0) Serial.read();
    }
    solveQuadratic(values[0], values[1], values[2]);
}

float disc(float a, float b, float c) {
    return (b*b) - (4*a*c);
}

float solveQuadratic(float a, float b, float c) {
    float discriminant = disc(a, b, c);
    if (discriminant < 0) {
        Serial.println("No real roots");
        return -1;
    }
    else if (discriminant == 0) {
        float midCalc = sqrt(discriminant);
        float root = (-b + midCalc) / (2*a);
        Serial.print("One real root: ");
        Serial.println(root, 2);  
    }
    else {
        float midCalc = sqrt(discriminant);
        float root1 = (-b + midCalc) / (2*a);
        float root2 = (-b - midCalc) / (2*a);
        Serial.print("Roots: ");
        Serial.print(root1, 2);  
        Serial.print(", ");
        Serial.println(root2, 2);
    }

    return 0;
}

void loop() {
    // Nothing here
}