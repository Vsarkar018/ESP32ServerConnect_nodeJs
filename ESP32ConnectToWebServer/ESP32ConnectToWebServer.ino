#include<WiFi.h>
#include <HTTPClient.h>
#include<ArduinoJson.h>

const char* ssid = "Redmi Note 9 Pro";
const char* password = "enterpassword";

const char* server = "http://192.168.192.244:5000/";
const long interval = 5000;
unsigned long previousMillis = 0;
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 }

void loop() {
  unsigned long currentMillis = millis();
    if(currentMillis - previousMillis >= interval) {
      if(WiFi.status()== WL_CONNECTED ){
        String output = getRequest(server);
        Serial.print("Get Request Data :");
        Serial.println(output);
        
//        output.replace(" ","");
//        output.replace("\n","");
//        output.trim();
//        output.remove(0,1);
        
        char json[500];
        output.toCharArray(json,500);
    StaticJsonDocument<48> doc;
      DeserializationError error = deserializeJson(doc, json,500);
      if (error) {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
        return;
      }

      int g = doc["0"]["g"]; // 2
      int v = doc["0"]["v"]; // 1
      Serial.println(g);
      Serial.println(v);
      pinMode(g,OUTPUT);
      digitalWrite(g,v);
        previousMillis = currentMillis;
      }else{
        Serial.println("WiFi Disconnected");
      }
    }
}

String getRequest(const char* server){
  HTTPClient client;
  client.begin(server);
  int httpCode = client.GET();
  String payload = "{}";
  if(httpCode>0){
    payload = client.getString();
    Serial.print("HTTP Status Code = " );
    Serial.println(httpCode);
  }else{
    Serial.println("Error");
    Serial.print("HTTP Status Code = " );
    Serial.println(httpCode);
  }
  client.end();
  return payload;
}
