// draw the screen/scroll the screen

#pragma rodata-name("BANK2")
#pragma code-name("BANK2")

#include "LEVELS/Stage1/Stage1.c"
#include "LEVELS/Stage2/Stage2.c"

// Extern declarations for stage data in bank3
extern const unsigned char* stage3_levels[];
extern const unsigned char stage3_max_rooms[];
extern const unsigned char stage3_offsets[];
extern const unsigned char stage3_bg_palette[];
extern const unsigned char stage3_palette_sp[];
extern const unsigned char stage3_metatiles[];

extern const unsigned char* stage4_levels[];
extern const unsigned char stage4_max_rooms[];
extern const unsigned char stage4_offsets[];
extern const unsigned char stage4_bg_palette[];
extern const unsigned char stage4_palette_sp[];
extern const unsigned char stage4_metatiles[];

// Extern declarations for stage data in bank4
extern const unsigned char* stage5_levels[];
extern const unsigned char stage5_max_rooms[];
extern const unsigned char stage5_offsets[];
extern const unsigned char stage5_bg_palette[];
extern const unsigned char stage5_palette_sp[];
extern const unsigned char stage5_metatiles[];

// Extern declarations for palette and metatile arrays in fixed bank
extern const unsigned char** stage_table[];
extern const unsigned char* stage_bg_palettes[];
extern const unsigned char* stage_metatiles[];

// Stage metadata
const unsigned char levels_per_stage[] = {
    8,  // stage 1
    2,  // stage 2
    2, // stage 3
    2, // stage 4
    2, // stage 5
};

void function_bank2()
{
}


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
	set_mt_pointer(stage1_metatiles);
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
	set_mt_pointer(stage1_metatiles);
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
		set_chr_bank_0(CHR_STAGE_1_CHARACTER_CHR);
		set_chr_bank_1(CHR_STAGE_1_BACKGROUND_CHR);
	} else if (current_stage == 1) {
		//set chr for this stage
		set_chr_bank_0(CHR_STAGE_1_CHARACTER_CHR);
		set_chr_bank_1(CHR_STAGE_2_BACKGROUND_CHR);
	} else if (current_stage == 2) {
		//set chr for this stage
		set_chr_bank_0(CHR_STAGE_1_CHARACTER_CHR);
		set_chr_bank_1(CHR_STAGE_3_BACKGROUND_CHR);
	} else if (current_stage == 3) {
		//set chr for this stage
		set_chr_bank_0(CHR_STAGE_1_CHARACTER_CHR);
		set_chr_bank_1(CHR_STAGE_4_BACKGROUND_CHR);
	} else if (current_stage == 4) {
		//set chr for this stage
		set_chr_bank_0(CHR_STAGE_1_CHARACTER_CHR);
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