#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "frame.h"

#define LED BIT6

#define SW1 1
#define SW2 2
#define SW3 4
#define SW4 8

#define SWITCHES 15

unsigned char button_state = 0;
unsigned char fd_status = 0;
unsigned char dn_status = 0;
unsigned char cl_status = 0;
unsigned char selected = 1;
unsigned char executed = 0;
unsigned char muted = 1;


static char 
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);	/* if switch down, sense up */
  return p2val;
}

void 
switch_init()			/* setup switch */
{  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE |= SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
}

int switches = 0;

void switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();
  switches = ~p2val & SWITCHES;

  // Button 1 pressed
  if ((!(P2IN & SW1)) & button_state == 0){
    if (selected < 4){
      selected ++;
    }
    
    else
      selected = 1;
  }
  
  else if ((!(P2IN & SW1)) & button_state != 0)
    ;
  
  // Button 2 pressed
  else if ((!(P2IN & SW2)) & button_state == 0){
    fillRectangle(0, 30, 128, 100, COLOR_WHITE);
    switch(selected){
    case 1:
      if(button_state == 0){
	executed = 1;
	button_state = 1;
      }
      break;

    case 2:
      if(button_state == 0){
	executed = 2;
	button_state = 1;
      }
      break;
      
    case 3:
      if(button_state == 0){
	executed = 3;
	button_state = 1;
      }
      break;

    case 4:
      if(button_state == 0){
	executed = 4;
	button_state = 1;
      }
      break;
    }
  }

  // Button 3 pressed
  else if ((!(P2IN & SW3)) & button_state == 1){
    executed = 0;
    button_state = 0;
  }

  // Button 4 pressed
  else if (!(P2IN & SW4)){
    if(!muted)
      muted = 1;
    else
      muted = 0;    
  }
  
  // Button Release
  else{

    if(button_state == 1)
      ;

    else
      ;
  }
}

short drawPos[2] = {21, 100}, controlPos[2] = {22, 100};
short colVelocity = 3, colLimits[2] = {21, screenWidth - 50};

void
draw_ball(int col, int row, unsigned short color)
{
  fillRectangle(col-1, row-1, 30, 30, color);
}


void
screen_update_ball()
{
  for (char axis = 0; axis < 2; axis ++) 
    if (drawPos[axis] != controlPos[axis]) /* position changed? */
      goto redraw;
  return;			/* nothing to do */
 redraw:
  draw_ball(drawPos[0], drawPos[1], COLOR_WHITE); /* erase */
  for (char axis = 0; axis < 2; axis ++) 
    drawPos[axis] = controlPos[axis];
  draw_ball(drawPos[0], drawPos[1], COLOR_PINK); /* draw */
}

void
draw_food(unsigned int color){
  short row = 0;
  while (row ++ < 10)
    for (short col = -row; col < row; col ++)
      drawPixel(70 + col, 113 + row, color);
}

void
dance_anim(unsigned int color, unsigned int offset){
  fillRectangle(44, 99 - offset, 5, 15 + offset, color);
  fillRectangle(79, 89 + offset, 5, 25 - offset, color);
}

void
clean_anim(unsigned int color1, unsigned int color2, unsigned int color3,
	   unsigned int color4, unsigned int offset){

  fillRectangle(49, 108, 12, 6, color1);
  fillRectangle(49 + offset, 108, 12, 6, color2);
  drawString5x7(52, 100, "o", color3, COLOR_WHITE);
  drawString5x7(52 + offset, 100, "o", color4, COLOR_WHITE);
}

void
rest_anim(){
  fillRectangle(49, 114, 30, 15, COLOR_PINK);
  drawString5x7(79, 109, "Z", COLOR_BLACK, COLOR_WHITE);  
}

void
screen_update_buttons()
{
  // Button 1
  switch(selected){
  case 1:
    foodIcon(COLOR_WHITE);
    restIcon(COLOR_BLACK);
    break;
    
  case 2:
    danceIcon(COLOR_WHITE);
    foodIcon(COLOR_BLACK);
    break;

  case 3:
    cleanIcon(COLOR_WHITE);
    danceIcon(COLOR_BLACK);
    break;

  case 4:
    restIcon(COLOR_WHITE);
    cleanIcon(COLOR_BLACK);
    break;
  }

  // Button 4
  {
    if (!muted){
      unmuteIcon(COLOR_RED);
      muteIcon(COLOR_BLACK);
    }

    else{
      muteIcon(COLOR_RED);
      unmuteIcon(COLOR_BLACK);
    }
  }
  or_sr(0x10);
}

void
screen_update_action()
{
  switch(executed){
  case 0:
    fillRectangle(0, 30, 128, 100, COLOR_WHITE);
    break;
        
  case 1:
    if (fd_status == 0){
      fillRectangle(29, 99, 30, 30, COLOR_PINK);
      fillRectangle(49, 114, 10, 10, COLOR_WHITE);
      draw_food(COLOR_YELLOW);
    }
    else{
      fillRectangle(29, 99, 30, 30, COLOR_PINK);
      draw_food(COLOR_WHITE);
    }
    break;

  case 2:
    fillRectangle(49, 99, 30, 30, COLOR_PINK);
    if (dn_status == 0){
      dance_anim(COLOR_WHITE, 10);
      dance_anim(COLOR_HOT_PINK, 0);
    }
    else{
      dance_anim(COLOR_WHITE, 0);
      dance_anim(COLOR_HOT_PINK, 10);
    }
    break;

  case 3:
    fillRectangle(49, 114, 30, 15, COLOR_PINK);
    if (cl_status == 0){
      clean_anim(COLOR_WHITE, COLOR_HOT_PINK, COLOR_LIGHT_BLUE, COLOR_WHITE, 12);
    }
    else{
      clean_anim(COLOR_HOT_PINK, COLOR_WHITE, COLOR_WHITE, COLOR_LIGHT_BLUE, 12);
    }
    break;

  case 4:
    rest_anim();
    break;    
  }
  or_sr(0x10);
}


short redrawScreen = 1;

void wdt_c_handler()
{
  static int secCount = 0;
  
  secCount ++;
  if (secCount >= 200){
    {				/* move ball */
      short oldCol = controlPos[0];
      short newCol = oldCol + colVelocity;
      if (newCol <= colLimits[0] || newCol >= colLimits[1])
	colVelocity = -colVelocity;
      else
	controlPos[0] = newCol;
    }
    
    {
      if (fd_status == 0)
	fd_status = 1;
      else
	fd_status = 0;
    }

    {
      if (dn_status == 0)
	dn_status = 1;
      else
	dn_status = 0;
    }

    {
      if (cl_status == 0)
	cl_status = 1;
      else
	cl_status = 0;
    }
    
    secCount = 0;
    redrawScreen = 1;
  }
}

void update_screen();

void
draw_frame(){
  // Top Bar  
  fillRectangle(0, 0, 128, 30, COLOR_RED);

  drawRectOutline(0, 0, 43, 29, COLOR_BLACK);    // Top-Left Box
  foodIcon(COLOR_BLACK);
  
  drawRectOutline(43, 0, 42, 29, COLOR_BLACK);   // Top-Middle Box
  danceIcon(COLOR_BLACK);

  drawRectOutline(85, 0, 43, 29, COLOR_BLACK);   // Top-Right Box
  unmuteIcon(COLOR_BLACK);
  
  // Bottom Bar
  fillRectangle(0, 130, 128, 30, COLOR_RED);

  drawRectOutline(0, 130, 43, 30, COLOR_BLACK);  // Bottom-Left Box
  cleanIcon(COLOR_BLACK);

  drawRectOutline(43, 130, 42, 30, COLOR_BLACK); // Bottom-Middle Box
  restIcon(COLOR_BLACK);

  drawRectOutline(85, 130, 43, 30, COLOR_BLACK); // Bottom-Right Box
}

void main()
{
  configureClocks();
  lcd_init();
  switch_init();

  enableWDTInterrupts();
  or_sr(0x8);

  clearScreen(COLOR_WHITE);
  draw_frame();
  
  while(1){ 
    if(redrawScreen){
      redrawScreen = 0;
      update_screen();
    }
    or_sr(0x10);
  }
}

void
update_screen()
{
  if (executed == 0)
    screen_update_ball();
  
  screen_update_buttons();
  screen_update_action();
}

void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES) {	      /* did a button cause this interrupt? */
    P2IFG &= ~SWITCHES;		      /* clear pending sw interrupts */
    switch_interrupt_handler();	/* single handler for all switches */
  }
}
