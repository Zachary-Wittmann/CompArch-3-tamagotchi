#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

#define centerRow (screenHeight/2)
#define centerCol (screenWidth/2)

int
foodIcon(int color){
  // Fork Icon
  fillRectangle(10, 15, 3, 11, color);
  fillRectangle(6, 13, 11, 3, color);
  fillRectangle(6, 4, 2, 9, color);
  fillRectangle(11, 4, 2, 9, color);
  fillRectangle(15, 4, 2, 9, color);

  // Knife Icon
  fillRectangle(25, 15, 3, 11, color);
  for (int r = 0; r < 12; r++){
    for (int c = r; c < 12; c++){
      drawPixel((r/2) + 25 , c + 4, color);
    }
  }
}

int
danceIcon(int color){
  fillRectangle(58, 6, 15, 2, color);
  fillRectangle(58, 8, 2, 10, color);
  fillRectangle(54, 16, 6, 6, color);
  fillRectangle(71, 8, 2, 10, color);
  fillRectangle(67, 16, 6, 6, color);
}

int
muteIcon(int color){
  fillRectangle(96, 10, 1, 10, color);
  fillRectangle(106, 5, 1, 20, color);
  for (int i = 0; i < 10; i++){
    drawPixel(96 + i, 10 - i/2, color);
    drawPixel(111 + i, 21 - i, color);
    drawPixel(96 + i, 20 + i/2, color);
    drawPixel(111 + i, 11 + i, color);
  }
}

int
unmuteIcon(int color){
  fillRectangle(96, 10, 1, 10, color);
  fillRectangle(106, 5, 1, 20, color);
  fillRectangle(111, 15, 10, 1, color);
  for (int i = 0; i < 10; i++){
    drawPixel(96 + i, 10 - i/2, color);
    drawPixel(111 + i, 10 - i/2, color);
    drawPixel(96 + i, 20 + i/2, color);
    drawPixel(111 + i, 20 + i/2, color);
  }
}

int
cleanIcon(int color){
  fillRectangle(2, 135, 35, 21, COLOR_RED);
  drawRectOutline(2, 135, 35, 21, color);
  drawRectOutline(3, 134, 35, 21, color);
  drawString5x7(8, 142, "SOAP", color, COLOR_RED);
}

int
restIcon(int color){
  drawString5x7(52, 149, "Z", color, COLOR_RED);
  drawString5x7(62, 143, "Z", color, COLOR_RED);
  drawString5x7(72, 137, "Z", color, COLOR_RED);
}

