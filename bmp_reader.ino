#include <FileIO.h>
#include "SPI.h"
#include "screen_4D_22_library.h"
screen22 myScreen(_4DSHIELD22);
uint16_t x=100, y=100;
unsigned int colour=0x0, val=0x0, rVal=0, gVal=0, bVal=0;
//int x=215, y=94, r=0, g=0, b=0;

void setup() {
  // put your setup code here, to run once:
  Bridge.begin();
  Serial.begin(115200);
  FileSystem.begin();
  myScreen.begin();
  //while(!Serial);
  Serial.println("all systems go...");
//  File fid = FileSystem.open("/mnt/sd/arduino/SA_Catapult.bmp",FILE_READ);
//  File fid = FileSystem.open("/mnt/sd/arduino/ICSPHeader.bmp",FILE_READ);
//  File fid = FileSystem.open("/mnt/sd/arduino/C_and_C.bmp",FILE_READ);
  File fid = FileSystem.open("/mnt/sd/arduino/rocket.bmp",FILE_READ);
  if(fid) {
    Serial.println("File open, preparing read");
    fid.seek(54);
  }
  else
    Serial.println("File error");
  myScreen.setOrientation(2);
  myScreen.solidRectangle(0, 0, 175, 219, whiteColour);
  for (int j=0;j<y;j++) {
    for (int k=0;k<x;k++) {
      val = fid.read();
      rVal = (val >> 3);
      val = fid.read();
      gVal = (val >> 2);
      val = fid.read();
      bVal = (val >> 3);
      colour=(bVal<<11)|(gVal<<5)|rVal;
      myScreen.point(k+(88-(x/2)),j+(110-(y/2)),colour);
      colour=0x0;
//      delay(5);//
    }
  }
  for(int i=0;i<3;i++){
      myScreen.setBacklight(LOW);
      delay(100);
      myScreen.setBacklight(HIGH);
  }
}



void loop() {
  // put your main code here, to run repeatedly:

}
