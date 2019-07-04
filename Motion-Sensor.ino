#include "ArduinoDeviceLibraries/Buzzer.h"
#include "ArduinoDeviceLibraries/FadingLED.h"

// Pins being used by devices.
int LED1_PIN =          0;
int LED2_PIN =          1;
int SILENT_LED_PIN =    2;
int PIR_PIN =           3;
int BUZZER_PIN =        A5;
int SILENT_BUTTON_PIN = 4; // Interrupt pin on UNO so....
int SILENT_BOTTON_INTERRUPT = SILENT_BUTTON_PIN; // Pin 3 = Interrupt 1. If using Pin 2, then Interrupt is 0.
int PIR_INTERRUPT = PIR_PIN; 

// Instantiate the objects
FadingLed   LED_1;
FadingLed   LED_2;
Buzzer      buzzer;

// Setup global variables.
volatile bool AllStill  = true;
volatile bool isSilent  = false; // Store if the board is in silent state. Also, volatile as it's handled via an ISR

void setup() {
   
    // Initialise the two LEDs and the Buzzer.
    LED_1.Init(LED1_PIN, 500, 0, false);
    LED_2.Init(LED2_PIN, 500, 250, false);
    buzzer.Init(BUZZER_PIN);

    // Set the PIR, Silent LED indicator and the Silent button pin mode.
    pinMode(PIR_PIN, INPUT);
    pinMode(SILENT_LED_PIN, OUTPUT);
    pinMode(SILENT_BUTTON_PIN, INPUT);

    // Setup an Interrupt for the Button.
    attachInterrupt(SILENT_BOTTON_INTERRUPT, handleButtonStateISR, RISING); // Attach an Interrup to the button press pin.
    attachInterrupt(PIR_INTERRUPT, handleMovementISR, CHANGE);

    // Quick Hello!
    SayHello(5);   
}

/*
 * Method just to show the board is alive. It flashes the LEDs, and makes one beep.
 */
void SayHello(int flashes) {
    int i = 0;
    
    while(i < flashes) {
      i++;     
      tone(BUZZER_PIN, 4000);
      digitalWrite(LED1_PIN, HIGH);
      digitalWrite(LED2_PIN, HIGH);
      digitalWrite(SILENT_LED_PIN, HIGH);
      delay(20);
      noTone(BUZZER_PIN);
      digitalWrite(LED1_PIN, LOW);
      digitalWrite(LED2_PIN, LOW);
      digitalWrite(SILENT_LED_PIN, LOW);
      delay(20);
    }
}

void loop() {
    // Update connected devices.
    LED_1.Update(AllStill==false);
    LED_2.Update(AllStill==false);
    buzzer.Update();
    digitalWrite(SILENT_LED_PIN, isSilent);
}

/*
 * ISR - Togle the silent mode.
 */
void handleButtonStateISR() {
//    Particle.publish("EVENT", "Button pressed", PUBLIC);    
 
    isSilent = !isSilent;
    if(isSilent == false)
        buzzer.Beep(30, 1500);
 
}

/*
    ISR to monitor movement PIR for any changes in state.
*/
void handleMovementISR() {
    int PIRValue = digitalRead(PIR_PIN);
    // If we went from a still state, and detected a movement...
    if(AllStill && PIRValue) {
        if(isSilent==false) {
            buzzer.Beep(160, 1500);
        }
    } 
    AllStill = PIRValue==LOW; // All still is false if we have movement.
}
