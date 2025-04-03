/**************************************************************************
 Stages_Play.h

                                                    2012/04/20　名前 鴫原 徹
****************************************************************************/
#pragma once

#include "StdAfx.h"
#include "Stage_Menu.h"
#include "TatraFactory/ScriptManager.h"
#include "TatraFactory/JudgeLine.h"
#include "TatraFactory/NoteObjects.h"
#include "TatraFactory/MusicScore.h"
#include "TatraFactory/JudgeSprite.h"
#include "OjouFactory/OjouFactoryP.h"
#include "TSound.h"
#include "Scene.h"
namespace wiz{
typedef	Ojou::Groove GrooveGauge;

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/**************************************************************************
 class PlayStage : public Stage;
 用途: ゲームステージクラス
****************************************************************************/
class PlayStage : public Stage{
	JudgeLine*		m_pJudgeLine;		// :判定ラインへのポインター              ┐
	JudgeSprite*	m_pJudgeSprite;		// :ジャッジ文字列                        │
	NoteObjects*	m_pNotesLine1;		// :ライン1の譜へのポインター             │
	NoteObjects*	m_pNotesLine2;		// :ライン2の譜へのポインター             ├ Object配列にも登録するけど、 
	NoteObjects*	m_pNotesLine3;		// :ライン3の譜へのポインター             │探す手間を省くために自分で覚えておく。
	NoteObjects*	m_pNotesLine4;		// :ライン4の譜へのポインター             ├ メモリの管理はObject配列に管理してもらう
	NoteObjects*	m_pAnalogNotesLine1;	// :アナログライン1の譜へのポインター │
	NoteObjects*	m_pAnalogNotesLine2;	// :アナログライン2の譜へのポインター │
	NoteObjects*	m_pNullNotesSound;	// :ノートのない音の一覧へのポインター    │
	Ojou::Groove*	m_pGroove;			// :ゲージクラスへのポインター            │
	Ojou::Score*	m_pPlayScore;		// :点数記憶&描画クラス                   ┘

	MusicScore		m_MusicScore;		// :楽譜
	XACTSound		m_Sound;			// :音声ライブラリ的な
	IXACT3Cue*		m_pBGMCue;
	ScoreNote::NoneData	m_NoteBuffer;	//
	MeasureSizeType		m_ActiveMeasureNum;
	SNoteSizeType		m_ActiveNoteNum;
	ResultFactor		m_ResultFactor;
	float			m_fGreatLine;			// :グレートなライン
	float			m_fGoodLine;			// :グッドなライン
	float			m_fBadLine;				// :判定の最低限ライン
	float			m_fTime;				// :ステージ読み込みからの経過時間
	float			m_fMeasureFirstTime;	// :
	float			m_fFirstTime;			// :
	float			m_fMeasureChangeDelay;	// :
	bool			m_bFirstFlag;			// :一番最初かのフラグ
	bool			m_bPlayBassSoundFlag;	// :
public:	
	enum {
		PLAYSTAGE = Scene::PLAY_STAGE_COMMAND,
		SENDITEM  ,

	};
/**************************************************************************
PlayStage(
LPDIRECT3DDEVICE9 pD3DDevice	//デバイス
);
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
	PlayStage(LPDIRECT3DDEVICE9 pD3DDevice,const Script::MLPHeader& Header,const Script::SCORELEVEL Level);
/**************************************************************************
PlayStage();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	~PlayStage();
/**************************************************************************
 JUDGE PlayJudge(int i_Distance);
 用途: 演奏の判定
 戻り値: 判定番号
***************************************************************************/
	JUDGE PlayJudge(NoteObjects* i_pNotes,bool i_bPressFlag);
/**************************************************************************
 JUDGE PlayJudge(int i_Distance);
 用途: 演奏の判定
 戻り値: 判定番号
***************************************************************************/
	JUDGE PlayJudge2(float i_Distance,float& o_JudgeRate,float& o_DistanceRate);
/**************************************************************************
 void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 インターフェイスへのポインタ
    const CONTROLER_STATE* pCntlState,   //コントローラーのステータス
	Command& Com					//シーンからステージ、もしくはステージからオブジェクトに
									//渡されるコマンドの参照
 );
 用途: シーンを描画
 戻り値: なし。
***************************************************************************/
    virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,const CONTROLER_STATE* pCntlState,Command& Com);
};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

}
//end of namespace wiz.
