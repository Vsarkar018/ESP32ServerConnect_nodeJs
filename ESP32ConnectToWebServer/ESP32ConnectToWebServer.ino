#include<WiFi.h>
#include <HTTPClient.h>
#include<ArduinoJson.h>

const char* ssid = "YOUR SSID NAME";
const char* password = "YOUR_NETWORK_PASSWORD";

const char* server = "http://IP_ADDRESS:PORT/";
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
        //Set Estimated Size of the imput stream 
        StaticJsonDocument<500> doc;
        DeserializationError error = deserializeJson(doc, json,500);

        if (error) {
          Serial.print("deserializeJson() failed: ");
          Serial.println(error.c_str());
          return;
        } 
                /*
                 JSon object in doc Format {
          "0": {
            "g": 2,
            "v": 1
          },
          "1": {
            "g": 12,
            "v": 1
          }
        }*/
        for (JsonPair item : doc.as<JsonObject>()) {
            const char* item_key = item.key().c_str(); 
            
            int g = item.value()["g"]; 
            int v = item.value()["v"]; 
            Serial.println(g);
            Serial.println(v);
            pinMode(g,OUTPUT);
            digitalWrite(g,v);
        }
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
