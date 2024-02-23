#include <ArduinoJson.h>

int eggXcoord = 0;
int eggYcoord = 0;

int motor1pin1 = 7;
int motor1pin2 = 8;

int motor2pin1 = 9;
int motor2pin2 = 13;

void readCoords() {

  if (Serial1.available()){

    StaticJsonDocument<300> doc2;

    DeserializationError err = deserializeJson(doc2, Serial1);

    if (err == DeserializationError::Ok){

      eggXcoord = doc2["eggX"];
      eggYcoord = doc2["eggY"];

      Serial.print("eggX = ");
      Serial.println(eggXcoord);
      Serial.print("eggY = ");
      Serial.println(eggYcoord);

    }
    else {
      // Print error to the "debug" serial port
      Serial.print("deserializeJson() returned ");
      Serial.println(err.c_str());
  
      // Flush all bytes in the "link" serial port buffer
      while (Serial1.available() > 0){
        Serial1.read();
      }
    }
  }
}

void motorForward() {

  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);

}

void xTrackLeft () {

  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);

  delay(80);

  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);

  delay(75);

}

void xTrackRight(){

  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);

  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);

  delay(80);

  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);

  delay(75);

}

void motorStop() {

  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);

}

void reposition() {

  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);

  delay(80);

  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);

  delay(75);
}


void setup() {

  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);

  analogWrite(6, 100);
  analogWrite(12, 100);


  Serial.begin(115200);
  Serial1.begin(31250); // Set baud rate to match ESP32-CAM's serial port
  
  delay(30000);

}

void loop() {

  long timestamp = millis();

  readCoords();
  //delay(200);

  if (eggXcoord > 0 && eggYcoord > 0) {
    if (eggXcoord > 5 && eggXcoord < 140){

      xTrackLeft();
    }

    if (eggXcoord < 320 && eggXcoord > 180){

      xTrackRight();
    }

    if (eggXcoord < 180 && eggXcoord > 140 && eggYcoord < 130){

      motorForward();
    }

    if (eggXcoord < 180 && eggXcoord > 140 && eggYcoord > 130){
      motorStop();
      //Serial.println("Egg ready to be gripped");
    }
  }
  else{
    reposition();
    //Serial.println("Reposition");
  }

  //delay(200);
}
