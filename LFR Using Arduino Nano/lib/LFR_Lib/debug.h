#ifndef debug_h
#define debug_h

#ifndef DEBUG_STAT
#define DEBUG_STAT false
#endif

#if DEBUG_STAT
    #define logln(VALUE) Serial.println(VALUE)
    #define log(VALUE) Serial.print(VALUE)
#else
    #define logln(VALUE)
    #define log(VALUE)
#endif

#endif