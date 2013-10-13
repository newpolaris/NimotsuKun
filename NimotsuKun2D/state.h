#include <vector>

#include "map_info.h"
#include "Array2D.h"
#include "image.h"

struct point;

class state
{
private:
	enum ImageID {
		IMAGE_ID_PLAYER,
		IMAGE_ID_WALL,
		IMAGE_ID_BLOCK,
		IMAGE_ID_GOAL,
		IMAGE_ID_SPACE,
            //
		IMAGE_ID_BLOCK_ON_GOAL,
		IMAGE_ID_PLAYER_ON_GOAL
	};

	point player_position;
	std::vector<point> block_position;
	std::vector<point> goal_position;
	bool bPlayerWantToQuit;

	const Image game_obj_image;
    Array2D<map_info> map;

public:
    static state* initalize_state();
	void draw() const;
	bool update(int ch);
	bool is_finished() const;

private:
	state(unsigned* map_data, unsigned x, unsigned y);
	ImageID id(int x, int y) const;
	point convert(int ch);

	void drawCell(int x, int y, ImageID id) const;
    int num_of_finished_box() const;
};


