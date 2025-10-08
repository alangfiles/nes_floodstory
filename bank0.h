
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
  location_with_scroll += 2;
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

char bg_coll_D2(void)
{
  // check 2 points on the bottom side
  // a little lower, for jumping
  location_with_scroll = Generic.x + scroll_x;
  location_with_scroll += 2;
  temp_x = (char)location_with_scroll;   // low byte
  temp_room = location_with_scroll >> 8; // high byte

  temp_y = Generic.y + Generic.height;
  temp_y += 2;
  if (bg_collision_sub())
    return 1;

  location_with_scroll = Generic.x + scroll_x + Generic.width;
  location_with_scroll -= 2;
  temp_x = (char)location_with_scroll;   // low byte
  temp_room = location_with_scroll >> 8; // high byte

  if (bg_collision_sub())
    return 1;

  return 0;
}

void move_player(void){

   // keep track of where the player was
	// the move them to the new place.
	// then check colision
	// move them back if they colide
	old_x = Player1.x; 

	if (pad1 & PAD_LEFT )
	{
		direction = LEFT;

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
	else if (pad1 & PAD_RIGHT)
	{

		direction = RIGHT;

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
	else
	{ // nothing pressed
		if (Player1.vel_x >= ACCEL)
			Player1.vel_x -= ACCEL;
		else if (Player1.vel_x < -ACCEL)
			Player1.vel_x += ACCEL;
		else
			Player1.vel_x = 0;
	}

	Player1.x += Player1.vel_x;


  // add gravity
	if (Player1.vel_y < 0x300)
	{
		Player1.vel_y += GRAVITY;
	}
	else
	{
		Player1.vel_y = 0x300; // consistent gravity
	}


	//jumping
  if (pad1 & PAD_A)
	{
    Player1.vel_y = JUMP_VEL; // JUMP
		// if (bg_coll_D())
		// {
    //   Player1.vel_y = JUMP_VEL; // JUMP
		// 	// sfx_play(SFX_JUMP, 0);
		// }
	}



	Player1.y += Player1.vel_y; // add gravity to y; (make him go up or down)
	

	
}

void check_player_colision(void){
  Generic.x = high_byte(Player1.x); // this is much faster than passing a pointer
	Generic.y = high_byte(Player1.y);
	Generic.width = HERO_WIDTH;
	Generic.height = HERO_HEIGHT; 

	if (Player1.vel_x < 0)
	{
		if (bg_coll_L())
		{ // check collision left
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
		{ // check collision right
			high_byte(Player1.x) = high_byte(Player1.x) - eject_R;
			Player1.vel_x = 0;
			if (Player1.x > 0xf000)
			{
				// no wrap around
				Player1.x = 0x0000;
			}
		}
	}
  if (Player1.y > 0xf000)			// limit how high he can go
	{
		Player1.y = 0x0000;
	}
if (Player1.vel_y > 0) // he's going down
	{

		if (bg_coll_D()) // if he's collising below
		{								 // check collision below

			high_byte(Player1.y) = high_byte(Player1.y) - eject_D;
			Player1.y &= 0xff00;
			if (Player1.vel_y > 0)
			{
				Player1.vel_y = 0;
			}
		}
	}
	else if (Player1.vel_y < 0) // he's going up
	{
		if (bg_coll_U())
		{ // check collision above
			high_byte(Player1.y) = high_byte(Player1.y) - eject_U;
			Player1.vel_y = 0;
		}
	}
}

void bank0_player_movement(void)
{

	//Move player left and right

  move_player();

  check_player_colision();



}

void bank0_draw_player_sprite(void)
{
	temp_x = Player1.x >> 8;
  temp_y = Player1.y >> 8; 
	temp_sprite = noah_box;  
	oam_meta_spr(temp_x, temp_y, temp_sprite);

}
