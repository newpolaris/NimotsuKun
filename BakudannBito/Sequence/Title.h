#pragma once

#include "image.h"

namespace Sequence {
class GameInstance;

class Title
{
public:
	Title() : image("data/image/dummy.dds") {}
	void update(GameInstance*);

private:
	Image image;
};

} // namespace Sequence
