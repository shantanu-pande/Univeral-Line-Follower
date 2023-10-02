#include <Arduino.h>
#ifndef IR_h
#define IR_h

class IR
{
private:
    uint8_t _PIN, _THR_PERCENTAGE = 50;
    uint16_t _MAX, _MIN, _THR, _VAL;
    bool _CALIB = false;
public:
    IR(uint8_t PIN);
    ~IR();

    void begin();
    void setThreshold(uint8_t percentage);
    void update();
    uint16_t getMax();
    uint16_t getMin();
    uint16_t getThr();
    uint16_t getVal();
};

class RLS08
{
private:
    uint8_t _IR1, _IR2, _IR3, _IR4, _IR5, _IR6, _IR7, _IR8; 
public:
    RLS08(uint8_t IR1, 
    uint8_t IR2, 
    uint8_t IR3, 
    uint8_t IR4, 
    uint8_t IR5, 
    uint8_t IR6, 
    uint8_t IR7, 
    uint8_t IR8);
    ~RLS08();

    void begin();
    void setThreshold(uint8_t percentage);
    void calib(int delay);
    void update();
    void getArray();

};


#endif