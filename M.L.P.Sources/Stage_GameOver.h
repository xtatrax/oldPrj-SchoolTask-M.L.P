/**************************************************************************
 Stages.h

                                                    2012/04/20　名前
****************************************************************************/
#pragma once

#include "StdAfx.h"
#include "Stage_Menu.h"

namespace wiz{


/**************************************************************************
 class GameOver : public MenuStage;
 用途: メインメニュークラス
****************************************************************************/
class GameOver : public MenuStage{
public:
/**************************************************************************
GameOver(
LPDIRECT3DDEVICE9 pD3DDevice	//デバイス
);
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
	GameOver(LPDIRECT3DDEVICE9 pD3DDevice);
/**************************************************************************
 void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 インターフェイスへのポインタ
    const CONTROLER_STATE* pCntlState,   //コントローラーのステータス
	Command& Com					//シーンからステージ、もしくはステージからオブジェクトに
									//渡されるコマンドの参照
 );
 用途: ステージを描画
 戻り値: なし。
***************************************************************************/
virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,const CONTROLER_STATE* pCntlState,Command& Com);

};

}
//end of namespace wiz.
