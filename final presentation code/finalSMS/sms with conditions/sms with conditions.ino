//admin -- https://webhook.site/#!/6e3155c8-220a-4c14-8939-425afd9e87cd

#include <SoftwareSerial.h>
/* Create object named SIM900 of the class SoftwareSerial */
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

//below for GSM
SoftwareSerial SIM900(9, 10);

//below for GPS
/* Create object named bt of the class SoftwareSerial */
SoftwareSerial GPS_SoftSerial(6, 5);/* (Rx, Tx) */
/* Create an object named gps of the class TinyGPSPlus */
TinyGPSPlus gps;
volatile float minutes, seconds;
volatile int degree, secs, mins;

//below for pressure
int fsrPin = 0;  // the FSR and 10K pulldown are connected to a0
int fsrReading;  // the analog reading from the FSR resistor divider

// defines pins numbers for US
const int trigPin = 3;
const int echoPin = 2;
// defines variables
long duration;
int distance;


void setup() {
  // for GSM
  SIM900.begin(9600); /* Define baud rate for software serial communication */
  Serial.begin(9600); /* Define baud rate for serial communication */

// for GPS
 GPS_SoftSerial.begin(9600);	/* Define baud rate for software serial communication */

  // for US sensor
  pinMode(trigPin, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);   // Sets the echoPin as an Input
}

void loop() {

// GPS start-----------------------------------------------------------------------------------------------------------------------------------------------
 smartDelay(1000);	/* Generate precise delay of 1ms */
        unsigned long start;
        double lat_val, lng_val, alt_m_val;
        uint8_t hr_val, min_val, sec_val;
        bool loc_valid, alt_valid, time_valid;
        lat_val = gps.location.lat();	/* Get latitude data */
        loc_valid = gps.location.isValid();	/* Check if valid location data is available */
        lng_val = gps.location.lng();	/* Get longtitude data */
        alt_m_val = gps.altitude.meters();	/* Get altitude data in meters */
        alt_valid = gps.altitude.isValid();	/* Check if valid altitude data is available */
        hr_val = gps.time.hour();	/* Get hour */
        min_val = gps.time.minute(); 	/* Get minutes */
        sec_val = gps.time.second();	/* Get seconds */
        time_valid = gps.time.isValid();	/* Check if valid time data is available */
        if (!loc_valid)
        {          
          Serial.print("Latitude : ");
          Serial.println("*****");
          Serial.print("Longitude : ");
          Serial.println("*****");
        }
        else
        {
          DegMinSec(lat_val);
          Serial.print("Latitude in Decimal Degrees : ");
          Serial.println(lat_val, 6);
          Serial.print("Latitude in Degrees Minutes Seconds : ");
          Serial.print(degree);
          Serial.print("\t");
          Serial.print(mins);
          Serial.print("\t");
          Serial.println(secs);
          DegMinSec(lng_val);	/* Convert the decimal degree value into degrees minutes seconds form */
          Serial.print("Longitude in Decimal Degrees : ");
          Serial.println(lng_val, 6);
          Serial.print("Longitude in Degrees Minutes Seconds : ");
          Serial.print(degree);
          Serial.print("\t");
          Serial.print(mins);
          Serial.print("\t");
          Serial.println(secs);
        }
        if (!alt_valid)
        {
          Serial.print("Altitude : ");
          Serial.println("*****");
        }
        else
        {
          Serial.print("Altitude : ");
          Serial.println(alt_m_val, 6);    
        }
        if (!time_valid)
        {
          Serial.print("Time : ");
          Serial.println("*****");
        }
        else
        {
          char time_string[32];
          sprintf(time_string, "Time : %02d/%02d/%02d \n", hr_val, min_val, sec_val);
          Serial.print(time_string);    
        }
     
// GPS end ------------------------------------------------------------------------------------------------------------------------------------------------




  // US start---------------------------------------------------------------------------------------------------------------------------------------------

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  if(distance > 6){
Serial.print("Distance greater than 6 triggered ");

// Pressure start------------------------------------------------------------------------------------------------------------------------------


  fsrReading = analogRead(fsrPin);

  Serial.println("Analog reading = ");
  Serial.println(fsrReading);  // print the raw analog reading


 if (fsrReading < 10) {
    Serial.println(" - No pressure");
  } else if (fsrReading < 200) {
    Serial.println(" - Light touch");
  } else if (fsrReading < 500) {
    Serial.println(" - Light squeeze");
  } else if (fsrReading < 800 ) {
    Serial.println(" - Medium squeeze");
    

  } else if (fsrReading > 800 ) {
    Serial.println(" - Big squeeze detected");
    Serial.println(" - trying SMS module");

    // below http request will be triggered once the pressure exceeds 800
    
    
    // SMS start------------------------------------------------------------------------------------------------------------------------------------------

   SIM900.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
     delay(1000);  // Delay of 1 second
     SIM900.println("AT+CMGS=\"+919080402253\"\r"); // Replace x with mobile number
     delay(1000);
     SIM900.println("Accident occured place - https://www.google.com/search?q=12.945850%2C79.167221");// The SMS text you want to send
     delay(100);
     SIM900.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 
      delay(20000); 
  // SMS end--------------------------------------------------------------------------------------------------------------------------------------------
    
  
  }
  delay(1000);

//pressure end------------------------------------------------------------------------------------------------------------------------------------------

  }

  // US End---------------------------------------------------------------------------------------------------------------------------------------------
delay(1000);
 
}

void ShowSerialData() {
  while (SIM900.available() != 0)      /* If data is available on serial port */
    Serial.write(char(SIM900.read())); /* Print character received on to the serial monitor */
}

void HttpGetRequest() {
}


// below function is for GPS
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (GPS_SoftSerial.available())	/* Encode data read from GPS while data is available on serial port */
      gps.encode(GPS_SoftSerial.read());
/* Encode basically is used to parse the string received by the GPS and to store it in a buffer so that information can be extracted from it */
  } while (millis() - start < ms);
}

// below function is for GPS
void DegMinSec( double tot_val)		/* Convert data in decimal degrees into degrees minutes seconds form */
{  
  degree = (int)tot_val;
  minutes = tot_val - degree;
  seconds = 60 * minutes;
  minutes = (int)seconds;
  mins = (int)minutes;
  seconds = seconds - minutes;
  seconds = 60 * seconds;
  secs = (int)seconds;
}



