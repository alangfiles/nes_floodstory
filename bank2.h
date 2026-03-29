// draw the screen/scroll the screen

#pragma rodata-name("BANK2")
#pragma code-name("BANK2")

#include "LEVELS/Stage1/level0.c"
#include "LEVELS/Stage2/level0.c"
#include "LEVELS/Stage2/giraffetiles.h"

void function_bank2()
{
}

// simple table structure: each stage has an array of pointers to level data (each "level" here is the room data pointer)
const unsigned char* stage0_levels[] = {
    stage1_level0_0,
    stage1_level0_1,
		stage1_level0_2,
		stage1_level0_3,
		stage1_level0_4,
		stage1_level0_5,
		stage1_level0_6,
		stage1_level0_7,
};

const unsigned char* stage1_levels[] = {
    stage2_level0_0,
		stage2_level0_1,
};

// table of stages
const unsigned char** stage_table[] = {
    stage0_levels,
    stage1_levels,
};

// how many levels each stage has
const unsigned char levels_per_stage[] = {
    sizeof(stage0_levels) / sizeof(stage0_levels[0]),
    sizeof(stage1_levels) / sizeof(stage1_levels[0]),
};

// Stage palettes
const unsigned char stage1_bg_palette[16] = { 0x21,0x0f,0x00,0x10,0x21,0x0f,0x30,0x08,0x21,0x0f,0x17,0x06,0x21,0x0f,0x19,0x29 };
const unsigned char stage2_bg_palette[16] = { 0x21,0x07,0x17,0x37, 0x21,0x30,0x32,0x02, 0x21,0x0f,0x17,0x06, 0x21,0x0f,0x18,0x28 };

const unsigned char* stage_bg_palettes[] = {
    stage1_bg_palette,
    stage2_bg_palette,
};



const unsigned char stage1_metatile[]={
	123, 124, 139, 140,  0,
	125, 126, 141, 142,  0,
	155, 156, 171, 172,  0,
	157, 158, 173, 174,  0,
	190, 175, 123, 124,  0,
	190, 190, 139, 140,  0,
	190, 191, 141, 142,  0,
	190, 190, 173, 174,  0,
	190, 185, 155, 156,  0,
	190, 190, 157, 158,  0,
	190, 187, 171, 172,  0,
	190, 175, 173, 174,  0,
	190, 189, 123, 124,  0,
	190, 189, 125, 126,  0,
	186, 191, 155, 156,  0,
	186, 184, 157, 158,  0,
	123, 174, 124, 123,  0,
	139, 140, 155, 156,  0,
	141, 142, 157, 158,  0,
	123, 124, 139, 1,  0,
	173, 142, 174, 1,  0,
	173, 1, 1, 1,  0,
	125, 126, 1, 1,  0,
	157, 158, 1, 1,  0,
	171, 172, 1, 1,  0,
	1, 123, 1, 1,  0,
	123, 173, 1, 174,  0,
	123, 124, 1, 123,  0,
	122, 124, 139, 140,  0,
	0, 0, 0, 122,  0,
	123, 106, 124, 123,  0,
	0, 0, 106, 0,  0,
	117, 118, 133, 134,  2,
	101, 102, 133, 134,  2,
	117, 118, 149, 150,  2,
	116, 118, 132, 134,  2,
	117, 119, 133, 135,  2,
	100, 102, 132, 134,  2,
	101, 103, 133, 135,  2,
	116, 118, 148, 150,  2,
	117, 119, 149, 151,  2,
	223, 223, 220, 205,  3,
	223, 206, 206, 219,  3,
	205, 206, 238, 238,  3,
	223, 207, 220, 204,  3,
	52, 207, 223, 51,  3,
	223, 207, 51, 207,  3,
	203, 206, 239, 238,  3,
	101, 102, 149, 150,  2,
	100, 102, 148, 150,  2,
	101, 103, 149, 151,  2,
	235, 235, 251, 252,  3,
	235, 234, 252, 251,  3,
	250, 235, 252, 252,  3,
	235, 236, 251, 252,  3,
	152, 153, 168, 169,  3,
	154, 152, 170, 168,  3,
	1, 1, 154, 152,  3,
	123, 139, 173, 155,  0,
	142, 123, 156, 174,  0,
	139, 124, 155, 173,  0,
	10, 11, 10, 11,  2,
	10, 11, 10, 11,  2,
	202, 202, 218, 218,  0,
	1, 1, 99, 115,  3,
	1, 1, 1, 99,  3,
	1, 1, 115, 1,  3,
	18, 19, 0, 0,  0,
	1, 1, 18, 19,  0,
	239, 159, 1, 1,  3,
	239, 239, 238, 239,  3,
	237, 237, 54, 55,  3,
	237, 56, 55, 0,  3,
	57, 237, 0, 57,  3,
	2, 13, 14, 2,  3,
	1, 1, 2, 2,  3,
	31, 2, 2, 47,  3,
	27, 12, 2, 1,  3,
	0, 0, 0, 0,  0,
	15, 63, 1, 2,  3,
	0, 0, 0, 0,  0,
	1, 1, 1, 1,  0,
	1, 1, 42, 1,  3,
	26, 1, 1, 42,  3,
	26, 1, 1, 1,  3,
	242, 242, 1, 1,  2,
	1, 243, 1, 1,  2,
	212, 1, 1, 1,  2,
	0, 0, 128, 129,  3,
	0, 0, 130, 130,  3,
	1, 42, 2, 2,  3,
	26, 1, 2, 2,  3,
	3, 170, 3, 232,  3,
	168, 169, 104, 252,  3,
	138, 3, 248, 3,  3,
	3, 3, 233, 3,  3,
	8, 25, 9, 24,  2,
	8, 25, 8, 24,  2,
	177, 178, 8, 24,  2,
	212, 176, 243, 192,  2,
	8, 25, 193, 194,  2,
	179, 243, 195, 212,  2,
	0, 0, 0, 240,  2,
	241, 0, 0, 0,  2,
	20, 4, 21, 4,  2,
	21, 4, 21, 5,  2,
	229, 230, 20, 4,  2,
	212, 228, 243, 244,  2,
	20, 4, 245, 246,  2,
	231, 243, 247, 212,  2,
	0, 226, 0, 0,  2,
	227, 0, 0, 0,  2,
	6, 23, 6, 23,  2,
	7, 22, 7, 23,  2,
	6, 23, 7, 23,  2,
	224, 225, 6, 22,  2,
	212, 208, 242, 242,  2,
	209, 243, 242, 242,  2,
	0, 0, 0, 210,  2,
	0, 0, 211, 0,  2,
	3, 3, 170, 170,  3,
	0, 0, 0, 0,  0,
	169, 169, 120, 105,  3,
	0, 0, 137, 0,  3,
	138, 0, 138, 0,  3,
	138, 0, 121, 0,  3,
	3, 3, 3, 249,  3,
	249, 233, 170, 170,  3,
	144, 144, 0, 0,  2,
	145, 146, 0, 0,  2,
	1, 1, 146, 146,  2,
	146, 144, 0, 0,  2,
	1, 1, 146, 144,  2,
	1, 146, 144, 0,  2,
	122, 50, 50, 223,  3,
	207, 137, 223, 207,  3,
	223, 51, 222, 223,  3,
	221, 207, 223, 52,  3,
	0, 0, 0, 0,  0,
	0, 0, 0, 122,  3,
	170, 168, 104, 105,  3,
	170, 168, 104, 104,  3,
	0, 0, 215, 167,  0,
	215, 167, 1, 1,  0,
	223, 207, 220, 219,  3,
	50, 51, 222, 223,  3,
	223, 53, 207, 221,  3,
	50, 52, 50, 51,  3,
	51, 53, 52, 53,  3,
	0, 122, 136, 223,  3,
	0, 136, 136, 207,  3,
	106, 0, 207, 106,  3,
	137, 0, 168, 137,  3,
	169, 106, 169, 170,  3,
	1, 255, 255, 0,  3,
	255, 1, 0, 254,  3,
	239, 239, 254, 253,  3,
	237, 238, 254, 255,  3,
	253, 254, 0, 0,  3,
	255, 253, 0, 0,  3,
	5, 3, 5, 3,  3,
	63, 3, 5, 3,  3,
	5, 3, 47, 3,  3,
	1, 31, 31, 2,  3,
	15, 2, 1, 15,  3,
	2, 47, 17, 17,  3,
	3, 3, 17, 17,  3,
	3, 97, 96, 3,  3,
	3, 98, 3, 3,  3,
	3, 3, 97, 3,  3,
	96, 3, 3, 3,  3,
	3, 3, 114, 3,  3,
	0, 0, 0, 113,  3,
	0, 0, 0, 112,  3,
	200, 1, 1, 1,  1,
	200, 201, 1, 217,  1,
	3, 3, 3, 3,  3,
	0, 0, 0, 0,  0,
	0, 0, 0, 0,  0,
	63, 3, 2, 63,  3,
	1, 1, 13, 1,  3,
	3, 14, 3, 3,  3,
	161, 3, 3, 3,  3,
	3, 3, 162, 3,  3,
	162, 3, 3, 161,  3,
	160, 3, 3, 161,  3,
	131, 3, 3, 131,  3,
	131, 147, 3, 3,  3,
	131, 3, 3, 147,  3,
	3, 3, 131, 3,  3,
	131, 3, 3, 3,  3,
	201, 217, 216, 1,  1,
	181, 182, 197, 198,  2,
	1, 180, 1, 196,  2,
	183, 1, 199, 1,  2,
	1, 1, 165, 166,  2,
	213, 214, 1, 1,  2,
	0, 0, 107, 107,  0,
	0, 0, 0, 0,  1,
	16, 16, 1, 1,  0,
	1, 159, 1, 1,  0,
	200, 201, 216, 217,  1,
	1, 1, 216, 217,  1,
	200, 1, 216, 217,  1,
	1, 201, 216, 217,  1,
	1, 1, 216, 1,  1,
	1, 1, 1, 217,  1,
	1, 217, 1, 1,  1,
	0, 94, 108, 3,  0,
	0, 0, 107, 108,  0,
	107, 94, 3, 109,  0,
	107, 94, 109, 93,  0,
	109, 3, 3, 109,  0,
	109, 109, 3, 3,  0,
	109, 3, 3, 3,  0,
	109, 64, 109, 64,  0,
	64, 110, 111, 64,  0,
	109, 20, 3, 111,  0,
	64, 110, 64, 64,  0,
	110, 110, 64, 110,  0,
	0, 0, 30, 30,  1,
	0, 0, 0, 28,  1,
	0, 0, 29, 0,  1,
	109, 109, 163, 164,  0,
	93, 91, 64, 159,  0,
	92, 128, 159, 1,  0,
	0, 0, 91, 92,  0,
	95, 0, 159, 95,  0,
	91, 92, 159, 1,  0,
	107, 108, 1, 163,  0,
	109, 3, 164, 3,  0,
	163, 164, 159, 159,  0,
	3, 109, 164, 3,  0,
	159, 159, 159, 159,  0,
	1, 1, 159, 159,  0,
	159, 1, 159, 159,  0,
	110, 159, 110, 143,  0,
	143, 127, 110, 110,  0,
	159, 159, 143, 127,  0,
	127, 159, 110, 143,  0,
};

// Stage metatile pointers (must be defined after stage1_metatile)
const unsigned char* stage_metatiles[] = {
    stage1_metatile,
    girafee_metatiles,
};


void drawMetatileBlock(void)
{
	// gottta set temp2 first
	address = get_ppu_addr(nt, x, temp_y);
	index = temp_y + (x >> 4);
	buffer_4_mt(address, index); // ppu_address, index to the data
}

void draw_screen_L(void)
{
	// scrolling to the left, draw metatiles as we go
	pseudo_scroll_x = scroll_x - 0x20;

	// high byte of pseudo_scroll_x is the room/level offset
	offset = (pseudo_scroll_x >> 8);

	// bounds-check the computed offset against how many levels this stage has
	if (offset >= levels_per_stage[current_stage] || offset < 0) {
		// fallback to room 0 if the computed offset is out-of-range
		offset = 0;
	}

	set_data_pointer(stage_table[current_stage][offset]);

	// choose the nametable based on the high byte of pseudo_scroll_x
	nt = ((pseudo_scroll_x >> 8) & 1);
	x = pseudo_scroll_x & 0xff;

	switch (scroll_count)
	{
	case 0:
		temp_y = 0;
		drawMetatileBlock();
		temp_y = 0x20;
		drawMetatileBlock();
		break;

	case 1:
		temp_y = 0x40;
		drawMetatileBlock();
		temp_y = 0x60;
		drawMetatileBlock();
		break;

	case 2:
		temp_y = 0x80;
		drawMetatileBlock();
		temp_y = 0xa0;
		drawMetatileBlock();
		break;

	default:
		temp_y = 0xc0;
		drawMetatileBlock();
		temp_y = 0xe0;
		drawMetatileBlock();
	}

	--scroll_count;		 // Decrement scroll_count for left scrolling
	scroll_count &= 3; // mask off top bits, keep it 0-3
}

void draw_screen_R(void)
{
	// scrolling to the right, draw metatiles as we go
	pseudo_scroll_x = scroll_x + 0x120;

	// high byte of pseudo_scroll_x is the room/level offset
	offset = (pseudo_scroll_x >> 8);

	// bounds-check the computed offset against how many levels this stage has
	if (offset >= levels_per_stage[current_stage] || offset < 0) {
		// fallback to room 0 if the computed offset is out-of-range
		offset = 0;
	}

	set_data_pointer(stage_table[current_stage][offset]);

	// choose the nametable based on the high byte of pseudo_scroll_x
	nt = ((pseudo_scroll_x >> 8) & 1);
	x = pseudo_scroll_x & 0xff;

	switch (scroll_count)
	{
	case 0:
		temp_y = 0;
		drawMetatileBlock();
		temp_y = 0x20;
		drawMetatileBlock();
		break;

	case 1:
		temp_y = 0x40;
		drawMetatileBlock();
		temp_y = 0x60;
		drawMetatileBlock();
		break;

	case 2:
		temp_y = 0x80;
		drawMetatileBlock();
		temp_y = 0xa0;
		drawMetatileBlock();
		break;

	default:
		temp_y = 0xc0;
		drawMetatileBlock();
		temp_y = 0xe0;
		drawMetatileBlock();
	}

	++scroll_count;		 // Increment scroll_count for right scrolling
	scroll_count &= 3; // mask off top bits, keep it 0-3
}

// copy a new collision map to one of the 2 c_map arrays
void new_cmap(void)
{
	offset = room_to_load;

	map = room_to_load & 1; // even or odd?
	if (!map) 
	{
		memcpy(c_map, stage_table[current_stage][offset], 240); 
		if (scrolling_direction) 
		{
			if (offset + 1 < levels_per_stage[current_stage])
				memcpy(c_map2, stage_table[current_stage][offset + 1], 240);
		}
		else
		{
			if (offset - 1 >= 0)
				memcpy(c_map2, stage_table[current_stage][offset - 1], 240);
		}
	}
	else
	{
		memcpy(c_map2, stage_table[current_stage][offset], 240);
		if (scrolling_direction)
		{
			if (offset + 1 < levels_per_stage[current_stage])
				memcpy(c_map, stage_table[current_stage][offset + 1], 240);
		}
		else
		{
			if (offset - 1 >= 0)
				memcpy(c_map, stage_table[current_stage][offset - 1], 240);
		}
	}
}


void prep_scroll_screen(void){
	// scroll
	// when the player is in the middle of the screen, reset the map loaded
	temp1 = low_byte(scroll_x) + high_byte(Player1.x);
	if (temp1 > 0x98 && temp1 < 0xa4) // middle of the screen
	{
		map_loaded = 0;
	}

	temp2 = Player1.x; // store his x before we check the scrolling

	if (Player1.x < MAX_LEFT)
	{

		if (!map_loaded)
		{
			room_to_load = ((scroll_x >> 8) - 1); // high byte = room, one to the left
			new_cmap();
			map_loaded = 1; // only do once
		}

		temp1 = (MAX_LEFT - Player1.x) >> 8;
		if (temp1 > 3)
			temp1 = 3; // max scroll change

		temp3 = scroll_x + high_byte(Player1.x);
		current_level = (temp3 >> 8);

		max_rooms = levels_per_stage[current_stage] - 1;
		max_scroll = (max_rooms * 0x100) - 1;

		if (max_rooms >= 1) // this is for the multi-room levels
		{
			if ((scroll_x - temp1) > max_scroll) // if subtracting the scroll makes it overflow
			{
				scroll_x = 0; // just go to zero (and move the guy)
			}
			else // otherwise scroll the window and offset the guy's movement
			{
				scroll_x -= temp1;																	 // scroll the window
				high_byte(Player1.x) = high_byte(Player1.x) + temp1; // add the offset to the guy
			}
		}
	}

	if (Player1.x > MAX_RIGHT)
	{
		if (!map_loaded) // gets reset whenever the player's in the middle of the level
		{
			room_to_load = ((scroll_x >> 8) + 1); // high byte = room, one to the left

			new_cmap();
			map_loaded = 1; // only do once
		}
		temp1 = (Player1.x - MAX_RIGHT) >> 8;
		if (temp1 > 3)
			temp1 = 3; // max scroll change

		if (max_rooms >= 1) // used for single room levels
		{
			scroll_x += temp1;																	 // scroll the window
			high_byte(Player1.x) = high_byte(Player1.x) - temp1; // sub the offet from the guy
		}
	}

	if (scroll_x >= max_scroll)
	{
		scroll_x = max_scroll;						// stop scrolling right, end of level
		Player1.x = temp2;								// but allow the x position to go all the way right
		if (high_byte(Player1.x) >= 0xe0) // but limit how far right he can go
		{
			Player1.x = 0xe000;
		}
	}


}


void handle_scrolling(void)
{
	// how to do scrolling:
	// if the hero is facing right, put an attribute column in front of the current nametable window
	// (4 frames = 1 column of 4 metatiles = 1 attribute column)
	// if the hero is facing left, put an attribute column in behind the current nametable window

	scrolling_direction = (Player1.vel_x >= 0) ? 0 : 1;

	// figure out if we're drawing to the right or left
	if (!r_scroll_frames && !l_scroll_frames)
	{
		if (Player1.vel_x > 0)
		{
			r_scroll_frames = 4;
		}
		else
		{
			l_scroll_frames = 4;
		}
	}

	if (r_scroll_frames)
	{
		draw_screen_R();
		--r_scroll_frames;
	}
	else if (l_scroll_frames)
	{
		draw_screen_L();
		--l_scroll_frames;
	}
}

#include "LEVELS/General/titletiled.c"
void bank2_load_title(void)
{
	
	ppu_off();

	// pal_bg(palette_bg);
	set_data_pointer(titletiled_0);
	set_mt_pointer(stage1_metatile);
		for (y = 0;; y += 0x20)
	{
		for (x = 0;; x += 0x20)
		{
			address = get_ppu_addr(0, x, y);
			index = (y & 0xf0) + (x >> 4);
			buffer_4_mt(address, index); // ppu_address, index to the data
			flush_vram_update2();
			if (x == 0xe0)
				break;
		}
		if (y == 0xe0)
			break;
	}
	
	ppu_on_all();
	game_mode = MODE_TITLE;
	multi_vram_buffer_horz("NOAH VS. ATRAHASIS", 18, NTADR_A(12, 6));
	multi_vram_buffer_horz("ONE ON ONE", 10, NTADR_A(14, 7));

	multi_vram_buffer_horz("BRIAN & ALAN GAMES", 18, NTADR_A(12, 10));

}

#include "LEVELS/General/gameovertiled.c"
void bank2_load_gameover(void)
{
	
	ppu_off();

	// pal_bg(palette_bg);
	set_data_pointer(gameovertiled_0);
	set_mt_pointer(stage1_metatile);
		for (y = 0;; y += 0x20)
	{
		for (x = 0;; x += 0x20)
		{
			address = get_ppu_addr(0, x, y);
			index = (y & 0xf0) + (x >> 4);
			buffer_4_mt(address, index); // ppu_address, index to the data
			flush_vram_update2();
			if (x == 0xe0)
				break;
		}
		if (y == 0xe0)
			break;
	}
	
	ppu_on_all();
	game_mode = MODE_GAMEOVER;

}


void bank2_load_room(void)
{
	// Load appropriate CHR bank for the current stage
	if (current_stage == 0) {
		//set chr for this stage
		set_chr_bank_1(CHR_STAGE_1_BACKGROUND_CHR);
	} else if (current_stage == 1) {
		//set chr for this stage
		set_chr_bank_1(CHR_STAGE_2_BACKGROUND_CHR);
	} else if (current_stage == 2) {
		//set chr for this stage
		set_chr_bank_1(CHR_STAGE_3_BACKGROUND_CHR);
	} else if (current_stage == 3) {
		//set chr for this stage
		set_chr_bank_1(CHR_STAGE_4_BACKGROUND_CHR);
	} else if (current_stage == 4) {
		//set chr for this stage
		set_chr_bank_1(CHR_STAGE_5_BACKGROUND_CHR);
	}
	
	// Load palette for this stage
	pal_bg(stage_bg_palettes[current_stage]);
	
	ppu_off(); 
	clear_vram_buffer();
	set_vram_buffer();
	
	set_data_pointer(stage_table[current_stage][current_level]);
	set_mt_pointer(stage_metatiles[current_stage]);
	// load_bg_after_pointer could work to save space if we set nametable on other usages to 0
	for (y = 0;; y += 0x20)
	{
		for (x = 0;; x += 0x20)
		{
			address = get_ppu_addr(nametable_to_load, x, y);
			index = (y & 0xf0) + (x >> 4);
			buffer_4_mt(address, index); // ppu_address, index to the data
			flush_vram_update2();
			if (x == 0xe0)
				break;
		}
		if (y == 0xe0)
			break;
	}

	// a little bit in the next room
	set_data_pointer(stage_table[current_stage][current_level+1]);
	for (y = 0;; y += 0x20)
	{
		x = 0;
		nt = (nametable_to_load + 1) % 2;
		address = get_ppu_addr(1, x, y);
		index = (y & 0xf0);
		buffer_4_mt(address, index); // ppu_address, index to the data
		flush_vram_update2();
		if (y == 0xe0)
			break;
	}
	// a little bit in the previous room
	if (current_level > 0) {
		set_data_pointer(stage_table[current_stage][current_level-1]);
		for (y = 0;; y += 0x20)
		{
			x = 240;
			nt = nametable_to_load;
			address = get_ppu_addr(nt, x, y);
			index = y + (x >> 4);
			buffer_4_mt(address, index); // ppu_address, index to the data
			flush_vram_update2();
			if (y == 0xe0)
				break;
		}
	}

	// copy the room to the collision map
	// the second one should auto-load with the scrolling code
	// we also copy the previous map into the other collision nametable
	// so that we can go backwards through the levels.
	// map = room_to_load & 1; // even or odd?

	// this just loads once, so copy the first collision map.
	memcpy(c_map, stage_table[current_stage][current_level], 240); 
	if (current_level + 1 < levels_per_stage[current_stage]) {
		memcpy(c_map2, stage_table[current_stage][current_level + 1], 240);
	}
 
	map_loaded = 1;
	ppu_on_all();
}

void bank2_scroll_screen(void){
	prep_scroll_screen();
	set_scroll_x(scroll_x);
	set_scroll_y(scroll_y);
	handle_scrolling();
}