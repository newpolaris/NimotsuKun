#pragma once

#include "image.h"

namespace Sequence{
namespace Game{
class Parent;

class Loading{
public:
	Loading();
	void update( Parent* );
private:
	Image image;
	int mCount;
	bool mStarted;
};

} //namespace Game
} //namespace Sequence
