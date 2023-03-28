// Include required libraries
#include <WiFi.h>      // Library for WiFi connectivity
#include <ESP32Servo.h> // Library for controlling servos with ESP32

// Define the different pins used
#define SERVO1 12 // Pin for the first servomotor
#define SERVO2 14 // Pin for the second servomotor
#define SERVO3 27 // Pin for the third servomotor
#define FAN 5 // Pin for the relay activating the fan

// Create servo objects
Servo servo1;
Servo servo2;
Servo servo3;

// Define WiFi credentials
const char* ssid = "Your Wifi name";
const char* password = "Your password";

// Create WiFi server object
WiFiServer server(80);

// Function to move a servo up
void Up(Servo servoI){
  for(int i = 0; i < 90; i++){
    servoI.write(i);
    delay(7);
  }
}

// Function to move a servo down
void Down(Servo servoI){
  for(int i = 90; i > 0; i++){
    servoI.write(i);
    delay(7);
  }
}

void setup() {
  // Start serial communication
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for WiFi connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  // Print WiFi connection details
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Start web server
  server.begin();
  Serial.println("Web server started");

  // Attach servos to their respective pins
  servo1.attach(SERVO1);
  servo2.attach(SERVO2);
  servo3.attach(SERVO3);

  // Define the pin to control the fan
  pinMode(FAN,OUTPUT);
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (client) {
    // Print client connection details
    Serial.println("New client connected.");

    // Wait for client to send request
    while (client.connected()) {
      if (client.available()) {
        // Read client request
        String request = client.readStringUntil('\r');

        // Check the request and move the appropriate servo
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
          // Case to switch on or off the fan
          case'3':
            if(request[1] == '0'){
              digitalWrite(5,HIGH);
            }
            else{
              digitalWrite(5,LOW);
            }
            break;
          default:
            // Print error message if request is invalid
            Serial.println("Missing parameters");
            break;
        }

        // Clear incoming request buffer
        client.flush();
      }
    }

    // Close client connection
    Serial.println("Client disconnected.");
  }
}
