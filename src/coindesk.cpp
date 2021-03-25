#include "coindesk.h"
#include <ArduinoJson.h>
Coindesk::Coindesk(Client &client, const char *_web_host, String &_web_api, bool _debug,unsigned long _timeout = 60000)
{
    this->client = &client; 
    web_host = _web_host; 
    web_api = _web_api;
    debug = _debug;
    timeout = _timeout;
}
Coindesk::~Coindesk(){
    delete this;
}
void Coindesk::make_request()
{   
    client->setTimeout(timeout);  
    if(debug == true){
        Serial.println(web_host);
        Serial.println(web_api);
    }
    if (!client->connect(web_host, 443))
    {
        if (debug == true)
        {
            Serial.println(F("Connection failed"));
        }
        return;
    }
    yield();
    if (debug == true)
    {
        Serial.println(F("Connection succeed"));
    }
    client->print(F("GET "));
    client->print(web_api);
    client->println(F(" HTTP/1.1"));
    client->print(F("Host: "));
    client->println(web_host);
    if (client->println() == 0)
    {
        if (debug == true)
        {
            Serial.println(F("Failed to send"));
        }
        return;
    }
    char status[32] = {0};
    client->readBytesUntil('\r', status, sizeof(status));
    if (strcmp(status, "HTTP/1.1 200 OK") != 0)
    {
        if (debug == true)
        {
            Serial.println(F("Unexpected reasponse"));
            Serial.println(status);
        }
        return;
    }
    char endOfHeaders[] = "\r\n\r\n";
    if (!client->find(endOfHeaders))
    {
        if (debug == true)
        {
            Serial.println("Invalid response");
        }

        return;
    }
    while (client->available())
    {
        char c = 0;
        client->readBytes(&c, 1);
        //Serial.print(c);
        output.concat(c);
    }
    if (debug == true)
    {
        Serial.print(output);
    }
    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, output);
    output = "";
    if (error)
    {
        if (debug == true)
        {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
        }
        return;
    } 
    JsonObject time = doc["time"];
    data.time_updated = (char *)time["updated"].as<char *>();
    data.time_updatedISO = (char *)time["updatedISO"].as<char *>();
    data.time_updateduk = (char *)time["updateduk"].as<char *>();
    data.disclaimer = (char *)doc["disclaimer"].as<char *>();
    data.chartname = (char *)doc["chartName"].as<char *>();
    JsonObject bpi = doc["bpi"];//Nested values
    //USD
    JsonObject bpi_USD = bpi["USD"];
    usd.code = (char *)bpi_USD["code"].as<char *>();
    usd.symbol = (char *)bpi_USD["symbol"].as<char *>();
    usd.rate_char = (char *)bpi_USD["rate"].as<char *>();
    usd.description = (char *)bpi_USD["description"].as<char *>();
    usd.rate_float = bpi_USD["rate_float"].as<float>();
    //GBP
    JsonObject bpi_GBP = bpi["GBP"];
    gbp.code = (char *)bpi_GBP["code"].as<char *>();
    gbp.symbol = (char *)bpi_GBP["symbol"].as<char *>();
    gbp.rate_char = (char *)bpi_GBP["rate"].as<char *>();
    gbp.description = (char *)bpi_GBP["description"].as<char *>();
    gbp.rate_float = bpi_GBP["rate_float"].as<float>();
    //EUR
    JsonObject bpi_EUR = bpi["EUR"];
    eur.code = (char *)bpi_EUR["code"].as<char *>();
    eur.symbol = (char *)bpi_EUR["symbol"].as<char *>();
    eur.rate_char = (char *)bpi_EUR["rate"].as<char *>();
    eur.description = (char *)bpi_EUR["description"].as<char *>();
    eur.rate_float = bpi_EUR["rate_float"].as<float>();
    if(debug == true){
    Serial.println("");
    //Data
    Serial.println(data.time_updated);
    Serial.println(data.time_updatedISO);
    Serial.println(data.time_updateduk);
    Serial.println(data.disclaimer);
    Serial.println(data.chartname);
    //USD
    Serial.println(usd.code);
    Serial.println(usd.symbol);
    Serial.println(usd.rate_char);
    Serial.println(usd.description);
    Serial.println(usd.rate_float);
    //GBP
    Serial.println(gbp.code);
    Serial.println(gbp.symbol);
    Serial.println(gbp.rate_char);
    Serial.println(gbp.description);
    Serial.println(gbp.rate_float);
    //EUR
    Serial.println(eur.code);
    Serial.println(eur.symbol);
    Serial.println(eur.rate_char);
    Serial.println(eur.description);
    Serial.println(eur.rate_float);
    }

    
}
