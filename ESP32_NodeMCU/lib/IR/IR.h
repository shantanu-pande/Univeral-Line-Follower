#ifndef IR_h
#define IR_h
#include <Arduino.h>

class IR
{
private:
    uint8_t _PIN;
    uint16_t _TRIG, _MAX, _MIN;
public:
    IR(uint8_t PIN);
    ~IR();

    uint8_t THRESH_PERCENTAGE = 0.5;

    //processing funnctions
    void begin();
    void set(uint16_t MAX, uint16_t MIN);
    void set_trig(uint16_t TRIG);
    bool read();
    uint16_t read_analog();

    //return variable
    uint16_t get_trig();
};

#endif