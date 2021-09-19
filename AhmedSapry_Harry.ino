// the 3 IR sensors 

const int IRRight = 8 ; 
const int IRCenter = 9 ;
const int IRLeft= 10;
int IR1 ;
int IR2 ;
int IR3 ;
int Lflag = 1 ;
int Rflag = 1 ; 
int Lcounter = 0 ;
int Rcounter = 0 ;

// pins of the DC motors 
const int in1 = 3 ;
const int in2 = 4 ;
const int in3 = 5;
const int in4 = 6 ;


void setup() {
  //sensors are Input 
  pinMode(IRRight,INPUT);
  pinMode(IRCenter,INPUT);
  pinMode(IRLeft,INPUT);
  // signal for motors are output 
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  

}

void loop() {
// taking the read from the sensors   
IR1 = digitalRead(IRRight);
IR2 = digitalRead(IRCenter);
IR3 = digitalRead(IRLeft);  

// IR == 1 means that it show black 
// and 0 means white 

if((IR1 == 0)&&(IR2==1)&&(IR3==0))
{
  forward();

} else 
{
  if((IR1 == 0)&&(IR2==1)&&(IR3==1)) {

   if(Lcounter<0){
    forward();
  }else{
  rotate90left();
  Lcounter ++;
    }
  }
   
  if((IR1 == 1)&&(IR2==0)&&(IR3==0))

  {
     if(Lcounter>=0){
       forward();
     }else{
        rotate90Right();
        Lcounter--;
     }
    }
  
   if((IR1 == 0)&&(IR2==0)&&(IR3==0)) 

  {
  // rotation 180 degree to return to the line again 
  rotate90Right();
  rotate90Right();
  
  } if((IR1 == 1)&&(IR2==1)&&(IR3==1)) 

  {
   if(Lcounter>=0)
    {
     rotate90left();
     Lcounter = 0 ;
     }
     if(Lcounter<0)
    {
     rotate90Right();
     Lcounter = 0 ;
     }
    
   
}
// which is the 3 IR read black 
//else{

//stOp();
  
// }


  
 }

}

void forward()
{

  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  
}
void backward()
{

  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  
}
void rotate90Right()
{
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  delay(500);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  
}
void rotate90left()
{
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  delay(500);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
}

void stOp()
{
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
}
