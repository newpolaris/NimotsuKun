#pragma once

#include "image.h"

namespace Sequence {
namespace DuoGame {
class Parent;

class Ready
{
public:
    Ready();
    void update(Parent*);
private:
	Image mImage;
};

} // namespace DuoGame
} // namespace Sequence
