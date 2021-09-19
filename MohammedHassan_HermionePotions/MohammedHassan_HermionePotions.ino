#include <Event.h>
#include <Timer.h>
#define red 12
#define white 11
#define green 13
#define push_button 2
Timer myTimer;
void setup() 
{
 //setting the pins 
 pinMode(red,OUTPUT);
 pinMode(white,OUTPUT);
 pinMode(green,OUTPUT);
 pinMode(push_button,INPUT);
 // to call the timers after pressing the button
 attachInterrupt(digitalPinToInterrupt(push_button), dothings,HIGH);
}

void loop() 
{
  //update the timer
   myTimer.update(); 
}
//to turn off the red light after 15 mins and to also stop the timer
void redLight_heatOFF()
{
  digitalWrite(red,LOW);
  myTimer.stop(1);
}
//flashing the green light every 2 min
void greenLight_MixingON()
{
  digitalWrite(green,HIGH);
  myTimer.after(2000,greenLight_MixingFLASHES);
}
//to flash the green light for 2 sec
void greenLight_MixingFLASHES()
{
  digitalWrite(green,LOW);
}
//flashing the White Light after 5 mins and 10 mins
void WhiteLight_IngredientON()
{
  digitalWrite(white,HIGH);
  myTimer.after(10000,WhiteLight_IngredientOFF);
}
//to flash the White light for 10 sec
void WhiteLight_IngredientOFF()
{
  digitalWrite(white,LOW);
}
//setting up the timers
void dothings()
{
  digitalWrite(red,HIGH);
  myTimer.after(900000,redLight_heatOFF);
  myTimer.every(120000,greenLight_MixingON);
  myTimer.after(300000,WhiteLight_IngredientON);
  myTimer.after(600000,WhiteLight_IngredientON);
}
