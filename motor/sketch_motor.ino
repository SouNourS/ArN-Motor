// Ces deux bibliotheques sont indispensables pour le shield
#include <SPI.h>
#include <Ethernet2.h>
#include <Servo.h>

// L'adresse MAC du shield
byte mac[] = { 0x90, 0xA2, 0xDA, 0x10, 0xDE, 0xE7 };
// L'adresse IP que prendra le shield
byte ip[] = { 192, 168, 0, 99 }; 

EthernetServer serveur(80);

Servo monServo;

void setup()
{
  // On demarre la voie serie pour deboguer
  Serial.begin(9600);
  
  Ethernet.begin(mac, ip);
  delay(1000);
  serveur.begin();

  monServo.attach(5);
  monServo.writeMicroseconds(1500);
}

void loop()
{
  // Regarde si un client est connecte et attend une reponse
  EthernetClient client = serveur.available();
  if (client) {
    // Gestion de la fin de la requete WEB qui est indiquee par l'envoi d'une ligne blanche
    //boolean currentLineIsBlank = true;
	// Code modifié pour exemple Nono !
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
    //Serial.println("Eteint");
    //delay(1000);
    //Serial.println("allume");
    //delay(1000);
  //}
}
