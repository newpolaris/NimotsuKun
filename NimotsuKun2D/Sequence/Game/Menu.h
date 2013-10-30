#pragma once

#include "image.h"

namespace Sequence{
namespace Game{
class Parent;

class Menu
{
public:
	Menu() : image("data/image/menu.dds") {}
	void update(Parent*);

private:
	void draw();
	Image image;
};

} // namespace Sequence
} // namespace Game