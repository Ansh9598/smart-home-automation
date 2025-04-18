/*
 * Board: DOIT ESP32 DEVKIT v1
 * Description: 4 Bulb (Relay) Smart Home Automation with Ubidots
 */
#include <WiFi.h>
#include <UbidotsESPMQTT.h>

#define RELAY1 16  // Use proper GPIO pins
#define RELAY2 17
#define RELAY3 18
#define RELAY4 19

#define TOKEN "BBUS-j4Ij5ErnqfoCx8yMRZsvpuhCTMMqyp"  // Your Ubidots TOKEN
#define WIFISSID "realme12"                          // Your SSID
#define WIFIPASS "09876543"                          // Your Wifi Password

Ubidots client(TOKEN);

// Callback to handle incoming messages
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String message = topic;

  if (message.substring(25) == "red/lv") {
    Serial.println("Red Bulb Command");

    Serial.println("text:");

    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println();
    Serial.print("Command: ");
    bool command = *payload - 48;
    Serial.println(command);
    digitalWrite(RELAY1, command);
  }

  if (message.substring(25) == "yellow/lv") {
    Serial.println("Yellow Bulb Command");

    Serial.println("text:");

    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println();
    Serial.print("Command: ");
    bool command = *payload - 48;
    Serial.println(command);
    digitalWrite(RELAY2, command);
  }

   if (message.substring(25) == "blue/lv") {
    Serial.println("blue Bulb Command");

    Serial.println("text:");

    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println();
    Serial.print("Command: ");
    bool command = *payload - 48;
    Serial.println(command);
    digitalWrite(RELAY3, command);
  }

   if (message.substring(25) == "white/lv") {
    Serial.println("white Bulb Command");

    Serial.println("text:");

    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println();
    Serial.print("Command: ");
    bool command = *payload - 48;
    Serial.println(command);
    digitalWrite(RELAY4, command);
  }
}


void setup() {
  Serial.begin(9600);
  Serial.println("Init... Smart Home Automation");

  // Set relay pins as output
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);

  // Initialize all relays as OFF
  digitalWrite(RELAY1, LOW);
  digitalWrite(RELAY2, LOW);
  digitalWrite(RELAY3, LOW);
  digitalWrite(RELAY4, LOW);

  // Connect to Wi-Fi
  Serial.print("Connecting to SSID: ");
  Serial.println(WIFISSID);
  client.wifiConnection(WIFISSID, WIFIPASS);

  // Connect to Ubidots
  client.ubidotsSetBroker("industrial.api.ubidots.com");
  client.setDebug(true);
  client.begin(callback);

  // Subscribe to each variable
  client.ubidotsSubscribe("smart-home", "blue");
  client.ubidotsSubscribe("smart-home", "red");
  client.ubidotsSubscribe("smart-home", "yellow");
  client.ubidotsSubscribe("smart-home", "white");

  Serial.println("Setup done");
}

void loop() {
  if (!client.connected()) {
    client.reconnect();
    client.ubidotsSubscribe("smart-home", "blue");
    client.ubidotsSubscribe("smart-home", "red");
    client.ubidotsSubscribe("smart-home", "yellow");
    client.ubidotsSubscribe("smart-home", "white");
  }
  client.loop();
  delay(1000);
}