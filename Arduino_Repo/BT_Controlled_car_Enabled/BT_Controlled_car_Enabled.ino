/***************************BLUETOOTH CONTROLLED CAR CODE**************************/

//Declare the arduino pins

int lm1 = 4;
int lm2 = 5;
int rm1 = 6;
int rm2 = 7;


//Enable Pin
int enA = 3;
int enB = 10;

int fl = 14;//A0
//int bl = A1;
int horn = 8;

void setup()
{
  //initlize the mode of the pins
   pinMode(lm1,OUTPUT);
   pinMode(lm2,OUTPUT);
   pinMode(rm1,OUTPUT);
   pinMode(rm2,OUTPUT);
   pinMode(enA,OUTPUT);
   pinMode(enB,OUTPUT);
   
   pinMode(horn,OUTPUT);
   pinMode(fl,OUTPUT);
   //pinMode(bl,OUTPUT);

   //set the serial communication rate
  Serial.begin(9600);
}

void demoOne()
{
  // this function will run the motors in both directions at a fixed speed
  // turn on motor A
  digitalWrite(lm1, HIGH);
  digitalWrite(lm2, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, 180);
  // turn on motor B
  digitalWrite(rm1, HIGH);
  digitalWrite(rm2, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enB, 180);
  delay(10);
}
//Backwards
void demoTwo()
{
  // this function will run the motors in both directions at a fixed speed
  // turn on motor A
  digitalWrite(lm1, LOW);
  digitalWrite(lm2, HIGH);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, 100);
  // turn on motor B
  digitalWrite(rm1, LOW);
  digitalWrite(rm2, HIGH);
  // set speed to 200 out of possible range 0~255
  analogWrite(enB, 100);
  delay(10);
}
//Right
void demoThree()
{
  // this function will run the motors in both directions at a fixed speed
  // turn on motor A
  digitalWrite(lm1, LOW);
  digitalWrite(lm2, HIGH);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, 150);
  // turn on motor B
  digitalWrite(rm1, HIGH);
  digitalWrite(rm2, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enB, 150);
  delay(10);
}
//Right
void demoFour()
{
  // this function will run the motors in both directions at a fixed speed
  // turn on motor A
  digitalWrite(lm1, HIGH);
  digitalWrite(lm2, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, 150);
  // turn on motor B
  digitalWrite(rm1, LOW);
  digitalWrite(rm2, HIGH);
  // set speed to 200 out of possible range 0~255
  analogWrite(enB, 150);
  delay(10);
}
void loop()
{
  //check whether arduino is reciving signal or not 
  while(Serial.available() == 0);
  char val = Serial.read() ;//reads the signal
  Serial.println(val);

  /*********For Forward motion*********/
  
  if (val == 'F')
  {
    Serial.println("FORWARD");

    
    demoOne();
    delay(1);
       
  }

 
    /*********For Backward Motion*********/
  else if(val == 'B')
  {
  Serial.println("BACK");
   
  
    demoTwo();
    delay(1);
       
  
  }
   /*********Right*********/
  else if(val == 'R')
  {
  Serial.println("RIGHT");
   
      demoThree();
      delay(1);
   
  }
   /*********Left*********/
  else if(val == 'L')
  {
   Serial.println("LEFT");
    
    demoFour();
    delay(1);
     
  
  }
   /*********Horn*********/
 else if(val == 'V')
  {
  digitalWrite(horn,HIGH);
  }
  else if(val == 'v')
  {
   digitalWrite(horn,LOW);
  }
  
  /*********Front Lights*********/
  else if(val == 'W')
  {
  digitalWrite(fl,HIGH);
  }
  else if(val == 'w')
  {
  digitalWrite(fl,LOW);
  }
  /*********Back Lights*********/
  else if(val == 'U')
  {
   // digitalWrite(bl,HIGH);
  }
  else if(val == 'u')
  {
   // digitalWrite(bl,LOW);
  }
  /*********STOP*********/
  else
  {
  //Serial.println(val); //Invalid!!!
     digitalWrite(lm1,LOW);  digitalWrite(rm1,LOW);
    digitalWrite(lm2,LOW);       digitalWrite(rm2,LOW);

  }
  Serial.flush();
  delay(1);
}
