#include "NPS_uS82_MCP3008.h"

#ifndef NPS_US82_H_
#define NPS_US82_H_

#define SW_PORT 8
#define GLED 13

void uSetup(){
  Serial.begin(9600);
  pinMode(PWM1, OUTPUT);
  pinMode(INA1, OUTPUT);
  pinMode(INB1, OUTPUT);
  pinMode(PWM2, OUTPUT);
  pinMode(INA2, OUTPUT);
  pinMode(INB2, OUTPUT);
  pinMode(13,OUTPUT);
  adc.begin(A0, A2, A1, A3);
  calAvg();
}

int analog(int __ch){
    return analogRead(__ch);
}

bool SW(){
    return digitalRead(SW_PORT);
}

bool in(int __ch){
    __ch = (__ch == 13 ? __ch : __ch+14);
    pinMode(__ch, INPUT);
    return digitalRead(__ch);
}

void out(int __ch, bool __state){
    __ch = (__ch == 13 ? __ch : __ch+14);
    pinMode(__ch, OUTPUT);
    digitalWrite(__ch,__state);
}

void SW_Press(){
    while(!SW());
    while(SW());
    delay(500);
}

#endif
