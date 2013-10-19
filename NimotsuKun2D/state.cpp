#include <vector>
#include <fstream>
#include <cassert>

#include "state.h"
#include "point.h"
#include "GameLib\Framework.h"

state* state::initalize_state()
{
	static const int MAP_SIZE_X = 8;
	static const int MAP_SIZE_Y = 5;

	// load initial game status
	static unsigned state_map[MAP_SIZE_Y*MAP_SIZE_X] = { 
		'#','#','#','#','#','#','#','#',
		'#',' ','.','.',' ','P',' ','#',
		'#',' ','B','B',' ',' ',' ','#',
		'#',' ',' ',' ',' ',' ',' ','#',
		'#','#','#','#','#','#','#','#' };

    using GameLib::cout;
    using GameLib::endl;

    try {
        return new state(state_map, MAP_SIZE_X, MAP_SIZE_Y);
    }
    catch (std::ifstream::failure e) {
        cout << "File Read Failure" << endl; 
		GameLib::Framework::instance().requestEnd();
        return nullptr;
    }
    catch (std::exception e) {
        cout << "Can't find file" << endl; 
        GameLib::Framework::instance().requestEnd();
        return nullptr;
    }
}

state::state(unsigned* map_data, unsigned x, unsigned y)
    : map(x, y), game_obj_image("nimotsuKunImage2.dds")
{
    for (unsigned i=0; i < map.size(); i++) {
        switch (map_data[i]) {
            case '#': map[i].set_wall(); break;
            case 'P': map[i].set_player(); break;
            case '.': map[i].set_goal(); break;
            case 'B': map[i].set_block(); break;
        }
    }

    for (unsigned y = 0; y < map.size_y; y++)
	for (unsigned x = 0; x < map.size_x; x++)
    {
        if (map(x,y).player)
            player_position = point(x,y);

        if (map(x,y).goal)
            goal_position.push_back(point(x,y));
    }
}

// get input and analysis exit status
point state::getInput()
{
	GameLib::Framework f = GameLib::Framework::instance();

	int dx = 0;
	int dy = 0;

    if (f.isKeyOn('q'))
    {
		f.requestEnd();
        return point(0,0);
    }

	if (f.isKeyOn('a'))
		dx -= 1;
	else if (f.isKeyOn('w'))
		dy -= 1;
	else if (f.isKeyOn('d'))
		dx += 1;
	else if (f.isKeyOn('s'))
		dy += 1;

	static point prev = point(dx,dy);
	
	if (prev == point(dx,dy))
		return point(0,0);
	else
	{
		return prev=point(dx,dy);
	}
}

bool state::update(point direction)
{
    if (direction == point(0,0))
        return false;

	point next_player_position = direction+player_position;
	map_info info = map(next_player_position);

	if (info.wall) {
		anim_false.push_back(Anim(IMAGE_ID_PLAYER, player_position, next_player_position));
	} else if (info.block) {
		point next_box_position = next_player_position+direction;
		map_info next_block_info = map(next_box_position);

		if (next_block_info.block || next_block_info.wall) {
            anim_false.push_back(Anim(IMAGE_ID_PLAYER, player_position, next_player_position));
		} else {
			// box move, player move			
            anim_true.push_back(Anim(IMAGE_ID_PLAYER, player_position, next_player_position));
            anim_true.push_back(Anim(IMAGE_ID_BLOCK, next_player_position, next_box_position));

			map(player_position).reset_player();
			map(next_player_position).set_player();
			player_position = next_player_position;
			map(next_player_position).reset_block();
			map(next_box_position).set_block();
		}
	} else { // player move only.
        anim_true.push_back(Anim(IMAGE_ID_PLAYER, player_position, next_player_position));

		map(player_position).reset_player();
		map(next_player_position).set_player();
		player_position = next_player_position;
	}
    return true;
}

bool state::update()
{
    static GameState gamestate = S_INPUT;

    switch (gamestate) {
    case S_ANIM:
        if (drawAnimation())
            gamestate = S_DET;
        break;
    case S_DET:
        if (is_finished())
            gamestate = S_ANIM_FINISH;
        else
            gamestate = S_INPUT;
        break;
    case S_ANIM_FINISH:
        // if (drawAnimationEnd())
            gamestate = S_FINISH;
        break;
    case S_FINISH:
		GameLib::Framework::instance().requestEnd();
        break;
    case S_INPUT:
        if (update(getInput())) 
            gamestate = S_ANIM;
        else
            draw(map);
        break;
    }
	return true;
}

void state::drawCell(int dst_x, int dst_y, ImageID id, float perX, float perY) const
{
	static const size_t cell_size = 32;
    game_obj_image.draw(cell_size*dst_x+static_cast<int>(cell_size*perX),
                        cell_size*dst_y+static_cast<int>(cell_size*perY),
                        cell_size*id, 0,
                        cell_size, cell_size);
}

bool state::drawAnimation() 
{
    static bool isInit = false;
    static Array2D<map_info> background;
	static const int max = 128;
	static const int max_false = max/1.5;

    static int count;

    if (!isInit) {
        isInit = true;
        background = map;

        if (anim_true.size() > 0) {
            count = max;
            
            for (unsigned i = 0; i < anim_true.size(); ++i) {
                point p = anim_true[i].m_after;
                background(p).reset_player();
                background(p).reset_block();
            }
        } else {
            count = max_false;

            for (unsigned i = 0; i < anim_false.size(); ++i) {
                point p = anim_false[i].m_before;
                background(p).reset_player();
                background(p).reset_block();
            }
        }
	}

	if (isInit)
	{
        draw(background);
        if (anim_true.size() > 0) {
            for (unsigned i = 0; i < anim_true.size(); ++i) {
                point p = anim_true[i].m_before;
                point dist = anim_true[i].m_after - anim_true[i].m_before;
                drawCell(p.x, p.y, anim_true[i].m_id, 
						 (float)dist.x*(max-count)/max,
						 (float)dist.y*(max-count)/max);
            }
        } else {
            for (unsigned i = 0; i < anim_false.size(); ++i) {
                point p = anim_false[i].m_before;
                point dist = anim_false[i].m_after - anim_false[i].m_before;

				float ts = (float)(max_false-count)/max_false*3.1415*2;
				float fs = 0.15*std::sinf(ts);

                drawCell(p.x, p.y, anim_false[i].m_id, (float)dist.x*fs, (float)dist.y*fs);
            }
        }

        count--;            

        if (count <= 0) {
            isInit = false;
            anim_true.clear();
            anim_false.clear();

			return true;
        }
    }
	return false;
}

void state::draw(Array2D<map_info>& map) const
{
    for (unsigned y=0; y < map.size_y; y++) 
    for (unsigned x=0; x < map.size_x; x++) 
	{
        const map_info& info = map(x,y);

		if (info.wall) {
			drawCell(x, y, IMAGE_ID_WALL);
        } else {
			drawCell(x, y, IMAGE_ID_SPACE);

            if (info.goal)  drawCell(x, y, IMAGE_ID_GOAL);
            if (info.block) drawCell(x, y, IMAGE_ID_BLOCK);
			if (info.player) drawCell(x, y, IMAGE_ID_PLAYER);
		}
	}
}

int state::num_of_finished_box() const
{
    int count = 0;
    for (auto it = goal_position.begin(); it != goal_position.end(); ++it)
        if (map(*it).block) count++;
    return count;
}

bool state::is_finished() const
{
    return goal_position.size() == num_of_finished_box();
}
