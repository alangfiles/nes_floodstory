#include "level0.c"

const unsigned char *const stage3_levels_list[] = {
    level0_0};

const unsigned char stage3_max_rooms[] = {1};

const unsigned char stage3_offsets[] = {0};

// Palettes for Stage 3
const unsigned char palette_bg[16]={ 0x21,0x0f,0x00,0x10,0x21,0x0f,0x30,0x08,0x21,0x0f,0x17,0x06,0x21,0x0f,0x19,0x29 };

const unsigned char stage3_palette_sp[16]={
	0x21,0x17,0x24,0x36,
	0x21,0x05,0x16,0x37,
	0x21,0x0f,0x11,0x30,
	0x21,0x17,0x3d,0x37 };

// Metatile data for Stage 3 - placeholder
const unsigned char metatile[]={
	0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	0, 0, 0, 0, 0};

const unsigned char metatile_colision_map[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

const unsigned char starting_x_place[] = {30};
const unsigned char starting_y_place[] = {160};

enum {
    ENEMY_TYPE1,
};

enum {
    ENTITY_TYPE1,
};

#define LEVEL_BOTTOM 230
#define LEVEL_TOP 0

const unsigned char level_0_enemies[] = {
    TURN_OFF};

const unsigned char *const Enemy_list[] = {
    level_0_enemies};

const unsigned char level_0_entities[] = {
    TURN_OFF};

const unsigned char *const entity_list[] = {
    level_0_entities};
