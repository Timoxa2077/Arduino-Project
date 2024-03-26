#include <Servo.h>

#define servo3_max 170
#define servo3_min 15
#define servo5_max 160
#define servo5_min 0
#define servo6_max 10
#define servo6_min 157
#define servo9_max 30
#define servo9_min 115
#define servo11_max 75
#define servo11_min 170


Servo servo3;
Servo servo5;
Servo servo6;
Servo servo9;
Servo servo11;
byte pos = 0;

void s_attach()
{
  servo3.attach(3);
  servo5.attach(5);
  servo6.attach(11);
  servo9.attach(9);
  servo11.attach(10);
}

void jest0()
{
  pos = 0;
  Serial.println(0);
  servo3.write(servo3_min);
  servo5.write(servo5_min);
  servo6.write(servo6_min);
  servo9.write(servo9_min);
  servo11.write(servo11_min);
}

void jest1()
{
  Serial.println(1);
  
  if(pos != 1)
  {
    pos = 1;
    servo9.write(servo9_min);
    servo3.write(servo3_max);
    servo11.write(servo11_max);
    
    servo5.write(servo5_min);
    servo6.write(servo6_min);
    servo9.write(servo9_max);
    delay(500);
  }
}

void jest2()
{
  Serial.println(2);
  
  if(pos != 2)
  {
    pos = 2;
  servo3.write(servo3_min);
  servo6.write(servo6_max+30);
  servo9.write(servo9_min);
  servo5.write(servo5_min);
  servo11.write(servo11_max+20);
  servo9.write(servo9_max+30);
  }
}

void jest3()
{
  Serial.println(3);
  
  if(pos != 3)
  {
    pos = 3;
    servo9.write(servo9_min);
    servo3.write(servo3_max);
    servo5.write(servo5_max);
    servo6.write(servo6_max);
    delay(500);
    servo9.write(servo9_max);
  }
}
