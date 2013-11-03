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

//?∞„É≠?º„Éê?´Â§â???∏„Çì?ô„ÅÜ)
Sequence::GameInstance* gRootSequence = 0; //?π„Å£?ì„Ç∑?º„Ç±?≥„Çπ
int gCounter = 0; //?°„Ç§?≥„É´?º„Éó?íÂõû?£„Åü?ûÊï∞?íÊï∞?à„Çã?´„Ç¶?≥„Çø

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
		//?ï„É¨?º„É†?¨„Éº?àË™ø???°„Çá?Ü„Åõ??
		setFrameRate( 60 ); //‰∏Ä?ûÂëº?π„Å∞?Ñ„ÅÑ??Å†?åÈù¢?í„Å™??Åß?º„Çì?ß„Åó?æ„ÅÜ??

		if ( gCounter % 60 == 0 ){ //60?ï„É¨?º„É†?´‰??û„Éï?¨„Éº?†„É¨?º„ÉàË°®Á§∫
			cout << " FrameRate:" << frameRate() << endl;
		}
		++gCounter;

		gRootSequence->update();

		//ÁµÇ‰∫Ü?§ÂÆö(q?åÊäº?ï„Çå?ü„Åã?Å„Éû?¶„Çπ?ß√ó„Éú?ø„É≥?åÂè©?ã„Çå?ü„Åã)
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
		HALT("bakana!"); //?Í∑ôÍµ§??ÄÍ≤??

	//?Î£®„éâ??µÏ∏£
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
			ASSERT( mStageID != 0 ); //??≤Íµõ?Î≥ùÍ≤è?Œ≥Íµ??âÍ±¶??£Í≤ç?Íæ†Íµ•??Í±?
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

