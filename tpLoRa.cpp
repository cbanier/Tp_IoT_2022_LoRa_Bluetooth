#include <SPI.h>
#include <LoRa.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define ssid "marcbarbierlaptop"
#define pass "suassig1"
const char* mqttServer = "test.mosquitto.org";

WiFiClient espClient;
PubSubClient client(espClient);

#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define DI0 26
const long freq = 868E6;
const int sf = 7;
const long sb = 125E3;

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to the WiFi network");
  client.setServer(mqttServer, 1883);
  
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("YoussancePublisher")) {
      Serial.println("connected") ;
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }

  pinMode(DI0, INPUT);
  SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setPins(SS, RST, DI0);
  if (!LoRa.begin(freq)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  } else {
    Serial.println("Starting LoRa ...");
  }

  LoRa.setSignalBandwidth(sb);
  LoRa.setSpreadingFactor(sf);

  char infoLoRa[32];
  sprintf(infoLoRa, "%ld,%d,%ld", freq, sf, sb);
  client.publish("/info/youssance", infoLoRa);
  Serial.println("infoLoRa published");
}

float d1, d2;
int i = 0;

void loop() {
  char infoLoRa[32];
  sprintf(infoLoRa, "%ld,%d,%ld", freq, sf, sb);
  client.publish("/info/youssance", infoLoRa);
  Serial.println("infoLoRa published");
  
  int packetLen, rssi;
  uint8_t rdbuff[256];
  packetLen = LoRa.parsePacket();
  if (packetLen != 0) {
    i = 0;
    while (LoRa.available()) {
      rdbuff[i] = LoRa.read(); 
      i++;
    }
    rdbuff[i] = '\0';
    Serial.printf("received pkt = %s\n", rdbuff);
    rssi = LoRa.packetRssi();
    Serial.printf("\nrssi = %d\n", rssi);
  }
  delay(500);
}