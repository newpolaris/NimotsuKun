#include <vector>

#include "Object.h"
#include "Array2D.h"
#include "image.h"

struct point;

class state
{
private:
	bool m_bAnimation;
	int mMoveCount;
	point player_position;
	std::vector<point> goal_position;
	bool bPlayerWantToQuit;

	const Image game_obj_image;
    Array2D<Object> map;

public:
    static state* initalize_state();
	bool update();
	void draw() const;
	bool is_finished() const;

private:
	state(unsigned* map_data, unsigned x, unsigned y);
    int num_of_finished_box() const;
	int frameRate() const;
};


