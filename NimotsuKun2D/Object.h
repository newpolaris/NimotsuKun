#pragma once

#include "point.h"

struct Image;

class Object 
{
public:
	Object() : block(false), wall(false), player(false), goal(false) {}

	void set_wall() { wall = true; }
	void set_block() { block = true; }	
	void set_player() { player = true; }	
	void set_goal() { goal = true; }

	void reset_wall() { wall = false; }
	void reset_block() { block = false; }	
	void reset_player() { player = false; }	
	void reset_goal() { goal = false; }

    bool isBlock() const { return block; }
    bool isWall() const { return wall; }
    bool isPlayer() const { return player; }
    bool isGoal() const { return goal; }

    void drawForeground(unsigned x, unsigned y, const Image& image, int count) const;
    void drawBackground(unsigned x, unsigned y, const Image& image) const;
    void move(const point& dir);

private:
	enum ImageID {
		IMAGE_ID_PLAYER,
		IMAGE_ID_WALL,
		IMAGE_ID_BLOCK,
		IMAGE_ID_GOAL,
		IMAGE_ID_SPACE,
	};

    void drawCell(int dst_x, int dst_y, ImageID id, const Image& image, float fx=0.f, float fy=0.f) const;

    point mDir;

	bool block;
	bool wall;
	bool player;
	bool goal;
};

