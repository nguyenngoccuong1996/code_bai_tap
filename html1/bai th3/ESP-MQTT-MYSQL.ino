#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

#define DHTTYPE DHT11   // DHT 11
#define ssid "BuBu"
#define password "13071996"
// Thông tin về MQTT Broker
#define mqtt_server "m16.cloudmqtt.com" // Thay bằng địa chỉ IP 
#define mqtt_topic_pub "Test"   //Giữ nguyên nếu bạn tạo topic tên là demo
#define mqtt_topic_sub "Test"
#define mqtt_user "rduccsnr"    //Giữ nguyên nếu bạn tạo user là lophocvui và pass là 123456
#define mqtt_pwd "DcKYWqq2FEjU"

const uint16_t mqtt_port = 12228; //Port của MQTT


WiFiClient espClient;
PubSubClient client(espClient);

const int DHTPin1 = D1;       //Đọc dữ liệu từ DHT11 ở chân D1 trên mạch esp8266

long lastMsg = 0;
char msg[50];
int value = 0;
// Timers auxiliar variables
long now = millis();
long lastMeasure = 0;

// Thiet Lap cam bien DHT.
DHT dht1(DHTPin1, DHTTYPE);


void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port); 
  dht1.begin();

}
// Hàm kết nối wifi
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
// Hàm reconnect thực hiện kết nối lại khi mất kết nối với MQTT Broker
void reconnect() {
  // Chờ tới khi kết nối
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Thực hiện kết nối với mqtt user và pass
    if (client.connect("ESP8266Client",mqtt_user, mqtt_pwd)) {
      Serial.println("connected");
      // Khi kết nối sẽ publish thông báo
      client.publish(mqtt_topic_pub, "ESP_reconnected");
      // ... và nhận lại thông tin này
      client.subscribe(mqtt_topic_sub);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Đợi 5s
      delay(5000);
    }
  }
}
void loop() {

  if (!client.connected()) {
    reconnect();
  }
  if(!client.loop())
    client.connect("ESP8266Client");

  now = millis();
  // Publishes new temperature and humidity every 30 seconds
  if (now - lastMeasure > 1000) {
    lastMeasure = now;
    getAndSendTemperatureAndHumidityData();
  }
}

void getAndSendTemperatureAndHumidityData()
{
  Serial.println("Collecting temperature data.");
  int h1 = dht1.readHumidity();
  int t1 = dht1.readTemperature();
  int h2 = dht2.readHumidity();
  int t2 = dht2.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h1) || isnan(t1) || isnan(h2) || isnan(t2)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity 1: ");
  Serial.print(h1);
  Serial.print(" %\t");
  Serial.print("Temperature 1: ");
  Serial.print(t1);
  Serial.print(" *C ");
  Serial.print("Humidity 2: ");
  Serial.print(h2);
  Serial.print(" %\t");
  Serial.print("Temperature 2: ");
  Serial.print(t2);
  Serial.print(" *C ");

  String temperature1 = String(t1);
  String humidity1 = String(h1);
  String temperature2 = String(t2);
  String humidity2 = String(h2);

//
//  // Just debug messages
//  Serial.print( "Sending temperature and humidity : [" );
//  Serial.print( temperature ); Serial.print( "," );
//  Serial.print( humidity );
//  Serial.print( "]   -> " );

  // Prepare a JSON payload string
  String payload = "{";
  payload += "\"Temp1\":"; payload += temperature1; payload += ",";
  payload += "\"Hum1\":"; payload += humidity1;
  payload += "\"Temp2\":"; payload += temperature2; payload += ",";
  payload += "\"Hum2\":"; payload += humidity2;
  payload += "}";

  // Send payload
  char attributes[100];
  payload.toCharArray( attributes, 100 );
  client.publish( "Test", attributes );
  Serial.println( attributes );
  delay(5000);
}
