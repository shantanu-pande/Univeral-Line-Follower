#include <Arduino.h>
#include <Config.h>
#include <Credentials.h>
#include <OTA.h>
#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);

void MPU_Update( void * parameter ) {
  for (;;) mpu6050.update();
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

  mpu6050.calcGyroOffsets(true);

  xTaskCreate(
    MPU_Update,          /* Task function. */
    "MPU_Update",        /* String with name of task. */
    10000,            /* Stack size in bytes. */
    NULL,             /* Parameter passed as input of the task */
    1,                /* Priority of the task. */
    NULL);            /* Task handle. */
}


void loop() {
}
