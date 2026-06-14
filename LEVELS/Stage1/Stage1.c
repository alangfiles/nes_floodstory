#include "level0.c"


const unsigned char *const stage1_levels_list[] = {
	stage1_level0_0, 
	stage1_level0_1,
	stage1_level0_2,
	stage1_level0_3,
	stage1_level0_4,
	stage1_level0_5,
	stage1_level0_6,};

const unsigned char* stage1_levels[] = {
    stage1_level0_0,
    stage1_level0_1,
	stage1_level0_2,
	stage1_level0_3,
	stage1_level0_4,
	stage1_level0_5,
	stage1_level0_6,
	stage1_level0_7,
};

const unsigned char stage1_max_rooms[] = {1};

const unsigned char stage1_offsets[] = {0};

// Metatile data for Stage 1
const unsigned char stage1_metatiles[]={
	123, 124, 139, 140,  0,
	125, 126, 141, 142,  0,
	155, 156, 171, 172,  0,
	157, 158, 173, 174,  0,
	190, 175, 123, 124,  0,
	190, 190, 139, 140,  0,
	190, 191, 141, 142,  0,
	190, 190, 173, 174,  0,
	190, 185, 155, 156,  0,
	190, 190, 157, 158,  0,
	190, 187, 171, 172,  0,
	190, 175, 173, 174,  0,
	190, 189, 123, 124,  0,
	190, 189, 125, 126,  0,
	186, 191, 155, 156,  0,
	186, 184, 157, 158,  0,
	123, 174, 124, 123,  0,
	139, 140, 155, 156,  0,
	141, 142, 157, 158,  0,
	123, 124, 139, 1,  0,
	173, 142, 174, 1,  0,
	173, 1, 1, 1,  0,
	125, 126, 1, 1,  0,
	157, 158, 1, 1,  0,
	171, 172, 1, 1,  0,
	1, 123, 1, 1,  0,
	123, 173, 1, 174,  0,
	123, 124, 1, 123,  0,
	122, 124, 139, 140,  0,
	0, 0, 0, 122,  0,
	123, 106, 124, 123,  0,
	0, 0, 106, 0,  0,
	117, 118, 133, 134,  2,
	101, 102, 133, 134,  2,
	117, 118, 149, 150,  2,
	116, 118, 132, 134,  2,
	117, 119, 133, 135,  2,
	100, 102, 132, 134,  2,
	101, 103, 133, 135,  2,
	116, 118, 148, 150,  2,
	117, 119, 149, 151,  2,
	223, 223, 220, 205,  3,
	223, 206, 206, 219,  3,
	205, 206, 238, 238,  3,
	223, 207, 220, 204,  3,
	52, 207, 223, 51,  3,
	223, 207, 51, 207,  3,
	203, 206, 239, 238,  3,
	101, 102, 149, 150,  2,
	100, 102, 148, 150,  2,
	101, 103, 149, 151,  2,
	235, 235, 251, 252,  3,
	235, 234, 252, 251,  3,
	250, 235, 252, 252,  3,
	235, 236, 251, 252,  3,
	152, 153, 168, 169,  3,
	154, 152, 170, 168,  3,
	1, 1, 154, 152,  3,
	123, 139, 173, 155,  0,
	142, 123, 156, 174,  0,
	139, 124, 155, 173,  0,
	10, 11, 10, 11,  2,
	10, 11, 10, 11,  2,
	202, 202, 218, 218,  0,
	1, 1, 99, 115,  3,
	1, 1, 1, 99,  3,
	1, 1, 115, 1,  3,
	18, 19, 0, 0,  0,
	1, 1, 18, 19,  0,
	239, 159, 1, 1,  3,
	239, 239, 238, 239,  3,
	237, 237, 54, 55,  3,
	237, 56, 55, 0,  3,
	57, 237, 0, 57,  3,
	2, 13, 14, 2,  3,
	1, 1, 2, 2,  3,
	31, 2, 2, 47,  3,
	27, 12, 2, 1,  3,
	0, 0, 0, 0,  0,
	15, 63, 1, 2,  3,
	0, 0, 0, 0,  0,
	1, 1, 1, 1,  0,
	1, 1, 42, 1,  3,
	26, 1, 1, 42,  3,
	26, 1, 1, 1,  3,
	242, 242, 1, 1,  2,
	1, 243, 1, 1,  2,
	212, 1, 1, 1,  2,
	0, 0, 128, 129,  3,
	0, 0, 130, 130,  3,
	1, 42, 2, 2,  3,
	26, 1, 2, 2,  3,
	3, 170, 3, 232,  3,
	168, 169, 104, 252,  3,
	138, 3, 248, 3,  3,
	3, 3, 233, 3,  3,
	8, 25, 9, 24,  2,
	8, 25, 8, 24,  2,
	177, 178, 8, 24,  2,
	212, 176, 243, 192,  2,
	8, 25, 193, 194,  2,
	179, 243, 195, 212,  2,
	0, 0, 0, 240,  2,
	241, 0, 0, 0,  2,
	20, 4, 21, 4,  2,
	21, 4, 21, 5,  2,
	229, 230, 20, 4,  2,
	212, 228, 243, 244,  2,
	20, 4, 245, 246,  2,
	231, 243, 247, 212,  2,
	0, 226, 0, 0,  2,
	227, 0, 0, 0,  2,
	6, 23, 6, 23,  2,
	7, 22, 7, 23,  2,
	6, 23, 7, 23,  2,
	224, 225, 6, 22,  2,
	212, 208, 242, 242,  2,
	209, 243, 242, 242,  2,
	0, 0, 0, 210,  2,
	0, 0, 211, 0,  2,
	3, 3, 170, 170,  3,
	0, 0, 0, 0,  0,
	169, 169, 120, 105,  3,
	0, 0, 137, 0,  3,
	138, 0, 138, 0,  3,
	138, 0, 121, 0,  3,
	3, 3, 3, 249,  3,
	249, 233, 170, 170,  3,
	144, 144, 0, 0,  2,
	145, 146, 0, 0,  2,
	1, 1, 146, 146,  2,
	146, 144, 0, 0,  2,
	1, 1, 146, 144,  2,
	1, 146, 144, 0,  2,
	122, 50, 50, 223,  3,
	207, 137, 223, 207,  3,
	223, 51, 222, 223,  3,
	221, 207, 223, 52,  3,
	0, 0, 0, 0,  0,
	0, 0, 0, 122,  3,
	170, 168, 104, 105,  3,
	170, 168, 104, 104,  3,
	0, 0, 215, 167,  0,
	215, 167, 1, 1,  0,
	223, 207, 220, 219,  3,
	50, 51, 222, 223,  3,
	223, 53, 207, 221,  3,
	50, 52, 50, 51,  3,
	51, 53, 52, 53,  3,
	0, 122, 136, 223,  3,
	0, 136, 136, 207,  3,
	106, 0, 207, 106,  3,
	137, 0, 168, 137,  3,
	169, 106, 169, 170,  3,
	1, 255, 255, 0,  3,
	255, 1, 0, 254,  3,
	239, 239, 254, 253,  3,
	237, 238, 254, 255,  3,
	253, 254, 0, 0,  3,
	255, 253, 0, 0,  3,
	5, 3, 5, 3,  3,
	63, 3, 5, 3,  3,
	5, 3, 47, 3,  3,
	1, 31, 31, 2,  3,
	15, 2, 1, 15,  3,
	2, 47, 17, 17,  3,
	3, 3, 17, 17,  3,
	3, 97, 96, 3,  3,
	3, 98, 3, 3,  3,
	3, 3, 97, 3,  3,
	96, 3, 3, 3,  3,
	3, 3, 114, 3,  3,
	0, 0, 0, 113,  3,
	0, 0, 0, 112,  3,
	200, 1, 1, 1,  1,
	200, 201, 1, 217,  1,
	3, 3, 3, 3,  3,
	0, 0, 0, 0,  0,
	0, 0, 0, 0,  0,
	63, 3, 2, 63,  3,
	1, 1, 13, 1,  3,
	3, 14, 3, 3,  3,
	161, 3, 3, 3,  3,
	3, 3, 162, 3,  3,
	162, 3, 3, 161,  3,
	160, 3, 3, 161,  3,
	131, 3, 3, 131,  3,
	131, 147, 3, 3,  3,
	131, 3, 3, 147,  3,
	3, 3, 131, 3,  3,
	131, 3, 3, 3,  3,
	201, 217, 216, 1,  1,
	181, 182, 197, 198,  2,
	1, 180, 1, 196,  2,
	183, 1, 199, 1,  2,
	1, 1, 165, 166,  2,
	213, 214, 1, 1,  2,
	0, 0, 107, 107,  0,
	0, 0, 0, 0,  1,
	16, 16, 1, 1,  0,
	1, 159, 1, 1,  0,
	200, 201, 216, 217,  1,
	1, 1, 216, 217,  1,
	200, 1, 216, 217,  1,
	1, 201, 216, 217,  1,
	1, 1, 216, 1,  1,
	1, 1, 1, 217,  1,
	1, 217, 1, 1,  1,
	0, 94, 108, 3,  0,
	0, 0, 107, 108,  0,
	107, 94, 3, 109,  0,
	107, 94, 109, 93,  0,
	109, 3, 3, 109,  0,
	109, 109, 3, 3,  0,
	109, 3, 3, 3,  0,
	109, 64, 109, 64,  0,
	64, 110, 111, 64,  0,
	109, 20, 3, 111,  0,
	64, 110, 64, 64,  0,
	110, 110, 64, 110,  0,
	0, 0, 30, 30,  1,
	0, 0, 0, 28,  1,
	0, 0, 29, 0,  1,
	109, 109, 163, 164,  0,
	93, 91, 64, 159,  0,
	92, 128, 159, 1,  0,
	0, 0, 91, 92,  0,
	95, 0, 159, 95,  0,
	91, 92, 159, 1,  0,
	107, 108, 1, 163,  0,
	109, 3, 164, 3,  0,
	163, 164, 159, 159,  0,
	3, 109, 164, 3,  0,
	159, 159, 159, 159,  0,
	1, 1, 159, 159,  0,
	159, 1, 159, 159,  0,
	110, 159, 110, 143,  0,
	143, 127, 110, 110,  0,
	159, 159, 143, 127,  0,
	127, 159, 110, 143,  0,
};

const unsigned char stage1_metatile_colision_map[] = {
		COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL,
		COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, 0, COL_ALL, COL_ALL,
		COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, 0, 0, 0, 0, 0, 0, 0,
		COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_ALL, COL_LADDER, COL_LADDER_TOP, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, COL_ALL, COL_ALL, COL_ALL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

const unsigned char starting_x_place[] = {30};
const unsigned char starting_y_place[] = {160};

enum {
    STAGE1_ENEMY_TYPE1,
};

enum {
    STAGE1_ENTITY_TYPE1,
};

#define LEVEL_BOTTOM 230
#define LEVEL_TOP 0

const unsigned char stage1_level_0_enemies[] = {
    TURN_OFF};

const unsigned char *const stage1_Enemy_list[] = {
    stage1_level_0_enemies};

// y, room, x, type
const unsigned char stage1_level_0_entities[] = {
	LEVEL_BOTTOM, 2, 0, ENTITY_PIT_WIDE_64, // Pit 1
	LEVEL_BOTTOM, 4, 0, ENTITY_PIT_WIDE_64, // Pit 2
	LEVEL_BOTTOM, 5, 95, ENTITY_PIT_WIDE_64, // Pit 3
	LEVEL_BOTTOM, 5, 175, ENTITY_PIT_WIDE_64, // Pit 4
	LEVEL_BOTTOM, 6, 159, ENTITY_PIT_WIDE_64, // Pit 5
	LEVEL_TOP, 7, 160, ENTITY_LEVEL_UP, // Level Up
	LEVEL_TOP, 8, 48, ENTITY_LEVEL_UP, // Level Up
	LEVEL_BOTTOM, 8, 160, ENTITY_LEVEL_DOWN, // Level Down
	LEVEL_BOTTOM, 9, 0, ENTITY_LEVEL_DOWN, // Level Down
	LEVEL_BOTTOM, 9, 16, ENTITY_LEVEL_DOWN, // Level Down
	LEVEL_BOTTOM, 9, 32, ENTITY_LEVEL_DOWN, // Level Down
	LEVEL_BOTTOM, 9, 48, ENTITY_LEVEL_DOWN, // Level Down
	LEVEL_BOTTOM, 10, 0, ENTITY_SPIKE_WIDE_64, // Spike
	LEVEL_BOTTOM, 10, 64, ENTITY_SPIKE_WIDE_64, // Spike
	LEVEL_BOTTOM, 10, 128, ENTITY_SPIKE_WIDE_64, // Spike
	LEVEL_BOTTOM, 10, 192, ENTITY_SPIKE_WIDE_64, // Spike
	LEVEL_BOTTOM, 11, 0, ENTITY_SPIKE_WIDE_64, // Spike
	LEVEL_BOTTOM, 11, 144, ENTITY_SPIKE_WIDE_64, // Spike
	LEVEL_BOTTOM, 12, 16, ENTITY_SPIKE_WIDE_64, // Spike
	LEVEL_BOTTOM, 11, 208, ENTITY_SPIKE_WIDE_64, // Spike
	LEVEL_BOTTOM, 12, 176, ENTITY_LEVEL_UP, // Level Up
	LEVEL_BOTTOM, 12, 192, ENTITY_LEVEL_UP, // Level Up
	LEVEL_BOTTOM, 12, 208, ENTITY_LEVEL_UP, // Level Up
	LEVEL_BOTTOM, 12, 224, ENTITY_LEVEL_UP, // Level Up
	LEVEL_BOTTOM, 12, 240, ENTITY_LEVEL_UP, // Level Up
	LEVEL_TOP, 13, 176, ENTITY_LEVEL_DOWN, // Level Down
	LEVEL_BOTTOM, 13, 48, ENTITY_LEVEL_UP, // Level Up
	LEVEL_TOP, 14, 48, ENTITY_LEVEL_DOWN, // Level Down
	LEVEL_TOP, 18, 192, ENTITY_LEVEL_UP, // Level Up
	LEVEL_TOP, 19, 48, ENTITY_LEVEL_UP, // Level Up
	LEVEL_BOTTOM, 19, 192, ENTITY_LEVEL_DOWN, // Level Down
	LEVEL_BOTTOM, 20, 48, ENTITY_LEVEL_DOWN, // Level Down
	TURN_OFF
};

const unsigned char *const stage1_entity_list[] = {
    stage1_level_0_entities};
