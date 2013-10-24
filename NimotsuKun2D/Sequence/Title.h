#pragma once

#include "Sequence.h"
#include "image.h"

class Title : public Sequence
{
public:
	Title() : titleImage("data/image/title.dds") {}

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
