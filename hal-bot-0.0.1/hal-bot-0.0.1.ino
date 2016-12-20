#define trigpin 2
#define echopin 3
unsigned int obstacleDistance = 15;
unsigned long startTime;
int turnInd = 0; // (0:Right Turn, 1:Left Turn)
const int rtAngleTime = 580;
const int leftWheelAdjustment = 40;


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

    //Serial.println(getObstacleDistance());

    if (getObstacleDistance() > obstacleDistance){
      goStraight();
    }
    else {
      turn();
    }

}

void turn(){

  if (turnInd == 0){
    turnRightU();
  }
  else{
    turnLeftU();
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
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  
  digitalWrite(11, LOW);
  digitalWrite(12, HIGH);
}

void goReverse()
{
  Serial.println("Going Reverse...");
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  
  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);

}


void turnRight()
{
  
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);

}


void turnLeft()
{
  
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  
  digitalWrite(11, LOW);
  digitalWrite(12, HIGH);

}

void turnRightU(){
    Serial.println("Taking Right U Turn...");
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
    
    /*startTime =  millis();
    while((millis() - startTime) < 100){
      goStraight();
    }
    pause();*/
    startTime =  millis();
    while((millis() - startTime) < rtAngleTime){
      turnRight();
    }
    turnInd = 1;
    Serial.println("Taking Right U Turn complete...");
}

void turnLeftU(){
    Serial.println("Taking Left U Turn...");
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
    
    /*startTime =  millis();
    while((millis() - startTime) < 100){
      goStraight();
    }
    pause();*/
    startTime =  millis();
    while((millis() - startTime) < (rtAngleTime+leftWheelAdjustment)){
      turnLeft();
    }
    turnInd = 0;
    Serial.println("Taking Left U Turn complete...");
}

int getObstacleDistance(){
    int duration,distance;
    digitalWrite(trigpin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigpin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigpin, LOW);
    
    duration = pulseIn(echopin, HIGH);
    distance = microsecondsToCentimeters(duration);
    //return duration;
    return distance;
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}

