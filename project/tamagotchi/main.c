#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "frame.h"

#define centerRow (screenHeight/2)
#define centerCol (screenWidth/2)

/** Initializes everything, clears the screen, draws "hello" and a square */
int
main()
{
  configureClocks();
  lcd_init();
  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_WHITE);

  // Top Bar
  fillRectangle(0, 0, 128, 30, COLOR_RED);
  drawRectOutline(0, 0, 43, 29, COLOR_BLACK);    // Top-Left Box
  foodIcon();
  
  drawRectOutline(43, 0, 42, 29, COLOR_BLACK);   // Top-Middle Box
  danceIcon();
  
  drawRectOutline(85, 0, 43, 29, COLOR_BLACK);   // Top-Right Box
  unmuteIcon();
  
  // Bottom Bar
  fillRectangle(0, 130, 128, 30, COLOR_RED);

  drawRectOutline(0, 130, 43, 30, COLOR_BLACK);  // Bottom-Left Box
  cleanIcon();

  drawRectOutline(43, 130, 42, 30, COLOR_BLACK); // Bottom-Middle Box
  restIcon();

  drawRectOutline(85, 130, 43, 30, COLOR_BLACK); // Bottom-Right Box
  statusIcon();
}
