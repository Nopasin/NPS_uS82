#include <Adafruit_MCP3008.h>
#include "NPS_us82_Motor.h"

Adafruit_MCP3008 adc;

#ifndef     NPS_US82_MCP3008_H_
#define     NPS_US82_MCP3008_H_

extern const int numSensors;
extern int Pins[], Min[], Max[], Background, last_value;
extern long F[], Val[];
extern int Error, Last_Error, LeftMotor, RightMotor, PowerMotor, Position;

void calAvg(){
  for (int i=0; i<numSensors; i++){
    Val[i] = (Max[i] + Min[i]) / 2;
  }
}

void readPrivate(long *sensor_values){
  unsigned char i, j;
  for (i = 0; i < numSensors; i++) sensor_values[i] = adc.readADC(i);
}

void Read(long *sensorValue) {
  unsigned char i, j;
  readPrivate(sensorValue);
  for (i = 0; i < numSensors; i++) {
    sensorValue[i] = map(sensorValue[i] , Min[i], Max[i] , 1000, 0);
    if (sensorValue[i] > 1000) sensorValue[i] = 1000;
    else if (sensorValue[i] < 0) sensorValue[i] = 0;
  }
}

int ReadLine(long *sensorValue) {
  int on_line = 0;
  unsigned long avg = 0;
  unsigned int sum = 0;
  unsigned long value = 0;
  on_line = 0;
  Read(sensorValue);
  avg = 0;
  sum = 0;
  for (int i = 0; i < numSensors; i++) {
    value = sensorValue[i];
    if (Background == 1) {
      value = 1000 - value;
      sensorValue[i] = value;
    }
    if (value > 200) on_line = 1;
    if (value > 50) {
      avg += value * (i * 1000);
      sum += value;
    }
  }
  if (on_line == 0) {
    if (last_value < ((numSensors - 1) * 1000) / 2) return 0;
    else return (numSensors - 1) * 1000;
  }
  else last_value = avg / sum;
  return last_value;
}

void Pid(int BaseSpeed, float Kp, float Kd) {
  Position = ReadLine(F);
  Error = Position - 3500;
  PowerMotor = (Kp * Error) + (Kd * (Error - Last_Error));
  Last_Error = Error;
  LeftMotor = BaseSpeed + PowerMotor;
  RightMotor = BaseSpeed - PowerMotor;
  LeftMotor = constrain(LeftMotor, -100, 100);
  RightMotor = constrain(RightMotor, -100, 100);
  Motors(LeftMotor, RightMotor);
}

void PidCurve(int BaseSpeed, float Kp, float Kd) {
  Position = ReadLine(F);
  Error = Position - 3500;
  PowerMotor = (Kp * Error) + (Kd * (Error - Last_Error));
  Last_Error = Error;
  LeftMotor = BaseSpeed + PowerMotor;
  RightMotor = BaseSpeed - PowerMotor;
  if (LeftMotor >= 100) LeftMotor = 100;
  if (LeftMotor <= 30) LeftMotor = -15;
  if (RightMotor >= 100) RightMotor = 100;
  if (RightMotor <= 30) RightMotor = -15;
  Motors(LeftMotor, RightMotor);
}

void ShowSensor() {
  while (1) {
    readPrivate(F);
    for (int i = 0; i < numSensors; i++){
      Serial.print(F[i]);
      Serial.print(",\t");
    }
    Serial.println("");
  }
}

#endif
