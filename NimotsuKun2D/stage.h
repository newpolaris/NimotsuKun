#pragma once

#include "types.h"
#include "point.h"
#include "image.h"
#include "Array2D.h"

struct stage 
{
	static const int MAP_SIZE_X = 8;
	static const int MAP_SIZE_Y = 5;

	enum ImageID {
		IMAGE_ID_PLAYER,
		IMAGE_ID_WALL,
		IMAGE_ID_BLOCK,
		IMAGE_ID_BLOCK_ON_GOAL,
		IMAGE_ID_GOAL,
		IMAGE_ID_PLAYER_ON_GOAL,
		IMAGE_ID_SPACE
	};

    stage(BYTE* map_data);

    map_info& operator()(point p) 
    {   return map(p.x, p.y); }

    const map_info& operator()(point p) const
    {   return map(p.x, p.y); }

    const map_info& operator()(int x, int y) const
    {    return map(x, y); }

	ImageID id(int x, int y) const;
	void drawCell(int x, int y, ImageID id) const;
	void draw() const;

	const Image game_obj_image;
    Array2D map;
};

