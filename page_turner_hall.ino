#include <ezButton.h>
#include <Servo.h>


ezButton forwardSwitch(6);  // create ezButton object that attach to pin 7;
ezButton halleffect(4);  // create ezButton object that attach to pin 9;
ezButton toggleSwitch(5);  // create ezButton object that attach to pin 11;
ezButton revarseSwitch(7); // create ezButton object that attach to pin 5; 
Servo myservo;

bool wasPressed = false;

bool arm = false;

bool ended = true;

int count = 0;

int firstTimer = 3700, secondTimer = 1000;

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
  arm = false;
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
    Serial.println("hall is on ");
  }


  if (toggleSwitch.isPressed()){
     firstTimer = 5900;//Page turn time
     secondTimer = 2000;//Page return time
     Serial.println("Big ");
     resetValues();
  }

   if (toggleSwitch.isReleased()){
    Serial.println("Small ");
    firstTimer = 5000;//Page turn time
    secondTimer = 1200;//Page return time
    resetValues();
  }

   if(forwardSwitch.isPressed()){
    Serial.println("forwardP");
    if (ended) {
       count=0;
      
      ended = false;
      wasPressed = true;
      moveDiriction = 1;
    }
  }

  if(revarseSwitch.isPressed()){
    Serial.println("reverseP");
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
      Serial.println("Moving");
      t1 = Timer;
      wasPressed = false;
      }
      if (Timer-t1 >= firstTimer && t1 != 0){
        myservo.detach();
        myservo.attach(3);
        myservo.write(-180 * moveDiriction);
        Serial.println("Moving back"); 
        t1 = 0;  
        arm = true;
  }

  if (halleffect.isPressed() && arm == true){
          Serial.println("Moving back1");
          myservo.detach();
          myservo.attach(3);
          myservo.write(-180 * moveDiriction);
          arm = false;
          t2 = Timer;
   }
   if (Timer-t2 >= secondTimer && t2 != 0){
          Serial.println("Moving forward1");
          myservo.detach();
          myservo.attach(3);
          myservo.write(180 * moveDiriction);
          t2 = 0;
    }    
 
    if (count >= 2){
        ended = true;
        resetValues();
        Serial.println("hall is 0 - back at the start");
      }

}


      
   
