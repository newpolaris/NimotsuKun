#include <vector>

#include "Object.h"
#include "Array2D.h"
#include "image.h"

struct point;

class Game
{
private:
	int mMoveCount;
	point player_position;
	std::vector<point> goal_position;
	bool bPlayerWantToQuit;

	const Image game_obj_image;
    Array2D<Object> map;

public:
    static Game* initalize_Game();
	void update();
	bool is_finished() const;

private:
	Game(char* map_data, unsigned x, unsigned y);
	bool game_update();
	void draw() const;
    int num_of_finished_box() const;
	int frameRate() const;
};


