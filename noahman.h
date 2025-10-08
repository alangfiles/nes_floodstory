
// ENUMS/DEFINES
#define LEFT 0
#define RIGHT 1
#define DOWN 4
#define UP 3

//MOVEMENT
#define ACCEL 30
#define DECEL 50
#define MAX_SPEED 0x160
#define GRAVITY 0x3c
#define JUMP_VEL -0x210

// collision
#define COL_DOWN 0x80
#define COL_ALL 0x40
#define COL_LADDER 0x01
#define COL_LADDER_TOP 0x02

//scrolling
#define MIN_SCROLL 0x0000


// player colision stuff
#define HERO_WIDTH 12
#define HERO_HEIGHT 20


// GLOBAL VARIABLES

enum
{
	BANK_0,
	BANK_1,
	BANK_2,
	BANK_3,
	BANK_4,
	BANK_5,
	BANK_6
};

#pragma bss-name(push, "ZEROPAGE")

// GLOBAL VARIABLES
unsigned char direction;
unsigned char direction_y;
unsigned char arg1;
unsigned char arg2;
unsigned char pad1;
unsigned char pad1_new;
unsigned char char_state;
unsigned char song;
unsigned char sound;

//player movement/display
unsigned int temp_x;
unsigned int temp_y;
unsigned int temp_sprite;
unsigned char old_x; //players last position (used for colision)
unsigned char old_y; //players last position (used for colision)

// collision
unsigned char eject_L;				 // from the left
unsigned char eject_R;				 // remember these from the collision sub routine
unsigned char eject_D;				 // from below
unsigned char eject_U;				 // from up
unsigned char collision_L;
unsigned char collision_R;
unsigned char collision_U;
unsigned char collision_D;
unsigned char coordinates;
unsigned int location_with_scroll;
unsigned char collision;

const unsigned char metatile_colision_map[] = {
		COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL,
		COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, 0, COL_ALL, COL_ALL,
		COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, 0, 0, 0, 0, 0, 0, 0,
		COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_LADDER, COL_LADDER_TOP, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 

//room loading
unsigned char nametable_to_load;
unsigned char level;
unsigned char offset;
int address;
unsigned char x; // room loader code
unsigned char y;
unsigned char nt;
unsigned char index;
unsigned char map;
unsigned int scroll_x;
unsigned int scroll_y;
unsigned char max_rooms;
unsigned int max_scroll;
unsigned char room_to_load = 0;
unsigned char temp_room;



#pragma bss-name(push, "BSS")
unsigned char c_map[240];
unsigned char c_map2[240]; // not used in this example

struct Hero
{
	unsigned int x; // low byte is sub-pixel
	unsigned int y;
	signed int vel_x; // speed, signed, low byte is sub-pixel
	signed int vel_y;
	unsigned char health;
};

struct Hero Player1 = {0x4000, 0x9400}; // starting position

struct Base
{
	unsigned char x;
	unsigned char y;
	unsigned char width;
	unsigned char height;
};

struct Base Generic;
struct Base Generic2;


#pragma bss-name(push, "XRAM")
// extra RAM at $6000-$7fff
unsigned char wram_array[0x2000];


