#include <vector>
#include <sstream>

#include "GameLib/Framework.h"

#include "point.h"
#include "file.h"

#include "Sequence/SoloGame/State.h"
#include "Sequence/SoloGame/Parent.h"
#include "Sequence/SoloGame/Player.h"

namespace Sequence {
namespace SoloGame {

point State::findOutMapSize(buffer_type& buffer)
{
	int arr[2]={0};
	int arr_idx = 0;

    for (unsigned i=0; i < buffer.size(); ++i)
    {
        if (buffer[i] == '\n') {
            // 한줄 길이 저장.
            arr[arr_idx++] = i-1;

			if (arr_idx == 2)
				break;
        }
    }

    int x = arr[0];

    // 마지막 줄에 \n\r과 같은 ending 기호를 빼먹은걸 대비하여,
    // simbol 길이 만큼 더하고, ending 기호 시작부터 자음 \n까지
    // 길이를 x로 둬서 나눈다.
	const static int pad_line_end_simbol = 2;

    const int x_size_with_end_simbol = arr[1]-arr[0];
    const int buffer_size_with_pad = buffer.size()+pad_line_end_simbol;

    int y = static_cast<int>(buffer_size_with_pad/x_size_with_end_simbol);

    return point(x, y);
}

State* State::initalizeWithStage(int stage)
{
    std::ostringstream oss;
    oss << "data/stageData/" << stage << ".txt";
    //これでstringが取れる(とれる)
    buffer_type stageFile(fileRead(oss.str())); 

    point size = findOutMapSize(stageFile);

	return new State(stageFile, size.x, size.y);
}

State::~State()
{
	SAFE_DELETE(mPlayer);
}

static const int pixels_per_one_block = 16;

State::State(buffer_type& stageData, int sx, int sy)
    : mX(sx)
    , mY(sy)
	, mSrcW(pixels_per_one_block)
	, mSrcH(pixels_per_one_block)
    , map(mX, mY)
    , mImage("data/image/BakudanBitoImage.dds")
{
    for (int j=0; j < mY; j++)
    for (int i=0; i < mX; i++)
        map(i,j) = MAP_NONE;

    unsigned idx=0;
    unsigned count=0;

    while (count < stageData.size()) {
		point pos(idx%mX, idx/mY);

        switch (stageData[count++]) {
        case ' ': map[idx++]=MAP_NONE;  break;
        case '#': map[idx++]=MAP_BLOCK; break;
        case 'p': 
			mPlayer = new Player(pos, point(mSrcW, mSrcH), point(mSrcW*0.8f, mSrcH*0.8f));
			idx++;				
			break;
        case 'm': idx++;				break;
        case 'b': idx++;				break;
        default: break;
        }
    }
}

void State::update(Parent* parent)
{
    /* Section 1: Object's internal time, position based status update.
     *            {Boom, Box} update first, player next
     *            Boom 제거(Remove)시 Player에게 알려야 하며 Boom List에서
     *            제거하여야 한다.
     *            Box 제거(Remove)시 State에게 알려야 한다.
     *            Position, Animation 진행을 위한 update 수행.
     */
    // for (int i = 0; i < boomList.size(); ++i)

	if (mPlayer)
		mPlayer->update(this);

    // Section 2: 
    // Boom total merge search.
    //
    // Section 3:
    // Boom 처리에 따른 Object status update.
    //
    // Section 4:
    // State change에 대한 대응 (pause, player dead)
}

// Used for background drawing.
void State::draw(int x, int y, MAP_INFO type) const
{
    point src;
    switch (type)
    {
    case MAP_NONE:      src=point(1,2); break;
    case MAP_BLOCK:     src=point(3,1); break;
    case MAP_BOX:       src=point(2,0); break;
    case MAP_PLAYER:    src=point(0,0); break;
    case MAP_MONSTER:   src=point(2,1); break;
    }

	mImage.draw(x, y, src.x*mSrcW, src.y*mSrcH, mSrcW, mSrcH);
}

void State::draw() const
{
    for (int j=0; j < mY; j++)
    for (int i=0; i < mX; i++)
        draw(i*mSrcW, j*mSrcH, map(i,j));

	if (mPlayer)
		mPlayer->draw(this);
}

bool State::isPossibleToMove(std::vector<point>& nextPositions)
{
	bool ret = true;

	std::for_each(nextPositions.begin(), nextPositions.end(),
		[&](point& i) { ret &= isPossibleToMove(i); });

	return ret;
}

bool State::isPossibleToMove(point nextPosition)
{
    MAP_INFO info = map(nextPosition);

	if (info == MAP_BLOCK || info == MAP_BOX || info == MAP_BOOM)
        return false;

    return true;
}

} // namespace SoloGame 
} // namespace Sequence