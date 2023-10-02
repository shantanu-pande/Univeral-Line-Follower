#include <IR.h>

IR::IR(uint8_t PIN)
{
    _PIN = PIN;
    _MAX = 4095;
    _MIN = 0;
    _THR = (_MAX+_MIN)*_THR_PERCENTAGE/100;
}

void IR::begin()
{
    pinMode(_PIN, INPUT);
    update();
}

void IR::update()
{
    _VAL = analogRead(_PIN);
    if(_CALIB){
        if(_VAL<_MIN) _MIN = _VAL;
        else if(_VAL>_MAX) _MAX = _VAL;
        _THR = (_MAX+_MIN)*_THR_PERCENTAGE/100;
    }
}

void IR::setThreshold(uint8_t percentage)
{
    _THR_PERCENTAGE = percentage;
}

uint16_t IR::getMax()
{
    return _MAX;
}

uint16_t IR::getMin()
{
    return _MIN;
}
uint16_t IR::getThr()
{
    return _THR;
}
uint16_t IR::getVal()
{
    return _VAL;
}

IR::~IR()
{
}


RLS08::RLS08(uint8_t IR1, 
    uint8_t IR2, 
    uint8_t IR3, 
    uint8_t IR4, 
    uint8_t IR5, 
    uint8_t IR6, 
    uint8_t IR7, 
    uint8_t IR8)
{
}

RLS08::~RLS08()
{
}