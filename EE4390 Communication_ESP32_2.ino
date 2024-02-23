#include <esp32cam.h>
#include <ArduinoJson.h>

int eggX = 137;
int eggY = 241;
bool sendXY = false;

void setup() {
    Serial.begin(31250); // Set the baud rate to match the Pico's configuration
}

void loop() {
    
  long timestamp = millis();

  sendXY = true;

  if(sendXY){
    // Create the JSON document to send to the Arduino
    StaticJsonDocument<200> doc2;
    doc2["timestamp"] = timestamp;
    doc2["eggX"] = eggX;
    doc2["eggY"] = eggY;

    // Send the JSON document over the "link" serial port to the Arduino
    serializeJson(doc2, Serial);

    // Wait - this is just for debug of serial communication - comment this out
    //delay(2500);
    sendXY = false;
  }

  delay(500);


}
