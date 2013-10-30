#include "GameInstance.h"
#include "Sequence/Title.h"
#include "Sequence/Game/Parent.h"
#include "Sequence/StageSelect.h"
#include "Sequence/Game/Clear.h"
#include "Sequence/Game/Menu.h"
#include "Sequence/Game/Loading.h"
#include "GameLib/Framework.h"

//?�ロ?�バ?�変???�ん?�う)
Sequence::GameInstance* gRootSequence = 0; //?�っ?�シ?�ケ?�ス
int gCounter = 0; //?�イ?�ル?�プ?�回?�た?�数?�数?�る?�ウ?�タ

namespace GameLib {
    void Framework::update() {
		if ( !gRootSequence ){
			gRootSequence = new Sequence::GameInstance();
		}
		//?�レ?�ム?�ー?�調???�ょ?�せ??
		setFrameRate( 60 ); //一?�呼?�ば?�い??��?�面?�な??��?�ん?�し?�う??

		if ( gCounter % 60 == 0 ){ //60?�レ?�ム?��??�フ?�ー?�レ?�ト表示
			cout << " FrameRate:" << frameRate() << endl;
		}
		++gCounter;

		gRootSequence->update();

		//終了?�定(q?�押?�れ?�か?�マ?�ス?�×ボ?�ン?�叩?�れ?�か)
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
		HALT("bakana!"); //?귙굤??��??

	//?루㎉??�츣
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
			ASSERT( mStageID != 0 ); //??�굛?볝겏?γ�??�걦??�겍?꾠굥??�?
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

