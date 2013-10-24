#pragma once

enum SequenceType {
	SEQUENCE_TITLE,
	SEQUENCE_STAGE_SELECT,
	SEQUENCE_LOAD,
	SEQUENCE_GAME,
	SEQUENCE_CLEAR,
	SEQUENCE_MENU,
};

class Sequence 
{
public:
	virtual void update()=0;
};