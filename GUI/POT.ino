#define POT 0
int A;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(POT,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  A = analogRead(POT);
  Serial.println(A);
  Serial.flush();
  delay(500);//millis(5000);
}
