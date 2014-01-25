#include "GameLib/Framework.h"

#include "Sequence/SoloGame/Player.h"
#include "Sequence/SoloGame/State.h"

#include <type_traits>

namespace Sequence {
namespace SoloGame {

// Helper to determine whether there's a const_iterator for T.
template<typename T>
struct has_const_iterator
{
private:
    template<typename C> static char test(typename C::const_iterator*);
    template<typename C> static int  test(...);
public:
    enum { value = sizeof(test<T>(0)) == sizeof(char) };
};

// SFINAE test
template <typename T>
class has_begin
{
    typedef char one;
    typedef long two;

    template <typename C> static one test( decltype(&C::helloworld) ) ;
    template <typename C> static two test(...);


public:
    enum { value = sizeof(test<T>(0)) == sizeof(char) };
};

// bar() is defined for Containers that define const_iterator as well
// as value_type.
template <typename Container>
typename std::enable_if<has_const_iterator<Container>::value,
                        void>::type
sum(const Container& c)
{
	auto ret = 0;
	foreach (c.begin(), c.end(), [&](auto i) {
		ret += i;
	});
}

void Player::update(State* state)
{
	using GameLib::Framework;

    // if (!alive)
    //    return;

    point direction(0,0);

	Framework f = Framework::instance();

    if (f.isKeyOn('w'))
        direction += point(0,-1);
    else if (f.isKeyOn('s'))
        direction += point(0,+1);
    if (f.isKeyOn('a'))
        direction += point(-1,0);
    else if (f.isKeyOn('d'))
        direction += point(+1,0);


	auto isPossibleToMove = [&](std::vector<point>& nextPositions)
		-> std::vector<bool>
	{
		std::vector<bool> ret;

		std::for_each(nextPositions.begin(), nextPositions.end(),
			[&](point& i) { ret.push_back(state->isPossibleToMove(i)); });

		return ret;
	};

	auto canMove = [&](point i) -> bool {
		auto result = isPossibleToMove(getBound(i));
		bool ret = true;
		std::for_each(result.begin(), result.end(),
			[&](bool i) { ret &= i; });
		return ret;
	};

	point newDirection = mPosition+direction;

    // 해당 방향으로 update 가능한지 조사.
    if (canMove(newDirection))
		mPosition = newDirection;

	// 양쪽 입력 중 하나라도 가능한지 조사 후 move!
	else if (std::abs(direction.x) + std::abs(direction.y) > 1) {
		if (canMove(mPosition + point(direction.x, 0)))
			mPosition = mPosition + point(direction.x, 0);
		else if (canMove(mPosition + point(0, direction.y)))
			mPosition = mPosition + point(0, direction.y);
	}

	// 아래 내역 option 으로 분리하려면 구조를 어떻게 잡아야 할까?
	// : if (OPTION == TRUE) ?
	else {
		// 여타 Puzzle 게임과 같은 미끄러지며 보상하는 기능.
		point OneWay = direction;
		if (std::abs(OneWay.y) > 0)
			OneWay.x = 0;

		auto sum = [] (point i) { return i.x + i.y; };
		const point test = point(-1, 1);
		auto bound = getBound(mPosition+OneWay);
		auto pass = isPossibleToMove(bound);

		point testIndices[4] = { point(0, 1), point(3, 2), point(0,3), point(1,2) };
		const std::vector<point> testIndex(&testIndices[0], &testIndices[4]);

		// 동시 입력 가능성 없음. 이동하지 않는 경우는 이미 걸러짐.
		const int index = (direction.y<0)*0 + (direction.y>0)*1 + (direction.x<0)*2 + (direction.x>0)*3;

		point indexPoint = testIndex[index];
		point someResult = point(pass[indexPoint.x], pass[indexPoint.y]);
		int sign = sum(someResult * point(-1, 1));

		mPosition += sign * (index < 2 ? point(1, 0) : point(0, 1));
	}
}

void Player::draw(const State* state)
{
    state->draw(mPosition.x, mPosition.y, State::MAP_PLAYER);
}

} // namespace SoloGame
} // namespace Sequence
