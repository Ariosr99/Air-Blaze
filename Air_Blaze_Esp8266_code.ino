#include<ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ESP8266HTTPClient.h>

String URL="http://api.thingspeak.com/update?api_key=GJ6G5593FHNPVWO8&field1=";

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    WiFi.disconnect();
    delay(2000);
    Serial.print("Start connection");
    WiFi.begin("Arihant","bwra0848");
    while((!(WiFi.status()==WL_CONNECTED))){
        delay(200);
        Serial.print("..");    
    }
Serial.println("connected");

}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(Serial.available()>0){
    String data=Serial.readStringUntil('\n');
    Serial.println(data);
    int S=data.indexOf('S');
    int T=data.indexOf('T');
    int U=data.indexOf('U');
    int V=data.indexOf('V');
    int W=data.indexOf('W');
    int X=data.indexOf('X');
    int Y=data.indexOf('Y');
    int Z=data.indexOf('Z');    
    
    if(S!=-1){
        float Pm2=data.substring(S+1).toFloat();
        
        Serial.print(Pm2);
        
        sendData(Pm2);
    }
    if(T!=-1){
        float Pm10=data.substring(T+1).toFloat();
        
        Serial.print(Pm10);
        
        sendData(Pm10);
    }
    if(U!=-1){
        float Smoke=data.substring(U+1).toFloat();
        
        Serial.print(Smoke);
        
        sendData(Smoke);
    }
    if(V!=-1){
        
        float co2=data.substring(V+1).toFloat();
        Serial.println(co2);
        sendData0(co2);
         
         
    }
    if(W!=-1){
        float co=data.substring(W+1).toFloat();
        Serial.println(co);
        sendData1(co);
        
         
    }
    if(X!=-1){
       float fg=data.substring(X+1).toFloat();
         Serial.println(fg);
         sendData2(fg);
        
    }

    if(Y!=-1){
        float h=data.substring(Y+1).toFloat();
         Serial.println(h);
         sendData3(h);
         
         
    }
    if(Z!=-1){
        float t=data.substring(Z+1).toFloat();
         Serial.println(t);
         sendData4(t);
         
    }
        
       
       
        
        
      
        
    }
  }


void sendData(float Smoke){
    WiFiClient client;
    HTTPClient http;
    String newUrl=URL+String(Smoke);
    http.begin(client,newUrl);
    int responsecode=http.GET();
    String data=http.getString();
    Serial.println(data);
    http.end();
}
void sendData0(float co2){
    WiFiClient client;
    HTTPClient http;
    String newUrl=URL+"&field2="+String(co2);
    http.begin(client,newUrl);
    int responsecode=http.GET();
    String data=http.getString();
    Serial.println(data);
    http.end();
}

void sendData1(float co){
    WiFiClient client;
    HTTPClient http;
    String newUrl=URL+"&field3="+String(co);
    http.begin(client,newUrl);
    int responsecode=http.GET();
    String data=http.getString();
    Serial.println(data);
    http.end();
}

void sendData2(float fg){
    WiFiClient client;
    HTTPClient http;
    String newUrl=URL+"&field4="+String(fg);
    http.begin(client,newUrl);
    int responsecode=http.GET();
    String data=http.getString();
    Serial.println(data);
    http.end();
}

void sendData3(float h){
    WiFiClient client;
    HTTPClient http;
    String newUrl=URL+"&field5="+String(h);
    http.begin(client,newUrl);
    int responsecode=http.GET();
    String data=http.getString();
    Serial.println(data);
    http.end();
}

void sendData4(float t){
    WiFiClient client;
    HTTPClient http;
    String newUrl=URL+"&field6="+String(t);
    http.begin(client,newUrl);
    int responsecode=http.GET();
    String data=http.getString();
    Serial.println(data);
    http.end();
}

void sendData5(float Pm2){
    WiFiClient client;
    HTTPClient http;
    String newUrl=URL+"&field7="+String(Pm2);
    http.begin(client,newUrl);
    int responsecode=http.GET();
    String data=http.getString();
    Serial.println(data);
    http.end();
}
void sendData6(float Pm10){
    WiFiClient client;
    HTTPClient http;
    String newUrl=URL+"&field8="+String(Pm10);
    http.begin(client,newUrl);
    int responsecode=http.GET();
    String data=http.getString();
    Serial.println(data);
    http.end();
}