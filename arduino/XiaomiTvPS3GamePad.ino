#include <Ps3Controller.h>
#include <BleGamepad.h> 

typedef struct {
  bool up;
  bool down;
  uint64_t bn;
} record_btns;

record_btns btns[16];

BleGamepad bleGamepad;

void setup() {
  Serial.begin(115200);
  Ps3.begin("11:22:33:44:55:66");
  bleGamepad.begin();

  for (int i=0; i <= 16; i++) {
    btns[i].up = false;  
    btns[i].down = true;
  }

  btns[0].bn = BUTTON_13;
  btns[1].bn = BUTTON_14;
  btns[2].bn = BUTTON_15;
  btns[3].bn = BUTTON_16;

  btns[4].bn = BUTTON_9;
  btns[5].bn = BUTTON_10;

  btns[6].bn = BUTTON_1;
  btns[7].bn = BUTTON_2;
  btns[8].bn = BUTTON_3;
  btns[9].bn = BUTTON_4;

  btns[10].bn = BUTTON_5;
  btns[11].bn = BUTTON_7;
  btns[12].bn = BUTTON_6;
  btns[13].bn = BUTTON_8;

  btns[14].bn = BUTTON_11;
  btns[15].bn = BUTTON_12;
}

void btn(int bn, bool st) {
  if(st){
    if (btns[bn].down) {
      btns[bn].up = true;
      btns[bn].down = false;
      bleGamepad.press(btns[bn].bn);
    }  
  } else {
    if (btns[bn].up) {
      btns[bn].up = false;
      btns[bn].down = true;            
      bleGamepad.release(btns[bn].bn);
    }
  }     
}

void loop() {
  if(bleGamepad.isConnected()) {
    if (Ps3.isConnected()) {  
      btn(0, Ps3.data.button.up);
      btn(1, Ps3.data.button.down);
      btn(2, Ps3.data.button.left);
      btn(3, Ps3.data.button.right);

      btn(4, Ps3.data.button.select);
      btn(5, Ps3.data.button.start);

      btn(6, Ps3.data.button.triangle);
      btn(7, Ps3.data.button.circle);
      btn(8, Ps3.data.button.cross);
      btn(9, Ps3.data.button.square);

      btn(10, Ps3.data.button.l1);
      btn(11, Ps3.data.button.l2);
      btn(12, Ps3.data.button.r1);
      btn(13, Ps3.data.button.r2);

      btn(14, Ps3.data.button.l3);
      btn(15, Ps3.data.button.r3);
    }  
  }
}
