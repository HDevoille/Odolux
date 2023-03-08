#include <WiFi.h>
#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;

const char* ssid = "votre_SSID";
const char* password = "votre_mot_de_passe";

WiFiServer server(80);

void Up(Servo servoI){
  for(int i = 0; i < 90; i++){
    servoI.write(i);
    delay(7);
  }
}

void Down(Servo servoI){
  for(int i = 90; i > 0; i++){
    servoI.write(i);
    delay(7);
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connexion au WiFi...");
  }

  Serial.println("");
  Serial.println("WiFi connecté");
  Serial.println("Adresse IP : ");
  Serial.println(WiFi.localIP());

  server.begin();
  Serial.println("Serveur web démarré");
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New client connected.");
    while (client.connected()) {
      if (client.available()) {
        String request = client.readStringUntil('\r');
        switch(request[0]){
          case'0':
            if(request[1] == '0'){
              Up(servo1);
            }
            else{
              Down(servo1);
            }
            break;
          case'1':
            if(request[1] == '0'){
              Up(servo2);
            }
            else{
              Down(servo2);
            }
            break;
          case'2':
            if(request[1] == '0'){
              Up(servo3);
            }
            else{
              Down(servo3);
            }
            break;
          default:
            Serial.println("Missing parameters");
            break;
        }
        client.flush();
      }
    }
    Serial.println("Client disconnected.");
  }
}
