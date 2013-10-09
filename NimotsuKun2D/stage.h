#pragma once

#include <vector>

#include "types.h"
#include "point.h"
#include "map_info.h"
#include "image.h"

struct stage 
{
	enum ImageID {
		IMAGE_ID_PLAYER,
		IMAGE_ID_WALL,
		IMAGE_ID_BLOCK,
		IMAGE_ID_BLOCK_ON_GOAL,
		IMAGE_ID_GOAL,
		IMAGE_ID_PLAYER_ON_GOAL,
		IMAGE_ID_SPACE
	};

	static const int MAP_SIZE_X = 8;
	static const int MAP_SIZE_Y = 5;

    stage(BYTE* map_data);
	const map_info& operator()(int x, int y) const
	{
		return map[y*MAP_SIZE_X+x];
	}

	map_info& operator()(int x, int y) 
	{
		return map[y*MAP_SIZE_X+x];
	}

	map_info& operator()(const point& po) 
	{
		return operator()(po.x, po.y);
	}

	const map_info& operator()(const point& po) const
	{
		return operator()(po.x, po.y);
	}

	ImageID id(int x, int y) const;
	void drawCell(int x, int y, ImageID id) const;
	void draw() const;

	const Image game_obj_image;

	std::vector<map_info> map; 
};

