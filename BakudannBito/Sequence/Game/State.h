#pragma once

#include <vector>

#include "Object.h"
#include "Array2D.h"
#include "image.h"
#include "file.h"
#include "Parent.h"

struct point;

class State
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
	void update(point);
	void draw() const;
    bool hasCleared() const;
	void reset();

private:
	State(buffer_type& stageData);
    int num_of_finished_box() const;
	int frameRate() const;
};


