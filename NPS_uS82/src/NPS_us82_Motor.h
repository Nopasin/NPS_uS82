#ifndef     NPS_US82_MOTOR_H_
#define     NPS_US82_MOTOR_H_
#include <Arduino.h>

#ifndef	ALL
#define	ALL     12
#endif
#define	PWM1	5
#define INA1	2
#define INB1	3
#define PWM2	6
#define INA2	4
#define	INB2	7

void Motors(int PowL, int PowR) {
  PowL = (PowL * 255) / 100;
  PowR = (PowR * 255) / 100;
  if (PowL > 0) {
    digitalWrite(INA1, LOW);
    digitalWrite(INB1, HIGH);
    analogWrite(PWM1, PowL);
  } else if (PowL == 0) {
    digitalWrite(INA1, HIGH);
    digitalWrite(INB1, HIGH);
    analogWrite(PWM1, 0);
  } else {
    digitalWrite(INA1, HIGH);
    digitalWrite(INB1, LOW);
    analogWrite(PWM1, -PowL);
  }

  if (PowR > 0) {
    digitalWrite(INA2, LOW);
    digitalWrite(INB2, HIGH);
    analogWrite(PWM2, PowR);
  } else if (PowR == 0) {
    digitalWrite(INA2, HIGH);
    digitalWrite(INB2, HIGH);
    analogWrite(PWM2, 0);
  } else {
    digitalWrite(INA2, HIGH);
    digitalWrite(INB2, LOW);
    analogWrite(PWM2, -PowR);
  }
}


#endif
