#include <vector>

#include "Object.h"
#include "Array2D.h"
#include "image.h"
#include "Sequence.h"
#include "file.h"

struct point;

class State : public Sequence
{
private:
	int mMoveCount;
	point mSize;
	point player_position;
	std::vector<point> goal_position;
	bool bPlayerWantToQuit;

	const Image game_obj_image;
    Array2D<Object> map;
	buffer_type mStageData;

public:
    static State* initalizeWithStage(int stage);
	void update();
	void draw() const;
	void reset();

private:
	State(buffer_type& stageData);
	bool game_update();
	bool is_finished() const;
    int num_of_finished_box() const;
	int frameRate() const;
};


