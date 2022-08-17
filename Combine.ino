// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include <Wire.h>
#include <Servo.h>
float temp;
int tempPin = 1;
#include "RTClib.h"
#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.
int Threshold = 550;           // Determine which Signal to "count as a beat" and which to ignore.
                               // Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
                               // Otherwise leave the default "550" value. 
const int PulseWire = 0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object 
int ledPin=13;
RTC_DS1307 rtc;
Servo servo;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
void setup () {
 while (!Serial); // for Leonardo/Micro/Zero
 Serial.begin(57600);
 pulseSensor.analogInput(PulseWire);   
  pulseSensor.setThreshold(Threshold); 
  if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.  
  } 
 if (! rtc.begin()) {
   Serial.println("Couldn't find RTC");
   while (1);
 }
 {  
  servo.attach(9); 
   pinMode(ledPin,OUTPUT);
  }
}
void loop () {{
  DateTime now = rtc.now();
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
 delay(6000);//Delay of 6 seconds
}
{
 servo.write(180);//180 angle
 digitalWrite(ledPin,HIGH); //HIGH is set to about 5V PIN13
 int myBPM = pulseSensor.getBeatsPerMinute(); 
 if (pulseSensor.sawStartOfBeat())           // Constantly test to see if "a beat happened". 
 Serial.println("♥  A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
 Serial.print("BPM: ");                        // Print phrase "BPM: " 
 Serial.println(myBPM);                        // Print the value inside of myBPM. 
 temp = analogRead(tempPin);// read analog volt from sensor and save to variable temp
 temp = temp * 0.48828125;// convert the analog volt to its temperature equivalent
   Serial.print("TEMPERATURE = ");
   Serial.print(temp); // display temperature value
   Serial.print("*C");
   Serial.println();
 delay(500);
 servo.write(0);
 digitalWrite(ledPin,LOW);  //LOW is set to about 5V PIN13
}
} 
