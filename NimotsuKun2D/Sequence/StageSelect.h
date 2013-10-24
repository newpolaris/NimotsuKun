#pragma once

#include "Sequence.h"
#include "image.h"

class StageSelect : public Sequence
{
public:
	StageSelect() : image("data/image/stageSelect.dds") {}

	void update()
	{
		draw();
		input();
	}

private:
	void input();
	void draw();

	Image image;
};
