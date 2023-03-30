#include <SoftwareSerial.h>
/* Create object named SIM900 of the class SoftwareSerial */
SoftwareSerial SIM900(9, 10);
void setup() {
  SIM900.begin(9600); /* Define baud rate for software serial communication */
  Serial.begin(9600); /* Define baud rate for serial communication */
}

void loop() {

  String temp = "vignesh";
  Serial.println("HTTP get method :");
  Serial.print("AT\\r\\n");
  SIM900.println("AT"); /* Check Communication */
  delay(1000);
  ShowSerialData(); /* Print response on the serial monitor */
  delay(1000);
  /* Configure bearer profile 1 */
  Serial.print("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"\\r\\n");
  SIM900.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\""); /* Connection type GPRS */
  delay(1000);
  ShowSerialData();
  delay(1000);
  Serial.print("AT+SAPBR=3,1,\"APN\",\"airtelgprs.com\"\\r\\n");
  SIM900.println("AT+SAPBR=3,1,\"APN\",\"airtelgprs.com\""); /* APN of the provider */
  delay(1000);
  ShowSerialData();
  delay(1000);
  Serial.print("AT+SAPBR=1,1\\r\\n");
  SIM900.println("AT+SAPBR=1,1"); /* Open GPRS context */
  delay(1000);
  ShowSerialData();
  delay(1000);
  Serial.print("AT+SAPBR=2,1\\r\\n");
  SIM900.println("AT+SAPBR=2,1"); /* Query the GPRS context */
  delay(1000);
  ShowSerialData();
  delay(1000);

  Serial.print("AT+HTTPINIT\\r\\n");
  SIM900.println("AT+HTTPINIT"); /* Initialize HTTP service */

  // Serial.print("AT+HTTPSSL\\r\\n");
  //   SIM900.println("AT+HTTPSSL"); /* Initialize HTTP service */



  delay(1000);
  ShowSerialData();
  delay(1000);



  Serial.print("AT+HTTPPARA=\"CID\",1\\r\\n");
  SIM900.println("AT+HTTPPARA=\"CID\",1"); /* Set parameters for HTTP session */


  delay(1000);
  ShowSerialData();
  delay(1000);


  
  // Serial.print("AT+HTTPPARA=\"URL\",\"webhook.site/ad8f49d1-67dc-4d43-acd4-2e9e2269aca3?gpsLocationLat=0000&gpsLocationLon=0000&pressure=0000&groundClearance=0000&name=harish&emergencyContact=11111&address=street\"\\r\\n");
  Serial.print("AT+HTTPPARA=\"URL\",\"webhook.site/8ce94d83-2f61-4a8d-bd9a-a579846f1878?gpsLocationLat=12.945970&gpsLocationLon=79.167060&pressure=870&groundClearance=18cm&name=harish&emergencyContact=987654321&address=11street\"\\r\\n");
  SIM900.println("AT+HTTPPARA=\"URL\",\"webhook.site/8ce94d83-2f61-4a8d-bd9a-a579846f1878?gpsLocationLat=12.945970&gpsLocationLon=79.167060&pressure=870&groundClearance=18cm&name=harish&emergencyContact=987654321&address=11street\""); /* Set parameters for HTTP session */


  delay(1000);
  ShowSerialData();
  delay(1000);
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
  delay(1000);
  ShowSerialData();
  delay(1000);
  Serial.print("AT+SAPBR=0,1\\r\\n");
  SIM900.println("AT+SAPBR=0,1"); /* Close GPRS context */
  delay(1000);
  ShowSerialData();
  delay(1000);
}

void ShowSerialData() {
  while (SIM900.available() != 0)      /* If data is available on serial port */
    Serial.write(char(SIM900.read())); /* Print character received on to the serial monitor */
}