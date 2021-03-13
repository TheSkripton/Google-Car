int in1=2;
int in2=3;
int in3=10;
int in4=12;
int enA=9;
int enB=11;
float Speed=0;
int state=0;
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8
int redraw = 0;
int redval=0;

int greenraw = 0;
int greenval=0;

int blueraw = 0;
int blueval=0;

int upperred=0;
int upperblue=0;
int uppergreen=0;

int normalred=0;
int normalblue=0;
int normalgreen=0;
void setup()
{
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  pinMode(13,OUTPUT);
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  Serial.begin(9600);
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  digitalWrite(13,LOW);
  Serial.begin(9600);
  configure();
}

void loop(){
  check_color();
}
void forward(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  accelerate();
}
void backward(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  accelerate();           
}
void left(){
  Speed=Speed-0.5;
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(enA, HIGH);
  digitalWrite(enB, HIGH);
  
}
void right(){
  Speed=Speed-0.5;
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(enA, HIGH);
  digitalWrite(enB, HIGH);
}
void Stop(){
  Speed=Speed-0.5;
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(enA, LOW);
  digitalWrite(enB, LOW);
  }
void accelerate(){
  if(Speed>250){
    Speed=255;
  }
  else{ 
    Speed=Speed+1; 
  }
  Serial.println(Speed);
  analogWrite(enA,Speed);
  analogWrite(enB,Speed);
}
int check_color(){
  
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);//RED
  redraw = pulseIn(sensorOut, LOW);
  delay(10);

  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);//GREEN
  greenraw = pulseIn(sensorOut, LOW);
  delay(10);

  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  blueraw = pulseIn(sensorOut, LOW);
  redval=map(redraw,normalred,upperred,0,255);
  greenval=map(greenraw,normalgreen,uppergreen,0,255);
  blueval=map(blueraw,normalblue,upperblue,0,164);
  
  if(redval>200 && greenval>200 && blueval>200){
    Serial.println("WHITE");
    right();
  }
  else if(redval<50 && greenval<70 && blueval<50){
    Serial.println("BLACK");
    Stop();
  }
  else if(redval>blueval && redval>greenval){
    Serial.println("RED");
    forward();
  }
  else if(redval<blueval && blueval>greenval){
    Serial.println("BLUE");
    backward();
  }
  else if(greenval>blueval && redval<greenval){
    Serial.println("GREEN");
    left();
    
  }
  else{
    Serial.println("BLACK");
    Stop();
  }
    Serial.print("  Red=");
    Serial.print(redval);
    Serial.print("  Blue=");
    Serial.print(blueval);
    Serial.print("  Green=");
    Serial.println(greenval);
}
int configure(){
  int newval;
  int count=0;
  
  digitalWrite(13,HIGH);
  delay(1000);
  digitalWrite(13,LOW);
  Serial.println("calibrateblack");
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);//RED
  normalred = pulseIn(sensorOut, LOW);
  delay(10);
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);//GREEN
  normalgreen = pulseIn(sensorOut, LOW);
  delay(10);
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);//BLUE
  normalblue = pulseIn(sensorOut, LOW);
  delay(10);
  
  while(count<500){
    digitalWrite(S2,LOW);
    digitalWrite(S3,LOW);//RED
    newval= pulseIn(sensorOut, LOW);
    normalred=(normalred+newval)/2;
    delay(10/3);
    
    digitalWrite(S2,HIGH);
    digitalWrite(S3,HIGH);//GREEN
    newval = pulseIn(sensorOut, LOW);
    normalgreen=(normalgreen+newval)/2;
    delay(10/3);
    
    digitalWrite(S2,LOW);
    digitalWrite(S3,HIGH);
    newval = pulseIn(sensorOut, LOW);//BLUE
    normalblue=(normalblue+newval)/2;
    delay(10/3);

    count=count+1;
  }
  count=0;
  digitalWrite(13,HIGH);
  Serial.println("calibrateRED");
  delay(1000);
  digitalWrite(13,LOW);
  delay(1000);
  
  /*RED CONFIGURATION*/
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);//RED
  upperred= pulseIn(sensorOut, LOW);
  while(count<500){
    digitalWrite(S2,LOW);
    digitalWrite(S3,LOW);//RED
    newval= pulseIn(sensorOut, LOW);
    upperred=(upperred+newval)/2;
    delay(10);
    count=count+1;
  }
  count=0;
  digitalWrite(13,HIGH);
  Serial.println("calibrateBLUE");
  delay(1000);
  digitalWrite(13,LOW);
  delay(1000);
  
  /*BLUE CONFIGURATION*/
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);//BLUE
  upperblue= pulseIn(sensorOut, LOW);
  while(count<500){
    digitalWrite(S2,LOW);
    digitalWrite(S3,HIGH);//BLUE
    newval= pulseIn(sensorOut, LOW);
    upperblue=(upperblue+newval)/2;
    delay(10);
    count=count+1;
  }
  count=0;
  digitalWrite(13,HIGH);
  Serial.println("calibrateGREEN");
  delay(1000);
  digitalWrite(13,LOW);
  delay(1000);
  
  /*green CONFIGURATION*/
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);//GREEN
  uppergreen= pulseIn(sensorOut, LOW);
  while(count<500){
    digitalWrite(S2,HIGH);
    digitalWrite(S3,HIGH);//GREEN
    newval= pulseIn(sensorOut, LOW);
    uppergreen=(upperblue+newval)/2;
    delay(10);
    count=count+1;
  }
}
