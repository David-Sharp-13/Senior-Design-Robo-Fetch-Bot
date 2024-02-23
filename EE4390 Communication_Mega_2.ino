#include <ArduinoJson.h>
//#include <SoftwareSerial.h

int eggXcoord = 0;
int eggYcoord = 0;
int eggSum = 0;

void setup() {
    Serial.begin(115200); // Debug serial port
    Serial1.begin(31250); // Set baud rate to match ESP32-CAM's serial port
}

void loop() {

  long timestamp = millis();

  if (Serial1.available()){

    StaticJsonDocument<300> doc2;

    DeserializationError err = deserializeJson(doc2, Serial1);

    if (err == DeserializationError::Ok){

      eggXcoord = doc2["eggX"];
      eggYcoord = doc2["eggY"];

      eggSum = eggXcoord + eggYcoord;

      Serial.print("timestamp = ");
      Serial.println(doc2["timestamp"].as<long>());
      Serial.print("eggX = ");
      Serial.println(eggXcoord);
      Serial.print("eggY = ");
      Serial.println(eggYcoord);
      Serial.print("eggSum = ");
      Serial.println(eggSum);
      Serial.println("YAY");

    }

  }

  delay(250);
}
