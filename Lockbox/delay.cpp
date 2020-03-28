#include "Delay.h"  

void NonBlockDelay::CountDown (unsigned long t)  
{  
  iMillis = millis();
  iTimeout = t;  
  return;  
};  

void NonBlockDelay::Skip(unsigned long t) 
{
  if (t > iTimeout) return;
  iTimeout -= t;
}

bool NonBlockDelay::OutofTime(void)  
{  
  unsigned long currentMillis = millis(); // grab current time
  return (unsigned long)(currentMillis - iMillis) >= iTimeout;
}

unsigned long NonBlockDelay::RemainingTime(void)  
{  
    unsigned long currentMillis = millis(); // grab current time
    return (unsigned long)(iTimeout - (currentMillis - iMillis));
}  
