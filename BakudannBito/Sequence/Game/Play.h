#pragma once

namespace Sequence{
namespace Game{
class Parent;

class Play{
public:
	Play() {}
	~Play() {}
	void update( Parent* );
};

} //namespace Game
} //namespace Sequence
