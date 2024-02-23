void setup() {
  Serial.begin(115200);
  Serial1.begin(31250);

}

void loop() {
  if(Serial1.available() > 0){

    String words = Serial1.readStringUntil('\n');
    Serial.println("Received " + words);

  }

}
