#include "IR.h"

IR::IR(uint8_t PIN)
{
    _PIN = PIN;
}

void IR::begin()
{
    pinMode(_PIN, INPUT);
}

void IR::set(uint16_t MAX, uint16_t MIN)
{
    _MAX = MAX;
    _MIN = MIN;
    _TRIG = (MAX+MIN)*(THRESH_PERCENTAGE)/100;
}

void IR::set_trig(uint16_t TRIG)
{
    _TRIG = TRIG;
}

bool IR::read()
{
    return (analogRead(_PIN)>=_TRIG);
}

uint16_t IR::read_analog()
{
    return analogRead(_PIN);
}

uint16_t IR::get_trig()
{
    return _TRIG;
}

IR::~IR()
{
}