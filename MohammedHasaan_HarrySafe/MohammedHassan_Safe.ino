long long counter = 0;
long long counter2 = 0;
long long counter3 = 0;
int degrees1 = 0;
int degrees2 = 0;
int degrees3 = 0;
const int pps = 360;
#define SIGNAL_A 2
#define SIGNAL_B 3
#define SIGNAL_A2 18
#define SIGNAL_B2 19
#define SIGNAL_A3 20
#define SIGNAL_B3 21
#define GrennLed  13
void setup() {
  //setting the pins and attach Interrupts for the encoders
  pinMode(SIGNAL_A,INPUT_PULLUP);
  pinMode(SIGNAL_B,INPUT_PULLUP);
  pinMode(SIGNAL_A2,INPUT_PULLUP);
  pinMode(SIGNAL_B2,INPUT_PULLUP);
  pinMode(SIGNAL_A3,INPUT_PULLUP);
  pinMode(SIGNAL_B3,INPUT_PULLUP);
  pinMode(GrennLed,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(SIGNAL_A),ISR_A,CHANGE);
  attachInterrupt(digitalPinToInterrupt(SIGNAL_B),ISR_B,CHANGE);
  attachInterrupt(digitalPinToInterrupt(SIGNAL_A2),ISR_A,CHANGE);
  attachInterrupt(digitalPinToInterrupt(SIGNAL_B2),ISR_B,CHANGE);
  attachInterrupt(digitalPinToInterrupt(SIGNAL_A3),ISR_A,CHANGE);
  attachInterrupt(digitalPinToInterrupt(SIGNAL_B3),ISR_B,CHANGE);
}

void loop() 
{ 
 //the equations to get the angles and the pps can be changed   
 degrees1 = ((float)counter/(pps*4))*360;
 degrees2 = ((float)counter2/(pps*4))*360;
 degrees3 = ((float)counter3/(pps*4))*360;
 //check if the angles is equal to the angles needed and turn on the green light 
 if(degrees1 == 37 && degrees2 == 10 && degrees3 == 54)
 {
   digitalWrite(GrennLed,HIGH);
 }

}
// a function to raise the counter every pulse clockwise and lower the counter every pulse counter clockwise
// for the A signal of the encoders 
void ISR_A()
{
  if(digitalRead(SIGNAL_A)!= digitalRead(SIGNAL_B))
  {
     counter++;
  }
  else
  {
    counter--;
  }  
  if(digitalRead(SIGNAL_A2)!= digitalRead(SIGNAL_B2))
  {
    counter2++;
  }   
  else
  {
    counter2--;
  }     
  if(digitalRead(SIGNAL_A3)!= digitalRead(SIGNAL_B3))
  {
    counter3++;
  }  
  else
  {
    counter3--;
  }    
}
// a function to raise the counter every pulse clockwise and lower the counter every pulse counter clockwise
// for the B signal of the encoders 
void ISR_B()
{
  if(digitalRead(SIGNAL_A) == digitalRead(SIGNAL_B))
  {
    counter++;
  }  
  else
  {
    counter--;
  }  
  if(digitalRead(SIGNAL_A2)== digitalRead(SIGNAL_B2))
  {
    counter2++;
  }  
  else
  {
    counter2--;
  }     
  if(digitalRead(SIGNAL_A3)== digitalRead(SIGNAL_B3))
  {
    counter3++;
  }  
  else
  {
    counter3--;
  }       
}
