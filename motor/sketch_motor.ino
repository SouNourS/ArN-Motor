#include <SPI.h>
#include <Ethernet2.h>
#include <Servo.h>

// L'adresse MAC du shield
byte mac[] = { 0x90, 0xA2, 0xDA, 0x10, 0xDE, 0xE7 };
// L'adresse IP que prendra le shield
byte ip[] = { 192, 168, 1, 101 };
// Port d'écoute
EthernetServer serveur(80);

Servo monServo;

char *url = (char *)malloc(20);
int index = 0;
bool bSensCam = 0;
int iSensCam = 0;
bool bVitesseCam = 0;
int iVitesseCam = 0;
int CamArret = 1500;
int CamMouv = 1500;

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
  monServo.writeMicroseconds(CamArret);
}

void loop()
{
  // Regarde si un client est connecte et attend une reponse
  EthernetClient client = serveur.available();
  if (client) {
    url == "";
    index = 0;
    // Gestion de la fin de la requete WEB qui est indiquee par l'envoi d'une ligne blanche
    //boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char carlu = client.read();
        if(carlu != '\n'){
          url[index] = carlu;
          index++;
        } else {
          url[index] == ' ';
          boolean ok = interpreteur();
          if(ok){
            action();
          }
        // et dans tout les cas on répond au client
        repondre(client);
        // on quitte le while
        break;
          }
        //}
}
	      }
     }
     delay(10);
     client.stop();
    }
void repondre(EthernetClient client) {
	//Envoi du header standard HTTP au browser
	client.println(F("HTTP/1.1 200 OK"));
	client.println(F("Content-Type: text/html; charset=utf-8"));
	client.println();
	client.println(F("<HTML>"));
	client.println(F("<HEAD>"));
	client.println(F("<TITLE>Contrôle Caméra 1</TITLE>"));
	client.println(F("</HEAD>"));
	client.println(F("<body BGCOLOR= #E0E0F8>"));
	client.println(F("<center>"));
	client.println(F("<H1>Contrôle Caméra 1</H1>"));
	client.println(F("<br><br>"));
	// Début tableau caméras
	client.println(F("<TABLE BORDER=0 WIDTH=80%>"));
	client.println(F("<TR>"));
	// IP 1
	//  <TD ALIGN="center"><a href="http://192.168.1.101"><input type="button" value="Caméra 1"></a></TD>
	client.println(F("<TD ALIGN= center ><a href='http://192.168.1.101'><input type='button' value='Caméra 1'></a></TD>"));
	// IP 2
	//  <TD ALIGN="center"><a href="http://192.168.1.102"><input type="button" value="Caméra 2"></a></TD>
	client.println(F("<TD ALIGN='center'><a href='http://192.168.1.102'><input type='button' value='Caméra 2'></a></TD>"));
	// IP 3
	//  <TD ALIGN="center"><a href="http://192.168.1.103"><input type="button" value="Caméra 3"></a></TD>
	client.println(F("<TD ALIGN='center'><a href='http://192.168.1.103'><input type='button' value='Caméra 3'></a></TD>"));
	// IP 4
	//  <TD ALIGN="center"><a href="http://192.168.1.104"><input type="button" value="Caméra 4"></a></TD>
	client.println(F("<TD ALIGN='center'><a href='http://192.168.1.104'><input type='button' value='Caméra 4'></a></TD>"));
	client.println(F("</TR>"));
	// Fin tableau caméras
	client.println(F("</TABLE>"));
	// Debut Tableau FDC + Boutons
	client.println(F("<TABLE BORDER=0 WIDTH=30%>"));
	// Debut ligne FDC
	client.println(F("<tr height='50'>"));
	// FDC 1
	client.println(F("<td ALIGN='center'><INPUT TYPE='radio' NAME='Fin de course' VALUE='FDC1' disabled >Max Zoom&nbsp;&nbsp;</td>"));
	// FDC 2 
	client.println(F("<td ALIGN='center'><INPUT TYPE='radio' NAME='Fin de course' VALUE='FDC2' disabled >Min Zoom&nbsp;&nbsp;</td>"));
	// Fin ligne FDC
	client.println(F("</tr>"));
  // Debut ligne boutons 2
  client.println(F("<tr height='50'>"));
  // Bouton +
  client.println(F("<td ALIGN='center'><a href='http://192.168.1.101/s=1&v=1'><input type='button'value='     Rapide     +'></a></td>"));
  // Bouton -
  client.println(F("<td ALIGN='center'><a href='http://192.168.1.101/s=0&v=1'><input type='button'value='     Rapide     -'></a></td>"));
  client.println(F("<br>"));
	client.println(F("</tr>"));
  // Debut ligne boutons
  client.println(F("<tr height='50'>"));
  client.println(F("<br>"));
	// Bouton +
	client.println(F("<td ALIGN='center'><a href='http://192.168.1.101/s=1&v=0'><input type='button'value='      Lent      +'></a></td>"));
	// Bouton -
	client.println(F("<td ALIGN='center'><a href='http://192.168.1.101/s=0&v=0'><input type='button'value='      Lent      -'></a></td>"));
	// Fin ligne boutons
	client.println(F("</tr>"));
	// Fin Tableau FDC + Boutons
	client.println(F("</TABLE>"));
	// Fin de fichier
	client.println(F("</center>"));
	client.println(F("</body>"));
	client.println(F("</HTML>"));
	  }

 boolean interpreteur(){
  index = 0;
  while(url[index-1] != 's' && url[index] != '='){
    index++;
    if(index == 20){
      return false;
      }
  }
  while(url[index] != '&'){
    if(url[index] >= '0' && url[index] <= '1'){
      char sens = url[index]-'0';
      bSensCam = sens;
    }
    index++;
    if(index == 20) {
      return false;
    }
  }
  while(url[index-2] != 'v' && url[index-1] != '='){
    if(url[index+1] >= '0' && url[index+1] <= '1'){
      char vit = url[index+1]-'0';
      bVitesseCam = vit;
    }
  index++;
  if(index == 20){
    return false;
  }
  }
  return true;
 }
 void action(){
  if(bSensCam == 0){
    iSensCam = -1;
  } else {
    iSensCam = 1;
  }
  if(bVitesseCam == 0){
    iVitesseCam = 1;
  } else {
    iVitesseCam = 6;
  }
  CamMouv = (iSensCam * iVitesseCam * 100) + CamArret ;
  monServo.writeMicroseconds(CamMouv);
  delay(1000);
  monServo.writeMicroseconds(CamArret);
 }
