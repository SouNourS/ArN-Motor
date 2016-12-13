#include <SPI.h>
#include <Ethernet2.h>
#include <Servo.h>

// L'adresse MAC du shield
byte mac[] = { 0x90, 0xA2, 0xDA, 0x10, 0xDE, 0xE7 };
// L'adresse IP que prendra le shield
byte ip[] = { 192, 168, 0, 101 }; 
// Port d'écoute
EthernetServer serveur(80);

Servo monServo;

void setup()
{
  // On démarre la voie serie pour deboguer
  Serial.begin(9600);
  // On crée la partie Eth
  Ethernet.begin(mac, ip);
  // Petite pause pour être sur que le shield Eth est démarré
  delay(1000);
  // Démarrage du serveur 
  serveur.begin();
  // Moteur sur le pin 5
  monServo.attach(5);
  // Moteur arreté !
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
	      // et dans tout les cas on répond au client
	      repondre(client);
	      // on quitte le while
	      break;
              //monServo.writeMicroseconds(1400);
	      }
     }
     delay(10);
     client.stop();
    }
void repondre(EthernetClient client) {
	//Envoi du header standard HTTP au browser
	client.println("HTTP/1.1 200 OK");
	client.println("Content-Type: text/html");
	client.println();
	client.println("<HTML>");
	client.println("<HEAD>");
	client.println("<TITLE>Contrôle Caméra 1</TITLE>");
	client.println("</HEAD>");
	client.print("<body BGCOLOR="),client.print(byte(34)); // <body BGCOLOR="
	client.print("#E0E0F8"); // #E0E0F8
	client.print(byte(34)),client.print(">"); // " >
	client.println("<center>");
	client.println("<H1>Contrôle Caméra 1</H1>");
	client.println("<br><br>");
	// Début tableau caméras
	client.println("<TABLE BORDER=0 WIDTH=80%>");
	client.println("<TR>");
	// IP 1
	//  <TD ALIGN="center"><a href="http://192.168.0.101"><input type="button" value="Caméra 1"></a></TD>
	client.print("<TD ALIGN="),client.print(byte(34));
	client.print("center"),client.print(byte(34));
	client.print("><a href="),client.print(byte(34));
	client.print("http://192.168.0.101"),client.print(byte(34));
	client.print("><input type="),client.print(byte(34));
	client.print("button"),client.print(byte(34));
	client.print("value="),client.print(byte(34));
	client.print("Caméra 1"),client.print(byte(34));
	client.print("></a></TD>");
	// IP 2
	//  <TD ALIGN="center"><a href="http://192.168.0.102"><input type="button" value="Caméra 2"></a></TD>
	client.print("<TD ALIGN="),client.print(byte(34));
	client.print("center"),client.print(byte(34));
	client.print("><a href="),client.print(byte(34));
	client.print("http://192.168.0.102"),client.print(byte(34));
	client.print("><input type="),client.print(byte(34));
	client.print("button"),client.print(byte(34));
	client.print("value="),client.print(byte(34));
	client.print("Caméra 2"),client.print(byte(34));
	client.print("></a></TD>");
	// IP 3
	//  <TD ALIGN="center"><a href="http://192.168.0.103"><input type="button" value="Caméra 3"></a></TD>
	client.print("<TD ALIGN="),client.print(byte(34));
	client.print("center"),client.print(byte(34));
	client.print("><a href="),client.print(byte(34));
	client.print("http://192.168.0.103"),client.print(byte(34));
	client.print("><input type="),client.print(byte(34));
	client.print("button"),client.print(byte(34));
	client.print("value="),client.print(byte(34));
	client.print("Caméra 3"),client.print(byte(34));
	client.print("></a></TD>");
	// IP 4
	//  <TD ALIGN="center"><a href="http://192.168.0.104"><input type="button" value="Caméra 4"></a></TD>
	client.print("<TD ALIGN="),client.print(byte(34));
	client.print("center"),client.print(byte(34));
	client.print("><a href="),client.print(byte(34));
	client.print("http://192.168.0.104"),client.print(byte(34));
	client.print("><input type="),client.print(byte(34));
	client.print("button"),client.print(byte(34));
	client.print("value="),client.print(byte(34));
	client.print("Caméra 4"),client.print(byte(34));
	client.print("></a></TD>");
	client.println("</TR>");
	// Fin tableau caméras
	client.println("</TABLE>");
	client.println("<br>"); // saut de ligne
	client.println("<br>"); // saut de ligne
	// Début tableau Vitesse
	client.println("<TABLE BORDER=0 WIDTH=50%>");
	client.println("<tr>");	
	// Vitesse lente
	client.print("<td ALIGN="),client.print(byte(34));
	client.print("center"),client.print(byte(34));
	client.print("><INPUT TYPE="),client.print(byte(34));
	client.print("radio"),client.print(byte(34));
	client.print("NAME="),client.print(byte(34));
	client.print("vitesse"),client.print(byte(34));
	client.print("VALUE="),client.print(byte(34));
	client.print("1"),client.print(byte(34));
	client.print("CHECKED>Vitesse Lente</td>");
	// Vitesse rapide
	client.print("<td ALIGN="),client.print(byte(34));
	client.print("center"),client.print(byte(34));
	client.print("><INPUT TYPE="),client.print(byte(34));
	client.print("radio"),client.print(byte(34));
	client.print("NAME="),client.print(byte(34));
	client.print("vitesse"),client.print(byte(34));
	client.print("VALUE="),client.print(byte(34));
	client.print("2"),client.print(byte(34));
	client.print("CHECKED>Vitesse Rapide</td>");	
	client.println("</tr>");
	// Fin tableau Vitesse
	client.println("</TABLE>");
	client.println("<br>"); // saut de ligne
	// Debut Tableau FDC + Boutons
	client.println("<TABLE BORDER=0 WIDTH=30%>");
	// Debut ligne FDC
	client.print("<tr height="),client.print(byte(34));
	client.print("50"),client.print(byte(34));
	client.print(">");
	// FDC 1
	client.print("<td ALIGN="),client.print(byte(34));
	client.print("center"),client.print(byte(34));
	client.print("><INPUT TYPE="),client.print(byte(34));
	client.print("radio"),client.print(byte(34));
	client.print("NAME="),client.print(byte(34));
	client.print("Fin de course"),client.print(byte(34));
	client.print("VALUE="),client.print(byte(34));
	client.print("FDC1"),client.print(byte(34));
	client.print("disabled >Max Zoom&nbsp;&nbsp;</td>");
	// FDC 2 
	client.print("<td ALIGN="),client.print(byte(34));
	client.print("center"),client.print(byte(34));
	client.print("><INPUT TYPE="),client.print(byte(34));
	client.print("radio"),client.print(byte(34));
	client.print("NAME="),client.print(byte(34));
	client.print("Fin de course"),client.print(byte(34));
	client.print("VALUE="),client.print(byte(34));
	client.print("FDC2"),client.print(byte(34));
	client.print("disabled >Min Zoom&nbsp;&nbsp;</td>");
	// Fin ligne FDC
	client.println("</tr>");
	// Debut ligne boutons
	client.println("<tr>");
	// Bouton +
	client.print("<td ALIGN="),client.print(byte(34));
	client.print("center"),client.print(byte(34));
	client.print("><input type="),client.print(byte(34));
	client.print("button"),client.print(byte(34));
	client.print("  value="),client.print(byte(34));
	client.print("        +        "),client.print(byte(34));
	client.print("></td>");
	// Bouton -
	client.print("<td ALIGN="),client.print(byte(34));
	client.print("center"),client.print(byte(34));
	client.print("><input type="),client.print(byte(34));
	client.print("button"),client.print(byte(34));
	client.print("  value="),client.print(byte(34));
	client.print("        -        "),client.print(byte(34));
	client.print("></td>");
	// Fin ligne boutons
	client.println("</tr>");
	// Fin Tableau FDC + Boutons
	client.println("</TABLE>");
	// Fin de fichier
	client.println("</center>");
	client.println("</body>");
	client.println("</HTML>");
	client.println("</HTML>");
}
  //if (!client) {
	//exemple
    //}
}
