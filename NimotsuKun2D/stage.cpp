#include <cassert>

#include "stage.h"
#include "image.h"
#include "GameLib\Framework.h"

stage::stage(BYTE* map_data)
    : map(MAP_SIZE_X*MAP_SIZE_Y)
    , game_obj_image("nimotsuKunImage.dds")
{
    for (int i=0; i < map.size(); i++)
    {
        switch (map_data[i])
        {
            case '#':
                map[i].set_wall();
                break;
            case 'P':
                map[i].set_player();
                break;
            case '.':
                map[i].set_goal();
                break;
            case 'B':
                map[i].set_block();
                break;
        }
    }
}

point get_src_pos(stage::ImageID id) 
{
	switch (id)
	{
	case stage::IMAGE_ID_BLOCK:
		return point(2,0);
	case stage::IMAGE_ID_BLOCK_ON_GOAL:
		return point(3,0);
	case stage::IMAGE_ID_GOAL:
		return point(4,0);
	case stage::IMAGE_ID_PLAYER:
		return point(0,0);
	case stage::IMAGE_ID_PLAYER_ON_GOAL:
		return point(4,0);
	case stage::IMAGE_ID_SPACE:
		return point(5,0);
	case stage::IMAGE_ID_WALL:
		return point(1,0);
	default:
		return point(0,0);
	}
}

void stage::drawCell(int dst_x, int dst_y, ImageID id) const
{
	static const size_t cell_size = 32;

    unsigned* vram = GameLib::Framework::instance().videoMemory();
    unsigned windowWidth = GameLib::Framework::instance().width();
	unsigned imageWidth = game_obj_image.width();

	unsigned src_x = get_src_pos(id).x;
	unsigned src_y = get_src_pos(id).y; 

    for (int i=0; i < cell_size; ++i)
    for (int j=0; j < cell_size; ++j)
	{
		size_t dst_pos = (dst_y*cell_size+i)*windowWidth+(dst_x*cell_size+j);
		size_t src_pos = (src_y*cell_size+i)*imageWidth +(src_x*cell_size+j);

        vram[dst_pos] = game_obj_image[src_pos];
	}
}

void stage::draw() const
{
    for (int y=0; y < MAP_SIZE_Y; y++)
    for (int x=0; x < MAP_SIZE_X; x++)
       drawCell(x, y, id(x,y));
}

stage::ImageID stage::id(int x, int y) const
{
	assert(x >= 0 || x < MAP_SIZE_X);
	assert(y >= 0 || y < MAP_SIZE_Y);

	const map_info& info = operator()(x, y);

	if (info.wall)
	{
		return IMAGE_ID_WALL;
	}
	else if (info.block)
	{
		if (info.goal)
			return IMAGE_ID_BLOCK_ON_GOAL;
		else 
			return IMAGE_ID_BLOCK;
	}
	else if (info.player)
	{
		if (info.goal)
			return IMAGE_ID_PLAYER_ON_GOAL;
		else
			return IMAGE_ID_PLAYER;
	}
	else
	{
		if (info.goal)
			return IMAGE_ID_GOAL;
		else
			return IMAGE_ID_SPACE;
	}
}
