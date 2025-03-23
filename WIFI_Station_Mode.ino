#include<ESP8266WiFi.h>

#define ssid "KING"
#define pass "heru@2026"

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid,pass);

  Serial.print("Connecting to");
  while (WiFi.status() != WL_CONNECTED){
    delay(400);
    Serial.print(".");
  }
  Serial.print("\n Wifi Connected");

  Serial.print("\n");
  Serial.print(WiFi.localIP());
}
void loop() {
}
