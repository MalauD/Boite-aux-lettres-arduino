//emettteur
#include <VirtualWire.h>

const byte TRIGGER_PIN = 2;
const byte ECHO_PIN = 3;

const unsigned long MEASURE_TIMEOUT = 25000UL;
const float SOUND_SPEED = 340.0 / 1000;

const float TRIGGER_DIST = 200;

void setup()
{
    ComSetup();
    UltrasonSetup();
}

void loop()
{
  if(CheckLetter()) {
    Serial.println("Presence de lettre");
    SendMessage("Lettre");
    delay(2000);
  }
  delay(20);
}

void ComSetup(){
  //Setup des comunications avec l'environement
  Serial.begin(9600);
  vw_setup(2000);
}

void UltrasonSetup(){
  //Initialisation des broches d'ultrason
  pinMode(TRIGGER_PIN, OUTPUT);
  digitalWrite(TRIGGER_PIN, LOW);
  pinMode(ECHO_PIN, INPUT);
}

void SendMessage(char *message){
  Serial.print("Envoi du message")
  //Envoi du message avec conversion en byte (1) et longueur du message (2)
  vw_send((uint8_t *)message, strlen(message));
  //Attent asynchrone du message
  vw_wait_tx();
  Serial.println("Termine !")
}

float TakeMeasurement(){
  //Envoi d'une impulsion sur l'emtteur pendant 10ms
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  //Attente d'un retour sur le Recepteur
  long measure = pulseIn(ECHO_PIN, HIGH, MEASURE_TIMEOUT);
  //Retour de la distance convertit avec la vitesse du sond
  return measure / 2.0 * SOUND_SPEED;
}

bool CheckLetter(){
  //Verification de la presence d'une lettre
  return TakeMeasurement() < TRIGGER_DIST;
}
