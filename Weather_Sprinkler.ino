#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h> 

const char* ssid = "your_ssid"; // replace with your network information
const char* password = "your_password"; // replace with your network information

int DA=0;//Direction A pin GPIO 0
int PWMA=5;//PWM A pin GPIO5

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(2000);
  pinMode(PWMA, OUTPUT);
  pinMode(DA, OUTPUT);
  // Wait for serial to initialize.
  while(!Serial) { }
  
  while(WiFi.status() != WL_CONNECTED){
    Serial.println("Connecting...");
    delay(200);
  }
   if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;  
    http.begin("http://api.openweathermap.org/data/2.5/onecall?lat=42.9675&lon=-78.78345&units=imperial&appid=  API KEY GOES HERE ");//replace your api key here
    int httpCode = http.GET();
    String json = http.getString();
    //Check the return code to ensure the request was successful                                                                 
    if (httpCode == 200) {    
        StaticJsonDocument<200> filter;
        filter["current"]["temp"] = true; // 304.51
        filter["current"]["feels_like"] = true; // 307.69
        
        filter["daily"][0]["rain"] = true; // 0.25
        filter["daily"][1]["rain"] = true; // 0.25
        
        const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + 2*JSON_OBJECT_SIZE(2) + 2*JSON_OBJECT_SIZE(2) + 40;
        DynamicJsonDocument doc(capacity);
        deserializeJson(doc, json, DeserializationOption::Filter(filter));
        
        float current_temp = doc["current"]["temp"]; // 304.51
        float current_feels_like = doc["current"]["feels_like"]; // 307.69
        
        float daily_0_rain = doc["daily"][0]["rain"]; // 0.25
        float daily_1_rain = doc["daily"][1]["rain"]; // 0.25
        
            Serial.print("Current Temp:");
            Serial.print(current_temp);
            Serial.println(" degrees F");
            Serial.print("Rainfall amount: ");
            Serial.println(daily_0_rain);
            Serial.print("Rain tomorrow: ");
            Serial.println(daily_1_rain);
        if(daily_0_rain < 12){
          
          digitalWrite(PWMA, HIGH);
          Serial.println("Less than 12 mm of rain detected, watering for 30 seconds...");
          delay(30000); //water for 30 seconds
          digitalWrite(PWMA, LOW);
          Serial.println("Stopped Watering");
        }
         
    }else{
      Serial.print("Error getting weather Http Code:");
      Serial.print(httpCode);

    }
    http.end();   //Close connection
  }
  Serial.println("Entering Deep Sleep mode");
  ESP.deepSleep(8.636e10); //8.636e10 is 24 hours minus 30 seconds to account for the extra time to water the plant
}

void loop() {
  //this code does not loop, it runs code on each restart

}
