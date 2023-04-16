#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

#define centerRow (screenHeight/2)
#define centerCol (screenWidth/2)

void
foodIcon(){
  // Fork Icon
  fillRectangle(10, 15, 3, 11, COLOR_BLACK);
  fillRectangle(6, 13, 11, 3, COLOR_BLACK);
  fillRectangle(6, 4, 2, 9, COLOR_BLACK);
  fillRectangle(11, 4, 2, 9, COLOR_BLACK);
  fillRectangle(15, 4, 2, 9, COLOR_BLACK);

  // Knife Icon
  fillRectangle(25, 15, 3, 11, COLOR_BLACK);
  for (int r = 0; r < 12; r++){
    for (int c = r; c < 12; c++){
      drawPixel((r/2) + 25 , c + 4, COLOR_BLACK);
    }
  }
}

void
danceIcon(){
  fillRectangle(58, 6, 15, 2, COLOR_BLACK);
  fillRectangle(58, 8, 2, 10, COLOR_BLACK);
  fillRectangle(54, 16, 6, 6, COLOR_BLACK);
  fillRectangle(71, 8, 2, 10, COLOR_BLACK);
  fillRectangle(67, 16, 6, 6, COLOR_BLACK);
}

void
muteIcon(){
  fillRectangle(96, 10, 1, 10, COLOR_BLACK);
  fillRectangle(106, 5, 1, 20, COLOR_BLACK);
  for (int i = 0; i < 10; i++){
    drawPixel(96 + i, 10 - i/2, COLOR_BLACK);
    drawPixel(111 + i, 21 - i, COLOR_BLACK);
    drawPixel(96 + i, 20 + i/2, COLOR_BLACK);
    drawPixel(111 + i, 11 + i, COLOR_BLACK);
  }
}

void
unmuteIcon(){
  fillRectangle(96, 10, 1, 10, COLOR_BLACK);
  fillRectangle(106, 5, 1, 20, COLOR_BLACK);
  fillRectangle(111, 15, 10, 1, COLOR_BLACK);
  for (int i = 0; i < 10; i++){
    drawPixel(96 + i, 10 - i/2, COLOR_BLACK);
    drawPixel(111 + i, 10 - i/2, COLOR_BLACK);
    drawPixel(96 + i, 20 + i/2, COLOR_BLACK);
    drawPixel(111 + i, 20 + i/2, COLOR_BLACK);
  }
}

void
cleanIcon(){
  fillRectangle(2, 135, 35, 21, COLOR_RED);
  drawRectOutline(2, 135, 35, 21, COLOR_BLACK);
  drawRectOutline(3, 134, 35, 21, COLOR_BLACK);
  drawString5x7(8, 142, "SOAP", COLOR_BLACK, COLOR_RED);
}

void
restIcon(){
  drawString5x7(52, 149, "Z", COLOR_BLACK, COLOR_RED);
  drawString5x7(62, 143, "Z", COLOR_BLACK, COLOR_RED);
  drawString5x7(72, 137, "Z", COLOR_BLACK, COLOR_RED);
}

void
statusIcon(){
  drawRectOutline(97, 135, 21, 21, COLOR_BLACK);
  drawRectOutline(98, 134, 21, 21, COLOR_BLACK);
  drawString5x7(106, 143, "S", COLOR_BLACK, COLOR_RED);
}
