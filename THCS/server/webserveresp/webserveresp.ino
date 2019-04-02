#include <ESP8266WiFi.h>

const char* ssid     = "Devil";
const char* password = "12345678a";


WiFiServer server(80);

String header;

String outputcoiState = "off";
String outputled2State = "off";


const int coi = 5;
const int led2 = 4;


void setup() {
  Serial.begin(115200);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
 
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();  

  if (client) {                             
    Serial.println("New Client.");         
    String currentLine = "";               
    while (client.connected()) {            
      if (client.available()) {           
        char c = client.read();            
        Serial.write(c);                   
        header += c;
        if (c == '\n') {                    
         
          if (currentLine.length() == 0) {  
      
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            if (header.indexOf("GET /5/on") >= 0) {
              Serial.println("D2 5 on");
              outputcoiState = "on";
              digitalWrite(D2, HIGH);
            } else if (header.indexOf("GET /5/off") >= 0) {
              Serial.println("D2 off");
              outputcoiState = "off";
              digitalWrite(D2, LOW);
            } else if (header.indexOf("GET /4/on") >= 0) {
              Serial.println("D3 on");
              outputled2State = "on";
              digitalWrite(D3, HIGH);
            } else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("D3 off");
              outputled2State = "off";
              digitalWrite(D3, LOW);
            }
            
            client.println("<!DOCTYPE html><html>");
            client.println("<meta charset='utf-8'>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #93B874; border: none; color: black; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 40px; margin: 5px; cursor: pointer;}");
            client.println(".button2 {background-color: #993300;}</style></head>");
            
            client.println("<body><h1>chào bạn! mời ban điều khiển</h1>");
            client.println("<p>coi - State " + outputcoiState + "</p>");      
            if (outputcoiState=="off") {
              client.println("<p><a href=\"/5/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/5/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            client.println("<p>led2 - State " + outputled2State + "</p>");      
            if (outputled2State=="off") {
              client.println("<p><a href=\"/4/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/4/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");
            client.println();
            break;
          } else { 
            currentLine = "";
          }
        } else if (c != '\r') {  
          currentLine += c;      
        }
      }
    }
   
    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
