#pragma once

#include "image.h"

namespace Sequence {
namespace DuoGame {
class Parent;

class Pause
{
public:
    Pause();
    void update(Parent*);
private:
	Image mImage;
};

} // namespace DuoGame
} // namespace Sequence


