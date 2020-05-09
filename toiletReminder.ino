#include "Arduino.h"
#include "NewPing.h"

#define HCSR04_PIN_TRIG	3
#define HCSR04_PIN_ECHO	2
#define ISD1820_PIN_PLAY 4

#define BOY_DISTANCE 60

NewPing hcsr04(HCSR04_PIN_TRIG,HCSR04_PIN_ECHO);

void setup() 
{
    //Serial.begin(9600);
    //while (!Serial);
    //Serial.println("start");
    pinMode(ISD1820_PIN_PLAY, OUTPUT);
}

void loop() 
{
    // waiting for boy to come
    int distance = hcsr04.ping_cm();
    //Serial.print(F("Distance: "));
    //Serial.print(distance);
    //Serial.println(F("[cm]"));

    // boy is close to toilet
    if (distance < BOY_DISTANCE) {
      
        // wait for boy to leave
        while (distance < BOY_DISTANCE) {
            distance = hcsr04.ping_cm();
            delay(1000);
        }
        
        // boy has left
        playReminder();
    }
    delay(2000);
}

void playReminder() {
    digitalWrite(ISD1820_PIN_PLAY, HIGH);
    // shut play pin (but continue play)
    delay(100);
    digitalWrite(ISD1820_PIN_PLAY, LOW);
    // wait until play is over
    delay(2000);
}
