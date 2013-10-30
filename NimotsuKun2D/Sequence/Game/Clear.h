#pragma once

#include "image.h"

namespace Sequence{
namespace Game{
class Parent;

class Clear
{
public:
	Clear();
	void update(Parent*);

private:
	Image image;
    int mCount;
};

} //namespace Game
} //namespace Sequence
