/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */

#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

#define centerRow (screenHeight/2)
#define centerCol (screenWidth/2)

/** Initializes everything, clears the screen, draws "hello" and a square */
int
main()
{
  configureClocks();
  lcd_init();
  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_BLUE);

  // drawString5x7(20,20, "hello", COLOR_GREEN, COLOR_RED);

  // fillRectangle(30,30, 60, 60, COLOR_ORANGE);

  draw_rhombus();
}

void
draw_rhombus(){
  for (int i = 0; i < 20; i++){
      drawPixel(centerCol + i, centerRow/2 + i, COLOR_PINK);
      drawPixel(centerCol - i, centerRow/2 + i, COLOR_PINK);
      drawPixel(centerCol + i, centerRow - i, COLOR_PINK);
      drawPixel(centerCol - i, centerRow - i, COLOR_PINK);
    }
}
