// Shared scrolling functions for stages
// Each stage bank will include this and define its stage data

#ifndef STAGE_SCROLLING_H
#define STAGE_SCROLLING_H

// Each bank should define these before including this file:
// extern const unsigned char* CURRENT_STAGE_LEVELS[];
// extern const unsigned char CURRENT_STAGE_METATILES[];
// #define CURRENT_STAGE_MAX_LEVELS (number of levels)

void drawMetatileBlock_stage(void)
{
	// gottta set temp2 first
	address = get_ppu_addr(nt, x, temp_y);
	index = temp_y + (x >> 4);
	buffer_4_mt(address, index); // ppu_address, index to the data
}

void draw_screen_L_stage(void)
{
	// scrolling to the left, draw metatiles as we go
	pseudo_scroll_x = scroll_x - 0x20;

	// high byte of pseudo_scroll_x is the room/level offset
	offset = (pseudo_scroll_x >> 8);

	// bounds-check the computed offset against how many levels this stage has
	if (offset >= CURRENT_STAGE_MAX_LEVELS || offset < 0) {
		// fallback to room 0 if the computed offset is out-of-range
		offset = 0;
	}

	set_data_pointer(CURRENT_STAGE_LEVELS[offset]);

	// choose the nametable based on the high byte of pseudo_scroll_x
	nt = ((pseudo_scroll_x >> 8) & 1);
	x = pseudo_scroll_x & 0xff;

	switch (scroll_count)
	{
	case 0:
		temp_y = 0;
		drawMetatileBlock_stage();
		temp_y = 0x20;
		drawMetatileBlock_stage();
		break;

	case 1:
		temp_y = 0x40;
		drawMetatileBlock_stage();
		temp_y = 0x60;
		drawMetatileBlock_stage();
		break;

	case 2:
		temp_y = 0x80;
		drawMetatileBlock_stage();
		temp_y = 0xa0;
		drawMetatileBlock_stage();
		break;

	default:
		temp_y = 0xc0;
		drawMetatileBlock_stage();
		temp_y = 0xe0;
		drawMetatileBlock_stage();
	}

	--scroll_count;		 // Decrement scroll_count for left scrolling
	scroll_count &= 3; // mask off top bits, keep it 0-3
}

void draw_screen_R_stage(void)
{
	// scrolling to the right, draw metatiles as we go
	pseudo_scroll_x = scroll_x + 0x120;

	// high byte of pseudo_scroll_x is the room/level offset
	offset = (pseudo_scroll_x >> 8);

	// bounds-check the computed offset against how many levels this stage has
	if (offset >= CURRENT_STAGE_MAX_LEVELS || offset < 0) {
		// fallback to room 0 if the computed offset is out-of-range
		offset = 0;
	}

	set_data_pointer(CURRENT_STAGE_LEVELS[offset]);

	// choose the nametable based on the high byte of pseudo_scroll_x
	nt = ((pseudo_scroll_x >> 8) & 1);
	x = pseudo_scroll_x & 0xff;

	switch (scroll_count)
	{
	case 0:
		temp_y = 0;
		drawMetatileBlock_stage();
		temp_y = 0x20;
		drawMetatileBlock_stage();
		break;

	case 1:
		temp_y = 0x40;
		drawMetatileBlock_stage();
		temp_y = 0x60;
		drawMetatileBlock_stage();
		break;

	case 2:
		temp_y = 0x80;
		drawMetatileBlock_stage();
		temp_y = 0xa0;
		drawMetatileBlock_stage();
		break;

	default:
		temp_y = 0xc0;
		drawMetatileBlock_stage();
		temp_y = 0xe0;
		drawMetatileBlock_stage();
	}

	++scroll_count;		 // Increment scroll_count for right scrolling
	scroll_count &= 3; // mask off top bits, keep it 0-3
}

// copy a new collision map to one of the 2 c_map arrays
void new_cmap_stage(void)
{
	offset = room_to_load;

	map = room_to_load & 1; // even or odd?
	if (!map) 
	{
		memcpy(c_map, CURRENT_STAGE_LEVELS[offset], 240); 
		if (scrolling_direction) 
		{
			if (offset + 1 < CURRENT_STAGE_MAX_LEVELS)
				memcpy(c_map2, CURRENT_STAGE_LEVELS[offset + 1], 240);
		}
		else
		{
			if (offset - 1 >= 0)
				memcpy(c_map2, CURRENT_STAGE_LEVELS[offset - 1], 240);
		}
	}
	else
	{
		memcpy(c_map2, CURRENT_STAGE_LEVELS[offset], 240);
		if (scrolling_direction)
		{
			if (offset + 1 < CURRENT_STAGE_MAX_LEVELS)
				memcpy(c_map, CURRENT_STAGE_LEVELS[offset + 1], 240);
		}
		else
		{
			if (offset - 1 >= 0)
				memcpy(c_map, CURRENT_STAGE_LEVELS[offset - 1], 240);
		}
	}
}


void prep_scroll_screen_stage(void){
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
			new_cmap_stage();
			map_loaded = 1; // only do once
		}

		temp1 = (MAX_LEFT - Player1.x) >> 8;
		if (temp1 > 3)
			temp1 = 3; // max scroll change

		temp3 = scroll_x + high_byte(Player1.x);
		current_level = (temp3 >> 8);

		max_rooms = CURRENT_STAGE_MAX_LEVELS - 1;
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

			new_cmap_stage();
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


void handle_scrolling_stage(void)
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
		draw_screen_R_stage();
		--r_scroll_frames;
	}
	else if (l_scroll_frames)
	{
		draw_screen_L_stage();
		--l_scroll_frames;
	}
}

#endif // STAGE_SCROLLING_H
