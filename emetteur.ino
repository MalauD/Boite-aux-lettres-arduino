//emettteur
#include <VirtualWire.h> 

const byte TRIGGER_PIN = 2; 
const byte ECHO_PIN = 3;

const unsigned long MEASURE_TIMEOUT = 25000UL; 
const float SOUND_SPEED = 340.0 / 1000;

const char *msg = "28790658"; 

 
void setup() 
{
    Serial.begin(9600); 
    Serial.println("Tuto VirtualWire");

    pinMode(TRIGGER_PIN, OUTPUT);
  digitalWrite(TRIGGER_PIN, LOW); 
  pinMode(ECHO_PIN, INPUT);
 
    vw_setup(2000);     
}
 
void loop()
{

  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  long measure = pulseIn(ECHO_PIN, HIGH, MEASURE_TIMEOUT);
   

  float distance_mm = measure / 2.0 * SOUND_SPEED;
  Serial.println(distance_mm); 
  if(distance_mm < 200) {
    Serial.print("TX ... "); 
    vw_send((uint8_t *)msg, strlen(msg)); 
    vw_wait_tx(); 
    Serial.println("Done !"); 
    delay(2000); 
  }
  delay(300 );
}
