/**************************************************************************
 Stages.h

                                                    2012/04/20　名前 鴫原 徹
****************************************************************************/
#pragma once

#include "StdAfx.h"
#include "Scene.h"
#include "TatraFactory/SHS.h"
#include "TatraFactory/WhiteoutEffect.h"
namespace wiz{
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/**************************************************************************
 class NowLoading : public Stage;
 用途: ゲームステージクラス
****************************************************************************/
class NowLoading : public Stage{
	Command				m_ReserveCommand;
	Script::MLPHeader	m_ReserveHeader;
	float				m_fTimeAccumulator;
	bool				m_bWhiteout;
	WhiteoutEffect*		m_pWEffect;
public:
	Stage*				m_ReserveStage;
/**************************************************************************
NowLoading(
LPDIRECT3DDEVICE9 pD3DDevice	//デバイス
);
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
	NowLoading(LPDIRECT3DDEVICE9 pD3DDevice,Script::MLPHeader& i_Header,Command i_Command);
/**************************************************************************
NowLoading();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	~NowLoading();
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
