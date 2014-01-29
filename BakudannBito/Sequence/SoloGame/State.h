#pragma once

#include <vector>

#include "file.h"
#include "point.h"
#include "image.h"
#include "Array2D.h"
#include "Boom.h"
#include "Map.h"

namespace Sequence {
namespace SoloGame {

class Parent;
class Player;

using Map::MAP_INFO;
using std::vector;

Interface IMapManage
{
	virtual bool isObstacle(point nextPosition) const = 0;
	virtual bool isPossibleToInstallBoom(point position) = 0;
};

class State
{
public:
	static State* initalizeWithStage(int stage);
	virtual ~State();
	int generateID();
    void draw() const;
	void draw(int x, int y, MAP_INFO type, bool inBlockDim=false) const;
    void update(Parent* parent);
	bool installBoom(int ID, point position, int range, int delay);
	bool isObstacle(point nextPosition) const;
	bool isPossibleToInstallBoom(point position);

private:
	static point findOutMapSize(buffer_type& buffer);

	State(buffer_type& stageData, int sx, int sy);

public:
    const int mSrcW;
    const int mSrcH;

private:
    int mX;
    int mY;
	Image mImage;
    Array2D<MAP_INFO> mMap;
	std::vector<Map::Boom> mBoomList;
	Player* mPlayer;
};

} // namespace SoloGame
} // namespace Sequence
