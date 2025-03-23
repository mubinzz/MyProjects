#include<ESP8266WiFi.h>

#define ssid "Batman"
#define pass "bat12345"

void setup() {
  Serial.begin(9600);
  WiFi.softAP(ssid,pass);
  Serial.print("\n");
  Serial.println(WiFi.softAPIP());
}
void loop() {
}
