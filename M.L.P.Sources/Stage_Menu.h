/**************************************************************************
 Stages.h

                                                    2012/04/20　名前
****************************************************************************/
#pragma once

#include "StdAfx.h"
#include "TatraFactory/Button.h"

namespace wiz{

/**************************************************************************
 class MenuStage : public Stage;
 用途: メニュータイプのステージクラス
 　　（メニュータイプであれば、この派生クラスを作ってメニューにすると使いやすい）
****************************************************************************/
class MenuStage : public Stage{
protected:
	vector<Button*> m_ButtonVec;
	//ボタンオブジェクトのみの配列（カメラなどは入れない）
	vector<Button*>::size_type m_SelectIndex;
	bool m_SelectLock;
	bool m_IsAnimetion;
/**************************************************************************
 void AddButton(
 void* pButton	//ボタンのポインタ
 );
 用途: メニューにボタンを追加する。m_Vecには直接入れない
 戻り値: なし
***************************************************************************/
	//void AddButton(void* pButton);
/**************************************************************************
 void AddButton(
 Button* pButton	//ボタンのポインタ
 );
 用途: メニューにボタンを追加する。これ以外にm_Vecにも必ず入れる
 戻り値: なし
***************************************************************************/
	void AddButton(Object* pButton);
public:
/**************************************************************************
 MenuStage(
 LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
 Stage* Par = 0					//親ステージ
 );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
	MenuStage(LPDIRECT3DDEVICE9 pD3DDevice,Stage* Par = 0);
/**************************************************************************
 virtual ~MenuStage();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
    virtual ~MenuStage();
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
