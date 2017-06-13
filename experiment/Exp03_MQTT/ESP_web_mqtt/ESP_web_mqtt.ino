#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <PubSubClient.h>

const char* ssid = "syokujinau";
const char* password = "0982721453";
const char* mqtt_server = "192.168.0.102";

const char clientID[] = "ESP8266Client";
const char topic[] = "home/yard/DHT11";

ESP8266WebServer server(80);
WiFiClient espClient;
PubSubClient client(espClient);

String msgStr;
char msg[25];

void setup(void){
  Serial.begin(9600);
  setupWIFI();
  client.setServer(mqtt_server, 1883);

  server.on("/", handleRoot);

  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });

  server.on("/temp", [](){
    String a="";
    a+="<!DOCTYPE html><html><head><title>Page Title</title><meta http-equiv=\"refresh\" content=\"3\" /></head><body>";
    a+="<h1>"+msgStr+ "</h1>";
    a+="</body></html>";
    server.send(200, "text/html", a);
    //msgStr="";
  });

  server.on("/temp.json", [](){
    server.send(200, "application/json", msgStr);
    msgStr="";
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println(F("HTTP server started"));
}

void loop(void){
  msgStr ="{\"temp\":" + (String)(19 + random(10)) + ",\"humid\":" + (String)20 + "}";
  server.handleClient();
  
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  msgStr.toCharArray(msg,25);
  client.publish(topic, msg);

  delay(1000);
}

void setupWIFI(){
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print(F("Connected to "));
  Serial.println(ssid);
  Serial.print(F("IP address: "));
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println(F("MDNS responder started"));
  }
}

void handleRoot() {
  server.send(200, "text/plain", "hello from esp8266!");
}

void handleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

//for MQTT
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    //Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(clientID)) {
      Serial.println(F("connected"));
      // Once connected, publish an announcement...
      // client.publish("home/yard/DHT11", "hello world");
      // ... and resubscribe
      //client.subscribe("inTopic");
    } else {
      Serial.print(F("failed, rc="));
      Serial.print(client.state());
      Serial.println(F(" try again in 5 seconds"));
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

