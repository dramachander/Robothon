#define trigpin 8
#define echopin 13
unsigned long startTime;
int turnInd = 0; // (0:Right Turn, 1:Left Turn)
const int rtAngleTime = 840;
const int leftWheelAdjustment = 100;


void setup() {
  // put your setup code here, to run once:
   Serial.begin (9600);
   pinMode(trigpin, OUTPUT);
   pinMode(echopin, INPUT);   
   pinMode(9, OUTPUT);
   pinMode(10, OUTPUT);
   pinMode(11, OUTPUT);
   pinMode(12, OUTPUT);
   startTime = millis();
}

void loop() {
  
    //Serial.println(millis() - startTime ); 

    Serial.println(getObstacleDistance());

    if (getObstacleDistance() > 20){
      goStraight();
    }
    else {
      turn();
    }

}

void turn(){

  if (turnInd == 0){
    turnRightU();
    turnInd = 1;
  }
  else{
    turnLeftU();
    turnInd = 0;
  }
  
}

void agriMode(){
  
}

void crazyMode(){
  
}


void pause(){
  //Serial.print("Pause:Left Motor\n");  
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  
  //Serial.print("Pause:Right Motor\n");  
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  
}

void goStraight()
{
   Serial.println("Going Straight...");  
  //Serial.print("Straight:Left Motor\n");  
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  
  //Serial.print("Straight:Right Motor\n");  
  digitalWrite(11, LOW);
  digitalWrite(12, HIGH);
}

void goReverse()
{
  Serial.println("Going Reverse...");
  //Serial.print("Reverse:Left Motor\n");  
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  
  //Serial.print("Reverse:Right Motor\n");  
  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);

}


void turnRight()
{
  //Serial.print("Left Motor\n");  
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  
  //Serial.print("Right Motor\n");  
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);

}


void turnLeft()
{
  //Serial.print("Left Motor\n");  
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  
  //Serial.print("Right Motor\n");  
  digitalWrite(11, LOW);
  digitalWrite(12, HIGH);

}

void turnRightU(){
    Serial.println("Taking Right U Trun...");
    startTime = millis();
    while((millis() - startTime) < rtAngleTime){
      turnRight();
    }
    pause();
    
    /*******
     * 
     * Check if the route exists and then continue else pause the machine
     * 
     *******/
    
    startTime =  millis();
    while((millis() - startTime) < 100){
      goStraight();
    }
    pause();
    startTime =  millis();
    while((millis() - startTime) < rtAngleTime){
      turnRight();
    }
    pause();
    turnInd = 1;
    
}

void turnLeftU(){
    Serial.println("Taking Left U Trun...");
    startTime = millis();
    while((millis() - startTime) < (rtAngleTime+leftWheelAdjustment)){
      turnLeft();
    }
    pause();
    
    /*******
     * 
     * Check if the route exists and then continue else pause the machine
     * 
     *******/
    
    startTime =  millis();
    while((millis() - startTime) < 100){
      goStraight();
    }
    pause();
    startTime =  millis();
    while((millis() - startTime) < (rtAngleTime+leftWheelAdjustment)){
      turnLeft();
    }
    pause();
    turnInd = 0;
    
}

int getObstacleDistance(){
    int duration, distance;
    digitalWrite(trigpin, HIGH);
    delay(100);
    digitalWrite(trigpin, LOW);
    duration = pulseIn(echopin, HIGH);
    distance = (duration / 2) / 29.1;
    //Serial.println("Onstacle distance : "+ distance);
    return duration;
}

