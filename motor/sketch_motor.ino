#include <SPI.h>
#include <Ethernet2.h>
#include <Servo.h>

// L'adresse MAC du shield
byte mac[] = { 0x90, 0xA2, 0xDA, 0x10, 0xDE, 0xE7 };
// L'adresse IP que prendra le shield
byte ip[] = { 192, 168, 0, 101 }; 
// Port d'�coute
EthernetServer serveur(80);

Servo monServo;

void setup()
{
  // On d�marre la voie serie pour deboguer
  Serial.begin(9600);
  // On cr�e la partie Eth
  Ethernet.begin(mac, ip);
  // Petite pause pour �tre sur que le shield Eth est d�marr�
  delay(1000);
  // D�marrage du serveur 
  serveur.begin();
  // Moteur sur le pin 5
  monServo.attach(5);
  // Moteur arret� !
  monServo.writeMicroseconds(1500);
}

void loop()
{
  // Regarde si un client est connecte et attend une reponse
  EthernetClient client = serveur.available();
  if (client) {
    // Gestion de la fin de la requete WEB qui est indiquee par l'envoi d'une ligne blanche
    //boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
              //Envoi du header standard HTTP au browser
              client.println("HTTP/1.1 200 OK");
              client.println("Content-Type: text/html");
              client.println();
              //envoi donnees
              client.print("Coucou toto ");
              monServo.writeMicroseconds(1400);
              Serial.println("Envoi message");
         client.stop();}
    }}
  //if (!client) {
	//exemple
    //}
}
