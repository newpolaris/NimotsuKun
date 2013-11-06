#pragma once

#include "image.h"

namespace Sequence {
namespace SoloGame {
class Parent;

class Play
{
public:
    Play();
    void update(Parent*);
private:
	Image mImage;
};

} // namespace SoloGame
} // namespace Sequence
