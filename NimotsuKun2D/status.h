#include <vector>

#include "point.h"
#include "stage.h"

struct game_status;
game_status* initalize_game_status();

struct game_status
{
	point player_position;
	std::vector<point> block_position;
	std::vector<point> goal_position;
	stage stage;
	bool bPlayerWantToQuit;

	// initailize game status using game map
	game_status(BYTE* map)
		: stage(map), bPlayerWantToQuit(false)
	{
		for (int y = 0; y < stage::MAP_SIZE_Y; y++)
		for (int x = 0; x < stage::MAP_SIZE_X; x++)
		{
			if (stage(x,y).player)
				player_position = point(x,y);

			if (stage(x,y).block)
				block_position.push_back(point(x,y));

			if (stage(x,y).goal)
				goal_position.push_back(point(x,y));
		}
	}

	point convert(int ch)
	{
		switch(ch)
		{
		case 'w':
			return point(0,-1);
		case 'a':
			return point(-1,0);
		case 's':
			return point(0,+1);
		case 'd':
			return point(+1,0);
		default:
			return point(0,0);
		}

	}

	bool update(int ch);

	int num_of_finished_box() const
	{
		int count = 0;
		for (auto it = goal_position.begin(); it != goal_position.end(); ++it)
		{
			if (stage(*it).block) 
				count++;
		}
		return count;
	}

	bool is_finished() const
	{
		return goal_position.size() == num_of_finished_box()
			|| bPlayerWantToQuit;
	}
};

