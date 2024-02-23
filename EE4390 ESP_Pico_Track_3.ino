#include <ArduinoJson.h>

int eggXcoord = 0;
int eggYcoord = 0;

int motor1pin1 = 3;
int motor1pin2 = 4;

int motor2pin1 = 5;
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
  }
}

void setup() {

  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);

  analogWrite(2, 80);
  analogWrite(12, 80);


  Serial.begin(115200);
  Serial1.begin(31250); // Set baud rate to match ESP32-CAM's serial port
  
  delay(300);

}

void loop() {

  long timestamp = millis();

  readCoords();

    if (eggXcoord > 5 && eggXcoord < 140){
      analogWrite(2, 80);
      analogWrite(12, 80);

      digitalWrite(motor1pin1, HIGH);
      digitalWrite(motor1pin2, LOW);

      digitalWrite(motor2pin1, LOW);
      digitalWrite(motor2pin2, HIGH);

      delay(75);

      digitalWrite(motor1pin1, LOW);
      digitalWrite(motor1pin2, LOW);

      digitalWrite(motor2pin1, LOW);
      digitalWrite(motor2pin2, LOW);

    }

    if (eggXcoord < 320 && eggXcoord > 180){
      analogWrite(2, 80);
      analogWrite(12, 80);

      digitalWrite(motor1pin1, LOW);
      digitalWrite(motor1pin2, HIGH);

      digitalWrite(motor2pin1, HIGH);
      digitalWrite(motor2pin2, LOW);

      delay(75);

      digitalWrite(motor1pin1, LOW);
      digitalWrite(motor1pin2, LOW);

      digitalWrite(motor2pin1, LOW);
      digitalWrite(motor2pin2, LOW);

    }

  if(eggXcoord < 180 && eggXcoord >140 && eggYcoord <155 ){

    digitalWrite(motor1pin1, HIGH);
    digitalWrite(motor1pin2, LOW);

    digitalWrite(motor2pin1, HIGH);
    digitalWrite(motor2pin2, LOW);

    readCoords();

  }

  readCoords();

  if(eggXcoord < 180 && eggXcoord > 140 && eggYcoord > 155){

    digitalWrite(motor1pin1, HIGH);
    digitalWrite(motor1pin2, LOW);

    digitalWrite(motor2pin1, HIGH);
    digitalWrite(motor2pin2, LOW);

    Serial.println("Egg ready to be gripped");

  }
  else if (eggXcoord == 0 && eggYcoord == 0){

    Serial.println("No egg found: reposition");

  }
}
