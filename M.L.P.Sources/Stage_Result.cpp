/**************************************************************************
 Stages.cpp

                                                    2012/04/20　自分の名前
****************************************************************************/
#include "StdAfx.h"
#include "Scene.h"
//#include "MainFactory.h"
//#include "MyFactory.h"
#include "OtaconFactory/OtaconFactory.h"
#include "Stage_Result.h"
#include "Shadow.h"

namespace wiz{
/**************************************************************************
 ResultMenu 定義部
****************************************************************************/
/**************************************************************************
ResultMenu::ResultMenu(
LPDIRECT3DDEVICE9 pD3DDevice	//デバイス
);
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
ResultMenu::ResultMenu(LPDIRECT3DDEVICE9 pD3DDevice,int Score,ResultFactor& rankFactor)
:MenuStage(pD3DDevice){
	try{
		
		Otacon::ResultFactory(pD3DDevice,m_Vec,m_TextureVec,Score,rankFactor);

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


}
//end of namespace wiz.
