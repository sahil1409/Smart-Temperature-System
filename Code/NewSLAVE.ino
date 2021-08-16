Code:

#include <HCSR04.h>
#define trigPin 7
#define echoPin 6
#include <SoftwareSerial.h>
SoftwareSerial BTserial(0, 1); // RX, TX

UltraSonicDistanceSensor distanceSensor(trigPin, echoPin);
int tempReading;
double tempK;
float tempC;
int rounded;
int temp_round;double distance;
float resolution=3.3/1024; //for conversion of voltage to temp
int val;
int tempPin = A0;

void setup() {
  Serial.begin(9600); //baud rate
  BTserial.begin(38400); //baud rate for bluetooth
}

void loop() {
  if (BTserial.available()) //checking mode via Bluetooth
    {  
       char mode = BTserial.read();//reading mode via bluetooth
       if (mode=='1') { //calculation of Temperature
          double temp = ((analogRead(A0) * resolution) * 100)+23.89;
          Serial.write(temp);
       }
       else { //calculation for distance
          tempReading = analogRead(A0);
          tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
          tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK );
          tempC = tempK - 273.15;
          distance = distanceSensor.measureDistanceCm(tempC);
          Serial.write(distance);
       }
    }
    if (Serial.available())
      {
        BTserial.write(Serial.read()); //sending data to BT
      }
}
