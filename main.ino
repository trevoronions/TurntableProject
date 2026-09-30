#define directionPin 6
#define stepPin 3
float currentPosition = 0.0;


void setup() {
  Serial.begin(9600); // Initialized baud rate 

  pinMode(directionPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
}

void loop() {
  Serial.println();
  Serial.print("Current Angle: ");
  Serial.println(currentPosition);
  Serial.println("SET to set position, UP to increase the current position, and RESET to reset back to zero position");
  Serial.print("USER INPUT: ");

  while (Serial.available() == 0 ) {
    // do nothing
  }
  
  String input = Serial.readStringUntil('\n');
  Serial.println(input);

  if (input == "UP"){
    while (true) { // loop to continue getting input
      Serial.println("Input an angle to increase the current count by (must be multiple of 0.9 Degrees) or 999 to return:"); // 999 int value to return so I can keep the parse value as an float
      Serial.println("USER INPUT: ");
      
      while (Serial.available() == 0 ) {} // do nothing
      
      float angle = Serial.parseFloat();
      String extra = Serial.readStringUntil('\n');
      int tenxAngle = round(angle * 10);
      Serial.println(angle);
      
      if (angle == 999.0){
        break;
      }
      
      else if (180.0 < angle + currentPosition) {
        Serial.println("Total angle exceeds 180");
        continue;
      }
      
      else if (tenxAngle % 9 == 0){
        int steps = tenxAngle / 9; 

        motorMovementWithSteps(steps, 0);
        currentPosition = angle + currentPosition; 
        break;
      }
      
      else {
        Serial.println("Angle is invalid (not a multiple of 0.9)");
        continue;
      }
    }
  }


  else if (input == "SET"){
    while (true){ // loop to continue getting input
      Serial.println("Input an angle to set the motor to (must be multiple of 0.9 Degrees) or 999 to return:"); // 999 int value to return so I can keep the parse value as an float
      Serial.println("USER INPUT: ");
      
      while (Serial.available() == 0 ) {} // do nothing
      
      float angle = Serial.parseFloat();
      String extra = Serial.readStringUntil('\n');
      
      Serial.println(angle);
      
      int tenxAngle = round(angle * 10); // So we can modulo by 18 

      if (angle == 999.0){
        break;
      }
      else if (angle > 180.0){
        Serial.println("Angle is invalid (greater than 180 Degrees)");
        continue; 
      }
      else if (tenxAngle % 9 == 0){ // Checking if valid angle
        int steps;
        if (angle == currentPosition){
          Serial.println("Angle inputted is same as current position");
          continue;
        }
        else if (angle - currentPosition > 0){
          steps = (angle - currentPosition) / 0.9;
          motorMovementWithSteps(steps, 0);
        }
        else {
          steps = (currentPosition - angle) / 0.9;
          motorMovementWithSteps(steps, 1);
        }
        currentPosition = angle; 
        break;
      }
      else {
        Serial.println("Angle is invalid (not a multiple of 0.9)");
        continue;

      }
    }
  }
  
  else if (input == "RESET"){
    int stepsToZero = currentPosition / 0.9; //calulate the amount of steps to zero 
    motorMovementWithSteps(stepsToZero, 1);
    currentPosition = 0.0;
  }

  else{
    Serial.println("Invalid Response");
  }

}

void motorMovementWithSteps(int steps, bool CW){
  int direction = CW ? HIGH : LOW;
  

  for (int i = 1; i <= steps; i++){ 
    digitalWrite(directionPin, direction);
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(5000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(5000);
  }
  Serial.print("Shifted by ");
  Serial.print(steps);
  Serial.println(" Steps");


}


