/**************************************************************************
 Stages.cpp

                                                    2012/04/20　自分の名前
****************************************************************************/
#include "StdAfx.h"
#include "Scene.h"
#include "Stage_MusicSelect.h"
#include "KoromoebFactory/KoromoebFactory.h"
#include "OujiFactory/OujiFactory2.h"

namespace wiz{






/**************************************************************************
 MusicSelect 定義部
****************************************************************************/
/**************************************************************************
MusicSelect::MusicSelect(
LPDIRECT3DDEVICE9 pD3DDevice	//デバイス
);
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
MusicSelect::MusicSelect(LPDIRECT3DDEVICE9 pD3DDevice)
:MenuStage(pD3DDevice){
	try{
		//wiz::Koromoeb::KoromoebFactoryMS(pD3DDevice,m_Vec,m_TextureVec);

		wiz::Ouji::OujiFactory2(pD3DDevice,m_Vec,m_TextureVec);
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
