/**************************************************************************
 Stages.cpp

                                                    2012/04/20　自分の名前
****************************************************************************/
#include "StdAfx.h"
#include "Scene.h"
#include "MainFactory.h"
#include "Stages.h"

namespace wiz{
/**************************************************************************
 MenuStage 定義部
****************************************************************************/
/**************************************************************************
 MenuStage::MenuStage(
 LPDIRECT3DDEVICE9 pD3DDevice,	//デバイス
 Stage* Par = 0					//親ステージ
 );
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
MenuStage::MenuStage(LPDIRECT3DDEVICE9 pD3DDevice,Stage* Par)
:Stage(Par),m_SelectIndex(0),m_SelectLock(true),m_IsAnimetion(false){
	m_pChildStage = 0;
	try{
        // ライティングモード
        pD3DDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
        //ライトのインスタンス初期化
        D3DCOLORVALUE Diffuse = {1.0f,1.0f,1.0f,0.0f};
        D3DCOLORVALUE Specular = {1.0f,1.0f,1.0f,0.0f};
        D3DCOLORVALUE Ambient = {0.5f,0.5f,0.5f,0.0f};
        m_Vec.push_back(new DirectionalLight(pD3DDevice,Diffuse,Specular,Ambient,
                    D3DXVECTOR3(0.4f, -1.0f, -0.4f)));
        //カメラのインスタンス初期化
        m_Vec.push_back(
			new LookDownCamera(D3DXVECTOR3( 0.0f, 0.01f,- 5.0f),D3DXVECTOR3( 0.0f, 0.0f, 0.0f),
				    1.0f, 100.0f,45.0f));
	}
	catch(...){
		//親クラスのClear()を呼ぶ
		Clear();
		//再スロー
		throw;
	}
}

/**************************************************************************
 virtual MenuStage::~MenuStage();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
MenuStage::~MenuStage(){
	//ボタン配列のみクリアする
	//配置されてるポインタの削除は行なわない
	m_ButtonVec.clear();
}


/**************************************************************************
 void MenuStage::AddButton(
	void* pButton	//ボタンのポインタ
 );
 用途: メニューにボタンを追加する。m_Vecには直接入れない
 戻り値: なし
***************************************************************************/
//void MenuStage::AddButton(void* pButton){
//	//ボタンだけの配列に追加
//	m_ButtonVec.push_back(pButton);
//	//オブジェクト配列に追加
//	m_Vec.push_back(pButton);
//}
/**************************************************************************
 void MenuStage::AddButton(
	void* pButton	//ボタンのポインタ
 );
 用途: メニューにボタンを追加する。m_Vecには直接入れない
 戻り値: なし
***************************************************************************/
//void MenuStage::AddButton(Button* pButton){
//	//ボタンだけの配列に追加
//	m_ButtonVec.push_back(pButton);
//	//オブジェクト配列に追加
//	//m_Vec.push_back(pButton);
//}


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
void MenuStage::Draw(LPDIRECT3DDEVICE9 pD3DDevice,const CONTROLER_STATE* pCntlState,Command& Com){
    if(!m_SelectLock){
		//	: 次のボタンへ
		if(pCntlState[0].CustomState.wPressedButtons & XINPUT_GAMEPAD_DPAD_DOWN 
			|| pCntlState[0].state.Gamepad.sThumbLY < 0){
			m_SelectIndex++;
			if(m_ButtonVec.size() <= m_SelectIndex){
				m_SelectIndex = 0;
			}
			m_SelectLock = true;
		}
		//	: 前のボタンへ
		if(pCntlState[0].CustomState.wPressedButtons & XINPUT_GAMEPAD_DPAD_UP
			|| pCntlState[0].state.Gamepad.sThumbLY > 0){
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
