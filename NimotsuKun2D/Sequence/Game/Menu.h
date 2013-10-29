#pragma once

#include "Sequence.h"
#include "image.h"

class Menu : public Sequence
{
public:
	Menu() : titleImage("data/image/menu.dds") {}

	void update()
	{
		draw();
		input();
	}

private:
	void input();
	void draw();

	Image titleImage;
};
