// Date and time functions using a PCF8523 RTC connected via I2C and Wire lib
#include "RTClib.h"

RTC_PCF8523 rtc;
int sec;
int rem;
int moistPin = A3;
int moistValue = 0;
int solenoidPin = 3;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup () {
  pinMode(3, OUTPUT);
  Serial.begin(57600);

#ifndef ESP8266
  while (!Serial); // wait for serial port to connect. Needed for native USB
#endif

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (! rtc.initialized() || rtc.lostPower()) {
    Serial.println("RTC is NOT initialized, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  rtc.adjust(DateTime(2022, 5, 11, 15,40,50));
  // This line sets the RTC with an explicit date & time, for example to set
  // January 21, 2014 at 3am you would call:
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));

  rtc.start();
  
  float drift = 43; // seconds plus or minus over oservation period - set to 0 to cancel previous calibration.
  float period_sec = (7 * 86400);  // total obsevation period in seconds (86400 = seconds in 1 day:  7 days = (7 * 86400) seconds )
  float deviation_ppm = (drift / period_sec * 1000000); //  deviation in parts per million (μs)
  float drift_unit = 4.34; // use with offset mode PCF8523_TwoHours
  int offset = round(deviation_ppm / drift_unit);
  Serial.print("Offset is "); Serial.println(offset); // Print to control offset

}

void loop () {

    
    DateTime now = rtc.now();
    
    sec = now.second();
    Serial.println(now.hour);
    rem = sec % 2;
    
    if (rem == 1) {
      Serial.println("odd");
    }
    if (rem == 0) {
      Serial.println("even");
    }

    Serial.println();
    delay(random(2000,4000));
}
