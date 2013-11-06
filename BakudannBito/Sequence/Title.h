#pragma once

#include <string>
#include <vector>

#include "image.h"

namespace Sequence {
class GameInstance;

class Title
{
public:
	Title();
	void update(GameInstance*);

private:
	Image mImage;
	std::vector<std::string> m_menu;
};

} // namespace Sequence
