#pragma once 

class Time
{
public:
	int getCurrentTime();

	int getFutureTime(int delay);
};

extern Time theTime;