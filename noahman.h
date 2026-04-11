
// ENUMS/DEFINES
#define LEFT 0
#define RIGHT 1
#define DOWN 4
#define UP 3

// Game modes
enum
{
	MODE_TITLE,
	MODE_GAMEOVER,
	MODE_LEVEL_SELECT,
	MODE_GAME,
	MODE_PAUSE,
	MODE_GAME_OVER
};

enum 
{
	CHR_STAGE_1_CHARACTER_CHR,
	CHR_STAGE_1_BACKGROUND_CHR,
	CHR_STAGE_2_BACKGROUND_CHR2,
	CHR_STAGE_2_BACKGROUND_CHR,
	CHR_STAGE_3_BACKGROUND_CHR2,
	CHR_STAGE_3_BACKGROUND_CHR,
	CHR_STAGE_4_BACKGROUND_CHR2,
	CHR_STAGE_4_BACKGROUND_CHR,
	CHR_STAGE_5_BACKGROUND_CHR2,
	CHR_STAGE_5_BACKGROUND_CHR,
};

//MOVEMENT
#define ACCEL 30
#define SLIDE_ACCEL 40
#define LADDER_ACCEL 20
#define DECEL 50
#define HITSTUN_DECEL 45
#define MAX_SPEED 0x160
#define MAX_SLIDE_SPEED 0x180
#define MAX_LADDER_SPEED 0x100
#define JUMP_VEL -0x510
#define GRAVITY 0x3c

// PROJECTILES
#define MAX_PROJECTILES 3
#define PROJECTILE_COOLDOWN_FRAMES 10
#define PROJECTILE_SPEED 3
#define PROJECTILE_SPEED_WITH_SCROLL 5

// collision
#define COL_DOWN 0x80
#define COL_ALL 0x40
#define COL_LADDER 0x01
#define COL_LADDER_TOP 0x02
#define TURN_OFF 0xff

//SCROLL
#define MAX_RIGHT 0x9000
#define MAX_LEFT 0x5000


// player colision stuff
#define HERO_WIDTH 11
#define HERO_HEIGHT 20

//CHR switching counter
#define CHR_FRAME_THRESHOLD 25


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
unsigned char pad1_state;
unsigned char char_state;
unsigned char song;
unsigned char sound;
unsigned char game_mode;
unsigned char selected_stage;

unsigned char frame_counter;
unsigned char chr_frame_counter;
unsigned char chr_frame_state;

//player movement/display
unsigned int temp_x;
unsigned int temp_y;
unsigned int temp_sprite;
unsigned char old_x; //players last position (used for colision)
unsigned char old_y; //players last position (used for colision)

// player state variables
unsigned char player_in_air;
unsigned char player_is_sliding;
unsigned char player_is_running;
unsigned char player_on_ladder;
unsigned char player_on_ladder_pose;
unsigned char player_on_ladder_top;
unsigned char player_in_hitstun;
unsigned char falling_down;
unsigned char multi_jump;
unsigned char multi_jump_max;
unsigned char short_jump_count;
unsigned char player_shooting;
unsigned char projectile_cooldown;
unsigned char projectile_index;
unsigned char hit_direction;

// animation variables
unsigned char animation_frame_counter;
unsigned char current_animation_frame;
const unsigned char *current_animation_ptr;

// projectile arrays
unsigned char projectiles_list[] = {TURN_OFF, TURN_OFF, TURN_OFF, TURN_OFF};
unsigned char projectiles_x[] = {0, 0, 0, 0};
unsigned char projectiles_y[] = {0, 0, 0, 0};

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
unsigned char map_loaded;
unsigned char scrolling_direction;

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
// unsigned char level;
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
unsigned char current_stage = 0;
unsigned char current_level = 0;
unsigned char scroll_count;
unsigned int pseudo_scroll_x;




#pragma bss-name(push, "BSS")
unsigned char c_map[240];
unsigned char c_map2[240];
unsigned int temp1;
unsigned int temp2;
unsigned int temp3;
unsigned char l_scroll_frames;
unsigned char r_scroll_frames;

struct Hero
{
	unsigned int x; // low byte is sub-pixel
	unsigned int y;
	signed int vel_x; // speed, signed, low byte is sub-pixel
	signed int vel_y;
	unsigned char health;
	unsigned char on_ground;
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

// finished placing things in XRAM; restore previous bss section so later globals
// (and any other files that include this header) don't get placed in XRAM.
// #pragma bss-name(pop)


