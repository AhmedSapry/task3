//preprossing for the interrupt pins 
int inter1_1 = 2 ;
int inter1_2 = 3 ;
int inter2_1 = 18 ;
int inter2_2 = 19 ;
int inter3_1 = 20 ;
int inter3_2 = 21;

//counter for each encoder 
double count1 = 0 ;
double count2 = 0 ;
double count3 = 0 ;
//the data 
int ppr = 2048 ;
float revo1 = 0 ;
float revo2 = 0 ;
float revo3 = 0 ;
int angle1 = 0;
int angle2 = 0; 
int angle3 = 0 ;
// the led
int led = 4;



void setup() {
  
  pinMode(inter1_1,INPUT_PULLUP);
  pinMode(inter1_2,INPUT_PULLUP);
  pinMode(inter2_1,INPUT_PULLUP);
  pinMode(inter2_2,INPUT_PULLUP);
  pinMode(inter3_1,INPUT_PULLUP);
  pinMode(inter3_2,INPUT_PULLUP);
  pinMode(led,OUTPUT);
  //Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(inter1_1),ISR_A1,CHANGE);
  attachInterrupt(digitalPinToInterrupt(inter1_2),ISR_B1,CHANGE);
  attachInterrupt(digitalPinToInterrupt(inter2_1),ISR_A2,CHANGE);
  attachInterrupt(digitalPinToInterrupt(inter2_2),ISR_B2,CHANGE);
  attachInterrupt(digitalPinToInterrupt(inter3_1),ISR_A3,CHANGE);
  attachInterrupt(digitalPinToInterrupt(inter3_2),ISR_B3,CHANGE);
  
}

void loop() {
  //number of revolutions for each encoder 
  revo1 = (count1)/(ppr*4);
  revo2 = (count2)/(ppr*4);
  revo3 = (count3)/(ppr*4);
  
  angle1 = revo1*360;
  angle2 = revo2*360;
  angle3 = revo3*360;
  //the condition 
  if((angle1==37)&&(angle2==10)&&(angle3==54))
  {

  digitalWrite(led,HIGH);
    
  }  
}
//callback functions 
void ISR_A1()
{
 if(digitalRead(inter1_1) != digitalRead(inter1_2))
 count1++;
 else 
 count1--;

}
void ISR_B1()
{
 if(digitalRead(inter1_1) == digitalRead(inter1_2))
 count1++;
 else 
 count1--;

}
void ISR_A2()
{
 if(digitalRead(inter2_1) != digitalRead(inter2_2))
 count2++;
 else 
 count2--;

}
void ISR_B2()
{
 if(digitalRead(inter2_1) == digitalRead(inter2_2))
 count2++;
 else 
 count2--;

}
void ISR_A3()
{
 if(digitalRead(inter3_1) != digitalRead(inter3_2))
 count3++;
 else 
 count3--;

}
void ISR_B3()
{
 if(digitalRead(inter3_1) == digitalRead(inter3_2))
 count3++;
 else 
 count3--;

}
