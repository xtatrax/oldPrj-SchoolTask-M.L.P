/**************************************************************************
 Stage_TITLE.cpp

                                                    2012/04/20　自分の名前
****************************************************************************/
#include "StdAfx.h"
#include "Scene.h"
//#include "MainFactory.h"
//#include "MyFactory.h"
//#include "MyFactory2.h"
#include "Stage_Title.h"
#include "OjouFactory/OjouFactory.h"

namespace wiz{
/**************************************************************************
 TitleMenu 定義部
****************************************************************************/
/**************************************************************************
TitleMenu::TitleMenu(
LPDIRECT3DDEVICE9 pD3DDevice	//デバイス
);
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
TitleMenu::TitleMenu(LPDIRECT3DDEVICE9 pD3DDevice,Stage* Par)
:MenuStage(pD3DDevice){
	try{
		
		//背景
		m_Vec.push_back(
			new Sprite(pD3DDevice,
			L"Media/Texture/white.png",
			&Rect(0,0,800,480),
			D3DXVECTOR3(0.0f,0.0f,0.0f),//中心
			D3DXVECTOR3(0.0f,0.0f,0.0f),//位置
			D3DXVECTOR3(0.0f,0.0f,0.0f),
			D3DXVECTOR3(1.0f,1.0f,0.0f),//大きさ
			D3DXVECTOR3(0.0f,0.0f,0.0f)));
		
		//スタートボタン
		Ojou::ButtonSprite* pSButton = new Ojou::ButtonSprite(pD3DDevice,
			L"Media/Texture/start.png",
			&Rect(0,0,290,190),
			//セレクト画面へ
			Scene::SC_OPEN_MUSICSELECT,
			0,
			D3DXVECTOR3(145.0f,95.0f,0.0f),
			D3DXVECTOR3(245.0f,380.0f,0.0f),
			D3DXVECTOR3(0.0f,0.0f,0.0f),
			D3DXVECTOR3(1.0f,1.0f,0.0f),
			D3DXVECTOR3(0.0f,0.0f,0.0f));
		m_ButtonVec.push_back(&pSButton->m_ButtonPrm);
		m_Vec.push_back(pSButton);

		//終了ボタン
		pSButton = new Ojou::ButtonSprite(pD3DDevice,
			L"Media/Texture/exit.png",
			&Rect(0,0,290,190),
			//終われ
			Scene::SC_EXIT,
			1,
			D3DXVECTOR3(145.0f,95.0f,0.0f),
			D3DXVECTOR3(600.0f,380.0f,0.0f),
			D3DXVECTOR3(0.0f,0.0f,0.0f),
			D3DXVECTOR3(1.0f,1.0f,0.0f),
			D3DXVECTOR3(0.0f,0.0f,0.0f));
		m_ButtonVec.push_back(&pSButton->m_ButtonPrm);
		m_Vec.push_back(pSButton);

		Ojou::OjouFactory(pD3DDevice,m_Vec,m_TextureVec);
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
/**************************************************************************
 void MenuStage::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 インターフェイスへのポインタ
    const CONTROLER_STATE* pCntlState,   //コントローラーのステータス
	Command& Com					//シーンからステージ、もしくはステージからオブジェクトに
									//渡されるコマンドの参照
 );
 用途: シーンを描画
 戻り値: なし。
***************************************************************************/
void TitleMenu::Draw(LPDIRECT3DDEVICE9 pD3DDevice,const CONTROLER_STATE* pCntlState,Command& Com){
    if(!m_SelectLock){
		//	: 次のボタンへ
		if(pCntlState[0].CustomState.wPressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT ){
			m_SelectIndex++;
			if(m_ButtonVec.size() <= m_SelectIndex){
				m_SelectIndex = 0;
			}
			m_SelectLock = true;
		}
		//	: 前のボタンへ
		if(pCntlState[0].CustomState.wPressedButtons & XINPUT_GAMEPAD_DPAD_LEFT){
			if(m_SelectIndex == 0){
				m_SelectIndex = (m_ButtonVec.size() - 1);
			}
			else{
				m_SelectIndex--;
			}
			m_SelectLock = true;
		}
		//選択状態の設定
		vector<Button*>::size_type btnsz = m_ButtonVec.size();
		for(vector<Button*>::size_type i = 0;i < btnsz;i++){
			if(i == m_SelectIndex){
				m_ButtonVec[i]->setSelect(true);
			}
			else{
				m_ButtonVec[i]->setSelect(false);
			}
		}
		//選択が決定された
		if(pCntlState[0].CustomState.wPressedButtons & XINPUT_GAMEPAD_A&&
			!m_ButtonVec.empty()
			){
			m_ButtonVec[m_SelectIndex]->setBoot();
			m_SelectLock = true;
		}
	}
	if(!(pCntlState[0].state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
		&&
		!(pCntlState[0].state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
		&&
		pCntlState[0].state.Gamepad.sThumbLY == 0
		&&
		!(pCntlState[0].state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
		&& 
		!m_IsAnimetion
		){
		m_SelectLock = false;
	}
	//最後にすべての配置オブジェクトの描画
	vector<Object*>::size_type sz = m_Vec.size();
	for(vector<Object*>::size_type i = 0;i < sz;i++){
		m_Vec[i]->Draw(pD3DDevice,m_Vec,pCntlState,Com);
	}
}

}
//end of namespace wiz.
