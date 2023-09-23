// //PID Constants
// #define Kp 0.0
// #define Ki 0.0
// #define Kd 0.0


//IR
#define IR_FRONT A0
#define IR_MID A1
#define IR_LEFT A2
#define IR_RIGHT A3
#define IR_RIGHT_MOST A6
#define IR_LEFT_MOST A7
#define IR_ALL {IR_MID, IR_FRONT, IR_LEFT_MOST, IR_RIGHT_MOST, IR_LEFT, IR_RIGHT}

//Motar Driver
#define LF 3
#define LR 5
#define RF 6
#define RR 9

// ESP01
#define TX_PIN 0
#define RX_PIN 1
#define ESP_ST 4

// Ultrasonic
#define SONIC_FR 10
#define SONIC_LF 11
#define SONIC_RI 12

// Gyro MPU6050
#define GYRO_SDA A4
#define GYRO_SCL A5
#define GYRO_INT 2

//Buttons
#define CALIB_BTN 7

//BUZZER
#define BUZZER 8