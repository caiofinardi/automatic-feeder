#include <IRremote.h>
#include <Servo.h>

int RECV_PIN = 11;
Servo myservo;  // create servo object to control a servo
IRrecv irrecv(RECV_PIN);
decode_results results;
int pos = 0;    // variable to store the servo position
bool timer = false;


void setup()
{
  pinMode(13, OUTPUT);
  myservo.attach(10);
  Serial.begin(9600);
  
  irrecv.enableIRIn(); // Start the receiver
  
  
}



void loop()
{
  if (irrecv.decode(&results))
    {
     Serial.println(results.value, HEX);
     Serial.println(results.value);

     
     if(timer){
      delay(5000);
         for (pos = 0; pos <= 270; pos += 10) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        Serial.println(pos);
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(10);                       // waits 15ms for the servo to reach the position
      }
      delay(50);
      for (pos = 270; pos >= 0; pos -= 10) { // goes from 180 degrees to 0 degrees
        Serial.println(pos);
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(10);                       // waits 15ms for the servo to reach the position
      }
      
     }

     if(results.value == 16754775 && !timer)//+
     {
        
         for (pos = 0; pos <= 270; pos += 10) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        Serial.println(pos);
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(10);                       // waits 15ms for the servo to reach the position
      }
      delay(50);
      for (pos = 270; pos >= 0; pos -= 10) { // goes from 180 degrees to 0 degrees
        Serial.println(pos);
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(10);                       // waits 15ms for the servo to reach the position
      }
         
       
        
     } else if (results.value == 16753245)//ch- 
     {
        timer = true;
        digitalWrite(13, HIGH);
        
        
     }//ch+
     else if (results.value == 16769565){
        timer = false;
        digitalWrite(13, LOW);
      }


     irrecv.resume(); // Receive the next value
    }
}

