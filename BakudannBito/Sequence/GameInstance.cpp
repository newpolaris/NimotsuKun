#include <fstream>
#include <cassert>

#include "GameInstance.h"
#include "Sequence/Title.h"
#include "Sequence/Game/Parent.h"
#include "Sequence/StageSelect.h"
#include "Sequence/Game/Clear.h"
#include "Sequence/Game/Menu.h"
#include "Sequence/Game/Loading.h"
#include "GameLib/Framework.h"

Sequence::GameInstance* gRootSequence = 0; 
int gCounter = 0;

namespace GameLib {
    void Framework::update() {
		if ( !gRootSequence ){
			try {
				gRootSequence = new Sequence::GameInstance();
			}
			catch (std::ifstream::failure e) {
				cout << "File Read Failure" << endl; 
				GameLib::Framework::instance().requestEnd();
				return;
			}
			catch (std::exception e) {
				cout << "Can't find file" << endl; 
				GameLib::Framework::instance().requestEnd();
				return;
			}
		}

		setFrameRate( 60 ); 

		if ( gCounter % 60 == 0 ){ 
			cout << " FrameRate:" << frameRate() << endl;
		}
		++gCounter;

		gRootSequence->update();

		if ( isKeyOn( 'q' ) ){
			requestEnd();
		}
		if ( isEndRequested() ){
			SAFE_DELETE( gRootSequence );
		}
    }
}

namespace Sequence {

GameInstance::GameInstance() 
    : mTitle( 0 )
    , mStageSelect( 0 )
    , mGame( 0 )
    , mNext( SEQUENCE_NONE )
    , mStageID( 0 )
{
	mTitle = new Title();
}

GameInstance::~GameInstance()
{
	SAFE_DELETE(mTitle);
	SAFE_DELETE(mGame);
	SAFE_DELETE(mStageSelect);
}

void GameInstance::update() 
{
	if (mTitle)
		mTitle->update(this);
	else if (mStageSelect)
		mStageSelect->update(this);
	else if (mGame)
		mGame->update(this);
	else
		HALT("bakana!");

	switch ( mNext ){
		case SEQUENCE_STAGE_SELECT:
			SAFE_DELETE( mTitle );
			SAFE_DELETE( mGame );
			mStageSelect = new StageSelect();
			break;
		case SEQUENCE_TITLE:
			SAFE_DELETE( mGame );
			mTitle = new Title(); 
			break;
		case SEQUENCE_GAME:
			SAFE_DELETE( mStageSelect );
			ASSERT( mStageID != 0 );
			mGame = new Game::Parent( mStageID );
			break;
	}
	mNext = SEQUENCE_NONE;
}

void GameInstance::moveTo( SeqID next ){
	mNext = next;
}

void GameInstance::setStageID( int stageID ){
	mStageID = stageID;
}

} //namespace Sequence

