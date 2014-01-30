#pragma once 

#include "Map.h"

namespace Sequence {
using Map::MAP_INFO;

class IMapManager
{
public:
	virtual bool isObstacle(point nextPosition) const = 0;
	virtual bool isPossibleToInstallBoom(point position) = 0;
};

class IMapObjectRequest
{
public:
	virtual void draw(int x, int y, MAP_INFO type, bool inBlockDim=false) const = 0;
};

} // namespace Sequence {