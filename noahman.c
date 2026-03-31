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

// Forward declarations from swappable banks
extern const unsigned char* stage1_levels[];
extern const unsigned char* stage2_levels[];
extern const unsigned char* stage3_levels[];
extern const unsigned char* stage4_levels[];
extern const unsigned char* stage5_levels[];

extern const unsigned char stage1_bg_palette[];
extern const unsigned char stage2_bg_palette[];
extern const unsigned char stage3_bg_palette[];
extern const unsigned char stage4_bg_palette[];
extern const unsigned char stage5_bg_palette[];

extern const unsigned char stage1_metatiles[];
extern const unsigned char stage2_metatiles[];
extern const unsigned char stage3_metatiles[];
extern const unsigned char stage4_metatiles[];
extern const unsigned char stage5_metatiles[];

// Stage table - fixed bank array of level pointers
const unsigned char** stage_table[] = {
    stage1_levels,
    stage2_levels,
    stage3_levels,
    stage4_levels,
    stage5_levels,
};

// Stage background palettes - FIXED BANK
const unsigned char stage1_bg_palette[16] = { 0x21,0x0f,0x00,0x10,0x21,0x0f,0x30,0x08,0x21,0x0f,0x17,0x06,0x21,0x0f,0x19,0x29 };
const unsigned char stage2_bg_palette[16] = { 0x21,0x07,0x17,0x37, 0x21,0x30,0x32,0x02, 0x21,0x0f,0x17,0x06, 0x21,0x0f,0x18,0x28 };
const unsigned char stage3_bg_palette[16] = { 0x0f,0x0a,0x00,0x10,0x0f,0x02,0x21,0x30,0x0f,0x0f,0x17,0x07,0x0f,0x0f,0x08,0x0f };
const unsigned char stage4_bg_palette[16] = { 0x22,0x0f,0x28,0x38,0x22,0x0f,0x00,0x3d,0x22,0x17,0x28,0x38,0x22,0x0f,0x28,0x30 };
const unsigned char stage5_bg_palette[16] = { 0x0f,0x05,0x07,0x29,0x0f,0x0c,0x36,0x0b,0x0f,0x0c,0x29,0x1a,0x0f,0x15,0x0c,0x05 };

// Stage palette pointers - FIXED BANK (always accessible from bank2_load_room)
const unsigned char* stage_bg_palettes[] = {
    stage1_bg_palette,
    stage2_bg_palette,
    stage3_bg_palette,
    stage4_bg_palette,
    stage5_bg_palette,
};

// Note: stage_metatiles pointer array can stay here since metatiles are only read during level loading
// and don't need to be pre-loaded like palettes
extern const unsigned char stage1_metatiles[];
extern const unsigned char stage2_metatiles[];
extern const unsigned char stage3_metatiles[];
extern const unsigned char stage4_metatiles[];
extern const unsigned char stage5_metatiles[];

// Stage metatile pointers - FIXED BANK (always accessible from bank2_load_room)
const unsigned char* stage_metatiles[] = {
    stage1_metatiles,
    stage2_metatiles,
    stage3_metatiles,
    stage4_metatiles,
    stage5_metatiles,
};

// Forward declarations
void load_level_select(void);
void update_level_select_display(void);

void projectile_movement(void) 
{
	for (temp1 = 0; temp1 < MAX_PROJECTILES; ++temp1)
	{
		if (projectiles_list[temp1] != TURN_OFF)
		{
			if (projectiles_x[temp1] > 250)
			{
				projectiles_list[temp1] = TURN_OFF;
			}
			else
			{
				// This code adjusts for when the screen is scrolling too.
				if (projectiles_list[temp1] == RIGHT)
				{
					if ((Player1.x <= MAX_LEFT) && (pad1 & PAD_LEFT))
					{
						projectiles_x[temp1] += PROJECTILE_SPEED_WITH_SCROLL;
					}
					else
					{
						projectiles_x[temp1] += PROJECTILE_SPEED;
					}
				}
				else if (projectiles_list[temp1] == LEFT)
				{
					if ((Player1.x >= MAX_RIGHT) && (pad1 & PAD_RIGHT))
					{
						projectiles_x[temp1] -= PROJECTILE_SPEED_WITH_SCROLL;
					}
					else
					{
						projectiles_x[temp1] -= PROJECTILE_SPEED;
					}
				}
			}
		}
	}
}

// void load_title(void)
// {
// 	ppu_off();
// 	clear_vram_buffer();
	
// 	// Load title screen
// 	multi_vram_buffer_horz("   NOAHMAN", 10, NTADR_A(8, 6));
// 	multi_vram_buffer_horz("PRESS START", 11, NTADR_A(9, 14));
	
// 	ppu_on_all();
// }



void load_level_select(void)
{
	ppu_off();
	clear_vram_buffer();
	oam_clear();
// 	void clear_background(void)
// {
	// draw all 0x00 into the bg
	vram_adr(NAMETABLE_A);
	for (temp_x = 0; temp_x < 1024; ++temp_x)
	{
		vram_put(0x00);
		flush_vram_update2();  
	}  
	
	// Initialize player state for game
	multi_jump_max = 1;
	multi_jump = 0;
	short_jump_count = 0;
	falling_down = 0;
	player_in_air = 0;
	projectile_cooldown = 0;
	
	// Initialize animation state
	direction = RIGHT;
	current_animation_frame = 0;
	animation_frame_counter = 0;
	current_animation_ptr = animate_playerstandright_data;
	
	
	//clear press start and noahman
	// Load level select screen
	multi_vram_buffer_horz("SELECT STAGE", 12, NTADR_A(8, 6));
	
	update_level_select_display();
	
	ppu_on_all();
}

void update_level_select_display(void)
{
	ppu_off();
	clear_vram_buffer();
	
	multi_vram_buffer_horz("SELECT STAGE", 12, NTADR_A(8, 4));
	
	// Display all 5 stages with selection marker
	if (selected_stage == 0)
		multi_vram_buffer_horz("X  BEAR", 7, NTADR_A(8, 8));
	else
		multi_vram_buffer_horz("   BEAR", 7, NTADR_A(8, 8));
	
	if (selected_stage == 1)
		multi_vram_buffer_horz("X  GIRAFFE", 10, NTADR_A(8, 10));
	else
		multi_vram_buffer_horz("   GIRAFFE", 10, NTADR_A(8, 10));
	
	if (selected_stage == 2)
		multi_vram_buffer_horz("X  WALRUS", 9, NTADR_A(8, 12));
	else
		multi_vram_buffer_horz("   WALRUS", 9, NTADR_A(8, 12));
	
	if (selected_stage == 3)
		multi_vram_buffer_horz("X  CAMEL", 8, NTADR_A(8, 14));
	else
		multi_vram_buffer_horz("   CAMEL", 8, NTADR_A(8, 14));
	
	if (selected_stage == 4)
		multi_vram_buffer_horz("X  LEVIATHAN", 12, NTADR_A(8, 16));
	else
		multi_vram_buffer_horz("   LEVIATHAN", 12, NTADR_A(8, 16));
	
	flush_vram_update2();
	ppu_on_all();
}

void main(void)   
{
	bank_spr(0);
	bank_bg(1);
	ppu_off();				// screen off
	pal_bg(palette_bg);	//	load the BG palette
	pal_spr(palette_sp); // load the sprite palette
  
	set_vram_buffer(); // do at least once 

	ppu_wait_nmi();
	set_mirroring(MIRROR_VERTICAL);

	nametable_to_load = 0;
	current_level = 0;
	current_stage = 0;
	selected_stage = 0;
	scroll_x = 0;
	scroll_y = 0;
	game_mode = MODE_TITLE;

	banked_call(BANK_2, bank2_load_title);
	
	ppu_on_all();			// turn on screen

	while (1)      
	{ 
		while (game_mode == MODE_TITLE)
		{
			ppu_wait_nmi();
			pad1 = pad_poll(0);
			pad1_new = get_pad_new(0);
			
			if (pad1_new & PAD_START)
			{
				game_mode = MODE_LEVEL_SELECT;
				load_level_select();
			}
		}

		while (game_mode == MODE_LEVEL_SELECT)
		{
			ppu_wait_nmi();
			pad1 = pad_poll(0);
			pad1_new = get_pad_new(0);
			
			if (pad1_new & PAD_UP)
			{
				if (selected_stage > 0)
					selected_stage--;
				update_level_select_display();
			}
			
			if (pad1_new & PAD_DOWN)
			{
				if (selected_stage < 4)
					selected_stage++;
				update_level_select_display();
			}
			
			if (pad1_new & PAD_START)
			{
				current_stage = selected_stage;
				current_level = 0;
				game_mode = MODE_GAME;
				banked_call(BANK_2, bank2_load_room);
			}
		}

		while (game_mode == MODE_GAME)
		{ 
			ppu_wait_nmi();      
			pad1 = pad_poll(0);  
			pad1_new = get_pad_new(0);
			pad1_state = pad1;

			if (pad1_new & PAD_START)   
			{ 
			} 
	  
			banked_call(BANK_0, bank0_player_movement);
			projectile_movement();
			banked_call(BANK_2, bank2_scroll_screen);  
	 
			oam_clear(); 
			banked_call(BANK_0, bank0_draw_player_sprite);
		} 
	}
}
