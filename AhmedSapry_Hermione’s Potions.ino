#include "Timer.h"
int sw = 2;
int red = 9;
int green = 8;
int white = 10 ;

Timer t; //the object of the libaray 


int flag = 0;
void setup()
{
  Serial.begin(9600);
  
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(white, OUTPUT);
  
  pinMode(sw, INPUT_PULLUP);
  
  int RedLedEvent = t.after(900000, Heat);                   // 15 mins equal to 900,000 milliseconds 
  int GreenLedEvent = t.every(120000, MixingIngredients);    // 2 mins equal to 12,0000 milliseconds 
  int WhiteLedEvent1 = t.after(300000, addingIngredients);   // 5 mins equal to 300,000 milliseconds
  int WhiteLedEvent2 = t.after(480000, addingIngredients);   // 8 mins equal to 480,000 milliseconds
  Serial.print("After event started id=");
  Serial.println(RedLedEvent); 
  
}

void loop()
{ 
  if(digitalRead(sw)==LOW)   //checking the state of switch 
   {
     flag=1;
     digitalWrite(red,HIGH);
   }

    if(flag==1)           // the flzg will allow to the code to continue 
   {
     t.update();
   }
   
}

void Heat()
{
 digitalWrite(red,LOW);
}

void MixingIngredients()
{
  Serial.println("stop the led event");
  t.oscillate(green, 500, LOW, 10);           // 10*500 = 5 S
}

void addingIngredients()
{
 t.oscillate(white, 250, LOW, 40);           // 250* 40 = 10 s 
}
