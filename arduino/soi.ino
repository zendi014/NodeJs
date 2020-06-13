//////////////////// LIBRARIES /////////////////////
#include <Arduino.h>
#include <Wire.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <SocketIoClient.h> // Extract and Locate the library from my github
//////////////////// GLOBAL DEFINE /////////////////////

WiFiClient client;
SocketIoClient soi;


const char *ssid = "DEA HOME";
const char *password = "92912733";
char path[] = "/";
char host[]= "192.168.1.12"; //WLAN IP (SERVER)
int port = 3000;






////////////////// LOOP AND SETUP ///////////////////////
void setup() {
    #if defined(ESP8266)
      Serial.begin(115200);
    #else
      Serial.begin(38400);
    #endif

    Serial.setDebugOutput(true);
    for(uint8_t t = 4; t > 0; t--) {
        Serial.printf("[SETUP] BOOT WAIT %d...\n", t);
        Serial.flush();
        delay(500);
    }

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    
    wifi_connection();

    // Initial socket
    soi.on("connect", connection);
    soi.begin(host, port);
}



int a = 0;

void loop() {
    soi.loop();
    if(a == 0){
      soi.emit("ebd", "EBD Connected"); // when its connected emit to server
      a=1;
    }
    broadcast();//broadcast data {name, status, value}
    delay(3000);
}




//////////////// BINDING CONNECTION /////////////////////
void wifi_connection(){
    Serial.print("\n");
    Serial.printf("WiFi Connecting to :: ");
    Serial.printf(ssid);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500); Serial.printf(".");
    }

    Serial.print("\n"); Serial.printf("WiFi connected");
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





void connection(const char * payload, size_t length) {
    soi.emit("connection", "EBD Connected");
}


//////////////// TRIGGER AND PARSE DATA /////////////////////


void broadcast(){ // broad cast to server
    StaticJsonDocument<800> dt; //init data
    dt["name"] = "EBD Syst 1";
    dt["status"] = "EN";
    dt["value"] = random(50, 150); //init random value or sensor data here

    char json_dt[800];
    serializeJson(dt, json_dt);
    soi.emit("ebd", json_dt);
}
