#include <Arduino.h>
#include <PinSetup.h> //define pins here [lib/LFR_Lib/PinSetup.h]

int caliberate(int, int);

void setup() {
  int result = caliberate(2, 3);

}

void loop() {

}

// caliberates the ir sensors
int caliberate(int x, int y) {
  return x + y;
}