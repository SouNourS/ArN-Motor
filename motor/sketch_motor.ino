#include <SPI.h>
#include <Ethernet2.h>
#include <Servo.h>

byte mac[] = { 0x90, 0xA2, 0xDA, 0x10, 0xDE, 0xE7 }; // L'adresse MAC du shield
byte ip[] = { 192, 168, 1, 101 }; // L'adresse IP que prendra le shield

EthernetServer serveur(80); // Port d'écoute

Servo monServo; // Init moteur

char *url = (char *)malloc(20);	//init url
int index = 0;					//init index (url)
bool bSensCam = 0;				//init sens de rotation du moteur 0,1 (-,+)
int iSensCam = 0;				//init sens de rotation du moteur -1,1 (-,+)
bool bVitesseCam = 0;			//init vitesse de rotation du moteur 0,1 (lent, rapide)
float fVitesseCam = 0.;			//init sens de rotation du moteur 0.1,6 (lent, rapide)
int CamArret = 1500;			//init valeur d'arret du moteur
int CamMouv = 1500;				//init du mouvement du moteur
int iTempsTourne = 0;			//init du temps de rotation en ms
unsigned long temps;			//init pour calcul du temps

void setup(){
	Serial.begin(9600); // On démarre la voie serie pour deboguer
	Ethernet.begin(mac, ip); // On crée la partie Eth
	delay(1000); // Petite pause pour être sur que le shield Eth est démarré
	serveur.begin(); // Démarrage du serveur
	monServo.attach(5); // Moteur sur le pin 5
	monServo.writeMicroseconds(CamArret); // Moteur arreté !
}

void loop(){
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
					// On analyse le GET pour savoir comment le moteur doit tourner.
					boolean ok = interpreteur();
					if(ok){
						// On fait tourner le moteur.
						action();
					}
					// et dans tout les cas on répond au client
					repondre(client);
					// on quitte le while
					break;
				}
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
			bSensCam = sens; // lecture du sens de rotation via s=
		}
		index++;
		if(index == 20) {
			return false;
		}
	}
	while(url[index-2] != 'v' && url[index-1] != '='){
		if(url[index+1] >= '0' && url[index+1] <= '1'){
			char vit = url[index+1]-'0';
			bVitesseCam = vit; // lecture de la vitesse de rotation via v=
		}
		index++;
		if(index == 20){
			return false;
		}
	}
	return true;
}
void action(){
	if(bSensCam == 0){ 	// sens -
		iSensCam = -1;
	} else {			// sens +
		iSensCam = 1;
	}
	if(bVitesseCam == 0){	// params vitesse lente
		fVitesseCam = 0.1;	// vitesse
		iTempsTourne = 500;	// temps (en ms)
	} else {				// params vitesse rapide
		fVitesseCam = 4;	// vitesse
		iTempsTourne = 1000;// temps (en ms)
	}
	CamMouv = (iSensCam * fVitesseCam * 100) + CamArret ; // Calcul de la vitesse du moteur.
	monServo.writeMicroseconds(CamMouv);	// le moteur tourne !
	temps = millis();
	while(millis()-temps <= iTempsTourne){ // delay maquillé pour future vérification d'un potar
		int toto = 1;
	}
	monServo.writeMicroseconds(CamArret);	// le moteur s'arrete !
}
