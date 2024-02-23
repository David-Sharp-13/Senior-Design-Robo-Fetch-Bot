#include <IRremote.h>

#define RECEIVER 13
#define BUTTON_1 0xBA45FF00
#define BUTTON_2 0xB946FF00
#define BUTTON_3 0xB847FF00
#define BUTTON_4 0xBB44FF00
#define BUTTON_5 0xBF40FF00
#define BUTTON_6 0xBC43FF00
#define BUTTON_7 0xF807FF00
#define BUTTON_8 0xEA15FF00
#define BUTTON_9 0xF609FF00
#define BUTTON_0 0xE619FF00
#define BUTTON_POUND 0xF20DFF00
#define BUTTON_ASTERICK 0xE916FF00
#define BUTTON_UP 0xE718FF00
#define BUTTON_RIGHT 0xA55AFF00
#define BUTTON_DOWN 0xAD52FF00
#define BUTTON_LEFT 0xF708FF00
#define BUTTON_OK 0xE31CFF00

uint32_t Previous;

decode_results results;

IRrecv IR(RECEIVER);

void setup() {
  Serial.begin(115200,SERIAL_8N1);

  IR.enableIRIn();
}

void loop() {
  
  if(IR.decode(&results)) {
    if(results.value==0xFFFFFFFF) {
      results.value=Previous;
    }
    switch (results.value){
      case BUTTON_1:
        Serial.println ("One egg");
      break;
      case BUTTON_2:
        Serial.println ("Two eggs");
      break;
      case BUTTON_3:
        Serial.println ("Three eggs");
      break;
      case BUTTON_UP:
        Serial.println ("Green Eggs");
      break;
      case BUTTON_RIGHT:
        Serial.println ("Red Eggs");
      break;
      case BUTTON_DOWN:
        Serial.println ("Blue Eggs");
      break;
      case BUTTON_LEFT:
        Serial.println ("Yellow Eggs");
      break;
    }
    IR.resume();
  }
  Previous=results.value;

}
