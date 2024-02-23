#include <WebServer.h>
#include <WiFi.h>
#include <esp32cam.h>
#include <ArduinoJson.h>
//#include <SoftwareSerial.h>
 
// Serial port for communication from the ESP32-CAM to the Arduino 
//SoftwareSerial mySerial1(15, 14);  //15=rx, 14=tx

//SoftAP set ESP32-CAM as an access point
const char* WIFI_SSID = "Eggquisitors-Access-Point";
const char* WIFI_PASS = "123456789";  //Needed 8 characters in the password to work

//WiFiServer server(serverPort);
WebServer server(80);

int eggX = 0;
int eggY = 0;

int Color = 0;
bool sendXY = false;
 
static auto loRes = esp32cam::Resolution::find(320, 240);
static auto midRes = esp32cam::Resolution::find(350, 530);
static auto hiRes = esp32cam::Resolution::find(800, 600);
void serveJpg()
{
  auto frame = esp32cam::capture();
  if (frame == nullptr) {
    //Serial.println("CAPTURE FAIL");
    server.send(503, "", "");
    return;
  }
  //Serial.printf("CAPTURE OK %dx%d %db\n", frame->getWidth(), frame->getHeight(),
  //              static_cast<int>(frame->size()));
 
  server.setContentLength(frame->size());
  server.send(200, "image/jpeg");
  WiFiClient client = server.client();
  frame->writeTo(client);
}
 
void handleJpgLo()
{
  if (!esp32cam::Camera.changeResolution(loRes)) {
    //Serial.println("SET-LO-RES FAIL");
  }
  serveJpg();
}
 
void handleJpgHi()
{
  if (!esp32cam::Camera.changeResolution(hiRes)) {
    //Serial.println("SET-HI-RES FAIL");
  }
  serveJpg();
}
 
void handleJpgMid()
{
  if (!esp32cam::Camera.changeResolution(midRes)) {
    //Serial.println("SET-MID-RES FAIL");
  }
  serveJpg();
}
 
void jXYcoord()  //routine to read data from the python program
{
  String data = server.arg("plain");
  StaticJsonDocument<256> doc;
  // Read the JSON document from the python program
  DeserializationError error = deserializeJson(doc, data);
  if (error) {
    //Serial.print(F("DeserializationJson() failed: "));
    //Serial.println (error.f_str());
    eggX = 0;
    eggY = 0;
    return;
  }
  eggX = doc["centerX"];
  eggY = doc["centerY"];
  // Use print statements to debug interface to Python program
  
  /*Serial.print("Payload from Client, (Python program):");
  Serial.println(data);
  Serial.print("X=");
  Serial.println(eggX); 
  Serial.print("Y=");
  Serial.println(eggY); */
  
  server.send(200,"text/plain","GOT THE DATA!"); 
} 
 
void  setup(){
 // Initialize "debug" serial port
  // The data rate must be much higher than the "link" serial port
  Serial.begin(31250);
  //Serial.println();
  // Initialize the "link" serial port to the Arduino
  // Use a low data rate to reduce the error ratio  
  //mySerial1.begin(31250);
  //while (!mySerial1) continue;

  {
    using namespace esp32cam;
    Config cfg;
    cfg.setPins(pins::AiThinker);
    cfg.setResolution(hiRes);
    cfg.setBufferCount(2);
    cfg.setJpeg(80);
 
    bool ok = Camera.begin(cfg);
    //Serial.println(ok ? "CAMERA OK" : "CAMERA FAIL");
  }
  /*WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }*/
  WiFi.softAP(WIFI_SSID, WIFI_PASS);   //Soft AP to connect direct to laptop with internet hotspot
  //Serial.print("http://");
  //Serial.println(WiFi.softAPIP());

  //Serial.println("  /cam-lo.jpg");
  //Serial.println("  /cam-hi.jpg");
  //Serial.println("  /cam-mid.jpg");
 
  server.on("/cam-lo.jpg", handleJpgLo);
  server.on("/cam-hi.jpg", handleJpgHi);
  server.on("/cam-mid.jpg", handleJpgMid);
 
  server.on("/jcoord", jXYcoord);   //need this to run the routine getting x, y coordinate data from the python code

  server.begin();
}
 
void loop()
{
  server.handleClient();

  long timestamp = millis();

  // Print the timestamp and coordinate values from the python program on the "debug" serial port
  /*Serial.print("timestamp = ");
  Serial.println(timestamp);
  Serial.print("eggX = ");
  Serial.println(eggX);
  Serial.print("eggY = ");
  Serial.println(eggY);
  Serial.println("---");*/

  /*if (Serial.available() != 0) {
    while (1){
    }
  }*/

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

  delay(75);

}