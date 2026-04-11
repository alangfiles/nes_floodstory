// Animation sprite data pulled from nes_bible_demo
// Standing animations
const unsigned char animate_playerstandleft_data[] = {
	- 4,- 2,0x00,0,
	  4,- 2,0x01,0,
	- 4,  6,0x10,0,
	  4,  6,0x11,0,

	- 4, 14,0x20,0,
	  4, 14,0x21,0,
	  0,- 1,0x0b,2,
	0x80
};

const unsigned char animate_playerstandright_data[] = {
	  5,- 2,0x00,0|OAM_FLIP_H,
	- 3,- 2,0x01,0|OAM_FLIP_H,
	  5,  6,0x10,0|OAM_FLIP_H,
	- 3,  6,0x11,0|OAM_FLIP_H,

	  5, 14,0x20,0|OAM_FLIP_H,
	- 3, 14,0x21,0|OAM_FLIP_H,
	  1,- 1,0x0b,2|OAM_FLIP_H,
	0x80
};

// Running animations - left
const unsigned char animate_playerrun1left_data[] = {
	 12, 15,0x46,0,
	- 4,- 2,0x1a,0,
	  4,- 2,0x1b,0,
	- 4,  6,0x32,0,

	  4,  6,0x33,0,
	- 4, 14,0x42,0,
	  4, 14,0x43,0,
	  0,  1,0x0b,2,
	0x80
};

const unsigned char animate_playerrun2left_data[] = {
	- 4,- 2,0x00,0,
	  4,- 2,0x01,0,
	- 4,  6,0x30,0,
	  4,  6,0x31,0,

	- 4, 14,0x40,0,
	  4, 14,0x41,0,
	  0,- 1,0x0b,2,
	0x80
};

const unsigned char animate_playerrun3left_data[] = {
	 12, 14,0x46,0,
	- 4,- 2,0x1a,0,
	  4,- 2,0x1b,0,
	- 4,  6,0x34,0,

	  4,  6,0x35,0,
	- 4, 14,0x44,0,
	  4, 14,0x45,0,
	  0,  1,0x0b,2,
	0x80
};

// Running animations - right
const unsigned char animate_playerrun1right_data[] = {
	  4,- 2,0x1a,0|OAM_FLIP_H,
	- 4,- 2,0x1b,0|OAM_FLIP_H,
	  4,  6,0x32,0|OAM_FLIP_H,
	- 4,  6,0x33,0|OAM_FLIP_H,

	  4, 14,0x42,0|OAM_FLIP_H,
	- 4, 14,0x43,0|OAM_FLIP_H,
	-12, 15,0x46,0|OAM_FLIP_H,
	  0,  1,0x0b,2|OAM_FLIP_H,
	0x80
};

const unsigned char animate_playerrun2right_data[] = {
	  4,- 2,0x00,0|OAM_FLIP_H,
	- 4,- 2,0x01,0|OAM_FLIP_H,
	  4,  6,0x30,0|OAM_FLIP_H,
	- 4,  6,0x31,0|OAM_FLIP_H,

	  4, 14,0x40,0|OAM_FLIP_H,
	- 4, 14,0x41,0|OAM_FLIP_H,
	  0,- 1,0x0b,2|OAM_FLIP_H,
	0x80
};

const unsigned char animate_playerrun3right_data[] = {
	  4,- 2,0x1a,0|OAM_FLIP_H,
	- 4,- 2,0x1b,0|OAM_FLIP_H,
	  4,  6,0x34,0|OAM_FLIP_H,
	- 4,  6,0x35,0|OAM_FLIP_H,

	  4, 14,0x44,0|OAM_FLIP_H,
	- 4, 14,0x45,0|OAM_FLIP_H,
	-12, 14,0x46,0|OAM_FLIP_H,
	  0,  1,0x0b,2|OAM_FLIP_H,
	0x80
};

// Jumping animations - left
const unsigned char animate_playerjumpleft_data[] = {
	- 4,- 5,0x27,0,
	  4,- 5,0x28,0,
	- 4,  3,0x37,0,
	  4,  3,0x38,0,

	- 4, 11,0x47,0,
	  4, 11,0x48,0,
	  4, 19,0x58,0,
	  0,- 4,0x0b,2,
	0x80
};

// Jumping animations - right
const unsigned char animate_playerjumpright_data[] = {
	  4,- 5,0x27,0|OAM_FLIP_H,
	- 4,- 5,0x28,0|OAM_FLIP_H,
	  4,  3,0x37,0|OAM_FLIP_H,
	- 4,  3,0x38,0|OAM_FLIP_H,

	  4, 11,0x47,0|OAM_FLIP_H,
	- 4, 11,0x48,0|OAM_FLIP_H,
	- 4, 19,0x58,0|OAM_FLIP_H,
	  0,- 4,0x0b,2|OAM_FLIP_H,
	0x80
};

// Sliding animations
const unsigned char animate_slideleft_data[] = {
	- 1, 11,0x0d,0,
	  7, 11,0x0e,0,
	 15, 10,0x0f,0,
	 23, 11,0x0c,0,

	- 9, 19,0x1c,0,
	- 1, 19,0x1d,0,
	  7, 19,0x1e,0,
	 15, 18,0x1f,0,

	  0, 12,0x0b,2,
	0x80
};

const unsigned char animate_slideright_data[] = {
	  1, 11,0x0d,0|OAM_FLIP_H,
	- 7, 11,0x0e,0|OAM_FLIP_H,
	-15, 10,0x0f,0|OAM_FLIP_H,
	-23, 11,0x0c,0|OAM_FLIP_H,

	  9, 19,0x1c,0|OAM_FLIP_H,
	  1, 19,0x1d,0|OAM_FLIP_H,
	- 7, 19,0x1e,0|OAM_FLIP_H,
	-15, 18,0x1f,0|OAM_FLIP_H,

	  0, 12,0x0b,2|OAM_FLIP_H,
	0x80
};

// Ladder climbing animations
const unsigned char animate_playerclimb1_data[] = {
	  0, 11,0x04,0,
	  8, 11,0x03,0,
	  0, 19,0x14,0,
	  8, 19,0x13,0,

	  0, 27,0x22,0,
	  8, 27,0x25,0,
	0x80
};

const unsigned char animate_playerclimb2_data[] = {
	  0, 11,0x02,0,
	  8, 11,0x05,0,
	  0, 19,0x12,0,
	  8, 19,0x15,0,

	  0, 27,0x24,0,
	  8, 27,0x23,0,
	0x80
};

const unsigned char animate_laddertop_data[] = {
	  8, 19,0x57,0|OAM_FLIP_H,
	  0, 19,0x57,0,
	  0, 27,0x26,0,
	  8, 27,0x36,0,

	  0, 11,0x55,0,
	  8, 11,0x56,0,
	0x80
};

// Standing shooting animations
const unsigned char animate_playerstandshootleft_data[] = {
	- 4,- 2,0x00,0,
	  4,- 2,0x01,0,
	- 4,  6,0x09,0,
	  4,  6,0x11,0,

	- 4, 14,0x20,0,
	  4, 14,0x21,0,
	  0,- 1,0x0b,2,
	-12,  6,0x08,0,
	0x80
};

const unsigned char animate_playerstandshootright_data[] = {
	  4,- 2,0x00,0|OAM_FLIP_H,
	- 4,- 2,0x01,0|OAM_FLIP_H,
	  4,  6,0x09,0|OAM_FLIP_H,
	- 4,  6,0x11,0|OAM_FLIP_H,

	  4, 14,0x20,0|OAM_FLIP_H,
	- 4, 14,0x21,0|OAM_FLIP_H,
	  0,- 1,0x0b,2|OAM_FLIP_H,
	 12,  6,0x08,0|OAM_FLIP_H,
	0x80
};
