
/*
 * Three LED Frequency Modulation Prototype
 *
 * Flashes three LEDs at different frequencies.
 * Intended as a precursor to a 3-wavelength
 * blood oximeter using Frequency Division Multiplexing (FDM).
 */

#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);

#define RED_LED D8
#define GREEN_LED D7
#define BLUE_LED A0

SerialLogHandler logHandler(LOG_LEVEL_INFO);

// LED frequencies in Hz
const float RED_FREQ = 1.0;
const float GREEN_FREQ = 2.0;
const float BLUE_FREQ = 5.0;

// Half-periods in milliseconds (50% duty cycle)
const unsigned long RED_INTERVAL = 500;
const unsigned long GREEN_INTERVAL = 250;
const unsigned long BLUE_INTERVAL = 100;

// Track previous toggle times
unsigned long redPrevious = 0;
unsigned long greenPrevious = 0;
unsigned long bluePrevious = 0;

// Track LED states
bool redState = LOW;
bool greenState = LOW;
bool blueState = LOW;

void setup() {
    pinMode(RED_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(BLUE_LED, OUTPUT);

    // Start with all LEDs off
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
}

void loop() {
    unsigned long currentTime = millis();

    // RED LED - 1 Hz
    if (currentTime - redPrevious >= RED_INTERVAL) {
        redPrevious = currentTime;
        redState = !redState;
        digitalWrite(RED_LED, redState);
    }

    // GREEN LED - 2 Hz
    if (currentTime - greenPrevious >= GREEN_INTERVAL) {
        greenPrevious = currentTime;
        greenState = !greenState;
        digitalWrite(GREEN_LED, greenState);
    }

    // BLUE LED - 5 Hz
    if (currentTime - bluePrevious >= BLUE_INTERVAL) {
        bluePrevious = currentTime;
        blueState = !blueState;
        digitalWrite(BLUE_LED, blueState);
    }
}
