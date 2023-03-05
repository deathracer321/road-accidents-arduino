#include <TinyGPS.h>;
#include <SoftwareSerial.h>;

SoftwareSerial mySerial(9, 10); char msg;
char call;
const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor const int echoPin = 6; // Echo Pin of Ultrasonic Sensor int fsrAnalogPin = 0; // FSR is connected to analog 0
int fsrReading;	// the analog reading from the FSR resistor divider float lat ,lon ; // create variable for latitude and longitude object SoftwareSerial gpsSerial(3,4);//rx,tx

TinyGPS gps; // create gps object


void setup() { mySerial.begin(9600);
Serial.begin(9600); // Starting Serial Terminal Serial.println("The GPS Received Signal:"); gpsSerial.begin(9600);
}


void loop() {
 
while(gpsSerial.available()){ // check for gps data if(gps.encode(gpsSerial.read()))// encode gps data
{
gps.f_get_position(&lat,&lon); // get latitude and longitude


Serial.print(lat); 
Serial.print(" "); 
Serial.print(lon);
Serial.print(" ");
}
}


String latitude = String(lat,6); 
String longitude = String(lon,6);
Serial.println(latitude+";"+longitude); delay(1000);

long duration, inches, cm; unsigned long seconds=1000L; 
pinMode(pingPin, OUTPUT); 
digitalWrite(pingPin, LOW); 
delayMicroseconds(2); 
digitalWrite(pingPin, HIGH); 
delayMicroseconds(10);
digitalWrite(pingPin, LOW); pinMode(echoPin, INPUT);
duration = pulseIn(echoPin, HIGH);
 
inches = microsecondsToInches(duration); 
cm = microsecondsToCentimeters(duration); 
fsrReading = analogRead(fsrAnalogPin); 
Serial.print("Analog reading = "); 
Serial.println(fsrReading); Serial.print(inches);
Serial.print("in, "); 
Serial.print(cm); Serial.print("cm"); Serial.println();
if(cm >10 || fsrReading >100){
mySerial.println("AT+CMGF=1");	//Sets the GSM Module in Text Mode delay(1000); // Delay of 1000 milli seconds or 1 second
mySerial.println("AT+CMGS=\"+918825739212\"\r"); // Replace x with mobile number
delay(1000);
mySerial.println("EMETGENCY!!!!! SEND AN AMBULANCE TO THE SHARED LOCATION ",latitude," and ",longitude );// The SMS text you want to send
delay(100);
mySerial.println((char)26);// ASCII code of CTRL+Z delay(1000);
exit(0);


}
delay(seconds);
}
 
long microsecondsToInches(long microseconds) { return microseconds / 74 / 2;
}


long microsecondsToCentimeters(long microseconds) { return microseconds / 29 / 2;
}

