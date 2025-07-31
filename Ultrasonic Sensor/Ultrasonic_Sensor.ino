#define trig 7
#define eco 6
double y;
int dis;
void setup() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(eco, INPUT);
  
}

void loop() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);

  digitalWrite(trig, LOW);

  y=pulseIn(eco, HIGH);
 dis= 0.0343*y;

 Serial.println(dis);

}
