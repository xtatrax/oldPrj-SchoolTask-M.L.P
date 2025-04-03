/**************************************************************************
 Stages.h

                                                    2012/04/20　名前
****************************************************************************/
#pragma once

#include "StdAfx.h"
#include "Stage_Menu.h"
#include "Stage_Play.h"

namespace wiz{


/**************************************************************************
 class ResultMenu : public MenuStage;
 用途: メインメニュークラス
****************************************************************************/
class ResultMenu : public MenuStage{
public:
/**************************************************************************
ResultMenu(
LPDIRECT3DDEVICE9 pD3DDevice	//デバイス
);
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
	ResultMenu(LPDIRECT3DDEVICE9 pD3DDevice,int Score,ResultFactor& rankFactor);
};

}
//end of namespace wiz.
