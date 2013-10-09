#include <vector>
#include <fstream>

#include "status.h"
#include "image.h"
#include "GameLib\Framework.h"

game_status* initalize_game_status()
{
	// load initial game status
	static BYTE stage_map[stage::MAP_SIZE_Y*stage::MAP_SIZE_X] = { 
		'#','#','#','#','#','#','#','#',
		'#',' ','.','.',' ','P',' ','#',
		'#',' ','B','B',' ',' ',' ','#',
		'#',' ',' ',' ',' ',' ',' ','#',
		'#','#','#','#','#','#','#','#' };

    using GameLib::cout;
    using GameLib::endl;

    try {
        return new game_status(stage_map);
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
	map_info info = stage(next_player_position);

	if (info.wall)
	{
		return false;
	}
	else if (info.block)
	{
		point next_box_position = next_player_position+convert(ch);
		map_info next_block_info = stage(next_box_position);

		if (next_block_info.block || next_block_info.wall)
		{
			return false;
		}
		else
		{
			// box move, player move			
			stage(player_position).reset_player();
			stage(next_player_position).set_player();
			player_position = next_player_position;
			stage(next_player_position).reset_block();
			stage(next_box_position).set_block();

			return true;
		}
	}
	// player move only.
	else
	{
		stage(player_position).reset_player();
		stage(next_player_position).set_player();
		player_position = next_player_position;
	}

	return true;
}


void printImage(const Image& image)
{
	unsigned* vram = GameLib::Framework::instance().videoMemory();
	const unsigned screen_width  = GameLib::Framework::instance().width();
	const unsigned screen_height = GameLib::Framework::instance().height();
	
	for (int y = 0; y < image.m_height; ++y) 
	for (int x = 0; x < image.m_width;  ++x)
		vram[ y * screen_width + x ] = image(x,y);
}