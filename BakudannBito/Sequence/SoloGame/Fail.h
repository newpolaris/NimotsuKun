#pragma once

#include "image.h"

namespace Sequence {
namespace SoloGame {
class Parent;

class Fail
{
public:
    Fail();
    void update(Parent*);
private:
	Image mImage;
};

} // namespace SoloGame

} // namespace Sequence
