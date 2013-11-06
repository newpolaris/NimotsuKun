#pragma once

#include "image.h"

namespace Sequence {
namespace DuoGame {
class Parent;

class DisplayResult
{
public:
    DisplayResult();
    void update(Parent*);
private:
	Image mImage;
};

} // namespace DuoGame
} // namespace Sequence
