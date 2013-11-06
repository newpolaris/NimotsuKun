#pragma once

#include "image.h"

namespace Sequence {
namespace SoloGame {
class Parent;

class Ready
{
public:
    Ready();
    void update(Parent*);
private:
	Image mImage;
};

} // namespace SoloGame

} // namespace Sequence
