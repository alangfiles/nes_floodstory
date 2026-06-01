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

#include "floodstory.h"
#include "metatile.h"
#include "LEVELS/levelselect.h"

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

// Stage background palettes - FIXED BANK
const unsigned char stage1_bg_palette[16] = { 0x21,0x0f,0x00,0x10,0x21,0x0f,0x30,0x08,0x21,0x0f,0x17,0x06,0x21,0x0f,0x19,0x29 };
const unsigned char stage2_bg_palette[16] = { 0x21,0x07,0x17,0x37, 0x21,0x30,0x32,0x02, 0x21,0x0f,0x17,0x06, 0x21,0x0f,0x18,0x28 };
const unsigned char stage3_bg_palette[16] = { 0x0f,0x0a,0x00,0x10,0x0f,0x02,0x21,0x30,0x0f,0x0f,0x17,0x07,0x0f,0x0f,0x08,0x0f };
const unsigned char stage4_bg_palette[16] = { 0x22,0x0f,0x28,0x38,0x22,0x0f,0x00,0x3d,0x22,0x17,0x28,0x38,0x22,0x0f,0x28,0x30 };
const unsigned char stage5_bg_palette[16] = { 0x0f,0x05,0x07,0x29,0x0f,0x0c,0x36,0x0b,0x0f,0x0c,0x29,0x1a,0x0f,0x15,0x0c,0x05 };
const unsigned char title_bg_palette[16] = { 0x11,0x21,0x00,0x10,0x11,0x31,0x30,0x21,0x11,0x29,0x27,0x38,0x11,0x29,0x19,0x21 };
const unsigned char level_select_bg_palette[16] = { 0x11,0x29,0x00,0x10,0x11,0x01,0x30,0x21,0x11,0x29,0x27,0x38,0x11,0x29,0x19,0x16 };

// Stage palette pointers - FIXED BANK (always accessible from bank2_load_room)
const unsigned char* stage_bg_palettes[] = {
    stage1_bg_palette,
    stage2_bg_palette,
    stage3_bg_palette,
    stage4_bg_palette,
    stage5_bg_palette,
};

// Forward declarations for stage-specific bank functions
extern void bank1_load_room(void);
extern void bank2_load_room(void);
extern void bank3_load_room(void);
extern void bank4_load_room(void);
extern void bank5_load_room(void);

extern void bank1_scroll_screen(void);
extern void bank2_scroll_screen(void);
extern void bank3_scroll_screen(void);
extern void bank4_scroll_screen(void);
extern void bank5_scroll_screen(void);

// Dispatcher function: calls the load function for the appropriate stage bank
void dispatch_load_room(void) {
    switch (current_stage) {
        case 0:
						set_chr_bank_0(CHR_STAGE_1_SPRITES);
						set_chr_bank_1(CHR_STAGE_1_BG_A);
            banked_call(BANK_1, bank1_load_room);
            break;
        case 1:
						set_chr_bank_0(CHR_STAGE_2_SPRITES);
						set_chr_bank_1(CHR_STAGE_2_BG_A);
            banked_call(BANK_2, bank2_load_room);
            break;
        case 2:
						set_chr_bank_0(CHR_STAGE_3_SPRITES);
						set_chr_bank_1(CHR_STAGE_3_BG_A);
            banked_call(BANK_3, bank3_load_room);
            break;
        case 3:
						set_chr_bank_0(CHR_STAGE_4_SPRITES);
						set_chr_bank_1(CHR_STAGE_4_BG_A);
            banked_call(BANK_4, bank4_load_room);
            break;
        case 4:
						set_chr_bank_0(CHR_STAGE_5_SPRITES);
						set_chr_bank_1(CHR_STAGE_5_BG_A);
            banked_call(BANK_5, bank5_load_room);
            break;
    }
}

void update_chr_banks_for_stage(unsigned char stage) {
		switch (stage) {
				case 0:
						// set_chr_bank_0(CHR_STAGE_1_CHARACTER_CHR);
						// set_chr_bank_1(CHR_STAGE_1_BACKGROUND_CHR);
						break;
				case 1:
						// if(chr_frame_state == 0) {
						// 	set_chr_bank_1(CHR_STAGE_2_BACKGROUND_CHR);
						// } else {
						// 	set_chr_bank_1(CHR_STAGE_2_BACKGROUND_CHR2);
						// }
						break;
				case 2:
						if(chr_frame_state == 0) {
							set_chr_bank_1(CHR_STAGE_3_BG_A);
						} else {
							set_chr_bank_1(CHR_STAGE_3_BG_B);
						}
						break;
				case 3:
						if(chr_frame_state == 0) { 
							set_chr_bank_1(CHR_STAGE_4_BG_A);
						} else {
							set_chr_bank_1(CHR_STAGE_4_BG_B);
						}
						break;
				case 4:
						if(chr_frame_state == 0) {
							set_chr_bank_1(CHR_STAGE_5_BG_A);
						} else {
							set_chr_bank_1(CHR_STAGE_5_BG_B);
						}
						break;
		}
}

// Dispatcher function: calls the scroll function for the appropriate stage bank
void dispatch_scroll_screen(void) {
    switch (current_stage) {
        case 0:
            banked_call(BANK_1, bank1_scroll_screen);
            break;
        case 1:
            banked_call(BANK_2, bank2_scroll_screen);
            break;
        case 2:
            banked_call(BANK_3, bank3_scroll_screen);
            break;
        case 3:
            banked_call(BANK_4, bank4_scroll_screen);
            break;
        case 4:
            banked_call(BANK_5, bank5_scroll_screen);
            break;
    }
}

// Forward declarations
void load_level_select(void);
void update_level_select_display(void);

const unsigned char level_select_guy[]={

	  0,- 8,0x20,0,
	  0,- 8,0x23,2,
	0x80

};

// Cursor anchor positions for each stage on the level select map.
const unsigned char level_select_cursor_x[5] = {52, 200, 216, 82, 194};
const unsigned char level_select_cursor_y[5] = {104,154, 34, 200, 210};

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

void load_level_select(void)
{
	ppu_off();
	clear_vram_buffer();
	oam_clear();
	set_chr_bank_1(CHR_LEVEL_MAP);
	pal_bg(level_select_bg_palette);
	vram_adr(NAMETABLE_A);
	vram_write(levelselect, sizeof(levelselect));
	
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
	
	ppu_on_all();
	update_level_select_display();
}

void update_level_select_display(void)
{
	oam_clear();
	oam_meta_spr(level_select_cursor_x[selected_stage], level_select_cursor_y[selected_stage], level_select_guy);
}

void main(void)   
{
	set_chr_bank_0(CHR_GENERAL_SPRITES);
	set_chr_bank_1(CHR_TITLE_SCREEN);
	bank_spr(0);
	bank_bg(1);
	ppu_off();				// screen off
	pal_bg(title_bg_palette);	//	load the title BG palette
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

	ppu_wait_nmi();
	
	banked_call(BANK_1, bank1_load_title);
	
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
			}

			update_level_select_display();
			
			if (pad1_new & PAD_START)
			{
				current_stage = selected_stage;
				current_level = 0;
				game_mode = MODE_GAME;
				dispatch_load_room();
			}
		}

		while (game_mode == MODE_GAME)
		{ 
			++frame_counter;
			++chr_frame_counter;

			if(chr_frame_counter >= CHR_FRAME_THRESHOLD)
			{
				chr_frame_state = (chr_frame_state + 1) % 2;
				chr_frame_counter = 0;
				update_chr_banks_for_stage(current_stage);
			}
			ppu_wait_nmi();      
			pad1 = pad_poll(0);  
			pad1_new = get_pad_new(0);
			pad1_state = pad1;

			if (pad1_new & PAD_START)   
			{ 
			} 
	  
			banked_call(BANK_0, bank0_player_movement);
			projectile_movement();
			dispatch_scroll_screen();
	 
			oam_clear(); 
			banked_call(BANK_0, bank0_draw_player_sprite);
		} 
	}
}
