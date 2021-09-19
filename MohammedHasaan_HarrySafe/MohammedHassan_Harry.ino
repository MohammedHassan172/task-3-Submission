#define IR1_F A0
#define IR2_R A1
#define IR3_L A2
int IR1_F_Value = 0;
int IR1_R_Value = 0;
int IR1_L_Value = 0;
bool wrongway = false;
void setup() {
  // there is 3 IR sensor in the front one in the middle and one is in the left and one in the right next to each others.
  pinMode(IR1_F, INPUT);
  pinMode(IR2_R, INPUT);
  pinMode(IR3_L, INPUT);
  Serial.begin(9600);

}

void loop() {
  //reading the value of the sensor
  IR1_F_Value = analogRead(IR1_F);
  IR1_R_Value = analogRead(IR2_R);
  IR1_L_Value = analogRead(IR3_L);
  //if the reading of the right sensor is higher than the max number(300)which can be changed to get better results
  //it will turn right 
  if(IR1_R_Value > 300 && IR1_L_Value < 300)
  {
    Serial.println("rotate90right();");
  }
  //to turn left
  else if(IR1_R_Value < 300 && IR1_L_Value > 300)
  {
    Serial.println("rotate90left();");
  }
  //move forward
  if(IR1_F_Value > 300 && wrongway == false)
  {
    Serial.println("moveForward();");
  }
  //move backward
  else if(IR1_F_Value < 300 || wrongway == true)
  {
    //it well say wrong way until right or left sensor pick up a signal
    wrongway = true;
    Serial.println("moveBackward();");
    if(IR1_R_Value > 300 || IR1_L_Value > 300)
    {
       wrongway = false;
    }
  }
 //if the 3 reading is higher than the max it will turn right 
 //because every tiem this happens it will need to turn right.
  if(IR1_R_Value > 300 && IR1_L_Value > 300 && IR1_F_Value > 300)
  {
     Serial.println("rotate90right();");
  }

}
