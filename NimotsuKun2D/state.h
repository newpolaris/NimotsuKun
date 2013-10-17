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
	};

    enum GameState {
        S_INPUT,
        S_ANIM,
        S_ANIM_FINISH,
        S_DET,
        S_FINISH
    };

    struct Anim
    {
        Anim(ImageID id, point before, point after)
            : m_id(id), m_before(before), m_after(after) {}

        ImageID m_id;
        point m_before;
        point m_after;
    };

	point player_position;
	std::vector<point> goal_position;
	bool bPlayerWantToQuit;

	const Image game_obj_image;
    Array2D<map_info> map;
    std::vector<Anim> anim_false;
    std::vector<Anim> anim_true;

public:
    static state* initalize_state();
	bool update();
	bool is_finished() const;

private:
	state(unsigned* map_data, unsigned x, unsigned y);
	point getInput();
	bool update(point direction);
    bool drawAnimation();
	void draw(Array2D<map_info>& map) const;
	void drawCell(int x, int y, ImageID id) const;
	void drawCell(int dst_x, int dst_y, ImageID id, float perX, float perY) const;
    int num_of_finished_box() const;
};

