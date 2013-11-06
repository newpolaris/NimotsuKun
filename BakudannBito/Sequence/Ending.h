#pragma once

#include "image.h"

namespace Sequence {
class GameInstance;

class Ending
{
public:
    Ending();
    void update(GameInstance*);

private:
	Image mImage;
};

} // namespace Sequence 
