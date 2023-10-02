#ifndef Config_h
    #define Config_h

    #define ESP32_RTOS
    #define DEBUG

    #ifdef DEBUG
        #define Tprint(text) TelnetStream.print(text)
        #define Tprintln(text) TelnetStream.println(text)
        #define Sprint(text) Serial.print(text)
        #define Sprintln(text) Serial.println(text)
    #else
        #define Tprint(text)
        #define Tprintln(text)
        #define Sprint(text)
        #define Sprint(text)
    #endif

    #define WIFI_SSID "RNXG_IOT"
    #define WIFI_PASS "Rnxg@2023-24"

    #define ULTRA_COMMON_TRIG   18
    #define ULTRA_FRONT         17
    #define ULTRA_LEFT          19
    #define ULTRA_RIGHT         5

    #define IR_1    36
    #define IR_2    39
    #define IR_3    34
    #define IR_4    35
    #define IR_5    32
    #define IR_6    33
    #define IR_7    25
    #define IR_8    26

    #define LEFT_F  4
    #define LEFT_R  16
    #define RIGHT_F 27
    #define RIGHT_R 13

#endif