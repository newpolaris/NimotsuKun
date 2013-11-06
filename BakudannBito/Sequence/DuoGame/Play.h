#pragma once

#include "image.h"

namespace Sequence {
namespace DuoGame {

class Parent;

class Play
{
public:
    Play();
    void update(Parent*);
private:
	Image mImage;
};

} // namespace DuoGame
} // namespace Sequence

