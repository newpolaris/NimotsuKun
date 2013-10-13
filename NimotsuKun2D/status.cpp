#include <vector>
#include <fstream>
#include <cassert>

#include "status.h"
#include "image.h"
#include "GameLib\Framework.h"

game_status* initalize_game_status()
{
	// load initial game status
	static BYTE game_status_map[game_status::MAP_SIZE_Y*game_status::MAP_SIZE_X] = { 
		'#','#','#','#','#','#','#','#',
		'#',' ','.','.',' ','P',' ','#',
		'#',' ','B','B',' ',' ',' ','#',
		'#',' ',' ',' ',' ',' ',' ','#',
		'#','#','#','#','#','#','#','#' };

    using GameLib::cout;
    using GameLib::endl;

    try {
        return new game_status(game_status_map);
    }
    catch (std::ifstream::failure e) {
        cout << "File Read Failure" << endl; 
		GameLib::Framework::instance().requestEnd();
        return nullptr;
    }
    catch (std::exception e) {
        cout << "Can't find file" << endl; 
        GameLib::Framework::instance().requestEnd();
        return nullptr;
    }
}

bool game_status::update(int ch)
{
	if (ch == 'q')
	{
		bPlayerWantToQuit = true;
		return true;
	}

	point next_player_position = convert(ch)+player_position;
	map_info info = map(next_player_position);

	if (info.wall)
	{
		return false;
	}
	else if (info.block)
	{
		point next_box_position = next_player_position+convert(ch);
		map_info next_block_info = map(next_box_position);

		if (next_block_info.block || next_block_info.wall)
		{
			return false;
		}
		else
		{
			// box move, player move			
			map(player_position).reset_player();
			map(next_player_position).set_player();
			player_position = next_player_position;
			map(next_player_position).reset_block();
			map(next_box_position).set_block();

			return true;
		}
	}
	// player move only.
	else
	{
		map(player_position).reset_player();
		map(next_player_position).set_player();
		player_position = next_player_position;
	}

	return true;
}

point get_src_pos(game_status::ImageID id) 
{
	switch (id)
	{
	case game_status::IMAGE_ID_BLOCK:
		return point(2,0);
	case game_status::IMAGE_ID_BLOCK_ON_GOAL:
		return point(5,0);
	case game_status::IMAGE_ID_GOAL:
		return point(3,0);
	case game_status::IMAGE_ID_PLAYER:
		return point(0,0);
	case game_status::IMAGE_ID_PLAYER_ON_GOAL:
		return point(4,0);
	case game_status::IMAGE_ID_SPACE:
		return point(4,0);
	case game_status::IMAGE_ID_WALL:
		return point(1,0);
	default:
		return point(0,0);
	}
}

void game_status::drawCell(int dst_x, int dst_y, ImageID id) const
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

#if 1
        unsigned src = game_obj_image[src_pos];
		unsigned dst = vram[dst_pos];

		unsigned char sa = src >> 24;
		unsigned char sr = (src & 0x00ff0000) >> 16;
		unsigned char sg = (src & 0x0000ff00) >> 8;
		unsigned char sb = src & 0x000000ff;

		unsigned char da = dst >> 24;
		unsigned char dr = (dst & 0x00ff0000) >> 16;
		unsigned char dg = (dst & 0x0000ff00) >> 8;
		unsigned char db = dst & 0x000000ff;

		dr = (sr*sa+dr*(0xff-sa)) >> 8;
		dg = (sg*sa+dg*(0xff-sa)) >> 8;
		db = (sb*sa+db*(0xff-sa)) >> 8;
		da = 0xff; 

		vram[dst_pos] = da<<24|dr<<16|dg<<8|db;
#else
		vram[dst_pos] = game_obj_image[src_pos];
#endif
	}
}

void game_status::draw() const
{
    for (int y=0; y < MAP_SIZE_Y; y++)
    for (int x=0; x < MAP_SIZE_X; x++)
	{
		ImageID image_id = id(x,y);

		if (image_id == IMAGE_ID_WALL) 
			drawCell(x, y, IMAGE_ID_WALL);
		else
		{
			drawCell(x, y, IMAGE_ID_SPACE);
			if (image_id == IMAGE_ID_BLOCK_ON_GOAL)
			{
				drawCell(x, y, IMAGE_ID_GOAL);
				drawCell(x, y, IMAGE_ID_BLOCK);
			}
			else if (image_id == IMAGE_ID_PLAYER_ON_GOAL)
			{
				drawCell(x, y, IMAGE_ID_GOAL);
				drawCell(x, y, IMAGE_ID_PLAYER);
			}
			else if (image_id != IMAGE_ID_SPACE)
			{
				drawCell(x, y, image_id);
			}
		}
	}
}

game_status::ImageID game_status::id(int x, int y) const
{
	assert(x >= 0 || x < MAP_SIZE_X);
	assert(y >= 0 || y < MAP_SIZE_Y);

	const map_info& info = map(x, y);

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
