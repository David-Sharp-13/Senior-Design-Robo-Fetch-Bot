// Test Sketch to setup communication between Pico and ESP32-CAM
// This is the code for the Pico
// If a key is pressed on the Pico's laptop, a GPIO will be toggled
// If GPIO is high, ESP32-CAM will transmit an integer over UART every few seconds
// Pico will receive and print the integers that are being sent
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(115200); // Set the baud rate to match with ESP32-CAM
  pinMode(24, OUTPUT);
}

int count = 0;

void loop() {

  digitalWrite(24, HIGH);
  delay(250);

  if (Serial.available() > 0) {
    int receivedData = Serial.parseInt(); // Read the incoming integer
    Serial.print("Received data: ");
    Serial.print(receivedData);
    count++;
    Serial.print(":  ");
    Serial.println(count);

    if (count >= 10){
      digitalWrite(24, LOW);
      Serial.println("Got to 10");
      delay(5000);
      count = 0;
    }
  }

}
