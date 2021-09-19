#include<Wire.h>

#define IMU_ADDRESS 0x68 //the address of sensor 
#define led 8  //pin 8 of arduino 
int16_t x_accel ,y_accel ,z_accel; //accelration variables 
int16_t x_gyro , y_gyro,z_gyro ;   //degress variables 
int16_t temp;

int32_t x_accel_offest = 0 ,y_accel_offest = 0 ,z_accel_offest = 0;
int32_t x_gyro_offest =0  , y_gyro_offest =0 ,z_gyro_offest =0  ;





void setup() {
  setImuRegister(0x6B,0x00); //setting our sensor 
  setImuRegister(0x1C,0x18); //chosing the scale 
  setImuRegister(0x1B,0x18);
  calibrateImu(5000);    //calibrating  step
  pinMode(led,OUTPUT);
}

void loop() {
  readImuAll(); //reading all the physical properties 
  x_gyro = x_gyro - x_gyro_offest; 
  y_gyro = y_gyro - y_gyro_offest;
  z_gyro = z_gyro - z_gyro_offest;
//Scaling 
 x_gyro = (x_gyro*2000)/(32,767);
 y_gyro = (y_gyro*2000)/(32,767);
 z_gyro = (z_gyro*2000)/(32,767);
// converting to degrees 
 x_gyro = (x_gyro*180)/PI;
 y_gyro = (y_gyro*180)/PI;
 z_gyro = (z_gyro*180)/PI;
 // checking the condition 
 if((x_gyro>60)||(y_gyro>60))
 {

  digitalWrite(led,HIGH);
  delay(100);
 }else 
 {
  digitalWrite(led,LOW);
 }
 delay(50); // wait a little bit 
 
}


void setImuRegister(uint8_t reg , uint8_t val)
{
   Wire.beginTransmission(IMU_ADDRESS);
   Wire.write(reg);
   Wire.write(val);
   Wire.endTransmission();
}

uint8_t readImu1Byte(uint8_t reg)
{
  uint8_t data1 = 0 ;
  Wire.beginTransmission(IMU_ADDRESS);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(IMU_ADDRESS,1);
  while (Wire.available()<1);
  data1 = Wire.read();
  return data1;
}

uint16_t readImu2Bytes(uint8_t reg)
{
  uint16_t data1 = 0 ;
  Wire.beginTransmission(IMU_ADDRESS);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(IMU_ADDRESS,2);
  while (Wire.available()<2);
  data1 = Wire.read()<<8 | Wire.read();
  return data1;
}

void readImuAll()
{
 Wire.beginTransmission(0x6B);
 Wire.write(0x3B);
 Wire.endTransmission();
 Wire.requestFrom(0x68,14); 
 while(Wire.available()<14);
 x_accel = Wire.read()<<8 | Wire.read();
 y_accel = Wire.read()<<8 | Wire.read();
 z_accel = Wire.read()<<8 | Wire.read();
 temp = Wire.read()<<8 | Wire.read();
 x_gyro = Wire.read()<<8 | Wire.read();
 y_gyro = Wire.read()<<8 | Wire.read();
 z_gyro = Wire.read()<<8 | Wire.read();
}

void calibrateImu(uint32_t n_iterations)
{

  for(uint32_t i = 0 ; i<n_iterations;i++)
  {

    x_accel_offest += readImu2Bytes(0x3B);
    y_accel_offest += readImu2Bytes(0x3D);
    z_accel_offest += readImu2Bytes(0x3F);


    

    x_gyro_offest += readImu2Bytes(0x43);
    y_gyro_offest += readImu2Bytes(0x45);
    z_gyro_offest += readImu2Bytes(0x47);

  }

  x_accel_offest /= n_iterations;
  y_accel_offest /= n_iterations;
  z_accel_offest /= n_iterations;

  x_gyro_offest /= n_iterations;
  y_gyro_offest /= n_iterations;
  z_gyro_offest /= n_iterations;


}
