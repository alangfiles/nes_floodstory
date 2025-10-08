/*	based off example of MMC1 for cc65 Doug Fraker 2019, 2022
 *
 [x] get a guy moving on the screen.
 [x] add and draw background
 [] add collision
 [] add jumping
 [] add shooting / projectiles
 [] add animations for player
 [] add scrolling
 *
 *
 */

#include "LIB/neslib.h"
#include "LIB/nesdoug.h"
#include "MMC1/bank_helpers.h"
#include "MMC1/bank_helpers.c"

#include "noahman.h"
#include "metatile.h"

//bank code, messy and in here.
#include "bank0.h"
#include "bank1.h"
#include "bank2.h"
#include "bank3.h"
#include "bank4.h"
#include "bank5.h"
#include "bank6.h"

// 7 shouldn't be needed, that's the fixed bank, just call it normally


// the fixed bank, bank 7
// game loop

#pragma rodata-name("CODE")
#pragma code-name("CODE")
const unsigned char palette_bg[16]={ 0x21,0x0f,0x00,0x10,0x21,0x0f,0x30,0x08,0x21,0x0f,0x17,0x06,0x21,0x0f,0x19,0x29 };

const unsigned char palette_sp[16]={
	0x21,0x17,0x24,0x36,
	0x21,0x05,0x16,0x37,
	0x21,0x0f,0x11,0x30,
	0x21,0x17,0x3d,0x37 };
void main(void)  
{
	bank_spr(0);
	bank_bg(1);
	ppu_off();				// screen off
	pal_bg(palette_bg);	//	load the BG palette
	pal_spr(palette_sp); // load the sprite palette
  
	set_vram_buffer(); // do at least once

	ppu_wait_nmi();
	banked_call(BANK_2, bank2_load_room);  
	ppu_on_all();			// turn on screen

	

	while (1)      
	{ // infinite loop
		ppu_wait_nmi();     
 
		pad1 = pad_poll(0);
		pad1_new = get_pad_new(0); 

		if (pad1_new & PAD_START)    
		{ 
		} 
  
		
		banked_call(BANK_0, bank0_player_movement);

		oam_clear();  
		banked_call(BANK_0, bank0_draw_player_sprite);

	}
}
