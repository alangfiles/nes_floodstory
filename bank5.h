// Stage 5 code and data
#pragma rodata-name("BANK5")
#pragma code-name("BANK5")

#include "LEVELS/Stage5/Stage5.c"

// Stage 5 level data pointers
extern const unsigned char* stage5_levels[];
extern const unsigned char stage5_metatiles[];
extern const unsigned char* stage_bg_palettes[];

// Scrolling functions for Stage 5 (replicated in each bank)
static void bank5_drawMetatileBlock(void)
{
	address = get_ppu_addr(nt, x, temp_y);
	index = temp_y + (x >> 4);
	buffer_4_mt(address, index);
}

static void bank5_draw_screen_L(void)
{
	pseudo_scroll_x = scroll_x - 0x20;
	offset = (pseudo_scroll_x >> 8);
	if (offset >= (sizeof(stage5_levels) / sizeof(stage5_levels[0])) || offset < 0) {
		offset = 0;
	}
	set_data_pointer(stage5_levels[offset]);
	nt = ((pseudo_scroll_x >> 8) & 1);
	x = pseudo_scroll_x & 0xff;

	switch (scroll_count)
	{
	case 0:
		temp_y = 0;
		bank5_drawMetatileBlock();
		temp_y = 0x20;
		bank5_drawMetatileBlock();
		break;

	case 1:
		temp_y = 0x40;
		bank5_drawMetatileBlock();
		temp_y = 0x60;
		bank5_drawMetatileBlock();
		break;

	case 2:
		temp_y = 0x80;
		bank5_drawMetatileBlock();
		temp_y = 0xa0;
		bank5_drawMetatileBlock();
		break;

	default:
		temp_y = 0xc0;
		bank5_drawMetatileBlock();
		temp_y = 0xe0;
		bank5_drawMetatileBlock();
	}

	--scroll_count;
	scroll_count &= 3;
}

static void bank5_draw_screen_R(void)
{
	pseudo_scroll_x = scroll_x + 0x120;
	offset = (pseudo_scroll_x >> 8);
	if (offset >= (sizeof(stage5_levels) / sizeof(stage5_levels[0])) || offset < 0) {
		offset = 0;
	}
	set_data_pointer(stage5_levels[offset]);
	nt = ((pseudo_scroll_x >> 8) & 1);
	x = pseudo_scroll_x & 0xff;

	switch (scroll_count)
	{
	case 0:
		temp_y = 0;
		bank5_drawMetatileBlock();
		temp_y = 0x20;
		bank5_drawMetatileBlock();
		break;

	case 1:
		temp_y = 0x40;
		bank5_drawMetatileBlock();
		temp_y = 0x60;
		bank5_drawMetatileBlock();
		break;

	case 2:
		temp_y = 0x80;
		bank5_drawMetatileBlock();
		temp_y = 0xa0;
		bank5_drawMetatileBlock();
		break;

	default:
		temp_y = 0xc0;
		bank5_drawMetatileBlock();
		temp_y = 0xe0;
		bank5_drawMetatileBlock();
	}

	++scroll_count;
	scroll_count &= 3;
}

static void bank5_new_cmap(void)
{
	offset = room_to_load;
	map = room_to_load & 1;
	if (!map) 
	{
		memcpy(c_map, stage5_levels[offset], 240); 
		if (scrolling_direction) 
		{
			if (offset + 1 < (sizeof(stage5_levels) / sizeof(stage5_levels[0])))
				memcpy(c_map2, stage5_levels[offset + 1], 240);
		}
		else
		{
			if (offset - 1 >= 0)
				memcpy(c_map2, stage5_levels[offset - 1], 240);
		}
	}
	else
	{
		memcpy(c_map2, stage5_levels[offset], 240);
		if (scrolling_direction)
		{
			if (offset + 1 < (sizeof(stage5_levels) / sizeof(stage5_levels[0])))
				memcpy(c_map, stage5_levels[offset + 1], 240);
		}
		else
		{
			if (offset - 1 >= 0)
				memcpy(c_map, stage5_levels[offset - 1], 240);
		}
	}
}

static void bank5_prep_scroll_screen(void)
{
	temp1 = low_byte(scroll_x) + high_byte(Player1.x);
	if (temp1 > 0x98 && temp1 < 0xa4) {
		map_loaded = 0;
	}

	temp2 = Player1.x;

	if (Player1.x < MAX_LEFT)
	{
		if (!map_loaded)
		{
			room_to_load = ((scroll_x >> 8) - 1);
			bank5_new_cmap();
			map_loaded = 1;
		}

		temp1 = (MAX_LEFT - Player1.x) >> 8;
		if (temp1 > 3)
			temp1 = 3;

		temp3 = scroll_x + high_byte(Player1.x);
		current_level = (temp3 >> 8);

		max_rooms = (sizeof(stage5_levels) / sizeof(stage5_levels[0])) - 1;
		max_scroll = (max_rooms * 0x100) - 1;

		if (max_rooms >= 1)
		{
			if ((scroll_x - temp1) > max_scroll)
			{
				scroll_x = 0;
			}
			else
			{
				scroll_x -= temp1;
				high_byte(Player1.x) = high_byte(Player1.x) + temp1;
			}
		}
	}

	if (Player1.x > MAX_RIGHT)
	{
		if (!map_loaded)
		{
			room_to_load = ((scroll_x >> 8) + 1);
			bank5_new_cmap();
			map_loaded = 1;
		}
		temp1 = (Player1.x - MAX_RIGHT) >> 8;
		if (temp1 > 3)
			temp1 = 3;

		if (max_rooms >= 1)
		{
			scroll_x += temp1;
			high_byte(Player1.x) = high_byte(Player1.x) - temp1;
		}
	}

	if (scroll_x >= max_scroll)
	{
		scroll_x = max_scroll;
		Player1.x = temp2;
		if (high_byte(Player1.x) >= 0xe0)
		{
			Player1.x = 0xe000;
		}
	}
}

static void bank5_handle_scrolling(void)
{
	scrolling_direction = (Player1.vel_x >= 0) ? 0 : 1;

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
		bank5_draw_screen_R();
		--r_scroll_frames;
	}
	else if (l_scroll_frames)
	{
		bank5_draw_screen_L();
		--l_scroll_frames;
	}
}

// Stage 5 specific functions
void bank5_load_room(void)
{
	// Load palette for this stage
	pal_bg(stage_bg_palettes[current_stage]);
	
	ppu_off(); 
	clear_vram_buffer();
	set_vram_buffer();
	
	set_data_pointer(stage5_levels[current_level]);
	set_mt_pointer(stage5_metatiles);
	
	for (y = 0;; y += 0x20)
	{
		for (x = 0;; x += 0x20)
		{
			address = get_ppu_addr(nametable_to_load, x, y);
			index = (y & 0xf0) + (x >> 4);
			buffer_4_mt(address, index);
			flush_vram_update2();
			if (x == 0xe0)
				break;
		}
		if (y == 0xe0)
			break;
	}

	// a little bit in the next room
	set_data_pointer(stage5_levels[current_level+1]);
	for (y = 0;; y += 0x20)
	{
		x = 0;
		nt = (nametable_to_load + 1) % 2;
		address = get_ppu_addr(1, x, y);
		index = (y & 0xf0);
		buffer_4_mt(address, index);
		flush_vram_update2();
		if (y == 0xe0)
			break;
	}
	// a little bit in the previous room
	if (current_level > 0) {
		set_data_pointer(stage5_levels[current_level-1]);
		for (y = 0;; y += 0x20)
		{
			x = 240;
			nt = nametable_to_load;
			address = get_ppu_addr(nt, x, y);
			index = y + (x >> 4);
			buffer_4_mt(address, index);
			flush_vram_update2();
			if (y == 0xe0)
				break;
		}
	}

	// copy the room to the collision map
	memcpy(c_map, stage5_levels[current_level], 240); 
	if (current_level + 1 < (sizeof(stage5_levels) / sizeof(stage5_levels[0]))) {
		memcpy(c_map2, stage5_levels[current_level + 1], 240);
	}
 
	map_loaded = 1;
	ppu_on_all();
}

void bank5_scroll_screen(void){
	bank5_prep_scroll_screen();
	set_scroll_x(scroll_x);
	set_scroll_y(scroll_y);
	bank5_handle_scrolling();
}

void function_bank5()
{
}

// Clean up macros to avoid conflicts with other banks
