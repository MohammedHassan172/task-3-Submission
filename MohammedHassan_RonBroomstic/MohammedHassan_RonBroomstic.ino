#define IMU_ADDRESS 0x68
#include <Wire.h>
#define led 12
//declaring the offset for thr gyroscope
int32_t x_gyro_offset =0,y_gyro_offset =0,z_gyro_offset =0;
int16_t x_gyro =0,y_gyro =0,z_gyro =0;
bool donecalibrate = false;
const float Pi = 3.14159;
unsigned long startMillis;
unsigned long currentMillis;
const unsigned long period = 500;
void setup() {
  //setting up the pins and the IMU
  pinMode(led,OUTPUT);
  setImuRegister(0x6B,0x00);
  //setting the scale for the gyroscope
  setImuRegister(0x1B,0x00);
  //to calibrate the gyroscope
  calibrateImu(3000);
  startMillis = millis();

}

void loop() 
{
   currentMillis = millis(); 
  //when the calibration is done we start to get the readings 
  if(donecalibrate == true)
  {
    x_gyro = (readImu2Byte(0x43)-x_gyro_offset) * (180/Pi);
    y_gyro = (readImu2Byte(0x45)-y_gyro_offset) * (180/Pi);
    z_gyro = (readImu2Byte(0x47)-z_gyro_offset) * (180/Pi);
   //to flash the red light if the roll or the pitch higher than 60 degrees
    if(x_gyro > 60 || y_gyro > 60)
    {
       if (currentMillis - startMillis >= period)  
       {
         digitalWrite(led, !digitalRead(led));  
         startMillis = currentMillis; 
       }
    }
  }
}
//the function to set up the IMU
void setImuRegister(uint8_t reg,uint8_t val)
{
  Wire.beginTransmission(IMU_ADDRESS);
  Wire.write(reg);
  Wire.write(val);
  Wire.endTransmission();
}
//to read 2 bytes
uint16_t readImu2Byte(uint8_t reg)
{
  uint16_t data=0;
  Wire.beginTransmission(IMU_ADDRESS);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(IMU_ADDRESS,2);
  while(Wire.available() < 1); 
  data = Wire.read()<< 8 | Wire.read();
  return data;
}
// the function to calibrate the IMU
void calibrateImu(uint32_t n_iterations)
{
 for(uint32_t i = 0;i < n_iterations;i++)
  {
   x_gyro_offset += readImu2Byte(0x43);
   y_gyro_offset += readImu2Byte(0x45);
   z_gyro_offset += readImu2Byte(0x47);
  } 
  x_gyro_offset /= n_iterations;
  y_gyro_offset /= n_iterations;
  z_gyro_offset /= n_iterations;
  donecalibrate = true;
}
void turn_off()
{
  digitalWrite(led,LOW);
}
