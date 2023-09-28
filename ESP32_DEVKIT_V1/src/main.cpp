#include <Arduino.h>
#include <Config.h>  // See config file for all pin maps
#include <Credentials.h>
#include <OTA.h>  // optimization needs here
#include <MPU6050_tockn.h>
#include <Wire.h>
#include <IR.h>
#include <log.h>
#include <HCSR04.h> // Need some changes to work with RTOS updates
// https://github.com/gamegine/HCSR04-ultrasonic-sensor-lib


MPU6050 mpu6050(Wire);

// IR IR1(IR_1);
// ...

HCSR04 HC_FRONT(ULTRA_COMMON_TRIG, ULTRA_FRONT);
HCSR04 HC_LEFT(ULTRA_COMMON_TRIG, ULTRA_LEFT);
HCSR04 HC_RIGHT(ULTRA_COMMON_TRIG, ULTRA_RIGHT);


void MPU_Update( void * parameter ) {
  for (;;) {
    mpu6050.update();
    TelnetStream.println("MPU_UPDATE");
    // TelnetStream.print(mpu6050.getAngleZ);
    vTaskDelay(10/portTICK_PERIOD_MS);
  }
}

void IR_Update( void * parameter ) {
  for (;;) {
    // TelnetStream.println("IR UPDATE");
    vTaskDelay(10/portTICK_PERIOD_MS);

    // IR1.update();
    // ...
  }
}

void HCSR04_Update( void * parameter ) {
  for (;;) {
    TelnetStream.print("HCSE04 Update: ");
    TelnetStream.print("\t");
    TelnetStream.print(HC_FRONT.dist());
    TelnetStream.print(" \t");
    TelnetStream.print(HC_LEFT.dist());
    TelnetStream.print(" \t");
    TelnetStream.println(HC_RIGHT.dist());
    vTaskDelay(10/portTICK_PERIOD_MS);
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

  pinMode(LEFT_F, OUTPUT);
  pinMode(LEFT_R, OUTPUT);
  pinMode(2, OUTPUT);

  delay(3000);

  // analogWrite(RIGHT_F, 90);
  // analogWrite(LEFT_F, 90);

  mpu6050.calcGyroOffsets(true);

  xTaskCreatePinnedToCore(
    MPU_Update,          /* Task function. */
    "MPU_Update",        /* String with name of task. */
    10000,            /* Stack size in bytes. */
    NULL,             /* Parameter passed as input of the task */
    1,                /* Priority of the task. */
    NULL,             /* Task handle. */
    1);               
    
  xTaskCreatePinnedToCore(
    IR_Update,          /* Task function. */
    "IR_Update",        /* String with name of task. */
    10000,            /* Stack size in bytes. */
    NULL,             /* Parameter passed as input of the task */
    1,                /* Priority of the task. */
    NULL,            /* Task handle. */
    1);

  xTaskCreatePinnedToCore(
    HCSR04_Update,          /* Task function. */
    "HCSR04_Update",        /* String with name of task. */
    10000,            /* Stack size in bytes. */
    NULL,             /* Parameter passed as input of the task */
    2,                /* Priority of the task. */
    NULL,            /* Task handle. */
    1);
}


void loop() {
}
