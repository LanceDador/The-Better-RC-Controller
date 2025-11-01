// C++ code
// Dador_PC = COM8 USB, COM10 BT
// Gab laptop = COM5 USB, COM4 BT
#include <Servo.h>
#include <DHT.h>
#define DHTTYPE DHT22

// motor config
const int enA = 5, enB = 6, in4 = 7, in3 = 8, in2 = 9, in1 = 10;
int msI = 2;
int motorSpd[] = {0,100,175,250};

// sensor config
const int battPin = A5, soilPin = A1, soilVCC = A0, dhtPin = A2;
float temp = 0.0, hum = 0.0;
DHT dht(dhtPin, DHTTYPE);

// servo config
const int servoA = 4, servoB = 3, servoC = 2, servoR = 11;
int sA = 90, sB = 90, sC = 90, sR = 90, gap = 2;
bool sA_up = false, sA_down = false, sB_up = false, sB_down = false, sC_up = false, sC_down = false, sR_up = false, sR_down = false;
Servo myServoA, myServoB, myServoC, myServoR;



void setup()
{
  Serial.begin(9600);
  dht.begin();
  
  int out[] = {soilVCC, in1, in2, in3, in4, enA, enB};
  for (int i=0; i<7; i++){
    pinMode(out[i], OUTPUT);
  }
  
  int inp[] = {battPin, soilPin};
  for (int i=0; i<2; i++){
    pinMode(inp[i], INPUT);
  }
  
  myServoA.attach(servoA);
  myServoB.attach(servoB);
  myServoC.attach(servoC);
  myServoR.attach(servoR);
}

void loop()
{
  if (Serial.available() > 0) {
    // read the incoming serial command:
    char serialData = Serial.read();
    
    switch (serialData){
      // v, battery, b=moisture, n=humidity, m=temperature
      case 'v':{       
      	checkBatt();
      	break;
        }
      case 'b':{
      	checkMoisture();
      	break;
        }
      case 'n':{
      	checkHum();
      	break;
        }
      case 'm':{
      	checkTemp();
      	break;
        }
      // wasd for direction control
      case 'w':{
        int a[] = {0, 1, 0, 1}, b[] = {1, 1};
      	move_motor(a, b, "Direction: Forward");
      	break;
        }
      case 'a':{
        int a[] = {0, 1, 1, 0}, b[] = {1, 0};
      	move_motor(a, b, "Direction: Left");
      	break;
        }
      case 's':{
        int a[] = {1, 0, 1, 0}, b[] = {1, 1};
      	move_motor(a, b, "Direction: Backward");
      	break;
      }
      case 'd':{
        int a[] = {1, 0, 0, 1}, b[] = {0, 1};
      	move_motor(a, b, "Direction: Right");
      	break;
      }
      // z=lower speed, x=stop, c=increase speed
      case 'x':{
      	stop();
      	break;
      }
      case 'z':{
        if (0<msI && msI<=3){
          msI--;
          Serial.println("Motor Speed: " + String(msI)+ "/3");
        }
      	break;
      }
      case 'c':{
      	if (0<=msI && msI<3){
          msI++;
          Serial.println("Motor Speed: " + String(msI)+ "/3");
        }
      	break;
      }
      // t/y = servo A, g/h = servo B, u/i = servo C, j/k = servo R,
      case 't': {
        sA_down = true, sA_up = false;
        Serial.println("Servo A going down");
        break;
      }
      case 'y': {
        sA_up = true, sA_down = false;
        Serial.println("Servo A going up");
        break;
      }
      case 'g': {
        sB_down = true, sB_up = false;
        Serial.println("Servo B going down");
        break;
      }
      case 'h': {
        sB_up = true, sB_down = false;
        Serial.println("Servo B going up");
        break;
      }
      case 'u': {
        sC_down = true, sC_up = false;
        break;
      }
      case 'i': {
        sC_up = true, sC_down = false;
        break;
      }
      case 'j': {
        sR_down = true, sR_up = false;
        break;
      }
      case 'k': {
        sR_up = true, sR_down = false;
        break;
      }
      case 'p':{
        sA_up = sA_down = sB_up = sB_down = sC_up = sC_down = sR_up = sR_down = false;
        Serial.println("All servos stopped");
        break;
      }
    }
  }

  // perform servo movement
  if (sA_down){
    moveServo(0, sA, myServoA);
    }
  else if (sA_up){
    moveServo(1, sA, myServoA);
  }

  if (sB_down){
    moveServo(0, sB, myServoB);
  }
  else if (sB_up){
    moveServo(1, sB, myServoB);
  }

  if (sC_down){
    moveServo(0, sC, myServoC);
  }
  else if (sC_up){
    moveServo(1, sC, myServoC);
  }
  
  if (sR_down){
    moveServo(0, sR, myServoR);
  }
  else if (sR_up){
    moveServo(1, sR, myServoR);
  }

  delay(100);
}

// ---------------------------------------------- // 
void checkBatt(){
  float batt = analogRead(battPin)/102.4;
  Serial.println(String(batt));
  return;
}

void checkMoisture(){
  digitalWrite(soilVCC, HIGH);
  float moist = analogRead(soilPin)/8.72;
  Serial.println(String(moist));
  delay(250);
  digitalWrite(soilVCC, LOW);
  return;
}

void checkTemp(){
  temp = dht.readTemperature();
  Serial.println(String(temp));
  return;
}

void checkHum(){
  hum = dht.readHumidity();
  Serial.println(String(hum));
  return;
}

// ---------------------------------------------- // 

void move_motor(int dirVal[], int mVal[] , String msg){
  int motorpins[] = {in1, in2, in3, in4};

  for (int i=0; i<4; i++){
    digitalWrite(motorpins[i], dirVal[i]);
  }
  analogWrite(enA, mVal[0]*motorSpd[msI]);
  analogWrite(enB, mVal[1]*motorSpd[msI]);
  Serial.println(msg);
}

void stop(){
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  Serial.println("Stopped Motors");
  return;
}

// ---------------------------------------------- // 

void moveServo(int val, int &sVal, Servo &sName){
  if (val && 0<=sVal && sVal<180){
    sVal+=gap;
  }
  else if (!val && 0<sVal && sVal<=180){
    sVal-=gap;
  }
  sName.write(sVal);
}