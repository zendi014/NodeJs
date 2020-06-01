//http://arduino.esp8266.com/stable/package_esp8266com_index.json
//https://dl.espressif.com/dl/package_esp32_index.json
// ArduinoJSON can be downloaded through sketch

//////////////////// LIBRARIES /////////////////////
#include <Arduino.h>
#include <Wire.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

//////////////////// GLOBAL DEFINE /////////////////////
WiFiClient client;

const char *ssid = "Wifi Berbayar";
const char *password = "tigarebu";
char path[] = "/";
char host[]= "192.168.43.240"; //WLAN IP (SERVER)
int port = 3000;




////////////////// LOOP AND SETUP ///////////////////////
void setup(){
    #if defined(ESP8266)
        Serial.begin(115200);
    #else
        Serial.begin(38400);
    #endif

    Serial.setDebugOutput(true);
    for (uint8_t t = 4; t > 0; t--)
    {
        Serial.printf("[SETUP] BOOT WAIT %d...\n", t);
        Serial.flush();
        delay(500);
    }    
    wifi_connection();
}




int c = 0;
void loop()
{
  post_json();

  //delay each 30 seconds
  c++;
  delay(10000);
  if(c%3 == 0 ){
    c = 0;
  }
}




//////////////// BINDING CONNECTION /////////////////////
void wifi_connection()
{
    Serial.print("\n");
    Serial.printf("WiFi Connecting to :: ");
    Serial.printf(ssid);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.printf(".");
    }

    Serial.print("\n");
    Serial.printf("WiFi connected");
    Serial.printf("IP address: ");
    Serial.print(WiFi.localIP());

    app_connection();
}





void app_connection()
{
    Serial.print("\n");
    Serial.printf("App Connecting to :: ");
    Serial.printf(host);

    if (client.connect(host, port))
    {
        Serial.printf("\n\nApp Server Connected\n\n");
    }
    else
    {
        Serial.printf("\nApp Server Connection failed\n & Trying...");
        app_connection();
    }

    Serial.print("");
}




///////////////////////////////////////////////////////////////


void post_json(){
    StaticJsonDocument<800> doc;   //Declaring static JSON buffer  
    doc["device_name"] = "node_2";
    doc["sensor_name"] = "HCSR04";
    doc["status"] = "EN";
    doc["value"] = random(35, 120); // read from sensors

    char data_json[800];
    serializeJson(doc, data_json);

    HTTPClient http;    //Declare object of class HTTPClient
   
    http.begin("http://ip_server:3000/api/service/create");      //Specify request destination
    http.addHeader("Content-Type", "application/json");
    
    int httpCode = http.POST(data_json);   //Send the request
    String payload = http.getString();                  //Get the response payload
    //Serial.println(payload);
   
    http.end();  //Close connection
}
