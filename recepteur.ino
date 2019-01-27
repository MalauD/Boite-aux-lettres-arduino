// ==== Recepteur 433 MHz ===============================

#include <VirtualWire.h>

uint8_t buf[VW_MAX_MESSAGE_LEN];
uint8_t buflen = VW_MAX_MESSAGE_LEN;
int switchstate = 0;

void setup()
{
    SetupIO();
    SetupCom();
}

void SetupIO(){
  pinMode(3, INPUT);
  pinMode(2, OUTPUT);
}

void SetupCom(){
  //Init des comunications avec le serial & le virtual VirtualWire
  Serial.begin(9600);
  Serial.println("Recepteur - 433mhz");

  vw_setup(2000);
  vw_rx_start();
}

void loop()
{
   switchstate = digitalRead(3);
   if (switchstate == HIGH) {
      digitalWrite(2, LOW);
   }
   if (PresenceOfLetter()){
      Serial.println("Lettre !");
      digitalWrite(2, HIGH);
   }
}

bool PresenceOfLetter(){
  //Verifie la presence d'un message dans le buffer de VirtualWire puis copie sur le buffer local
  if(vw_wait_rx_max(200) && vw_get_message(buf, &buflen)){
    return true;
  } 
  return false;
}
