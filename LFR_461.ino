//l298n driver
const int IN1 = 7;    //Orange    //L1
const int IN2 = 4;    //Green     //L2
const int IN3 = 3;    //Blue      //R1
const int IN4 = 2;    //ash       //R2
const int ENA = 6;    //White
const int ENB = 5;    //Black
//sensor
const int pinOUT1 = 8;  //Blue   
const int pinOUT2 = 9;  //Yellow
const int pinOUT3 = 10; //Green
const int pinOUT4 = 11; //Blue 
const int pinOUT5 = 12; //Violet
//IR sensor variable
int s1 = 0;
int s2 = 0;
int s3 = 0;
int s4 = 0;
int s5 = 0;

void setup() 
{
    //Arduino to Motor Driver
    Serial.begin(9600);
    //Motor Driver
    pinMode (IN1, OUTPUT);
    pinMode (IN2, OUTPUT);
    pinMode (IN3, OUTPUT);
    pinMode (IN4, OUTPUT);
    pinMode (ENA, OUTPUT);
    pinMode (ENB, OUTPUT);
    //IR sensor to Arduino
    pinMode(pinOUT1,INPUT);
    pinMode(pinOUT2,INPUT);
    pinMode(pinOUT3,INPUT);
    pinMode(pinOUT4,INPUT);
    pinMode(pinOUT5,INPUT);
}

void loop() 
{
    pid();
}

int calculate_position() 
{
    //IR input
    s1 = digitalRead(pinOUT1);
    s2 = digitalRead(pinOUT2);
    s3 = digitalRead(pinOUT3);
    s4 = digitalRead(pinOUT4);
    s5 = digitalRead(pinOUT5);

    int error=0;
    
         if((s1 == 0) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 1)) error=-4;
    else if((s1 == 0) && (s2 == 0) && (s3 == 1) && (s4 == 1) && (s5 == 1)) error=-3;
    else if((s1 == 1) && (s2 == 0) && (s3 == 1) && (s4 == 1) && (s5 == 1)) error=-2;
    else if((s1 == 1) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1)) error=-1;
    else if((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 1) && (s5 == 1)) error=0;
    else if((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 1)) error=1;
    else if((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 0) && (s5 == 1)) error=2;
    else if((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 0) && (s5 == 0)) error=3;
    else if((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 0)) error=4;
    else if((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 1)) error=100;
   
    return error;
}

#define Kp 10.1                
#define Kd 19.2123
#define Ki 0.001
int lastError = 0;
int right_turn = 1; 
int errorSum = 0;  
#define rightBaseSpeed 190    
#define leftBaseSpeed 190 

void pid() 
{
    int error = calculate_position(); 
    if(error==100)
    {
        // Stop Case
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        analogWrite(ENB, 0);
        analogWrite(ENA, 0);
        return;
    }
    int errorSum = errorSum + error;
    //PID Formula
    int motorSpeed = Kp * error + Ki * errorSum + Kd * (error - lastError);
    lastError = error;
  
    int rightMotorSpeed = rightBaseSpeed - motorSpeed;
    int leftMotorSpeed = leftBaseSpeed + motorSpeed;
    
    rightMotorSpeed=constrain(rightMotorSpeed,0,255);
    leftMotorSpeed=constrain(leftMotorSpeed,0,255);
    
    if(leftMotorSpeed<=180)
    {
      //Strong Left
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH); //Left motor Backward
      digitalWrite(IN3, HIGH); //Right motor Forward
      digitalWrite(IN4, LOW);
    }
    else if(rightMotorSpeed<=180)
    {
      //Strong Right
      digitalWrite(IN1, HIGH); //Left motor Forward
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH); //Right motor Backward
    }else
    {
      //Forward
      digitalWrite(IN1, HIGH); //Left motor Forward
      digitalWrite(IN3, HIGH); //Right motor Forward
      digitalWrite(IN2, LOW);
      digitalWrite(IN4, LOW);
    }

    analogWrite(ENA, leftMotorSpeed);  //Left motor
    analogWrite(ENB, rightMotorSpeed); //Right motor

    // Test Case
    Serial.print("error ");
    Serial.print(error);
    Serial.print('\t');
    Serial.print("motorSpeed ");
    Serial.print(motorSpeed);
    Serial.print('\t');
    Serial.print("leftMotorSpeed ");
    Serial.print(leftMotorSpeed);
    Serial.print('\t');
    Serial.print("rightMotorSpeed ");
    Serial.print(rightMotorSpeed);
    Serial.println();
      
}
