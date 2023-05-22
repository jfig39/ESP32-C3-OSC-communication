/**
 * Send OSC messages from NodeMCU to another OSC speaking device.
 * Case: Press a button (connected to NodeMCU) and get informed about it on your smartphone screen
 * Created by Fabian Fiess in November 2016
 * Inspired by Oscuino Library Examples, Make Magazine 12/2015
 */
 
#include <WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>                // for sending OSC messages

char ssid[] = "Capstone23";                 // your network SSID (name)
char pass[] = "capstone2023";              // your network password



WiFiUDP Udp;                           // A UDP instance to let us send and receive packets over UDP
const IPAddress destIp(192,168,2,215);   // remote IP of the target device //192,168,2,255 for rasp
const unsigned int destPort = 9999;    // remote port of the target device where the NodeMCU sends OSC to
const unsigned int localPort = 9999;   // local port to listen for UDP packets at the NodeMCU (another device must send OSC messages to this port)
float convertedVal = 0.0;

void setup() {
    Serial.begin(115200);
      analogReadResolution(12);
     // Specify a static IP address
     // If you erase this line, your ESP8266 will get a dynamic IP address
     //WiFi.config(IPAddress(192,168,0,123),IPAddress(192,168,0,1), IPAddress(255,255,255,0)); 
  
    // Connect to WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    Serial.println("Starting UDP");
    Udp.begin(localPort);
    Serial.print("Local port: ");
    Serial.println(localPort);

}

void loop() {
    // read btnInput and send OSC
    OSCMessage msgADC("/ADC");
  
 int analogValue0 = analogRead(1);
 int analogValue1 = analogRead(2);


Serial.printf("ADC analog value = %d\n",analogValue0 );
Serial.printf("ADC analog value = %d\n",analogValue1);
//Serial.printf("ADC millivolts value = %d\n",analogVolts1);
msgADC.add((float)analogRead(1));
msgADC.add((float)analogRead(2));
   
  
    Udp.beginPacket(destIp, destPort);
    msgADC.send(Udp);
    //msgADC1.send(Udp);
    Udp.endPacket();
    msgADC.empty();
  //  msgADC1.empty();
    //delay(100);
}
