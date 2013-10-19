#include <vector>

#include "Object.h"
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
	};

	point player_position;
	std::vector<point> goal_position;
	bool bPlayerWantToQuit;

	const Image game_obj_image;
    Array2D<Object> map;

public:
    static state* initalize_state();
	void draw() const;
	bool update();
	bool is_finished() const;

private:
	state(unsigned* map_data, unsigned x, unsigned y);
	void drawCell(int x, int y, ImageID id) const;
    int num_of_finished_box() const;
};


