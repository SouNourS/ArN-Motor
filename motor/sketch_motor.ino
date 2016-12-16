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
	      // et dans tout les cas on r�pond au client
	      repondre(client);
	      // on quitte le while
	      break;
              //monServo.writeMicroseconds(1400);
	      }
     }
     delay(10);
     client.stop();
    }
}
void repondre(EthernetClient client) {
	//Envoi du header standard HTTP au browser
	client.println("HTTP/1.1 200 OK");
	client.println("Content-Type: text/html; charset=utf-8");
	client.println();
	client.println("<HTML>");
	client.println("<HEAD>");
	client.println("<TITLE>Contr�le Cam�ra 1</TITLE>");
	client.println("</HEAD>");
	client.println("<body BGCOLOR='#E0E0F8'>");
	client.println("<center>");
	client.println("<H1>Contr�le Cam�ra 1</H1>");
	client.println("<br><br>");
	// D�but tableau cam�ras
	client.println("<TABLE BORDER=0 WIDTH=80%>");
	client.println("<TR>");
	// IP 1
	//  <TD ALIGN="center"><a href="http://192.168.0.101"><input type="button" value="Cam�ra 1"></a></TD>
	client.println("<TD ALIGN='center'><a href='http://192.168.0.101'><input type='button' value='Cam�ra 1'></a></TD>");
	// IP 2
	//  <TD ALIGN="center"><a href="http://192.168.0.102"><input type="button" value="Cam�ra 2"></a></TD>
	client.println("<TD ALIGN='center'><a href='http://192.168.0.102'><input type='button' value='Cam�ra 2'></a></TD>");
	// IP 3
	//  <TD ALIGN="center"><a href="http://192.168.0.103"><input type="button" value="Cam�ra 3"></a></TD>
	client.println("<TD ALIGN='center'><a href='http://192.168.0.103'><input type='button' value='Cam�ra 3'></a></TD>");
	// IP 4
	//  <TD ALIGN="center"><a href="http://192.168.0.104"><input type="button" value="Cam�ra 4"></a></TD>
	client.println("<TD ALIGN='center'><a href='http://192.168.0.104'><input type='button' value='Cam�ra 4'></a></TD>");
	client.println("</TR>");
	// Fin tableau cam�ras
	client.println("</TABLE>");
	client.println("<br>"); // saut de ligne
	client.println("<br>"); // saut de ligne
	// D�but tableau Vitesse
	client.println("<TABLE BORDER=0 WIDTH=50%>");
	client.println("<tr>");	
	// Vitesse lente
	client.println("<td ALIGN='center'><INPUT TYPE='radio' NAME='vitesse' VALUE='1' CHECKED>Vitesse Lente</td>");
	// Vitesse rapide
	client.println("<td ALIGN='center'><INPUT TYPE='radio' NAME='vitesse' VALUE='2' CHECKED>Vitesse Rapide</td>");
	client.println("</tr>");
	// Fin tableau Vitesse
	client.println("</TABLE>");
	client.println("<br>"); // saut de ligne
	// Debut Tableau FDC + Boutons
	client.println("<TABLE BORDER=0 WIDTH=30%>");
	// Debut ligne FDC
	client.println("<tr height='50'>");
	// FDC 1
	client.println("<td ALIGN='center'><INPUT TYPE='radio' NAME='Fin de course' VALUE='FDC1' disabled >Max Zoom&nbsp;&nbsp;</td>");
	// FDC 2 
	client.println("<td ALIGN='center'><INPUT TYPE='radio' NAME='Fin de course' VALUE='FDC2' disabled >Min Zoom&nbsp;&nbsp;</td>");
	// Fin ligne FDC
	client.println("</tr>");
	// Debut ligne boutons
	client.println("<tr>");
	// Bouton +
	client.println("<td ALIGN='center'><input type='button'  value='        +        '></td>");
	// Bouton -
	client.println("<td ALIGN='center'><input type='button'  value='        -        '></td>");
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
