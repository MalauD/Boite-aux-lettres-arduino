// ==== Recepteur 433 MHz ===============================

#include <VirtualWire.h> 
 
uint8_t buf[VW_MAX_MESSAGE_LEN]; 
uint8_t buflen = VW_MAX_MESSAGE_LEN; 
int switchstate = 0;
void setup() 
{
  pinMode(3, INPUT);
    Serial.begin(9600); 
    Serial.println("Tuto VirtualWire");     
    pinMode(2, OUTPUT);
 
    vw_setup(2000);
    vw_rx_start();  
}
 
void loop()
{
   switchstate = digitalRead(3);
   if (switchstate == HIGH) {
    digitalWrite(2, LOW);
   }
    if (vw_wait_rx_max(200)) 

        if (vw_get_message(buf, &buflen)) 
        {
            Serial.print("RX : ");
            for (byte i = 0; i < buflen; i++) 
             //Serial.print(buf[i]);   
             {Serial.print(buf[i]- '0');   
             }
             digitalWrite(2, HIGH);
        }
    }
}
