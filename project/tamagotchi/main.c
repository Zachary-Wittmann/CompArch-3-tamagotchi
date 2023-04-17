#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "frame.h"

#define centerRow (screenHeight/2)
#define centerCol (screenWidth/2)

#define LED BIT6

#define SW1 1
#define SW2 2
#define SW3 4
#define SW4 8

#define SWITCHES 15

int button_state = 0;
int selected = 1;
int muted = 0;

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

void
switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();
  switches = ~p2val & SWITCHES;

  // Button 1 pressed
  if (!(P2IN & SW1)){
    if (selected < 4){
      selected ++;
    }
    
    else
      selected = 1;
  }
  
  // Button Release
  else{
    ;
  }
}

short redrawScreen = 1;

void
wdt_c_handler()
{
  redrawScreen = 1;
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
  if (!muted)
    unmuteIcon(COLOR_BLACK);
  else
    muteIcon(COLOR_BLACK);
  
  // Bottom Bar
  fillRectangle(0, 130, 128, 30, COLOR_RED);

  drawRectOutline(0, 130, 43, 30, COLOR_BLACK);  // Bottom-Left Box
  cleanIcon(COLOR_BLACK);

  drawRectOutline(43, 130, 42, 30, COLOR_BLACK); // Bottom-Middle Box
  restIcon(COLOR_BLACK);

  drawRectOutline(85, 130, 43, 30, COLOR_BLACK); // Bottom-Right Box
}

void
main()
{
  u_char width = screenWidth, height = screenHeight;

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
  if (selected == 1){
    foodIcon(COLOR_WHITE);
    restIcon(COLOR_BLACK);
  }
  
  else if (selected == 2){
    danceIcon(COLOR_WHITE);
    foodIcon(COLOR_BLACK);
  }
    
  else if (selected == 3){
    cleanIcon(COLOR_WHITE);
    danceIcon(COLOR_BLACK);
  }

  else if (selected == 4){
    restIcon(COLOR_WHITE);
    cleanIcon(COLOR_BLACK);
  }
}

void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES) {	      /* did a button cause this interrupt? */
    P2IFG &= ~SWITCHES;		      /* clear pending sw interrupts */
    switch_interrupt_handler();	/* single handler for all switches */
  }
}
