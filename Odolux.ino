#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;

const char* ssid = "votre_SSID";
const char* password = "votre_mot_de_passe";

WebServer server(80);

void handleSetString() {
  if (server.hasArg("maChaine")) {
    String maChaine = server.arg("maChaine");
    Serial.print("Chaine reçue : ");
    Serial.println(maChaine);
    
    // Séparez la chaîne en deux entiers
    int entier1 = maChaine.substring(0, 2).toInt();
    int entier2 = maChaine.substring(2, 4).toInt();
    
    Serial.print("Entier 1 : ");
    Serial.println(entier1);
    Serial.print("Entier 2 : ");
    Serial.println(entier2);
    
    // utilisez entier1 et entier2 dans votre code ici
    switch(entier1){
      case 0:
        if(entier2 == 1){
          servo1.write(90);
        }
        else{
          servo1.write(0);
        }
        break;
      case 1:
        if(entier2 == 1){
          servo2.write(90);
        }
        else{
          servo2.write(0);
        }
        break;
      case 2:
        if(entier2 == 1){
          servo3.write(90);
        }
        else{
          servo3.write(0);
        }
        break;
      default:
        println("Paramètre incorrect");
        break;
    }
    
    server.send(200, "text/plain", "Chaine reçue !");
  } else {
    server.send(400, "text/plain", "Paramètre manquant !");
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Attendez la connexion WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connexion au WiFi...");
  }

  Serial.println("");
  Serial.println("WiFi connecté");
  Serial.println("Adresse IP : ");
  Serial.println(WiFi.localIP());

  // Configurez les gestionnaires de requêtes
  server.on("/", [](){
    server.send(200, "text/plain", "Salut !");
  });

  server.on("/setString", handleSetString);

  // Démarrez le serveur web
  server.begin();
  Serial.println("Serveur web démarré");
}

void loop() {
  // Écoutez les requêtes HTTP entrantes
  server.handleClient();
}
