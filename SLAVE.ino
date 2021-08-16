#include <HCSR04.h>
#define trigPin 7
#define echoPin 6

#include <SoftwareSerial.h>0
SoftwareSerial BTserial(1, 0); // RX | TX

UltraSonicDistanceSensor distanceSensor(trigPin, echoPin);
int tempReading;
double tempK;
float tempC;
int rounded;
int temp_round;double distance;
float resolution=3.3/1024;
int val;
int tempPin = A0;

void setup() {
  Serial.begin(9600);//Baud rate
  BTserial.begin(38400);
}

void loop() {
  Serial.println("m");
  if (BTserial.available())
    {  
       char mode = BTserial.read();
       if (mode=='1') {
          Serial.println("t");
          double temp = ((analogRead(A0) * resolution) * 100)+23.89;
          BTserial.write(temp);
       }
       else {
          Serial.println("d");
          tempReading = analogRead(A0);
          //Serial.println("Temp:" + String(tempReading) + " K");
          tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
          tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK );
          tempC = tempK - 273.15;
          distance = distanceSensor.measureDistanceCm(tempC);
          BTserial.write(distance);
          Serial.println(distance);
       }
    }





  
}

