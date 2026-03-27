
#pragma rodata-name("BANK0")
#pragma code-name("BANK0")
// player movement
// player sprite drawing
#include "sprites.h"

//colision code:

char bg_collision_sub(void)
{
  if (temp_y >= 0xf0)
    return 0;

  coordinates = (temp_x >> 4) + (temp_y & 0xf0);
  // we just need 4 bits each from x and y

  map = temp_room & 1; // high byte
  if (!map)
  {
    collision = c_map[coordinates];
  }
  else
  {
    collision = c_map2[coordinates];
  }

  return metatile_colision_map[collision];
}
void bg_collision_fast(void)
{
  // rewrote this for enemies, bg_collision was too slow
  // test 1 point on each side

  collision_L = 0;
  collision_R = 0;
  collision_D = 0;

  if (Generic.y >= 0xf0)
    return;

  location_with_scroll = Generic.x + scroll_x;
  temp_x = location_with_scroll & 0xff;  // low byte x
  temp_room = location_with_scroll >> 8; // high byte x

  temp_y = Generic.y + 6; // y middle

  bg_collision_sub();

  if (bg_collision_sub() & COL_ALL)
  {
    ++collision_L;
  }

  // right side
  location_with_scroll += Generic.width;
  temp_x = location_with_scroll & 0xff;  // low byte x
  temp_room = location_with_scroll >> 8; // high byte x

  // temp_y is unchanged
  bg_collision_sub();

  if (bg_collision_sub() & COL_ALL)
  { // find a corner in the collision map
    ++collision_R;
  }

  // underneath
  location_with_scroll -= (Generic.width >> 1); // middle of character
  temp_x = (char)location_with_scroll;          // low byte
  temp_y += 6;

  if (bg_collision_sub() & COL_ALL)
  {
    ++collision_D;
  }
}

char bg_coll_L(void)
{
  // check 2 points on the left side
  location_with_scroll = Generic.x + scroll_x;
  temp_x = (char)location_with_scroll;   // low byte
  temp_room = location_with_scroll >> 8; // high byte

  eject_L = temp_x | 0xf0;
  temp_y = Generic.y + 2;
  if (bg_collision_sub() & COL_ALL)
    return 1;

  temp_y = Generic.y + Generic.height;
  temp_y -= 2;
  if (bg_collision_sub() & COL_ALL)
    return 1;

  return 0;
}

char bg_coll_R(void)
{
  // check 2 points on the right side
  location_with_scroll = Generic.x + scroll_x + Generic.width;
  temp_x = (char)location_with_scroll;   // low byte
  temp_room = location_with_scroll >> 8; // high byte

  eject_R = (temp_x + 1) & 0x0f;
  temp_y = Generic.y + 2;
  if (bg_collision_sub() & COL_ALL)
    return 1;

  temp_y = Generic.y + Generic.height;
  temp_y -= 2;
  if (bg_collision_sub() & COL_ALL)
    return 1;

  return 0;
}

char bg_coll_ladder(void)
{
  location_with_scroll = Generic.x + scroll_x + 7;
  temp_x = (char)location_with_scroll; // low byte
  temp_y = Generic.y + Generic.height;
  temp_y -= 2;
  if (bg_collision_sub() & COL_LADDER || bg_collision_sub() & COL_LADDER_TOP)
    return location_with_scroll;

  return 0;
}

char bg_coll_ladder_top_at_player(void)
{
  location_with_scroll = Generic.x + scroll_x + 7;
  temp_x = (char)location_with_scroll; // low byte
  temp_y = Generic.y + Generic.height;
  temp_y -= 2;

  if (bg_collision_sub() & COL_LADDER)
    return 1;

  return 0;
}

char bg_coll_ladder_top_under_player(void)
{
  location_with_scroll = Generic.x + scroll_x + 7;
  temp_x = (char)location_with_scroll; // low byte
  temp_y = Generic.y + Generic.height;
  temp_y += 4;
  if (bg_collision_sub() & COL_LADDER_TOP)
    return 1;

  return 0;
}

char bg_coll_U(void)
{
  // check 2 points on the top side
  location_with_scroll = Generic.x + scroll_x;
  location_with_scroll += 2;
  temp_x = (char)location_with_scroll;   // low byte
  temp_room = location_with_scroll >> 8; // high byte

  temp_y = Generic.y;
  eject_U = temp_y | 0xf0;
  if (bg_collision_sub() & COL_ALL)
    return 1;

  location_with_scroll = Generic.x + scroll_x + Generic.width;
  location_with_scroll -= 2;
  temp_x = (char)location_with_scroll;   // low byte
  temp_room = location_with_scroll >> 8; // high byte

  if (bg_collision_sub() & COL_ALL)
    return 1;

  return 0;
}

char bg_coll_D(void)
{

  // check 2 points on the bottom side
  location_with_scroll = Generic.x + scroll_x;
  // location_with_scroll += 2;
  temp_x = (char)location_with_scroll;   // low byte
  temp_room = location_with_scroll >> 8; // high byte

  temp_y = Generic.y + Generic.height;

  if ((temp_y & 0x0f) > 3)
    return 0; // bug fix
  // so we don't snap to those platforms
  // don't fall too fast, or might miss it.

  eject_D = (temp_y + 1) & 0x0f;

  // if (bg_collision_sub() & COL_ALL || ((bg_collision_sub() & COL_LADDER_TOP) && !player_on_ladder))
	if (bg_collision_sub() & COL_ALL || ((bg_collision_sub() & COL_LADDER_TOP)))
    return 1;

  location_with_scroll = Generic.x + scroll_x + Generic.width;
  location_with_scroll -= 2;
  temp_x = (char)location_with_scroll;   // low byte
  temp_room = location_with_scroll >> 8; // high byte

  // if (bg_collision_sub() & COL_ALL || ((bg_collision_sub() & COL_LADDER_TOP) && !player_on_ladder))
	if (bg_collision_sub() & COL_ALL || ((bg_collision_sub() & COL_LADDER_TOP)))
    return 1;

  return 0;
}

// char bg_coll_D2(void)
// {
//   // check 2 points on the bottom side
//   // a little lower, for jumping
//   location_with_scroll = Generic.x + scroll_x;
//   location_with_scroll += 2;
//   temp_x = (char)location_with_scroll;   // low byte
//   temp_room = location_with_scroll >> 8; // high byte

//   temp_y = Generic.y + Generic.height;
//   temp_y += 2;
//   if (bg_collision_sub())
//     return 1;

//   location_with_scroll = Generic.x + scroll_x + Generic.width;
//   location_with_scroll -= 2;
//   temp_x = (char)location_with_scroll;   // low byte
//   temp_room = location_with_scroll >> 8; // high byte

//   if (bg_collision_sub())
//     return 1;

//   return 0;
// }

void movement(void)
{
	// Handle hitstun state
	if (player_in_hitstun)
	{
		--player_in_hitstun;
	}

	if (player_in_hitstun > 0)
	{
		if (hit_direction == RIGHT)
		{
			Player1.vel_x += HITSTUN_DECEL;
			if (Player1.vel_x >= MAX_SPEED)
				Player1.vel_x = MAX_SPEED;
		}
		else
		{
			Player1.vel_x -= HITSTUN_DECEL;
			if (Player1.vel_x < -MAX_SPEED)
				Player1.vel_x = -MAX_SPEED;
		}
	}

	// Handle horizontal movement
	old_x = Player1.x;

	if (pad1 & PAD_LEFT && !player_in_hitstun && !player_is_sliding)
	{
		direction = LEFT;
		player_is_running = 1;

		if (!player_on_ladder)
		{
			if (Player1.vel_x >= DECEL)
			{
				Player1.vel_x -= DECEL;
			}
			else if (Player1.vel_x > 0)
			{
				Player1.vel_x = 0;
			}
			else
			{
				Player1.vel_x -= ACCEL;
				if (Player1.vel_x < -MAX_SPEED)
					Player1.vel_x = -MAX_SPEED;
			}
		}
	}
	else if (pad1 & PAD_RIGHT && !player_in_hitstun && !player_is_sliding)
	{
		direction = RIGHT;
		player_is_running = 1;

		if (!player_on_ladder)
		{
			if (Player1.vel_x <= DECEL)
			{
				Player1.vel_x += DECEL;
			}
			else if (Player1.vel_x < 0)
			{
				Player1.vel_x = 0;
			}
			else
			{
				Player1.vel_x += ACCEL;
				if (Player1.vel_x >= MAX_SPEED)
					Player1.vel_x = MAX_SPEED;
			}
		}
	}
	else
	{
		// No directional input, natural friction
		player_is_running = 0;
		if (Player1.vel_x >= ACCEL)
			Player1.vel_x -= ACCEL;
		else if (Player1.vel_x < -ACCEL)
			Player1.vel_x += ACCEL;
		else
			Player1.vel_x = 0;
	}

	// Handle sliding
	if (player_is_sliding > 0)
	{
		--player_is_sliding;

		if (direction == LEFT)
		{
			Player1.vel_x = -MAX_SLIDE_SPEED;
		}
		else
		{
			Player1.vel_x = MAX_SLIDE_SPEED;
		}
	}

	Player1.x += Player1.vel_x;

	// Bounds checking for X
	if (Player1.x > 0xf000)
	{
		if (old_x >= 0x8000)
		{
			Player1.x = 0xf000; // max right
		}
		else
		{
			Player1.x = 0x0000; // max left
		}
		Player1.vel_x = 0;
	}

	// Collision for horizontal movement
	Generic.x = high_byte(Player1.x);
	Generic.y = high_byte(Player1.y);
	Generic.width = HERO_WIDTH;
	Generic.height = HERO_HEIGHT;

	if (Player1.vel_x < 0)
	{
		if (bg_coll_L())
		{
			high_byte(Player1.x) = high_byte(Player1.x) - eject_L;
			Player1.vel_x = 0;
			if (Player1.x > 0xf000)
			{
				Player1.x = 0xf000;
			}
		}
	}
	else if (Player1.vel_x > 0)
	{
		if (bg_coll_R())
		{
			high_byte(Player1.x) = high_byte(Player1.x) - eject_R;
			Player1.vel_x = 0;
			if (Player1.x > 0xf000)
			{
				Player1.x = 0x0000;
			}
		}
	}

	// Handle vertical movement (ladders and gravity)
	if (player_on_ladder && (bg_coll_ladder() || bg_coll_ladder_top_under_player()))
	{
		if (pad1 & PAD_DOWN)
		{
			direction_y = DOWN;
			++player_on_ladder_pose;
			Player1.vel_y += LADDER_ACCEL;
			if (Player1.vel_y > MAX_LADDER_SPEED)
			{
				Player1.vel_y = MAX_LADDER_SPEED;
			}
			player_on_ladder_top = 0;
		}
		else if (pad1 & PAD_UP)
		{
			direction_y = UP;
			++player_on_ladder_pose;
			Player1.vel_y -= LADDER_ACCEL;
			if (Player1.vel_y < -MAX_LADDER_SPEED)
			{
				Player1.vel_y = -MAX_LADDER_SPEED;
			}
			// If on ladder top, zip upward
			if (bg_coll_ladder_top_under_player())
			{
				++player_on_ladder_top;

				if (player_on_ladder_top > 10)
				{
					// Bump player upward
					if (Player1.vel_y == -MAX_LADDER_SPEED)
					{
						Player1.y -= 0x200;
					}
					else
					{
						Player1.y -= 0x800;
					}
					player_on_ladder_top = 0;
					player_on_ladder = 0;
				}
			}
		}
		else
		{
			Player1.vel_y = 0;
		}
	}
	else
	{
		// Not on ladder or no valid ladder underneath
		if (player_on_ladder && bg_coll_ladder_top_under_player())
		{
			player_on_ladder = 0;
		}

		// Apply gravity
		if (Player1.vel_y < 0x300)
		{
			Player1.vel_y += GRAVITY;
		}
		else
		{
			Player1.vel_y = 0x300; // Consistent max gravity
		}
	}

	// Enter ladder when standing on top of ladder
	if (pad1 & PAD_DOWN)
	{
		direction_y = DOWN;
		if (bg_coll_ladder_top_under_player())
		{
			Player1.x = (Player1.x + 0x700) & ~0xF00;
			player_on_ladder_pose = 0;
			player_on_ladder = 1;
			player_in_air = 0;
			falling_down = 0;
			Player1.vel_y = 0;
			Player1.vel_x = 0;
		}
	}

	Player1.y += Player1.vel_y;

	// Bounds checking for Y
	if (Player1.y > 0xf000)
	{
		Player1.y = 0x0000;
	}

	Generic.x = high_byte(Player1.x);
	Generic.y = high_byte(Player1.y);

	// Track falling state
	if (Player1.vel_y > 0)
	{
		++falling_down;

		if (falling_down > 2 && !player_on_ladder)
		{
			player_in_air = 1;
		}

		// Collision below
		if (bg_coll_D())
		{
			player_in_air = 0;
			falling_down = 0;
			multi_jump = 0;
			player_on_ladder = 0;

			high_byte(Player1.y) = high_byte(Player1.y) - eject_D;
			Player1.y &= 0xff00;
			if (Player1.vel_y > 0)
			{
				Player1.vel_y = 0;
			}
			Player1.on_ground = 1;
		}
	}
	else if (Player1.vel_y < 0)
	{
		// Collision above
		if (bg_coll_U())
		{
			high_byte(Player1.y) = high_byte(Player1.y) - eject_U;
			Player1.vel_y = 0;
		}
	}

	// Update generic position for checks
	Generic.y = high_byte(Player1.y);

	// Handle projectile cooldown
	if (projectile_cooldown > 0)
	{
		--projectile_cooldown;
	}

	// Ladder entry input (new press or held)
	if (pad1_new & PAD_UP || pad1_state & PAD_UP)
	{
		direction_y = UP;
		if (!player_on_ladder && bg_coll_ladder())
		{
			Player1.x = (Player1.x + 0x700) & ~0xF00;
			player_on_ladder_pose = 0;
			player_on_ladder = 1;
			player_in_air = 0;
			falling_down = 0;
			Player1.vel_y = 0;
			Player1.vel_x = 0;
		}
	}

	// Sliding input
	if (pad1_state & PAD_DOWN && pad1_new & PAD_A && !player_on_ladder)
	{
		player_is_sliding = 25;
	}
	// Jumping input
	else if (pad1_new & PAD_A && !player_in_hitstun && !player_is_sliding)
	{
		if (player_on_ladder)
		{
			player_on_ladder = 0;
			player_on_ladder_top = 0;
			player_in_air = 1;
		}
		else if (bg_coll_D() || multi_jump < multi_jump_max)
		{
			++multi_jump;
			Player1.vel_y = JUMP_VEL;
			// sfx_play(SFX_JUMP, 0);
			short_jump_count = 1;
			player_in_air = 1;
		}
	}

	// Shooting input
	if (pad1_new & PAD_B && projectile_cooldown == 0 && !player_in_hitstun && !player_is_sliding)
	{
		// Check for empty projectile slot
		temp2 = 0;
		for (temp1 = 0; temp1 < MAX_PROJECTILES; ++temp1)
		{
			if (projectiles_list[temp1] == TURN_OFF)
			{
				temp2 = 1;
				break;
			}
		}

		if (temp2)
		{
			projectile_cooldown = PROJECTILE_COOLDOWN_FRAMES;
			player_shooting = 10;
			projectile_index = temp1;

			// Set projectile direction based on player facing
			if (direction == RIGHT)
			{
				projectiles_list[projectile_index] = RIGHT;
			}
			else
			{
				projectiles_list[projectile_index] = LEFT;
			}

			projectiles_x[projectile_index] = high_byte(Player1.x) + 10;
			projectiles_y[projectile_index] = high_byte(Player1.y);
			// sfx_play(SFX_SHOOT, 0);
		}
	}

	// Handle short jump control
	if (short_jump_count)
	{
		++short_jump_count;
		if (short_jump_count > 30)
			short_jump_count = 0;
	}
	if ((short_jump_count) && ((pad1 & PAD_A) == 0) && (Player1.vel_y < -0x200))
	{
		Player1.vel_y = -0x200;
		short_jump_count = 0;
	}
}

void check_player_colision(void){
  // This is now integrated into movement()
}

void bank0_player_movement(void)
{
  movement();
}

void bank0_draw_player_sprite(void)
{
	temp_x = Player1.x >> 8;
  temp_y = Player1.y >> 8; 
	
	// Use sliding sprite if player is sliding, otherwise use standing sprite
	if (player_is_sliding)
	{
		temp_sprite = noah_slide;
	}
	else
	{
		temp_sprite = noah_box;
	}
	
	oam_meta_spr(temp_x, temp_y, temp_sprite);
	
	// Draw projectiles
	for (temp1 = 0; temp1 < MAX_PROJECTILES; ++temp1)
	{
		if (projectiles_list[temp1] != TURN_OFF)
		{
			oam_meta_spr(projectiles_x[temp1], projectiles_y[temp1], projectile);
		}
	}
}
