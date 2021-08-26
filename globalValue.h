#pragma once

const int SUBWINSIZEX = 450;
const int SUBWINSIZEY = 550;

const int TILE_NUM_X = 30; 
const int TILE_NUM_Y = 20;

const int TILE_SIZE_X = 64;
const int TILE_SIZE_Y = 64;

const int CAMERA_MOVE_X = 37;
const int CAMERA_MOVE_Y = 37;

const int MAP_SIZE_X = TILE_NUM_X * TILE_SIZE_X;
const int MAP_SIZE_Y = TILE_NUM_Y * TILE_SIZE_Y;

const int CAMERA_SIZE_X = WINSIZEX;
const int CAMERA_SIZE_Y = WINSIZEY;

const int SAMPLE_TILE_X = 8;
const int SAMPLE_TILE_Y = 4;

struct tagSampleTile
{
	RECT rcTile;
	Vec2 frame;
};