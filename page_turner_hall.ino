#include <ezButton.h>
#include <Servo.h>


ezButton forwardSwitch(7);  // create ezButton object that attach to pin 7;
ezButton halleffect(9);  // create ezButton object that attach to pin 9;
ezButton toggleSwitch(11);  // create ezButton object that attach to pin 11;
ezButton revarseSwitch(13); // create ezButton object that attach to pin 5; 
Servo myservo;

bool wasPressed = false;

bool ended = true;

int count = 0;

int firstTimer = 5300, secondTimer = 4000;

int t1 = 0, t2 = 0;

int Timer;

int moveDiriction = 1;

static void resetValues() {
  myservo.detach();
  t1 = 0;
  t2 = 0;
  wasPressed = false;
  count=0;
  Timer = 0;
}

void setup() {
  Serial.begin(9600);
  
  forwardSwitch.setDebounceTime(50); // set debounce time to 50 Timereconds
  revarseSwitch.setDebounceTime(50); // set debounce time to 50 Timereconds
  toggleSwitch.setDebounceTime(50); // set debounce time to 50 Timereconds
  halleffect.setDebounceTime(50); // set debounce time to 50 Timereconds
  
  Timer = 0;
}

void loop() {
  Timer = millis();

  revarseSwitch.loop();
  forwardSwitch.loop(); // MUST call the loop() function first
  toggleSwitch.loop(); // MUST call the loop() function first
  halleffect.loop(); // MUST call the loop() function first
  

   if (halleffect.isPressed() && count <= 2){
    count++;
    Serial.print("hall is on ");
  }


  if (toggleSwitch.isPressed()){
     firstTimer = 5300;
     secondTimer = 4000;
     Serial.print("big ");
     resetValues();
  }

   if (toggleSwitch.isReleased()){
    Serial.print("small ");
    firstTimer = 4200;
    secondTimer = 4200;
    resetValues();
  }

   if(forwardSwitch.isPressed()){
    if (ended) {
       count=0;
      
      ended = false;
      wasPressed = true;
      moveDiriction = 1;
    }
  }

  if(revarseSwitch.isPressed()){
    Serial.print("reverse ");
    if (ended) {
      count=0;
      
      ended = false;
      wasPressed = true;
      moveDiriction = -1;
    }
  }
  
   if (wasPressed && (forwardSwitch.isPressed() || revarseSwitch.isPressed())){ 
      myservo.detach();
      myservo.attach(3);
      myservo.write(180 * moveDiriction);
      Serial.print("blahsdha ");
      t1 = Timer;
      Serial.print(t1);
      Serial.print(Timer);

      wasPressed = false;
      }
      if (Timer-t1 >= firstTimer && t1 != 0){
        myservo.detach();
        myservo.attach(3);
        myservo.write(-180 * moveDiriction);
        Serial.print("blah "); 
        t1 = 0;
        t2 = Timer;  
  }

  if (Timer-t2 >= secondTimer && t2 != 0){
          Serial.print("hi");
          myservo.detach();
          myservo.attach(3);
          myservo.write(180 * moveDiriction);
          t2 = 0;
    }
    if (count >= 2){
        ended = true;
        resetValues();
        Serial.print("hall is 0 ");
      }
}


      
   
