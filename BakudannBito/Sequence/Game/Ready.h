#pragma once

#include "image.h"

namespace Sequence {
namespace Game {
class Parent;

class Ready
{
public:
    Ready();
    void update(Parent*);

private:
	void draw(Parent* parent) const;

	Image mImage;
};

} // namespace Game
} // namespace Sequence
