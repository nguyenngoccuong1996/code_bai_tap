#include <DHT.h>         
 
const int DHTPIN1 = D1;       
const int DHTTYPE = DHT11;  
DHT dht(DHTPIN1, DHTTYPE);
 
void setup() {
  Serial.begin(115200);
  dht.begin();         
}
 
void loop() {
  float h = dht.readHumidity();    
  float t = dht.readTemperature(); 
  
  Serial.print("Nhiet do : ");
  Serial.println(t);               
  Serial.print("Do am : ");
  Serial.println(h);  
  
  delay(3000);
  Serial.println();                //Xuống hàng
  
}
