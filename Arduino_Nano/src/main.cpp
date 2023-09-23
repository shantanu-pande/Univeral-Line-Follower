#include <Arduino.h>
#include <Definiation.h>
#define DEBUG_STAT false
#include <debug.h>
#include <Motor.h>
#include <PID_v1.h>


uint16_t PID(uint16_t ERR);

Motor left(3, 5);
Motor right(6, 9);


void setup() {

    left.begin();
    right.begin();
    left.stop();
    right.stop();    
}

void loop() {
    left.forward(255);
    delay(1000);
    right.reverse(255);
    delay(1000);
}

