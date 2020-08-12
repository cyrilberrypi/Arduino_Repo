int PIRPin = 3;
int LEDPin = 4;

void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  pinMode (LEDPin,OUTPUT);
  pinMode (PIRPin,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  //status
  int LDRStatus = analogRead (A0);

  //Still on this
  //If condition
  if (PIRPin, HIGH){
    digitalWrite (LEDPin,HIGH);
    //Serial.print ("turn OFF the LED:");
    Serial.println("Motion Detected");
  }else {
    digitalWrite (LEDPin,LOW);
    //Serial.print("ON the LED:");
  }
  delay (20);

}
