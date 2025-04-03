/**************************************************************************
 Stages.cpp

                                                    2012/04/20　自分の名前
****************************************************************************/
#include "StdAfx.h"
#include "Scene.h"
#include "Stage_GameOver.h"
#include "KoromoebFactory/KoromoebFactory.h"

namespace wiz{
/**************************************************************************
 GameOver 定義部
****************************************************************************/
/**************************************************************************
GameOver::GameOver(
LPDIRECT3DDEVICE9 pD3DDevice	//デバイス
);
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/

GameOver::GameOver(LPDIRECT3DDEVICE9 pD3DDevice)
:MenuStage(pD3DDevice){
	try{
		wiz::Koromoeb::KoromoebFactoryGO(pD3DDevice,m_Vec,m_TextureVec);
	}
	catch(...){
		//ボタン配列のクリアする
		//ポインタは破棄しない
		m_ButtonVec.clear();
		//オブジェクトのクリア
		//ここでポインタが破棄される
		Clear();
		//再throw
		throw;
	}
}
//*/
/**************************************************************************
 void GameOver::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 インターフェイスへのポインタ
    const CONTROLER_STATE* pCntlState,   //コントローラーのステータス
	Command& Com					//シーンからステージ、もしくはステージからオブジェクトに
									//渡されるコマンドの参照
 );
 用途: ステージを描画
 戻り値: なし。
***************************************************************************/
void GameOver::Draw(LPDIRECT3DDEVICE9 pD3DDevice,const CONTROLER_STATE* pCntlState,Command& Com){

	if(pCntlState[0].CustomState.wPressedButtons){
		Com.m_Command	= Scene::SC_OPEN_TITLE;
		Com.m_Param1	= 0;
		Com.m_Param2	= 0;
	}

	MenuStage::Draw( pD3DDevice, pCntlState, Com);
}

}
//end of namespace wiz.
