#include <IRremote.h>
#include <Servo.h>

int RECV_PIN = 11;
Servo myservo;  // create servo object to control a servo
IRrecv irrecv(RECV_PIN);
decode_results results;
int pos = 0;    // variable to store the servo position


void setup()
{
  myservo.attach(10);
  Serial.begin(9600);
  
  irrecv.enableIRIn(); // Start the receiver
  
  
}



void loop()
{
  if (irrecv.decode(&results))//recebe qualquer tecla apertada
    {
     Serial.println(results.value, HEX);
     Serial.println(results.value);

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
         
  

     irrecv.resume(); // Receive the next value
    }
}

