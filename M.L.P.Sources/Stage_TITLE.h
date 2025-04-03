/**************************************************************************
 Stages.h

                                                    2012/04/20　名前
****************************************************************************/
#pragma once

#include "StdAfx.h"
#include "Stage_Menu.h"
#include "TatraFactory/Button.h"
#include "OjouFactory/OjouFactory.h"

namespace wiz{


/**************************************************************************
 class TitleMenu : public MenuStage;
 用途: メインメニュークラス
****************************************************************************/
class TitleMenu : public MenuStage{
public:
/**************************************************************************
TitleMenu(
LPDIRECT3DDEVICE9 pD3DDevice	//デバイス
Stage* Par = 0					//親ステージ
);
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
	TitleMenu(LPDIRECT3DDEVICE9 pD3DDevice,Stage* Par = 0);
	void Draw(LPDIRECT3DDEVICE9 pD3DDevice,const CONTROLER_STATE* pCntlState,Command& Com);
};
}
//end of namespace wiz.
