/*****************Library*****************/
#include <M5Stack.h>
#include <OneWire.h>
#include <Event.h>
#include <Timer.h>
#include "Timer.h"
///////////////Parameters/////////////////
// WIFI params
const char* ssid = "LPiOTIA";
const char* password = "";

// CSE params
const char* host = "134.59.143.78";
const int httpPort = 8080;

// AE params
const int aePort   = 80;
const char* origin   = "Cae_device1";
///////////////////////////////////////////
Timer t;
//WiFiServer server(aePort);
/****************************Capteur de Luminosite*****************************/
  int LuminositerPinA = 36; //valeur annalogique de la photo-resistance
/*****************************************************************************/
void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println();
  M5.begin();
  // Connect to WIFI network
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.persistent(false);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Start HTTP server
  server.begin();
  Serial.println("Server started");

  // Create AE resource
  String resulat = send("/server",2,"{\"m2m:ae\":{\"rn\":\"mydevice1\",\"api\":\"mydevice1.company.com\",\"rr\":\"true\",\"poa\":[\"http://"+WiFi.localIP().toString()+":"+aePort+"\"]}}");
  
  if(resulat=="HTTP/1.1 201 Created"){
    // Create Container resource
    send("/server/mydevice1",3,"{\"m2m:cnt\":{\"rn\":\"luminosity\"}}");

    // Create ContentInstance resource
    send("/server/mydevice1/luminosity",4,"{\"m2m:cin\":{\"con\":\"0\"}}");
    
    // Create Container resource
    send("/server/mydevice1",3,"{\"m2m:cnt\":{\"rn\":\"led\"}}");

    // Create ContentInstance resource
    send("/server/mydevice1/led",4,"{\"m2m:cin\":{\"con\":\"OFF\"}}");

    // Create Subscription resource
    send("/server/mydevice1/led",23,"{\"m2m:sub\":{\"rn\":\"led_sub\",\"nu\":[\"Cae_device1\"],\"nct\":1}}");
  }

  t.every(1000*5, push);
}

// Method in charge of receiving event from the CSE
void loop(){
  t.update();
  // Check if a client is connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the request
  String req = client.readString();
  Serial.println(req);
  client.flush();
  
//-------AGIRE SUR LE CAPTEUR ALLUME LA LED EN FONCTION DE LA TEMP-------

 /* if (req.indexOf("ON") != -1){
    digitalWrite(5, 1);
  }else if (req.indexOf("OFF") != -1){
    digitalWrite(5, 0);
  }else{
    Serial.println("invalid request");
    client.stop();
    return;
  }*/
  if (sensorValue <= 500 ){
    digitalWrite(5, 1);
  }else
    digitalWrite(5, 0);
 //-----------------------------------------------------------------------
  client.flush();

  // Send HTTP response to the client
  String s = "HTTP/1.1 200 OK\r\n";
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");
 
}


// Method in charge of sending request to the CSE
String send(String url,int ty, String rep) {

  // Connect to the CSE address
  Serial.print("connecting to ");
  Serial.println(host);
 
  WiFiClient client;
 
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return "error";
  }

  
  // prepare the HTTP request
  String req = String()+"POST " + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "X-M2M-Origin: " + origin + "\r\n" +
               "Content-Type: application/json;ty="+ty+"\r\n" +
               "Content-Length: "+ rep.length()+"\r\n"
               "Connection: close\r\n\n" + 
               rep;

  Serial.println(req+"\n");

  // Send the HTTP request
  client.print(req);
               
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return "error";
    }
  }

  // Read the HTTP response
  String res="";
  if(client.available()){
    res = client.readStringUntil('\r');
    Serial.print(res);
  }
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
  Serial.println();
  return res;
}

void push(){
  int sensorValue = 0;
  sensorValue = analogRead(LuminositerPinA);
  Serial.println(sensorValue);
  if(sensorValue >=500)
    digitalWrite(5, 1);
  else
  digitalWrite(5, 0);
  String data = String()+"{\"m2m:cin\":{\"con\":\""+sensorValue+"\"}}";
  send("/server/mydevice1/temperature",4,data);

}
