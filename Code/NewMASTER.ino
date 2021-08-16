include <LiquidCrystal.h>
#define buzzer 9
#define backlight 10
#include <SoftwareSerial.h>
SoftwareSerial BTserial(0, 1); // RX, TX

LiquidCrystal lcd(12, 11, 5, 4, 3, 8);

volatile boolean modes = 1; //assigning mode as 1 in start
int rounded;

void setup() {
  BTserial.begin(38400);//Baud rate
  Serial.begin(9600);
  lcd.begin(16, 2);
  attachInterrupt(0, changeMode, FALLING);
  pinMode(2, INPUT); //touch sensor
  pinMode(buzzer, OUTPUT);
  pinMode(backlight, OUTPUT); //lcd
  digitalWrite(backlight, HIGH);
  backlightOn();
}

void loop() {
  if (modes == 1) { //mode 1 is temperature
    Serial.write('1');
    if (Btserial.available())
    { 
        float temp = BTserial.read(); //read temperature via BT
        backlightOn(); //lcd ON
        if (temp >= 35) {
            //rounded = 0;
            lcd.clear();
            //lcd.print("Out of range");
            //lcd.setCursor(0, 0);
            lcd.print("Temperature:" + String(temp) + " C");
            lcd.setCursor(0,1);
            lcd.print("PRECAUTIONS!!");
            Serial.println("Temperature1:"+String(temp)+" C");
        }
        else{
            lcd.clear();
            //lcd.print("Out of range");
            //lcd.setCursor(0, 0);
            lcd.print("Temperature:" + String(temp) + " C");
            lcd.setCursor(0,1);
            lcd.print("SAFE");
            Serial.println("Temperature1:"+String(temp)+ " C");
        }
    }
}
    else { //distance mode 
    Serial.write('0');
    if (BTserial.available()){ //reading distance via BT
      double distance = Serial.read();
      if (distance >= 300 || distance <= 0) { //outside range
      rounded = 0;
      lcd.clear();
      backlightOff();
    }
    else {
      rounded = round(distance);
      if (distance >= 200) {
        backlightOff();
        lcd.clear();
      }
      else if (distance <= 200 && distance > 100) {
        backlightOn();
        lcd.clear();
        lcd.print("APPROACHING");
        lcd.setCursor(0, 1);
        lcd.print("Distance:");
        lcd.print(rounded);
        lcd.print(" cm");
        Serial.println("APPROACHING"+ String(rounded) + " cm");
        
      }
      else if (distance <= 100 && distance > 50) {
        backlightOn();
        lcd.clear();
        lcd.print("Keep away");
        lcd.setCursor(0, 1);
        lcd.print("Distance:");
        lcd.print(rounded);
        lcd.print(" cm");
        Serial.println("Keep away" + String(rounded) + " cm");
        delay(200);
        buzz();
        backlightOff();
        delay(100);
        unbuzz();
        backlightOn();
        delay(100);
      }
      else if (distance <= 50) {
        backlightOn();
        lcd.clear();
        lcd.print("ALERT!!!");
        lcd.setCursor(0, 1);
        lcd.print("Distance:");
        lcd.print(rounded);
        lcd.print(" cm");
        Serial.println("ALERT!!!" + String(rounded) + " cm");
        delay(200);
        buzz();
        backlightOff();
        delay(200);
        unbuzz();
        backlightOn();
        delay(200);
        buzz();
        backlightOff();
        delay(200);
        unbuzz();
        backlightOn();
      }
    }
  }
  delay(700);
}
  if (Serial.available())
      {
       BTserial.write(Serial.read());//send mode value to slave
      } 
}
void changeMode() { //for changing mode via touch sensor
  modes = !modes;
}
void backlightOn() { //for lcd to switch ON
  digitalWrite(backlight, HIGH);
}
void backlightOff() { //for lcd to switch OFF
  digitalWrite(backlight, LOW);
}
void buzz() { //for buzzer ON
  digitalWrite(buzzer, HIGH);
}
void unbuzz() { for buzzer OFF
  digitalWrite(buzzer, LOW);
}
include <LiquidCrystal.h>
#define buzzer 9
#define backlight 10
#include <SoftwareSerial.h>
SoftwareSerial BTserial(0, 1); // RX, TX

LiquidCrystal lcd(12, 11, 5, 4, 3, 8);

volatile boolean modes = 1; //assigning mode as 1 in start
int rounded;

void setup() {
  BTserial.begin(38400);//Baud rate
  Serial.begin(9600);
  lcd.begin(16, 2);
  attachInterrupt(0, changeMode, FALLING);
  pinMode(2, INPUT); //touch sensor
  pinMode(buzzer, OUTPUT);
  pinMode(backlight, OUTPUT); //lcd
  digitalWrite(backlight, HIGH);
  backlightOn();
}

void loop() {
  if (modes == 1) { //mode 1 is temperature
    Serial.write('1');
    if (Btserial.available())
    { 
        float temp = BTserial.read(); //read temperature via BT
        backlightOn(); //lcd ON
        if (temp >= 35) {
            //rounded = 0;
            lcd.clear();
            //lcd.print("Out of range");
            //lcd.setCursor(0, 0);
            lcd.print("Temperature:" + String(temp) + " C");
            lcd.setCursor(0,1);
            lcd.print("PRECAUTIONS!!");
            Serial.println("Temperature1:"+String(temp)+" C");
        }
        else{
            lcd.clear();
            //lcd.print("Out of range");
            //lcd.setCursor(0, 0);
            lcd.print("Temperature:" + String(temp) + " C");
            lcd.setCursor(0,1);
            lcd.print("SAFE");
            Serial.println("Temperature1:"+String(temp)+ " C");
        }
    }
}
    else { //distance mode 
    Serial.write('0');
    if (BTserial.available()){ //reading distance via BT
      double distance = Serial.read();
      if (distance >= 300 || distance <= 0) { //outside range
      rounded = 0;
      lcd.clear();
      backlightOff();
    }
    else {
      rounded = round(distance);
      if (distance >= 200) {
        backlightOff();
        lcd.clear();
      }
      else if (distance <= 200 && distance > 100) {
        backlightOn();
        lcd.clear();
        lcd.print("APPROACHING");
        lcd.setCursor(0, 1);
        lcd.print("Distance:");
        lcd.print(rounded);
        lcd.print(" cm");
        Serial.println("APPROACHING"+ String(rounded) + " cm");
        
      }
      else if (distance <= 100 && distance > 50) {
        backlightOn();
        lcd.clear();
        lcd.print("Keep away");
        lcd.setCursor(0, 1);
        lcd.print("Distance:");
        lcd.print(rounded);
        lcd.print(" cm");
        Serial.println("Keep away" + String(rounded) + " cm");
        delay(200);
        buzz();
        backlightOff();
        delay(100);
        unbuzz();
        backlightOn();
        delay(100);
      }
      else if (distance <= 50) {
        backlightOn();
        lcd.clear();
        lcd.print("ALERT!!!");
        lcd.setCursor(0, 1);
        lcd.print("Distance:");
        lcd.print(rounded);
        lcd.print(" cm");
        Serial.println("ALERT!!!" + String(rounded) + " cm");
        delay(200);
        buzz();
        backlightOff();
        delay(200);
        unbuzz();
        backlightOn();
        delay(200);
        buzz();
        backlightOff();
        delay(200);
        unbuzz();
        backlightOn();
      }
    }
  }
  delay(700);
}
  if (Serial.available())
      {
       BTserial.write(Serial.read());//send mode value to slave
      } 
}
void changeMode() { //for changing mode via touch sensor
  modes = !modes;
}
void backlightOn() { //for lcd to switch ON
  digitalWrite(backlight, HIGH);
}
void backlightOff() { //for lcd to switch OFF
  digitalWrite(backlight, LOW);
}
void buzz() { //for buzzer ON
  digitalWrite(buzzer, HIGH);
}
void unbuzz() { for buzzer OFF
  digitalWrite(buzzer, LOW);
}
