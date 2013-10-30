#pragma once

#include "image.h"

namespace Sequence {
class GameInstance;

class StageSelect
{
public:
	StageSelect() : image("data/image/stageSelect.dds") {}
	void update(GameInstance* parent);

private:
	Image image;
};

} // namespace Sequence