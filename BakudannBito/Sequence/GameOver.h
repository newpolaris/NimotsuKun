#pragma once

#include "image.h"

namespace Sequence {
class GameInstance;

class GameOver 
{
public:
    GameOver();
    void update(GameInstance*);

private:
	Image mImage;
};

} // namespace Sequence 
