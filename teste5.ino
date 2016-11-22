#include <IRremote.h>
#include <Servo.h>

int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;
bool timer = false;


void setup()
{
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  
  irrecv.enableIRIn(); // Start the receiver
  
  
}



void loop()
{
  if(timer){
        digitalWrite(13, HIGH);
        delay(100);
        digitalWrite(13,LOW);
        delay(100);
    }
    
  if (irrecv.decode(&results))
    {
     Serial.println(results.value, HEX);
     Serial.println(results.value);

    
        
     if (results.value == 16753245)//ch- 
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

