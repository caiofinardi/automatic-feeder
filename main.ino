#include <IRremote.h>
#include <Servo.h>
#include <Timer.h>

int RECV_PIN = 11;
Servo myservo;  // create servo object to control a servo
IRrecv irrecv(RECV_PIN);
decode_results results;
int pos = 0;    // variable to store the servo position
bool timer = false;
double elapsed_time = 0;
Timer t;
double time_to_go = 0;
double standard = 30000;


void setup()
{
  pinMode(13, OUTPUT);
  myservo.attach(9);
  Serial.begin(9600);
  t.every(10000,checkTime);
  irrecv.enableIRIn(); // Start the receiver
  
  
}



void loop()
{
  t.update();
  if (irrecv.decode(&results))
    {
     Serial.println(results.value, HEX);
     Serial.println(results.value);

     
     if(results.value == 16754775)//+
     {
        
        dispose();
         
       
       //ch EQ -: Liga Timer
     } else if (results.value == 16748655){
        turnOnTimer();
        
     }//ch '1' -:  Adiciona
     else if (results.value == 16724175){ 
        time_to_go += standard;
      }//ch '0' -: Termina timer
      else if(results.value == 16738455){
        turnOffTimer();
      }
      
     irrecv.resume(); // Receive the next value
    }
}

void checkTime(){
  if(timer){
      elapsed_time += 30000;
      Serial.println(elapsed_time/1000);
      Serial.println(time_to_go/1000);
      if(elapsed_time >= time_to_go){
        dispose();
        turnOffTimer();
      }
  }
}

void dispose(){
  for (pos = 0; pos <= 270; pos += 10) { // goes from 0 degrees to 180 degrees
          // in steps of 1 degree
          //Serial.println(pos);
          myservo.write(pos);              // tell servo to go to position in variable 'pos'
          delay(10);                       // waits 15ms for the servo to reach the position
        }
      delay(50);
      for (pos = 270; pos >= 0; pos -= 10) { // goes from 180 degrees to 0 degrees
        //Serial.println(pos);
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(10);                       // waits 15ms for the servo to reach the position
      }
}

void turnOnTimer(){
  timer = true;
  time_to_go = standard;
  digitalWrite(13, HIGH);
}

void turnOffTimer(){
  timer = false;
  elapsed_time = 0;
  time_to_go = 0;
  digitalWrite(13, LOW);
}


