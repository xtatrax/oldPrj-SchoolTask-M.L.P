/**************************************************************************
 Scene.h

 class Scene; 宣言
                                                    2012/04/17　名前 鴫原 徹
****************************************************************************/
#pragma once

#include "StdAfx.h"
namespace wiz{

/**************************************************************************
 class Scene;
 用途: シーンクラス
****************************************************************************/
class Scene
{
	Command Com;
	Stage* m_pRootStage;
	Stage* StgBuf;
	void Clear();
public:
	enum CommandType{
		SC_NONE = 0,
		SC_EXIT,				//	: 終了
		SC_OPEN_TITLE,			//	: タイトル画面へ
		SC_OPEN_MUSICSELECT,	//	: ミュージックセレクト画面へ
		SC_OPEN_PLAY,			//	: プレイングステージへ
		SC_OPEN_RESULT,			//	: 結果表示ステージへ
		SC_OPEN_GAMEOVER,		//	: ゲームオーバーステージへ
		SC_OPEN_DBGM,			//	: デバッグスメニューへ
		SC_OPEN_DBGS,			//	: デバッグステージへ
		SC_RET_GAME,			//	: 
		CREATE_NUM,				//	:
		TITLE_STAGE_COMMAND			= 1000,	//	:
		SELECT_STAGE_COMMAND		= 2000,	//	:
		PLAY_STAGE_COMMAND			= 3000,	//	:
		RESULT_STAGE_COMMAND		= 4000,	//	:
		NOWLOADING_STAGE_COMMAND	= 5000	//	:
		
	};
private:
	enum{
		SC_CREATE_TITLE = CREATE_NUM+1,	//	: タイトル画面へ
		SC_CREATE_MUSICSELECT,	//	: ミュージックセレクト画面へ
		SC_CREATE_PLAY,			//	: プレイングステージ
		SC_CREATE_RESULT,		//	: 結果表示ステージへ
		SC_CREATE_GAMEOVER,		//	: ゲームオーバーステージへ
		SC_CREATE_DBGM,			//	: デバッグスメニューへ
		SC_CREATE_DBGS,			//	: デバッグステージへ
	};
public:
/**************************************************************************
 Scene(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
 );
 用途: コンストラクタ。シーンを生成
 戻り値: なし。失敗したら例外をthrow
***************************************************************************/
    Scene(LPDIRECT3DDEVICE9 pD3DDevice);
/**************************************************************************
 ~Scene();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
    ~Scene();
/**************************************************************************
 void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 インターフェイスへのポインタ
    const CONTROLER_STATE* pCntlState   //コントローラーのステータス
 );
 用途: シーンを描画
 戻り値: なし。
***************************************************************************/
    void Draw(LPDIRECT3DDEVICE9 pD3DDevice,const CONTROLER_STATE* pCntlState);
};
}
//end of namespace wiz.

