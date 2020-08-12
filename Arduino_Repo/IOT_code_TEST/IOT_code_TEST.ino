//load libraries
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <stdlib.h>



#define I2C_ADDR          0x3F        //Define I2C Address where the PCF8574A is
#define BACKLIGHT_PIN      3
#define En_pin             2
#define Rw_pin             1
#define Rs_pin             0
#define D4_pin             4
#define D5_pin             5
#define D6_pin             6
#define D7_pin             7

//Initialise the LCD
LiquidCrystal_I2C      lcd(I2C_ADDR, En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);


#define DEBUG true
#define SSID "CyanideHSpot"     // "SSID-WiFiname"
#define PASS "aeronaut" // "password"
#define IP "184.106.153.149"      // thingspeak.com ip

String msg = "GET /update?key=QGV29X62I82TL5I3"; //change it with your api key like "GET /update?key=Your Api Key"
SoftwareSerial esp8266(9,10);


//Variables
float temp;
int hum;
String tempC;
int error;

// Rain Drop Sensor

int nRainln = A1;
int nRainDigitalln = 2;
int nRainVal;
boolean blsRaining = false;
String strRaining;

void setup()
{
  lcd.begin(16, 2);
   lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
    lcd.setBacklight(HIGH);  
  delay(100);
  lcd.setCursor(0,1);
  lcd.print("Connecting...");
  Serial.begin(115200); //or use default 115200.
  esp8266.begin(115200);
  Serial.println("AT");
  esp8266.println("AT");

  pinMode(2, INPUT);

  delay(5000);

  if(esp8266.find("OK"))
  {
    Serial.println("ESP8266 FOUND!!");
    connectWiFi();
  }
}

void loop()
{
  //Rain drop code
  nRainVal = analogRead(nRainln);
  blsRaining = !(digitalRead(nRainDigitalln));

  /*
  if (blsRaining) {
    strRaining = "YES";
  }
  else {
    strRaining = "NO";
  }
  */
  
   //Condition
   if ((nRainVal) <= 500) {
    strRaining = "YES";
  }
  else {
    strRaining = "NO";
  }
  
  Serial.print ("Raining?: ");
  Serial.println (strRaining);
  Serial.print(" Moisture Level: ");
  Serial.println(nRainVal);
  delay(1000);
  
  
  lcd.clear();
  //Read temperature and humidity values from DHT sensor:
  start: //label
    error=0;
//    temp = dht.readTemperature();
//    hum = dht.readHumidity();
    lcd.setCursor(0, 0);
    lcd.print("Temp = ");
    lcd.print(temp);
    lcd.print(" C");
    delay (100);
    lcd.setCursor(0, 1); // set the cursor to column 0, line 2
    lcd.print("Humi = ");
    lcd.print(hum);
    lcd.print(" %");
    delay(1000);
    char buffer[10];
    // there is a useful c function called dtostrf() which will convert a float to a char array
    //so it can then be printed easily.  The format is: dtostrf(floatvar, StringLengthIncDecimalPoint, numVarsAfterDecimal, charbuf);
    tempC = dtostrf(temp, 4, 1, buffer);
    updateTemp();
    //Resend if transmission is not completed
    if (error==1)
    {
      goto start; //go to label "start"
    } 
  delay(3600);
}

void updateTemp()
{
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += IP;
  cmd += "\",80"; 
  Serial.println(cmd);
  esp8266.println(cmd);
  delay(2000);
  if(esp8266.find("Error"))
  {
    return;
  }
  cmd = msg ;
  cmd += "&field1=";    //field 1 for temperature
  cmd += nRainVal; //tempC
  cmd += "&field2=";  //field 2 for humidity
  cmd += String(nRainVal); //hum
  cmd += "\r\n";
  Serial.print("AT+CIPSEND=");
  esp8266.print("AT+CIPSEND=");
  Serial.println(cmd.length());
  esp8266.println(cmd.length());
  if(esp8266.find(">"))
  {
    Serial.print(cmd);
    esp8266.print(cmd);
  }
  else
  {
    Serial.println("AT+CIPCLOSE");
    esp8266.println("AT+CIPCLOSE");
    //Resend...
    error=1;
  }
}

boolean connectWiFi()
{
  Serial.println("AT+CWMODE=1");
  esp8266.println("AT+CWMODE=1");
  delay(2000);
  String cmd="AT+CWJAP=\"";
  cmd+=SSID;
  cmd+="\",\"";
  cmd+=PASS;
  cmd+="\"";
  Serial.println(cmd);
  esp8266.println(cmd);
  delay(5000);
  if(esp8266.find("OK"))
  {
    return true;
  }
  else
  {
    return false;
  }

  //delay
  delay(10000);
}
