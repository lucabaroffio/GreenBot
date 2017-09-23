#include <Servo.h>

#define BRAKE 0
#define CW    1
#define CCW   2
#define CS_THRESHOLD 15   // Definition of safety current (Check: "1.3 Monster Shield Example").

//MOTOR 1
#define MOTOR_A1_PIN 7
#define MOTOR_B1_PIN 8

//MOTOR 2
#define MOTOR_A2_PIN 4
#define MOTOR_B2_PIN 9

//MOTOR CONTROLS
#define PWM_MOTOR_1 5
#define PWM_MOTOR_2 6

//MOTOR ENABLE
#define EN_PIN_1 A0
#define EN_PIN_2 A1

//MOTOR CURRENT SENSOR
//#define CURRENT_SEN_1 A2
//#define CURRENT_SEN_2 A3

//DEFINE MOTORS
#define MOTOR_1 0
#define MOTOR_2 1

//DISTANCE SENSOR
#define DISTANCE_ECHO 12
#define DISTANCE_TRIGGER 13
#define DISTANCE_ENABLED 0

//ESC
#define ESC_SIG 10

//MAX SPEED FOR BATTERY
#define MAX_SPEED 110
#define CRUISE_SPEED 80

short usSpeed = 150;  //default motor speed
unsigned short usMotor_Status = BRAKE;

Servo esc1;
 
void setup()                         
{

  esc1.attach(ESC_SIG); 

  if(DISTANCE_ENABLED){
     pinMode(DISTANCE_TRIGGER, OUTPUT); // Sets the trigPin as an Output
     pinMode(DISTANCE_ECHO, INPUT); // Sets the echoPin as an Input
  }
  
  pinMode(MOTOR_A1_PIN, OUTPUT);
  pinMode(MOTOR_B1_PIN, OUTPUT);

  pinMode(MOTOR_A2_PIN, OUTPUT);
  pinMode(MOTOR_B2_PIN, OUTPUT);

  pinMode(PWM_MOTOR_1, OUTPUT);
  pinMode(PWM_MOTOR_2, OUTPUT);

  //pinMode(CURRENT_SEN_1, OUTPUT);
  //pinMode(CURRENT_SEN_2, OUTPUT);  

  pinMode(EN_PIN_1, OUTPUT);
  pinMode(EN_PIN_2, OUTPUT);

  if(DISTANCE_ENABLED){
     digitalWrite(DISTANCE_TRIGGER, LOW);
  }

  Serial.begin(9600);              // Initiates the serial to do the monitoring 
  Serial.println("Begin motor control");
  Serial.println(); //Print function list for user selection
  /*Serial.println("Enter number for control option:");
  Serial.println("1. STOP");
  Serial.println("2. FORWARD");
  Serial.println("3. REVERSE");
  Serial.println("4. READ CURRENT");
  Serial.println("+. INCREASE SPEED");
  Serial.println("-. DECREASE SPEED");
  Serial.println();*/

  digitalWrite(EN_PIN_1, HIGH);
  digitalWrite(EN_PIN_2, HIGH);
  esc1.writeMicroseconds(700); //LOW for ESC
  delay(60000); // 30 seconds before starting

}

void loop() 
{
    /*while (get_distance() > 40){
      // Forward
      Forward(usSpeed);
      delay(500); 
    }
    Stop();
    delay(2000);
    // go back 1s
    Reverse(usSpeed);
    delay(2000);
    Stop();
    delay(2000);
    // turn 1s
    Turn(usSpeed);
    delay(2000);
    Stop();
    delay(2000);*/

    esc1.writeMicroseconds(900);
    delay(1000);
    esc1.writeMicroseconds(700);
    delay(5000);

    Forward(CRUISE_SPEED);
    delay(3000);
    Stop();
    delay(3000);
    Turn(CRUISE_SPEED);
    delay(3000);
    Stop();

    delay(60000);

    
}

void Stop()
{
  Serial.println("Stop");
  usMotor_Status = BRAKE;
  motorGo(MOTOR_1, usMotor_Status, 0);
  motorGo(MOTOR_2, usMotor_Status, 0);
}

void Forward(int speed)
{
  Serial.println("Forward: " + (String) speed);
  usMotor_Status = CW;
  motorGo(MOTOR_1, CW, speed);
  motorGo(MOTOR_2, CCW, speed);
}

void Reverse(int speed)
{
  Serial.println("Reverse" + (String) speed);
  usMotor_Status = CCW;
  motorGo(MOTOR_1, CCW, speed);
  motorGo(MOTOR_2, CW, speed);
}

void Turn(int speed)
{
  Serial.println("Turn" + (String) speed);
  usMotor_Status = CCW;
  motorGo(MOTOR_1, CW, speed);
  motorGo(MOTOR_2, CW, speed);
}

void IncreaseSpeed()
{
  usSpeed = usSpeed + 10;
  if(usSpeed > 255)
  {
    usSpeed = 255;  
  }
  
  Serial.print("Speed +: ");
  Serial.println(usSpeed);

  motorGo(MOTOR_1, usMotor_Status, usSpeed);
  motorGo(MOTOR_2, usMotor_Status, usSpeed);  
}

void DecreaseSpeed()
{
  usSpeed = usSpeed - 10;
  if(usSpeed < 0)
  {
    usSpeed = 0;  
  }
  
  Serial.print("Speed -: ");
  Serial.println(usSpeed);

  motorGo(MOTOR_1, usMotor_Status, usSpeed);
  motorGo(MOTOR_2, usMotor_Status, usSpeed);  
}

void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm)         //Function that controls the variables: motor(0 ou 1), direction (cw ou ccw) e pwm (entra 0 e 255);
{
  if(motor == MOTOR_1)
  {
    if(direct == CW)
    {
      digitalWrite(MOTOR_A1_PIN, LOW); 
      digitalWrite(MOTOR_B1_PIN, HIGH);
    }
    else if(direct == CCW)
    {
      digitalWrite(MOTOR_A1_PIN, HIGH);
      digitalWrite(MOTOR_B1_PIN, LOW);      
    }
    else
    {
      digitalWrite(MOTOR_A1_PIN, LOW);
      digitalWrite(MOTOR_B1_PIN, LOW);            
    }
    
    analogWrite(PWM_MOTOR_1, pwm); 
  }
  else if(motor == MOTOR_2)
  {
    if(direct == CW)
    {
      digitalWrite(MOTOR_A2_PIN, LOW);
      digitalWrite(MOTOR_B2_PIN, HIGH);
    }
    else if(direct == CCW)
    {
      digitalWrite(MOTOR_A2_PIN, HIGH);
      digitalWrite(MOTOR_B2_PIN, LOW);      
    }
    else
    {
      digitalWrite(MOTOR_A2_PIN, LOW);
      digitalWrite(MOTOR_B2_PIN, LOW);            
    }
    
    analogWrite(PWM_MOTOR_2, pwm);
  }
}

int get_distance(){
   
   // Sets the trigPin on HIGH state for 10 micro seconds
   digitalWrite(DISTANCE_TRIGGER, HIGH);
   delayMicroseconds(10);
   digitalWrite(DISTANCE_TRIGGER, LOW);
   // Reads the echoPin, returns the sound wave travel time in microseconds
   long duration = pulseIn(DISTANCE_ECHO, HIGH);
   // Calculating the distance (in cm)
   Serial.println("Distance: " + (String) (duration*0.034/2));
   return duration*0.034/2;
}
