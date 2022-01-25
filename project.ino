#include <SimpleTimer.h>

#include <Blynk.h>

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>


// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "ESO9eK_WyiAIkLIW-LgJK0QJWyaHNBlh";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "FreeForAll";
char pass[] = "hqadmin1";


int timerConso;
Servo servo;

              // tell servo to go to position in variable 'pos'


//servo.detach() ;
// waits 15ms for the servo to reach the position
  
//your personal code for servo should end here
SimpleTimer timer;

// function to be called repeatedly
void RepeatTask() {
 
  oneOZ();
  setToZero();
        
}


void oneOZ() {
      servo.write(0);
delay(1000);
servo.write(180);
delay(1500);            // start the function cradle
     // Run rest of show in-between waiting for this loop to repeat or quit.
}

void twoOZ() {
      servo.write(0);
delay(1000);
servo.write(180);
delay(3000);            // start the function cradle
     // Run rest of show in-between waiting for this loop to repeat or quit.
}

void setToZero() {
   servo.write(0);
    delay(1000);
}

BLYNK_WRITE(V3) 
{
  int pinValue = param.asInt();
  Blynk.run();
  if (pinValue == 1) {    // if Button sends 1
    
     oneOZ();
  } else {
   setToZero();
   
  }
}

BLYNK_WRITE(V4) 
{
  int pinValue = param.asInt();
  Blynk.run();
  if (pinValue == 1) {    // if Button sends 1
    
    twoOZ();
     
  } else {
    setToZero();
  }
}

BLYNK_WRITE(V5) 
{
  int pinValue = param.asInt();
  //Blynk.run();
  
  if (pinValue == 1) {    // if Button sends 1
   
   
  timer.enable (timerConso);

  
        
  } else {
    timer.disable (timerConso);
    setToZero();
  }

 //return pinValue;
}




void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  servo.attach(4); //attaches servo to pin 4 (D2 on node mcu)
  timerConso = timer.setInterval(15000, RepeatTask);
  timer.disable (timerConso);
  setToZero();
}

void loop()
{
  //BLYNK_WRITE(V3);
  Blynk.run();
 
  timer.run();
 
}
