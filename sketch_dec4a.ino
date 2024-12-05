#include <Adafruit_CircuitPlayground.h>
//The Ritual
//By Joe Crighton
//Makes a noise if you shake the Arduino while left button is pressed, just so it isnt constantly beeping.
bool leftButtonPressed;
bool rightButtonPressed;
bool state0 = true; //IDLE
bool state1 = false; //STEP 1
bool state2 = false; //STEP 2
bool state3 = false; //VICTORY
bool state4 = false; //LOSE

int lightLevel; //used in ST0 to determine if box has been opened
bool slideSwitch; //used in ST1 to initiate the ritual

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
  //state2 = false;
  //tate0 = true;
}

void loop() { //
  lightLevel = CircuitPlayground.lightSensor(); //detects brightness level
  slideSwitch = CircuitPlayground.slideSwitch(); //slideswitch used in st1
  leftButtonPressed = CircuitPlayground.leftButton();
  rightButtonPressed = CircuitPlayground.rightButton();
  //Serial.print("Light Sensor: ");
  //Serial.println(lightLevel);
  delay(1000);

  if (state0 == true) { //IDLE : WAITS FOR BOX TO BE OPENED, CAN BE PUT BACK TO SLEEP BY CLOSING BOX
    CircuitPlayground.clearPixels();
    if (lightLevel >= 10) {
      state0 = false;
      state1 = true;
    }
  }
  if (state1 == true) { //BEGIN : PIXELS WILL BE RED
    Serial.println("STATE1: RITUAL HAS BEGUN. THERE IS STILL TIME");
    CircuitPlayground.setPixelColor(0,20,0,0); //Lights up left side pixels red
    CircuitPlayground.setPixelColor(1,20,0,0);
    CircuitPlayground.setPixelColor(2,20,0,0);
    CircuitPlayground.setPixelColor(3,20,0,0);
    CircuitPlayground.setPixelColor(4,20,0,0);
    CircuitPlayground.setPixelColor(5,20,0,0);
    CircuitPlayground.setPixelColor(6,20,0,0);
    CircuitPlayground.setPixelColor(7,20,0,0);
    CircuitPlayground.setPixelColor(8,20,0,0);
    CircuitPlayground.setPixelColor(9,20,0,0);
    if (slideSwitch) { //ADVANCE TO STATE 2
      state1 = false;
      state2 = true;
    }
    if (lightLevel <= 10) { //PUT THE ARTIFACT BACK IN THE BOX TO PUT IT BACK TO SLEEP
      state0 = true;
      state1 = false;
      Serial.print("STATE0");
    } //get player to state2
  }
  if (state2 == true) {
    Serial.println("STATE2: RITUAL HAS ADVANCED. THIS CANNOT BE REVERSED.");
    CircuitPlayground.setPixelColor(0,20,20,0); //Lights up left side pixels red
    CircuitPlayground.setPixelColor(1,20,20,0);
    CircuitPlayground.setPixelColor(2,20,20,0);
    CircuitPlayground.setPixelColor(3,20,20,0);
    CircuitPlayground.setPixelColor(4,20,20,0);
    CircuitPlayground.setPixelColor(5,0,0,0);
    CircuitPlayground.setPixelColor(6,0,0,0);
    CircuitPlayground.setPixelColor(7,0,0,0);
    CircuitPlayground.setPixelColor(8,0,0,0);
    CircuitPlayground.setPixelColor(9,0,0,0);
    //if left button pressed le win
    if (leftButtonPressed) {
      state3 = true;
    }
    if (rightButtonPressed) {
      state4 = true;
    }
    //if right button pressed le lose
  }
  if (state3 == true) { //yuo win!!!1
    state2 = false;
    Serial.println("STATE3: RITUAL COMPLETE. PLACE BACK IN BOX");
    CircuitPlayground.setPixelColor(0,0,20,0); //Lights up left side pixels red
    CircuitPlayground.setPixelColor(1,0,20,0);
    CircuitPlayground.setPixelColor(2,0,20,0);
    CircuitPlayground.setPixelColor(3,0,20,0);
    CircuitPlayground.setPixelColor(4,0,20,0);
    CircuitPlayground.setPixelColor(5,0,20,0);
    CircuitPlayground.setPixelColor(6,0,20,0);
    CircuitPlayground.setPixelColor(7,0,20,0);
    CircuitPlayground.setPixelColor(8,0,20,0);
    CircuitPlayground.setPixelColor(9,0,20,0);
    if (lightLevel <= 10) {
      state3 = false;
      state1 = true;
    }
  }
  if (state4 == true) { //you lose!!!
    state2 = false;
    Serial.println("STATE4: THE RITUAL HAS FAILED. YOU JUST DIED");
    CircuitPlayground.setPixelColor(0,20,0,0); //Lights up left side pixels red
    CircuitPlayground.setPixelColor(1,20,0,0);
    CircuitPlayground.setPixelColor(2,20,0,0);
    CircuitPlayground.setPixelColor(3,20,0,0);
    CircuitPlayground.setPixelColor(4,20,0,0);
    CircuitPlayground.setPixelColor(5,20,0,0);
    CircuitPlayground.setPixelColor(6,20,0,0);
    CircuitPlayground.setPixelColor(7,20,0,0);
    CircuitPlayground.setPixelColor(8,20,0,0);
    CircuitPlayground.setPixelColor(9,20,0,0);
    delay(100);
    CircuitPlayground.clearPixels();
    if (lightLevel <= 10) {
      state4 = false;
      state1 = true;
    }
  }
}
  //set state 1 to true
  //state 1 if loop
  //set state 2 to true
  //set state 3 to true

//ST0 idle
//board checks after delay for light above X value, if its above that value, it runs the rest of the code. if the light goes below that value, it reverts to idle
//ST1 begin
//board will require 
//ST2 step 2
//ST3 safe
//board will turn green, indicating success.