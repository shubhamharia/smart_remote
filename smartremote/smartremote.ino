#include <ESP8266WiFi.h>
#include <Espalexa.h>
#include <IRremote.h>
void device1Changed(uint8_t brightness);
void device2Changed(uint8_t brightness);
void device3Changed(uint8_t brightness);
void device4Changed(uint8_t brightness);
void device5Changed(uint8_t brightness);
void device6Changed(uint8_t brightness);
void device7Changed(uint8_t brightness);
String Device_1_Name = "TV";
String Device_2_Name = "SAB";
String Device_3_Name = "sony";
String Device_4_Name = "star";
String Device_5_Name = "volume up";
String Device_6_Name = "volume dowm";
String Device_7_Name = "news";
uint32_t power = 0xC0000C;
uint32_t butn1 = 0xC00001;
uint32_t butn2 = 0xC00002;
uint32_t butn3 = 0xC00003;
uint32_t butn4 = 0xC00004;
uint32_t butn5 = 0xC00005;
uint32_t butn6 = 0xC00006;
uint32_t butn7 = 0xC00007;
uint32_t butn8 = 0xC00008;
uint32_t butn9 = 0xC00009;
uint32_t butn0 = 0xC00000;
uint32_t volup = 0xC00010;
uint32_t voldown = 0xC00011;
IRsend irsend(12);
Espalexa espalexa;
boolean connectWifi();
boolean wifiConnected = false;
const char* ssid = "Paresh";
const char* password = "9925014216";
int value;
void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  wifiConnected = connectWifi();
  if (wifiConnected)
  { // Define your devices here.
    espalexa.addDevice(Device_1_Name, device1Changed);
    espalexa.addDevice(Device_2_Name, device2Changed);
    espalexa.addDevice(Device_3_Name, device3Changed);
    espalexa.addDevice(Device_4_Name, device4Changed);
    espalexa.addDevice(Device_5_Name, device5Changed);
    espalexa.addDevice(Device_6_Name, device6Changed);
    espalexa.addDevice(Device_7_Name, device7Changed);
    espalexa.begin();
  }
}
void loop() {
  espalexa.loop();
  delay(1);
}
void device1Changed(uint8_t brightness)
{
  //Control the device
  irsend.sendRC6(power, 24);
  Serial.println("TV");
  delay(1000);
}
void device2Changed(uint8_t brightness)
{ Serial.println(brightness);
  Serial.println("truning sab HD");
  irsend.sendRC6(butn1, 24);
  delay(500);
  irsend.sendRC6(butn3, 24);
  delay(500);
  irsend.sendRC6(butn2, 24);
  delay(1000);

}

void device4Changed(uint8_t brightness) {
  Serial.println("truning Star plus");
  irsend.sendRC6(butn1, 24);
  delay(500);
  irsend.sendRC6(butn1, 24);
  delay(500);
  irsend.sendRC6(butn5, 24);
  delay(1000);
}
void device3Changed(uint8_t brightness) {
  Serial.println("truning Sony");
  irsend.sendRC6(butn1, 24);
  delay(500);
  irsend.sendRC6(butn2, 24);
  delay(500);
  irsend.sendRC6(butn8, 24);
  delay(1000);
}
void device7Changed(uint8_t brightness) {
  Serial.println("truning news");
  irsend.sendRC6(butn1, 24);
  delay(500);
  irsend.sendRC6(butn7, 24);
  delay(500);
  irsend.sendRC6(butn2, 24);
  delay(500);
  irsend.sendRC6(butn1, 24);
  delay(1000);
}

void device5Changed(uint8_t brightness) {
  Serial.println("volume up");
  irsend.sendRC6(volup, 24);
  delay(1500);
}
void device6Changed(uint8_t brightness) {
  Serial.println("volume down");
  irsend.sendRC6(voldown, 24);
  delay(1500);
}
boolean connectWifi()
{
  boolean state = true;
  int i = 0;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20) {
      state = false; break;
    }
    i++;
  }
  Serial.println("");
  if (state) {
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("Connection failed.");
  }
  return state;
}
