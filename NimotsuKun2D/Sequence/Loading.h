#pragma once

#include "Sequence.h"
#include "image.h"

class Loading : public Sequence
{
public:
	Loading();
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
