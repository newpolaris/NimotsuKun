#include <vector>

#include "point.h"
#include "map_info.h"
#include "Array2D.h"
#include "image.h"
#include "types.h"

struct game_status;
game_status* initalize_game_status();

struct game_status
{
    typedef map_info map_type;
	const Image game_obj_image;
    Array2D<map_type> map;

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

	point player_position;
	std::vector<point> block_position;
	std::vector<point> goal_position;
	bool bPlayerWantToQuit;

	// initailize game status using game map
	game_status(BYTE* map_data)
		: map(MAP_SIZE_X, MAP_SIZE_Y)
        , bPlayerWantToQuit(false)
        , game_obj_image("nimotsuKunImage2.dds")
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

		for (int y = 0; y < MAP_SIZE_Y; y++)
		for (int x = 0; x < MAP_SIZE_X; x++)
		{
			if (map(x,y).player)
				player_position = point(x,y);

			if (map(x,y).block)
				block_position.push_back(point(x,y));

			if (map(x,y).goal)
				goal_position.push_back(point(x,y));
		}
	}

	ImageID id(int x, int y) const;
	void drawCell(int x, int y, ImageID id) const;
	void draw() const;

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
			if (map(*it).block) 
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

