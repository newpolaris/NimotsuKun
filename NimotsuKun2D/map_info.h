#pragma once

struct map_info
{
	map_info() : block(false), wall(false), player(false), goal(false) {}

	void set_wall() { wall = true; }
	void set_block() { block = true; }	
	void set_player() { player = true; }	
	void set_goal() { goal = true; }

	void reset_wall() { wall = false; }
	void reset_block() { block = false; }	
	void reset_player() { player = false; }	
	void reset_goal() { goal = false; }

	bool block;
	bool wall;
	bool player;
	bool goal;
};

