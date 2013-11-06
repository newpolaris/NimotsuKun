#pragma once

#include "image.h"

namespace Sequence {
namespace SoloGame {
class Parent;

class Clear
{
public:
    Clear();
    void update(Parent*);
private:
	Image mImage;
};

} // namespace SoloGame

} // namespace Sequence

