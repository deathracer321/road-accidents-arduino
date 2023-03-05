#include <SoftwareSerial.h>
/* Create object named SIM900 of the class SoftwareSerial */

SoftwareSerial SIM900(9, 10);


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


  // for US sensor
  pinMode(trigPin, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);   // Sets the echoPin as an Input
}

void loop() {


  fsrReading = analogRead(fsrPin);

  Serial.println("Analog reading = ");
  Serial.println(fsrReading);  // print the raw analog reading


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
 if (fsrReading < 10) {
    Serial.println(" - No pressure");
  } else if (fsrReading < 200) {
    Serial.println(" - Light touch");
  } else if (fsrReading < 500) {
    Serial.println(" - Light squeeze");
  } else if (fsrReading < 800 ) {
    Serial.println(" - Medium squeeze");
    Serial.println(" - trying http module");

  } else if (fsrReading > 800 ) {
    Serial.println(" - Big squeeze detected");
    Serial.println(" - distance detected inside if else" + distance );
    Serial.println(" - trying http module");

    // below http request will be triggered once the pressure exceeds 800
    
    
    // GSM start------------------------------------------------------------------------------------------------------------------------------------------

    Serial.println("HTTP get method :");
    Serial.print("AT\\r\\n");
    SIM900.println("AT"); /* Check Communication */
    delay(5000);
    ShowSerialData(); /* Print response on the serial monitor */
    delay(5000);
    /* Configure bearer profile 1 */
    Serial.print("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"\\r\\n");
    SIM900.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\""); /* Connection type GPRS */
    delay(5000);
    ShowSerialData();
    delay(5000);
    Serial.print("AT+SAPBR=3,1,\"APN\",\"airtelgprs.com\"\\r\\n");
    SIM900.println("AT+SAPBR=3,1,\"APN\",\"airtelgprs.com\""); /* APN of the provider */
    delay(5000);
    ShowSerialData();
    delay(5000);
    Serial.print("AT+SAPBR=1,1\\r\\n");
    SIM900.println("AT+SAPBR=1,1"); /* Open GPRS context */
    delay(5000);
    ShowSerialData();
    delay(5000);
    Serial.print("AT+SAPBR=2,1\\r\\n");
    SIM900.println("AT+SAPBR=2,1"); /* Query the GPRS context */
    delay(5000);
    ShowSerialData();
    delay(5000);

    Serial.print("AT+HTTPINIT\\r\\n");
    SIM900.println("AT+HTTPINIT"); /* Initialize HTTP service */


    delay(5000);
    ShowSerialData();
    delay(5000);



    Serial.print("AT+HTTPPARA=\"CID\",1\\r\\n");
    SIM900.println("AT+HTTPPARA=\"CID\",1"); /* Set parameters for HTTP session */


    delay(5000);
    ShowSerialData();
    delay(5000);


    Serial.print("AT+HTTPPARA=\"URL\",\"webhook.site/ad8f49d1-67dc-4d43-acd4-2e9e2269aca3?gpsLocationLat=0000&gpsLocationLon=0000&pressure=0000&groundClearance=0000&name=harish&emergencyContact=11111&address=street\"\\r\\n");
    SIM900.println("AT+HTTPPARA=\"URL\",\"webhook.site/ad8f49d1-67dc-4d43-acd4-2e9e2269aca3?gpsLocationLat=0000&gpsLocationLon=0000&pressure=0000&groundClearance=0000&name=harish&emergencyContact=11111&address=street\""); /* Set parameters for HTTP session */


    delay(5000);
    ShowSerialData();
    delay(5000);
    Serial.print("AT+HTTPACTION=0\\r\\n");
    SIM900.println("AT+HTTPACTION=0"); /* Start GET session */
    delay(10000);
    ShowSerialData();
    delay(10000);
    Serial.print("AT+HTTPREAD\\r\\n");
    SIM900.println("AT+HTTPREAD"); /* Read data from HTTP server */
    delay(8000);
    ShowSerialData();
    delay(8000);
    Serial.print("AT+HTTPTERM\\r\\n");
    SIM900.println("AT+HTTPTERM"); /* Terminate HTTP service */
    delay(5000);
    ShowSerialData();
    delay(5000);
    Serial.print("AT+SAPBR=0,1\\r\\n");
    SIM900.println("AT+SAPBR=0,1"); /* Close GPRS context */
    delay(5000);
    ShowSerialData();
    delay(5000);
    Serial.println(" - Completed http module");

  // GSM end--------------------------------------------------------------------------------------------------------------------------------------------
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
