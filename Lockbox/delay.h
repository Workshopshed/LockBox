#if defined(ARDUINO) && ARDUINO >= 100  
#include <Arduino.h>  
#else  
#include <WProgram.h>  
#endif  
class NonBlockDelay {  
    unsigned long iTimeout;
    unsigned long iMillis;
  public:  
    void CountDown (unsigned long);  
    bool OutofTime (void);  
    unsigned long RemainingTime(void);  
    void Skip(unsigned long t);
};  
