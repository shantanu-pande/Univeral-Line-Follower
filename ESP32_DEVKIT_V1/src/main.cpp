#include <Arduino.h>
#include "Config.h"  // See config file for all pin maps
#include <OTA.h>  // optimization needs here
#include <MPU6050_tockn.h>
#include <Motor.h>
#include <IR.h>
#include <HCSR04.h> // Need some changes to work with RTOS updates
#include <TelnetStream.h>
#include <WebSocketsServer.h>

WebSocketsServer webSocket = WebSocketsServer(80);
MPU6050 mpu6050(Wire);
HCSR04 HC_FRONT(ULTRA_COMMON_TRIG, ULTRA_FRONT);
HCSR04 HC_LEFT(ULTRA_COMMON_TRIG, ULTRA_LEFT);
HCSR04 HC_RIGHT(ULTRA_COMMON_TRIG, ULTRA_RIGHT);
Motor left(LEFT_F, LEFT_R);
Motor right(RIGHT_F, RIGHT_R);

void onWebSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length);
void updateSensorsVar( void * parameter );
void spawnTasks();

void setup()
{
  #ifdef DEBUG
    Serial.begin(115200);
    TelnetStream.begin();
  #endif

  Sprintln("Booting");
  setupOTA("Line Follower", WIFI_SSID, WIFI_PASS);

  Wire.begin();
  mpu6050.begin();
  webSocket.begin();
  webSocket.onEvent(onWebSocketEvent);
  mpu6050.calcGyroOffsets();

  #if defined(ESP32_RTOS) && defined(ESP32)
    spawnTasks();
  #endif        
}


void updateSensorsVar( void * parameter ) {
  for (;;) {
    mpu6050.update();
    webSocket.loop();
    vTaskDelay(5/portTICK_PERIOD_MS);
  }
}

void onWebSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      break;

    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] Connection from ", num);
        Serial.println(ip.toString());
      }
      break;

    case WStype_TEXT:
      {
        TelnetStream.printf("[%u] Text: %s\n", num, payload);
        webSocket.sendTXT(num, payload);
      }
      break;

    case WStype_BIN:
    case WStype_ERROR:
    case WStype_FRAGMENT_TEXT_START:
    case WStype_FRAGMENT_BIN_START:
    case WStype_FRAGMENT:
    case WStype_FRAGMENT_FIN:

    default:
      break;
  }
}

void spawnTasks()
{
  xTaskCreatePinnedToCore(
    updateSensorsVar,    /* Task function. */
    "MPU_Update",     /* String with name of task. */
    10000,            /* Stack size in bytes. */
    NULL,             /* Parameter passed as input of the task */
    1,                /* Priority of the task. */
    NULL,             /* Task handle. */
    1);               /* CPU Core */

  xTaskCreatePinnedToCore(
    ota_handle,       /* Task function. */
    "OTA_HANDLE",     /* String with name of task. */
    10000,            /* Stack size in bytes. */
    NULL,             /* Parameter passed as input of the task */
    1,                /* Priority of the task. */
    NULL,             /* Task handle. */
    1);               /* CPU Core */
}

void loop() {
}