#include <Arduino.h>
#include <Config.h>  // See config file for all pin maps
#include <Credentials.h>
#include <OTA.h>  // optimization needs here
#include <MPU6050_tockn.h>
#include <Wire.h>

// #include <IR.h> Not Created yet

// #include <HCSR04.h> Need some changes to work with RTOS updates
// https://github.com/gamegine/HCSR04-ultrasonic-sensor-lib


MPU6050 mpu6050(Wire);

// IR IR1(pin);
// IR IR2(pin);
// IR IR3(pin);
// ...

// HCSR04 HC_FRONT(5, 6);
// HCSR04 HC_LEFT(5, 6);
// HCSR04 HC_RIGHT(5, 6);


void MPU_Update( void * parameter ) {
  for (;;) {
    mpu6050.update();
  }
}

void IR_Update( void * parameter ) {
  for (;;) {
    // IR1.update();
    // ...
  }
}

void HCSR04_Update( void * parameter ) {
  for (;;) {
    // HC_FRONT.update();
    // ...
  }
}


void setup() {
  Serial.begin(115200);
  Serial.println("Booting");
  setupOTA("Line Follower", WIFI_SSID, WIFI_PASS);
  Wire.begin();
  mpu6050.begin();

  // Config.setup()
  pinMode(14, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(2, OUTPUT);
  digitalWrite(27, LOW);
  // ^^^^^^^^^^^^^^^^^^^^^

  mpu6050.calcGyroOffsets(true);

  xTaskCreate(
    MPU_Update,          /* Task function. */
    "MPU_Update",        /* String with name of task. */
    10000,            /* Stack size in bytes. */
    NULL,             /* Parameter passed as input of the task */
    1,                /* Priority of the task. */
    NULL);            /* Task handle. */
    
  xTaskCreate(
    IR_Update,          /* Task function. */
    "IR_Update",        /* String with name of task. */
    1000,            /* Stack size in bytes. */
    NULL,             /* Parameter passed as input of the task */
    1,                /* Priority of the task. */
    NULL);            /* Task handle. */
    
  xTaskCreate(
    HCSR04_Update,          /* Task function. */
    "HCSR04_Update",        /* String with name of task. */
    1000,            /* Stack size in bytes. */
    NULL,             /* Parameter passed as input of the task */
    1,                /* Priority of the task. */
    NULL);            /* Task handle. */

}


void loop() {
}
