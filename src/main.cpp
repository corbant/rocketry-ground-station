#include <SPI.h>
#include <LoRa.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#define ss 5
#define rst 14
#define dio0 2

#define SSID "Base Station"

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
// Create an Event Source on /events
AsyncEventSource events("/events");

void setup() {
	Serial.begin(115200);
	while (!Serial);
	Serial.println("LoRa Sender");
	LoRa.setPins(ss, rst, dio0);
	if(!LoRa.begin(433E6)) {
		Serial.println("Starting LoRa failed!");
		digitalWrite(26, HIGH);
		while (1);
	}else{
		Serial.println("yoot");
	}
	WiFi.mode(WIFI_AP);
	WiFi.softAP(SSID);
}

void loop() {

	if(Serial.available() > 1){
		LoRa.beginPacket();
		LoRa.print("armed");
		LoRa.endPacket();
		Serial.println("armed");
		
		delay(100);
	}

	// send packet

	int packetSize = LoRa.parsePacket();
	if (packetSize) {
	// received a packet
	Serial.print("Received packet '");

	// read packet
	while (LoRa.available()) {
		Serial.print((char)LoRa.read());
	}

	// print RSSI of packet
	Serial.print("' with RSSI ");
	Serial.println(LoRa.packetRssi());
	}
  
}