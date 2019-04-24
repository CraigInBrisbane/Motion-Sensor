#include "Buzzer.h"
#include "FadingLED.h"

// Pins being used by devices.
int LED1_PIN = 4;
int LED2_PIN = 3;
int PIR_PIN = 6;
int BUZZER_PIN = 5;

// Instantiate the objects
FadingLED LED_1;
FadingLED LED_2;
Buzzer buzzer;

// Setup global variables.
bool AllStill = true;

// Setup.
void setup() {
    // Initialise the two LEDs
    LED_1.Init(LED1_PIN, 500, 0);
    LED_2.Init(LED2_PIN, 500, 250);
    buzzer.Init(BUZZER_PIN);
    // Set the PIR pinmode.
    pinMode(PIR_PIN, INPUT);
    buzzer.Beep(40, 1500);
}

// Function to check if movement has been detected.
bool CheckMovement() {
    // Read the pin value.
    int val = digitalRead(PIR_PIN);
    
    // Has a new movement been detected?
    if(val==true && AllStill==true) {
        buzzer.Beep(160, 1500);
        AllStill = false;
    } 
    AllStill = !val; // All still is false if we have movement.
    return val != 0;    
}


void loop() {
    // Check for moment.
    bool val = CheckMovement();
    // Update connected devices.
    LED_1.Update(val);
    LED_2.Update(val);
    buzzer.Update();
}
