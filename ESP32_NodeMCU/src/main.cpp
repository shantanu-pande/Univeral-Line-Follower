/*
ESP32 Multitasking With Real Time Operating System


*/

#include <Arduino.h>
// #include <Motor.h>

//Free-RTOS setup to use singel core
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

//Modules
// Motor left(1,2,3);
// Motor right(5,6);

//Variables


//Constants

// Pins
static const int led_pin = LED_BUILTIN;

void WebServer(void *parameter) {
  //Setup

  //Loop
  while(1) {
    Serial.println("Web Server");
    delay(10);
  }
}

void update_sensors(void *parameter) {
  //Setup Here

  //Loop
  while(1) {
    Serial.println("Update");
    delay(10);
  }
}

void drive(void *parameter) {
  //Setup Here
  
  //Loop
  while(1) {
    Serial.println("Forward");
    delay(10);
  }
}

void setup() {
  //Init modules
  // Configure pin
  pinMode(led_pin, OUTPUT);
    Serial.begin(9600);


  // Task to run forever
  xTaskCreatePinnedToCore(  // Use xTaskCreate() in vanilla FreeRTOS
              drive,  // Function to be called
              "drive",   // Name of task
              1024,         // Stack size (bytes in ESP32, words in FreeRTOS)
              NULL,         // Parameter to pass to function
              1,            // Task priority (0 to configMAX_PRIORITIES - 1)
              NULL,         // Task handle
              app_cpu);     // Run on one core for demo purposes (ESP32 only)

  // Task to run forever
  xTaskCreatePinnedToCore(  // Use xTaskCreate() in vanilla FreeRTOS
              update_sensors,  // Function to be called
              "Update Sensors",   // Name of task
              1024,         // Stack size (bytes in ESP32, words in FreeRTOS)
              NULL,         // Parameter to pass to function
              1,            // Task priority (0 to configMAX_PRIORITIES - 1)
              NULL,         // Task handle
              app_cpu);     // Run on one core for demo purposes (ESP32 only)

  xTaskCreatePinnedToCore(  // Use xTaskCreate() in vanilla FreeRTOS
              WebServer,  // Function to be called
              "Web Server",   // Name of task
              1024,         // Stack size (bytes in ESP32, words in FreeRTOS)
              NULL,         // Parameter to pass to function
              1,            // Task priority (0 to configMAX_PRIORITIES - 1)
              NULL,         // Task handle
              app_cpu);     // Run on one core for demo purposes (ESP32 only)

  // If this was vanilla FreeRTOS, you'd want to call vTaskStartScheduler() in
  // main after setting up your tasks.
}

void loop() {
  // Do nothing
  // setup() and loop() run in their own task with priority 1 in core 1
}