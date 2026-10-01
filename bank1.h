// Stage 1 code and data
#pragma rodata-name("BANK1")
#pragma code-name("BANK1")

#include "LEVELS/Stage1/Stage1.c"

// Stage 1 level data pointers
extern const unsigned char* stage1_levels[];
extern const unsigned char stage1_metatiles[];
extern const unsigned char* stage_bg_palettes[];

// Scrolling functions for Stage 1 (replicated in each bank)
static void bank1_drawMetatileBlock(void)
{
	address = get_ppu_addr(nt, x, temp_y);
	index = temp_y + (x >> 4);
	buffer_4_mt(address, index);
}

static void bank1_draw_screen_L(void)
{
	pseudo_scroll_x = scroll_x - 0x20;
	offset = (pseudo_scroll_x >> 8);
	if (offset >= (sizeof(stage1_levels) / sizeof(stage1_levels[0])) || offset < 0) {
		offset = 0;
	}
	set_data_pointer(stage1_levels[offset]);
	nt = ((pseudo_scroll_x >> 8) & 1);
	x = pseudo_scroll_x & 0xff;

	switch (scroll_count)
	{
	case 0:
		temp_y = 0;
		bank1_drawMetatileBlock();
		temp_y = 0x20;
		bank1_drawMetatileBlock();
		break;

	case 1:
		temp_y = 0x40;
		bank1_drawMetatileBlock();
		temp_y = 0x60;
		bank1_drawMetatileBlock();
		break;

	case 2:
		temp_y = 0x80;
		bank1_drawMetatileBlock();
		temp_y = 0xa0;
		bank1_drawMetatileBlock();
		break;

	default:
		temp_y = 0xc0;
		bank1_drawMetatileBlock();
		temp_y = 0xe0;
		bank1_drawMetatileBlock();
	}

	--scroll_count;
	scroll_count &= 3;
}

static void bank1_draw_screen_R(void)
{
	pseudo_scroll_x = scroll_x + 0x120;
	offset = (pseudo_scroll_x >> 8);
	if (offset >= (sizeof(stage1_levels) / sizeof(stage1_levels[0])) || offset < 0) {
		offset = 0;
	}
	set_data_pointer(stage1_levels[offset]);
	nt = ((pseudo_scroll_x >> 8) & 1);
	x = pseudo_scroll_x & 0xff;

	switch (scroll_count)
	{
	case 0:
		temp_y = 0;
		bank1_drawMetatileBlock();
		temp_y = 0x20;
		bank1_drawMetatileBlock();
		break;

	case 1:
		temp_y = 0x40;
		bank1_drawMetatileBlock();
		temp_y = 0x60;
		bank1_drawMetatileBlock();
		break;

	case 2:
		temp_y = 0x80;
		bank1_drawMetatileBlock();
		temp_y = 0xa0;
		bank1_drawMetatileBlock();
		break;

	default:
		temp_y = 0xc0;
		bank1_drawMetatileBlock();
		temp_y = 0xe0;
		bank1_drawMetatileBlock();
	}

	++scroll_count;
	scroll_count &= 3;
}

static void bank1_new_cmap(void)
{
	offset = room_to_load;
	if (offset >= (sizeof(stage1_levels) / sizeof(stage1_levels[0])))
		return;

	map = room_to_load & 1;
	if (!map) 
	{
		memcpy(c_map, stage1_levels[offset], 240); 
		if (scrolling_direction) 
		{
			if (offset + 1 < (sizeof(stage1_levels) / sizeof(stage1_levels[0])))
				memcpy(c_map2, stage1_levels[offset + 1], 240);
		}
		else
		{
			if (offset > 0)
				memcpy(c_map2, stage1_levels[offset - 1], 240);
		}
	}
	else
	{
		memcpy(c_map2, stage1_levels[offset], 240);
		if (scrolling_direction)
		{
			if (offset + 1 < (sizeof(stage1_levels) / sizeof(stage1_levels[0])))
				memcpy(c_map, stage1_levels[offset + 1], 240);
		}
		else
		{
			if (offset > 0)
				memcpy(c_map, stage1_levels[offset - 1], 240);
		}
	}
}

static void bank1_prep_scroll_screen(void)
{
	unsigned char level_index;
	unsigned char level_first_room;
	unsigned char level_room_count;
	unsigned char current_room;

	temp1 = low_byte(scroll_x) + high_byte(Player1.x);
	if (temp1 > 0x98 && temp1 < 0xa4) {
		map_loaded = 0;
	}

	temp2 = Player1.x;
	level_index = current_section;
	level_first_room = stage1_offsets[level_index];
	level_room_count = stage1_max_rooms[level_index];
	if (level_room_count == 0)
	{
		level_room_count = 1;
	}

	max_rooms = level_room_count - 1;
	max_scroll = (level_first_room + max_rooms) * 0x100;

	current_room = scroll_x >> 8;
	if (current_room < level_first_room)
	{
		current_room = 0;
	}
	else
	{
		current_room -= level_first_room;
	}

	if (Player1.x < MAX_LEFT)
	{
		if (!map_loaded && current_room > 0)
		{
			room_to_load = ((scroll_x >> 8) - 1);
			bank1_new_cmap();
			map_loaded = 1;
		}

		temp1 = (MAX_LEFT - Player1.x) >> 8;
		if (temp1 > 3)
			temp1 = 3;

		temp3 = scroll_x + high_byte(Player1.x);
		current_level = (temp3 >> 8);

		if (max_rooms >= 1)
		{
			temp3 = level_first_room * 0x100;
			if (scroll_x <= temp3 + temp1)
			{
				scroll_x = temp3;
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
		if (!map_loaded && current_room < max_rooms)
		{
			room_to_load = ((scroll_x >> 8) + 1);
			bank1_new_cmap();
			map_loaded = 1;
		}
		temp1 = (Player1.x - MAX_RIGHT) >> 8;
		if (temp1 > 3)
			temp1 = 3;

		if (max_rooms >= 1 && current_room < max_rooms)
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

	current_level = scroll_x >> 8;
}

static void bank1_handle_scrolling(void)
{
	unsigned int next_update_x;

	scrolling_direction = (Player1.vel_x >= 0) ? 0 : 1;

	if (!r_scroll_frames && !l_scroll_frames)
	{
		next_update_x = scroll_x & 0xfff0;
		if (next_update_x != scroll_update_x)
		{
			scroll_update_x = next_update_x;
			if (Player1.vel_x > 0)
			{
				r_scroll_frames = 4;
			}
			else if (Player1.vel_x < 0)
			{
				l_scroll_frames = 4;
			}
		}
	}

	if (r_scroll_frames)
	{
		bank1_draw_screen_R();
		--r_scroll_frames;
	}
	else if (l_scroll_frames)
	{
		bank1_draw_screen_L();
		--l_scroll_frames;
	}
}

#include "LEVELS/title.h"
void bank1_load_title(void)
{
	ppu_off();
	vram_adr(NAMETABLE_A);
	vram_write(title, sizeof(title));
	
	ppu_on_all();
}

static const unsigned char story_line_0[] = "GOD HAS TOLD YOU TO BUILD";
static const unsigned char story_line_1[] = "A BOAT AND TAKE 2 OF EVERY";
static const unsigned char story_line_2[] = "ANIMAL (AND MAYBE 7 OF";
static const unsigned char story_line_3[] = "SOME), BECAUSE THERE WILL";
static const unsigned char story_line_4[] = "BE A FLOOD (WHATEVER THAT";
static const unsigned char story_line_5[] = "IS).";
static const unsigned char story_line_6[] = "YOU COLLECTED THE ANIMALS";
static const unsigned char story_line_7[] = "BUT 5 OF THE WILIEST";
static const unsigned char story_line_8[] = "ANIMALS HAVE ESCAPED YOUR";
static const unsigned char story_line_9[] = "ARK. GO COLLECT THEM AND";
static const unsigned char story_line_10[] = "PREPARE FOR THE FLOOD.";
static const unsigned char story_line_11[] = "PRESS START";

void bank1_load_story(void)
{
	ppu_off();
	pal_bg(title_bg_palette);
	vram_adr(NAMETABLE_A);
	vram_fill(0x03, 0x03c0);
	vram_fill(0x00, 0x0040);
	vram_adr(NTADR_A(3, 4));
	vram_write(story_line_0, sizeof(story_line_0) - 1);
	vram_adr(NTADR_A(2, 6));
	vram_write(story_line_1, sizeof(story_line_1) - 1);
	vram_adr(NTADR_A(3, 8));
	vram_write(story_line_2, sizeof(story_line_2) - 1);
	vram_adr(NTADR_A(2, 10));
	vram_write(story_line_3, sizeof(story_line_3) - 1);
	vram_adr(NTADR_A(3, 12));
	vram_write(story_line_4, sizeof(story_line_4) - 1);
	vram_adr(NTADR_A(13, 14));
	vram_write(story_line_5, sizeof(story_line_5) - 1);
	vram_adr(NTADR_A(3, 17));
	vram_write(story_line_6, sizeof(story_line_6) - 1);
	vram_adr(NTADR_A(5, 19));
	vram_write(story_line_7, sizeof(story_line_7) - 1);
	vram_adr(NTADR_A(3, 21));
	vram_write(story_line_8, sizeof(story_line_8) - 1);
	vram_adr(NTADR_A(3, 23));
	vram_write(story_line_9, sizeof(story_line_9) - 1);
	vram_adr(NTADR_A(5, 25));
	vram_write(story_line_10, sizeof(story_line_10) - 1);
	vram_adr(NTADR_A(10, 27));
	vram_write(story_line_11, sizeof(story_line_11) - 1);
	vram_adr(0x23c0);
	vram_fill(0x00, 0x0040);

	ppu_on_all();
}

#include "LEVELS/General/gameovertiled.c"
void bank1_load_gameover(void)
{
	ppu_off();

	set_data_pointer(gameovertiled_0);
	set_mt_pointer(stage1_metatiles);
	for (y = 0;; y += 0x20)
	{
		for (x = 0;; x += 0x20)
		{
			address = get_ppu_addr(0, x, y);
			index = (y & 0xf0) + (x >> 4);
			buffer_4_mt(address, index);
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


// Stage 1 specific functions
void bank1_load_room(void)
{
	unsigned char level_first_room;
	unsigned char level_room_count;

	level_first_room = stage1_offsets[current_section];
	level_room_count = stage1_max_rooms[current_section];
	if (level_room_count == 0)
	{
		level_room_count = 1;
	}

	// Load palette for this stage
	pal_bg(stage_bg_palettes[current_stage]);
	
	ppu_off(); 
	clear_vram_buffer();
	set_vram_buffer();
	
	set_data_pointer(stage1_levels[current_level]);
	set_mt_pointer(stage1_metatiles);
	
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
	if (current_level + 1 < level_first_room + level_room_count)
	{
		set_data_pointer(stage1_levels[current_level+1]);
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
	}
	// a little bit in the previous room
	if (current_level > level_first_room) {
		set_data_pointer(stage1_levels[current_level-1]);
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
	memcpy(c_map, stage1_levels[current_level], 240); 
	if (current_level + 1 < level_first_room + level_room_count) {
		memcpy(c_map2, stage1_levels[current_level + 1], 240);
	}
	memcpy(c_metatile_map, stage1_metatile_colision_map, 240);
 
	map_loaded = 1;
	scroll_update_x = scroll_x & 0xfff0;
	ppu_on_all();
}

void bank1_scroll_screen(void){
	bank1_prep_scroll_screen();
	set_scroll_x(scroll_x);
	set_scroll_y(scroll_y);
	if (r_scroll_frames || l_scroll_frames || ((scroll_x >> 5) != (scroll_update_x >> 5)))
		bank1_handle_scrolling();
	scroll_update_x = scroll_x;
}

void bank1_transition_section(void)
{
	unsigned char section_count;
	unsigned char target_section;

	section_count = sizeof(stage1_offsets) / sizeof(stage1_offsets[0]);
	transition_complete = 0;

	if (transition_direction == TRANSITION_UP)
	{
		if (current_section + 1 >= section_count)
		{
			transition_direction = TRANSITION_NONE;
			return;
		}

		target_section = current_section + 1;
		Player1.y = 0xd000;
	}
	else if (transition_direction == TRANSITION_DOWN)
	{
		if (current_section == 0)
		{
			transition_direction = TRANSITION_NONE;
			return;
		}

		target_section = current_section - 1;
		Player1.y = 0x1800;
	}
	else
	{
		return;
	}

	current_section = target_section;
	max_rooms = stage1_max_rooms[current_section] - 1;
	if (transition_direction == TRANSITION_UP)
	{
		current_level = stage1_offsets[current_section];
	}
	else
	{
		current_level = stage1_offsets[current_section] + max_rooms;
	}

	scroll_x = current_level * 0x100;
	scroll_y = 0;
	max_scroll = (stage1_offsets[current_section] + max_rooms) * 0x100;
	room_to_load = current_level;
	nametable_to_load = current_level & 1;
	map_loaded = 0;
	l_scroll_frames = 0;
	r_scroll_frames = 0;
	scroll_count = 0;
	scroll_update_x = scroll_x & 0xfff0;
	Player1.vel_x = 0;
	Player1.vel_y = 0;
	player_on_ladder = 0;
	player_on_ladder_top = 0;
	transition_direction = TRANSITION_NONE;
	transition_complete = 1;
}

// populate the generic entity arrays from this stage's entity list
void bank1_entity_obj_init(void)
{
	pointer = stage1_entity_list[0];

	for (index = 0; index < MAX_ENTITY; ++index)
	{
		entity_y[index] = TURN_OFF; // turn off all objects by default
	}

	for (index = 0, index2 = 0; index < MAX_ENTITY; ++index)
	{
		temp1 = pointer[index2]; // y
		entity_y[index] = temp1;

		if (temp1 == TURN_OFF)
			break;

		++index2;
		entity_active[index] = 0;

		temp1 = pointer[index2]; // room
		entity_room[index] = temp1;
		++index2;

		temp1 = pointer[index2]; // x
		entity_actual_x[index] = temp1;
		++index2;

		temp1 = pointer[index2]; // type
		entity_type[index] = temp1;
		++index2;
	}
}

void function_bank1()
{
}