#include <LiquidCrystal.h>
#define buzzer 9
#define backlight 10

#include <SoftwareSerial.h>0
SoftwareSerial BTserial(1, 0); // RX | TX

LiquidCrystal lcd(12, 11, 5, 4, 3, 8);
//UltraSonicDistanceSensor distanceSensor(trigPin, echoPin);

volatile boolean modes = 1;
int rounded;

void setup() {
  Serial.begin(9600);//Baud rate
  lcd.begin(16, 2);
  attachInterrupt(0, changeMode, FALLING);
  pinMode(2, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(backlight, OUTPUT);
  digitalWrite(backlight, HIGH);
  backlightOn();
  BTserial.begin(38400);
}

void loop() {
  Serial.println("AAAA");
  if (modes == 1) {
    BTserial.write('1');
    if (BTserial.available())
    { 
        float temp = BTserial.read();
        backlightOn();
        if (temp >= 35) {
        //rounded = 0;
        lcd.clear();
        //lcd.print("Out of range");
        //lcd.setCursor(0, 0);
        lcd.print("Temperature:" + String(temp) + " C");
      
        lcd.setCursor(0,1);
        lcd.print("PRECAUTIONS!!");
        Serial.println("Temperature1:" + String(temp) + " C");
    }
    else{
        lcd.clear();
        //lcd.print("Out of range");
        //lcd.setCursor(0, 0);
        lcd.print("Temperature:" + String(temp) + " C");
        lcd.setCursor(0,1);
        lcd.print("SAFE");
      
        Serial.println("Temperature1:" + String(temp) + " C");
    }
    }
}
  else {
    BTserial.write('0');
    if (BTserial.available()){
      double distance = BTserial.read();
      if (distance >= 300 || distance <= 0) {
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
        Serial.println("APPROACHING" + String(rounded) + " cm");

        
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
}

void changeMode() {
  modes = !modes;
}

void backlightOn() {
  digitalWrite(backlight, HIGH);
}

void backlightOff() {
  digitalWrite(backlight, LOW);
}
void buzz() {
  digitalWrite(buzzer, HIGH);
}
void unbuzz() {
  digitalWrite(buzzer, LOW);
}

