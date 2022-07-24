#include <PS2X_lib.h>



//set all the motor control pins to outputs
#define ENA 0 //left  motor
#define ENB 1 //right motor
#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11
//⬆Define L298N  
#define PS2_DAT        4  //14    
#define PS2_CMD        2  //15
#define PS2_SEL        10  //16
#define PS2_CLK        3  //17

int error = 0;         //连接正确与否的判断标志
byte type = 0;         //ps2x.readType()转换判别标志     
byte vibrate = 0;
int banduan=0;

void setup() 
{  
  Serial.begin (9600); // 9600 bps connect to raspberry pi
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);//left  motor
  pinMode(ENB,OUTPUT);//right motor
}
void Motor(int left, int right)
{ //go forward or go back 
       if (left <0){digitalWrite(IN1,LOW ); digitalWrite(IN2,HIGH);}
  else if (left >0){digitalWrite(IN1,HIGH); digitalWrite(IN2,LOW );}
  else             {digitalWrite(IN1,LOW ); digitalWrite(IN2,LOW );}
       if (right<0){digitalWrite(IN3,LOW ); digitalWrite(IN4,HIGH);}
  else if (right>0){digitalWrite(IN3,HIGH); digitalWrite(IN4,LOW );}
  else             {digitalWrite(IN3,LOW ); digitalWrite(IN4,LOW );}
  left  = abs(left );//Absolute left  speed
  right = abs(right);//Absolute right speed
  int potValue_left   = left;  // Read left
  int potValue_right  = right; // Read left
  int pwmOutput_left  = map(potValue_left , 0, 100, 0 , 255); // Map the potentiometer value from 0 to 255
  int pwmOutput_right = map(potValue_right, 0, 100, 0 , 255); // Map the potentiometer value from 0 to 255
  analogWrite(ENA, pwmOutput_left ); // Send PWM signal to L298N Enable pin 
  analogWrite(ENB, pwmOutput_right); // Send PWM signal to L298N Enable pin 
}
void Motor_T(int left, int right, float t, int brake)
{
  t=t*1000;// ms to s
  Motor(left,right);
  delay(t);
  if(brake=1){Motor(0,0);} //brake
}
void loop() 
{  
  Motor_T(0,-1,0.1,1);
  

  /*if ( Serial.available())
    {
    long spd = Serial.read(),t;int l,r,b;
    l=(spd/1000 )%1000;r=spd%1000;    // ttttttblllrrr
    b=(spd/1000000)%10;t=spd/10000000;// ttttttblllrrr
    //spd=r+l*1000+b*1000000+t*10000000;
    if('s' == Serial.read())
    Motor_T(l,r,t,b);
    Serial.println("Hello Raspberry,I am Arduino.");
    */}
