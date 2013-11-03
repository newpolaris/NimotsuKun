#pragma once

#include "Sequence.h"
#include "image.h"

class Clear : public Sequence
{
public:
	Clear();
	void update()
	{
		draw();
		input();
	}

private:
	void input();
	void draw();

	int m_startTime;
	Image image;
};
