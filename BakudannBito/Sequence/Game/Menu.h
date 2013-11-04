#pragma once

#include <string>
#include <vector>
#include "image.h"

namespace Sequence{
namespace Game{
class Parent;

class Menu
{
public:
    Menu();
	void update(Parent*);

private:
	void draw();
	Image image;

    std::vector<std::string> m_menu;
};

} // namespace Sequence
} // namespace Game
