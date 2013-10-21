#include "Object.h"
#include "image.h"

void Object::move(const point& move) 
{
	mDir = move;
}

void Object::drawBackground(unsigned x, unsigned y, const Image& game_obj_image) const
{
    if (isWall()) {
        drawCell(x, y, IMAGE_ID_WALL, game_obj_image);
    } else {
        drawCell(x, y, IMAGE_ID_SPACE, game_obj_image);

        if (isGoal())  drawCell(x, y, IMAGE_ID_GOAL, game_obj_image);
    }
}

void Object::drawForeground(unsigned x, unsigned y, const Image& game_obj_image, int count) const
{
    ImageID id = IMAGE_ID_SPACE;
    if (isBlock()) {
        id = IMAGE_ID_BLOCK;
    } else if (isPlayer()) {
        id = IMAGE_ID_PLAYER;
    }

    // next position is base.
    float fx = -(float)mDir.x*(500-count)/500;
    float fy = -(float)mDir.y*(500-count)/500;

    if (id != IMAGE_ID_SPACE) {
        drawCell(x, y, id, game_obj_image, fx, fy);
    }
}

void Object::drawCell(int dst_x, int dst_y, ImageID id, const Image& game_obj_image, float fx, float fy) const
{
    static const size_t cell_size = 32;

    int dx = static_cast<int>(cell_size*fx);
    int dy = static_cast<int>(cell_size*fy);

    game_obj_image.draw(cell_size*dst_x+dx, cell_size*dst_y+dy,
                        cell_size*id, 0,
                        cell_size, cell_size);
}

