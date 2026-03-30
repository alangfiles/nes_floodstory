// enemy movement
// projectile movement
// enemy sprites
#pragma rodata-name("BANK1")
#pragma code-name("BANK1")

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

void function_bank1()
{
}