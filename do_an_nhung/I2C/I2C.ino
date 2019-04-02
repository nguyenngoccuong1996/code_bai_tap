#include <MCP3008.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <DHT.h>

WiFiClient client;

/* SƠ Đồ KếT NốI MCP3008 AND ESP
ESP		MCP3008
VCC		15,16
GND		9,14
D5		13
D6		12
D7		11
D8		10  */

#define DHTPIN D3
#define DHTTYPE DHT11
#define CS_PIN D8
#define CLOCK_PIN D5
#define MOSI_PIN D7
#define MISO_PIN D6

float temp = 28.5;
float cb1 = 0;
float cb2 = 0;
float cb3 = 0;
float t = 0;
float da = 45;
String apiKey = "H3WIOKMM85YKBIVB";
const char* ssid     = "BuBu";      // tên wifi 
const char* password = "13071996";  // password
const char* server = "api.thingspeak.com";
MCP3008 adc(CLOCK_PIN, MOSI_PIN, MISO_PIN, CS_PIN);
DHT dht(DHTPIN, DHTTYPE);
void setup() 
{
  pinMode(D1, OUTPUT); //chan dieu khien lamp
  pinMode(D2, OUTPUT); //chan dieu khien Bump
  
  Serial.begin(115200);
  dht.begin();
  WiFi.begin(ssid, password);
  //while (WiFi.status() != WL_CONNECTED) {
  //  Serial.print(".");
 // }
}
 
void loop() 
{
 Data();
 Auto_Lamp();
 Auto_Bump();
 Serial.print("Nhiet do : ");
 Serial.print(t);
 Serial.print(" *C\t");
 Serial.print("Do am dat 1 :");
 Serial.print(cb1);
 Serial.print(" %\t");
 Serial.print("Do am dat 2 :");
 Serial.print(cb2);
 Serial.print(" %\t");
 Serial.print("Do am dat 3 :");
 Serial.print(cb3);
 Serial.print(" %\t");
 Serial.println("Sending To ThingSpeak");
 
 if (client.connect(server, 80)) { //server thingspeak là "184.106.153.149" hoặc api.thingspeak.com
    // Gửi dữ liệu lên thingspeak ở field1 và field2
    String postStr = apiKey;
    postStr += "&field5=";
    postStr += String(t);
    postStr += "&field6=";
    postStr += String(cb1);
    postStr += "&field7=";
    postStr += String(cb2);
    postStr += "&field8=";
    postStr += String(cb3);
    postStr += "\r\n\r\n\r\n\r\n";
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
    Serial.println("-------------------------------------------------------------------------------------------------------------------");
  }
  client.stop();

  delay(5000);
}

int getSoilMoist1()
{
  int i = 0;
  int anaValue = 0;
  for (i = 0; i < 10; i++)  //
  {
    anaValue += adc.readADC(0);
    delay(50);   // Đợi đọc giá trị ADC
  }
  anaValue = anaValue / (i);
  anaValue = map(anaValue, 1023, 0, 0, 100); //Ít nước:0%  ==> Nhiều nước 100%
  return anaValue;
}

int getSoilMoist2()
{
  int i = 0;
  int anaValue = 0;
  for (i = 0; i < 10; i++)  //
  {
    anaValue += adc.readADC(1);
    delay(50);   // Đợi đọc giá trị ADC
  }
  anaValue = anaValue / (i);
  anaValue = map(anaValue, 1023, 0, 0, 100); //Ít nước:0%  ==> Nhiều nước 100%
  return anaValue;
}

int getSoilMoist3()
{
  int i = 0;
  int anaValue = 0;
  for (i = 0; i < 10; i++)  //
  {
    anaValue += adc.readADC(2);
    delay(50);   // Đợi đọc giá trị ADC
  }
  anaValue = anaValue / (i);
  anaValue = map(anaValue, 1023, 0, 0, 100); //Ít nước:0%  ==> Nhiều nước 100%
  return anaValue;
}

void Data(){
 cb1 = getSoilMoist1();
 cb2 = getSoilMoist2();
 cb3 = getSoilMoist3();
 t = dht.readTemperature();
}
void Auto_Lamp()
{
   if(t < temp)
  {
    digitalWrite(D1, LOW);
  }
  else{
    digitalWrite(D1, HIGH);
  }
}
void Auto_Bump()
{
   if(cb1 < da && cb2 < da)
  {
    digitalWrite(D2, LOW);
  }
  else if(cb1 < da && cb3 < da)
  {
    digitalWrite(D2, LOW);
  }
  else if(cb3 < da && cb2 < da)
  {
    digitalWrite(D2, LOW);
  }
  else{
    digitalWrite(D2, HIGH);
  }
}
