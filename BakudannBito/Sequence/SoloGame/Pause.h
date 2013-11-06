#pragma once

#include "image.h"

namespace Sequence {
namespace SoloGame {
class Parent;

class Pause
{
public:
    Pause();
    void update(Parent*);
private:
	Image mImage;
};

} // namespace SoloGame
} // namespace Sequence
