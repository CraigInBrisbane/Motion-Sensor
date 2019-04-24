#include "Buzzer.h"
#include "FadingLED.h"

// Pins being used by devices.
int LED1_PIN =          10;
int LED2_PIN =          9;
int PIR_PIN =           4;
int BUZZER_PIN =        A0;
int SILENT_LED_PIN =    2;
int SILENT_BUTTON_PIN = 3; // Interrupt pin on UNO so....
int SILENT_BOTTON_INTERRUPT = 1; // Pin 3 = Interrupt 1. If using Pin 2, then Interrupt is 0.

// Instantiate the objects
FadingLED   LED_1;
FadingLED   LED_2;
Buzzer      buzzer;

// Setup global variables.
bool AllStill           = true;
volatile bool isSilent  = false; // Store if the board is in silent state. Also, volatile as it's handled via an ISR

void setup() {
   
    // Initialise the two LEDs and the Buzzer.
    LED_1.Init(LED1_PIN, 500, 0);
    LED_2.Init(LED2_PIN, 500, 250);
    buzzer.Init(BUZZER_PIN);

    // Set the PIR, Silent LED indicator and the Silent button pin mode.
    pinMode(PIR_PIN, INPUT);
    pinMode(SILENT_LED_PIN, OUTPUT);
    pinMode(SILENT_BUTTON_PIN, INPUT);

    // Setup an Interrupt for the Button.
    attachInterrupt(SILENT_BOTTON_INTERRUPT, handleButtonStateISR, RISING); // Attach an Interrup to the button press pin.

    // Quick Hello!
    SayHello(5);   
}

/*
 * Method to test of movement has been detected.
 */
bool CheckMovement() {
    // Read the pin value.
    int val = digitalRead(PIR_PIN);
    
    // Has a new movement been detected?
    if(val==true && AllStill==true) {
        if(isSilent==false)
          buzzer.Beep(160, 1500);
        AllStill = false;
    } 
    AllStill = !val; // All still is false if we have movement.
    return val != 0;    
}

/*
 * Method just to show the board is alive. It flashes the LEDs, and makes one beep.
 */
void SayHello(int flashes) {
    int i = 0;
    tone(BUZZER_PIN, 4000);
    
    while(i < flashes) {
      i++;     
      digitalWrite(LED1_PIN, HIGH);
      digitalWrite(LED2_PIN, HIGH);
      digitalWrite(SILENT_LED_PIN, HIGH);
      delay(30);
      noTone(BUZZER_PIN);
      digitalWrite(LED1_PIN, LOW);
      digitalWrite(LED2_PIN, LOW);
      digitalWrite(SILENT_LED_PIN, LOW);
      delay(30);
    }
}

void loop() {
   // Check for moment.
    bool val = CheckMovement();
    // Update connected devices.
    LED_1.Update(val);
    LED_2.Update(val);
    buzzer.Update();
    digitalWrite(SILENT_LED_PIN, isSilent);
}
/*
 * ISR - Togle the silent mode.
 */
void handleButtonStateISR() {
  isSilent = !isSilent;
}
