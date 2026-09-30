#define directionPin 6
#define stepPin 3
#include <list>

void setup() {
  Serial.begin(9600); // Initialized baud rate 
  float currentPosition = 0.0;

  println("Give a starting location in a 1.8 Degree multiple");


}

void loop() {
  
  println("SET to set position, UP to step once, and STOP to end and reset");
  println("USER INPUT:");

  while (Serial.available() == 0 ) {
    // do nothing
  }
  
  String input = Serial.readStringUntil('\n');
  

  if (input == "UP"){
    // Step motor once 
  }

  elif (input == "SET"){
    while (true){ // loop to continue getting input
      println("Input an angle (must be multiple of 1.8 Degrees) or 999 to return"); // 999 int value to return so I can keep the parse value as an float
      while (Serial.available() == 0 ) {} // do nothing
      float angle = Serial.parseFloat('\n');
      int tenxAngle = round.(angle * 10); // So we can modulo by 18 

      if (angle == 999.0){
        break;
      }
      elif (angle > 180.0){
        println("Angle is invaid (greater than 180 Degrees)")
        continue; 
      }
      elif (tenxPosition % 18 == 0){ // Checking if valid angle
        int steps = tenxPosition / 18; 
        motorMovementWithSteps(steps);
        currentPosition = angle; 
        break;
      }
      else {
        println("Angle is invalid (not a multiple of 1.8)");
        continue;

      }
    }
  }
  
  elif (input == "STOP"){
    stepsToZero = currentPosition / 1.8; //calulate the amount of steps to zero 
    motorMovementWithSteps(stepsToZero, 1)

    return 0; // Stops program
  }

  else{
    println("Invalid Response");
  }

}

void motorMovementWithSteps(int steps, bool CW){
  int direction = CW ? HIGH : LOW;
  

  for (int i = 0; i <= steps; i++){
    digitalWrite(directionPin, direction);
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(50);
    digitalWrite(stepPin, LOW);
    delayMicrosecond(50);
  }
}

