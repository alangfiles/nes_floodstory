// Animation sprite data pulled from nes_bible_demo
// Standing animations
const unsigned char animate_playerstandleft_data[] = {
	-2, -2, 0x00, 0,
	6, -2, 0x01, 0,
	-2, 6, 0x10, 0,
	6, 6, 0x11, 0,
	-2, 14, 0x20, 0,
	6, 14, 0x21, 0,
	2, -1, 0x0b, 2,
	0x80
};

const unsigned char animate_playerstandright_data[] = {
	6, -2, 0x00, 0 | OAM_FLIP_H,
	-2, -2, 0x01, 0 | OAM_FLIP_H,
	6, 6, 0x10, 0 | OAM_FLIP_H,
	-2, 6, 0x11, 0 | OAM_FLIP_H,
	6, 14, 0x20, 0 | OAM_FLIP_H,
	-2, 14, 0x21, 0 | OAM_FLIP_H,
	2, -1, 0x0b, 2 | OAM_FLIP_H,
	0x80
};

// Running animations - left
const unsigned char animate_playerrun1left_data[]={
	14,  14,0x46,0,
	-2,- 2,0x1a,0,
	6,- 2,0x1b,0,
	-2,  6,0x32,0,
	6,  6,0x33,0,
	-2,  14,0x42,0,
	6,  14,0x43,0,
	2,- 1,0x0b,2,
	0x80
};

const unsigned char animate_playerrun2left_data[]={
	-2,- 2,0x00,0,
	6,- 2,0x01,0,
	-2,  6,0x30,0,
	6,  6,0x31,0,
	-2,  14,0x40,0,
	6,  14,0x41,0,
	2,- 1,0x0b,2,
	0x80
};

const unsigned char animate_playerrun3left_data[]={
	14,  13,0x46,0,
	-2,- 2,0x1a,0,
	6,- 2,0x1b,0,
	-2,  6,0x34,0,
	6,  6,0x35,0,
	-2,  14,0x44,0,
	6,  14,0x45,0,
	2,- 1,0x0b,2,
	0x80
};

// Running animations - right
const unsigned char animate_playerrun1right_data[]={
	6,- 2,0x1a,0|OAM_FLIP_H,
	-2,- 2,0x1b,0|OAM_FLIP_H,
	6,  6,0x32,0|OAM_FLIP_H,
	-2,  6,0x33,0|OAM_FLIP_H,
	6,  14,0x42,0|OAM_FLIP_H,
	-2,  14,0x43,0|OAM_FLIP_H,
	- 10,  14,0x46,0|OAM_FLIP_H,
	2,- 1,0x0b,2|OAM_FLIP_H,
	0x80
};

const unsigned char animate_playerrun2right_data[]={
	6,- 2,0x00,0|OAM_FLIP_H,
	-2,- 2,0x01,0|OAM_FLIP_H,
	6,  6,0x30,0|OAM_FLIP_H,
	-2,  6,0x31,0|OAM_FLIP_H,
	6,  14,0x40,0|OAM_FLIP_H,
	-2,  14,0x41,0|OAM_FLIP_H,
	2,- 1,0x0b,2|OAM_FLIP_H,
	0x80
};

const unsigned char animate_playerrun3right_data[]={
	6,  13,0x46,0|OAM_FLIP_H,
	-2,- 2,0x1a,0,
	6,- 2,0x1b,0,
	6,  6,0x34,0|OAM_FLIP_H,
	-2,  6,0x35,0|OAM_FLIP_H,
	6,  14,0x44,0|OAM_FLIP_H,
	-2,  14,0x45,0|OAM_FLIP_H,
	2,- 1,0x0b,2|OAM_FLIP_H,
	0x80
};

// Jumping animations - left
const unsigned char animate_playerjumpleft_data[] = {
	-2, -2, 0x27, 0,
	6, -2, 0x28, 0,
	-2, 6, 0x37, 0,
	6, 6, 0x38, 0,
	-2, 14, 0x47, 0,
	6, 14, 0x48, 0,
	6, 22, 0x58, 0,
	2, -1, 0x0b, 2,
	0x80
};

// Jumping animations - right
const unsigned char animate_playerjumpright_data[] = {
	6, -2, 0x27, 0 | OAM_FLIP_H,
	-2, -2, 0x28, 0 | OAM_FLIP_H,
	6, 6, 0x37, 0 | OAM_FLIP_H,
	-2, 6, 0x38, 0 | OAM_FLIP_H,
	6, 14, 0x47, 0 | OAM_FLIP_H,
	-2, 14, 0x48, 0 | OAM_FLIP_H,
	-2, 22, 0x58, 0 | OAM_FLIP_H,
	2, -1, 0x0b, 2 | OAM_FLIP_H,
	0x80
};

// Sliding animations
const unsigned char animate_slideleft_data[] = {
	-18, 19, 0xe6, 0,
	-10, 11, 0xa6, 0,
	-2, 11, 0xb6, 0,
	6, 12, 0xc6, 0,
	14, 13, 0xd6, 0,
	-10, 19, 0xf6, 0,
	-2, 19, 0x3e, 0,
	6, 20, 0x4e, 0,
	14, 21, 0x4f, 0,
	-9, 12, 0x0b, 2,
	0x80
};

const unsigned char animate_slideright_data[] = {
	22, 19, 0xe6, 0 | OAM_FLIP_H,
	14, 11, 0xa6, 0 | OAM_FLIP_H,
	6, 11, 0xb6, 0 | OAM_FLIP_H,
	-2, 12, 0xc6, 0 | OAM_FLIP_H,
	-10, 13, 0xd6, 0 | OAM_FLIP_H,
	14, 19, 0xf6, 0 | OAM_FLIP_H,
	6, 19, 0x3e, 0 | OAM_FLIP_H,
	-2, 20, 0x4e, 0 | OAM_FLIP_H,
	-10, 21, 0x4f, 0 | OAM_FLIP_H,
	13, 12, 0x0b, 2 | OAM_FLIP_H,
	0x80
};

// Ladder climbing animations
const unsigned char animate_playerclimb1_data[] = {
	-2, -2, 0x04, 0,
	6, -2, 0x03, 0,
	-2, 6, 0x14, 0,
	6, 6, 0x13, 0,
	-2, 14, 0x22, 0,
	6, 14, 0x25, 0,
	0x80
};

const unsigned char animate_playerclimb2_data[] = {
	-2, -2, 0x02, 0,
	6, -2, 0x05, 0,
	-2, 6, 0x12, 0,
	6, 6, 0x15, 0,
	-2, 14, 0x24, 0,
	6, 14, 0x23, 0,
	0x80
};

const unsigned char animate_laddertop_data[] = {
	-2, 6, 0x57, 0,
	6, 6, 0x57, 0 | OAM_FLIP_H,
	-2, 14, 0x26, 0,
	6, 14, 0x36, 0,
	-2, -2, 0x55, 0,
	6, -2, 0x56, 0,
	0x80
};

// Standing shooting animations
const unsigned char animate_playerstandshootleft_data[] = {
	-2, -2, 0x00, 0,
	6, -2, 0x01, 0,
	-2, 6, 0x09, 0,
	6, 6, 0x11, 0,
	-2, 14, 0x20, 0,
	6, 14, 0x21, 0,
	2, -1, 0x0b, 2,
	-10, 6, 0x08, 0,
	0x80
};

const unsigned char animate_playerstandshootright_data[] = {
	6, -2, 0x00, 0 | OAM_FLIP_H,
	-2, -2, 0x01, 0 | OAM_FLIP_H,
	6, 6, 0x09, 0 | OAM_FLIP_H,
	-2, 6, 0x11, 0 | OAM_FLIP_H,
	6, 14, 0x20, 0 | OAM_FLIP_H,
	-2, 14, 0x21, 0 | OAM_FLIP_H,
	2, -1, 0x0b, 2 | OAM_FLIP_H,
	14, 6, 0x08, 0 | OAM_FLIP_H,
	0x80
};
