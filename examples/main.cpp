#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <coindesk.h>
#include <WiFiClientSecure.h>
const char *ssid = "";//paste here your wifi ssid
const char *passwd = "";//paste here your wifi password
WiFiClientSecure client;
const char *fingerprint = ""; //fingerprint
const char *web_host = "api.coindesk.com";                            //website
String web_api = "/v1/bpi/currentprice.json";                         //url
bool debug = false; //set to true to get more debug information
unsigned long timeout = 60000; // deafult timeout is 60000 
Coindesk crypto1(client, web_host, web_api,debug,timeout);
unsigned long times = 0;
void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(200);
  WiFi.begin(ssid, passwd);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println(".");
    delay(1000);
  }
  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("Connected to: ");
    Serial.println(ssid);
    IPAddress ip = WiFi.localIP();
    Serial.println(ip);
  }

  //client.setInsecure();//if you don't want to check the api website fingerprint
  client.setFingerprint(fingerprint);
}
void loop()
{
  crypto1.make_request();
  if(millis() >= times + 10000){
    times += 10000;
    Serial.println(crypto1.data.time_updated);
    Serial.println(crypto1.data.time_updatedISO);
  }
}
