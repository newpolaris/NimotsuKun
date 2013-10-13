#include <vector>

#include "point.h"
#include "map_info.h"
#include "Array2D.h"
#include "image.h"
#include "types.h"

class game_status
{
private:
    typedef map_info map_type;
	const Image game_obj_image;
    Array2D<map_type> map;

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

public:
    static game_status* initalize_game_status();
	// initailize game status using game map
	game_status(BYTE* map_data, unsigned x, unsigned y);
	ImageID id(int x, int y) const;
	point convert(int ch);
	void drawCell(int x, int y, ImageID id) const;
	void draw() const;
	bool update(int ch);
	point get_src_pos(ImageID id) const;
    int num_of_finished_box() const;
	bool is_finished() const
	{
		return goal_position.size() == num_of_finished_box()
			|| bPlayerWantToQuit;
	}
};

