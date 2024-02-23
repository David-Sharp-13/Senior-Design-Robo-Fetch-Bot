// Test Sketch to setup communication between Pico and ESP32-CAM
// This is the code for the ESP32-CAM
// If a key is pressed on the Pico's laptop, a GPIO will be toggled between the controllers
// If GPIO is high, ESP32-CAM will transmit an integer over UART every few seconds
// Pico will receive and print the integers that are being sent
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(115200); // Set the baud rate to match with Arduino Mega
  pinMode(2,INPUT);
  digitalWrite(2,LOW);
}

void loop() {

  if(digitalRead(2) == HIGH){
    int dataToSend = 123; // Replace this with your integer data

    Serial.print(dataToSend); // Send the integer data
    Serial.write('\n'); // Add a newline character to indicate the end of the integer

    delay(500); // Adjust the delay as needed
  }
  else{
    Serial.println("I'm DEAD");
    delay(250);
  }
  
}
