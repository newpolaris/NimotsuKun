#include "GameLib/Framework.h"

#include "time.h"

int Time::getFutureTime(int delay)
{
	return getCurrentTime() + delay*1000;
}

int Time::getCurrentTime()
{
	using GameLib::Framework;
	Framework f = Framework::instance();

	return f.time();
}

Time theTime;
