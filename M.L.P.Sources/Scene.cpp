/**************************************************************************
 Scene.cpp

 class Scene; 定義
                                                    2012/04/20　自分の名前
****************************************************************************/
#include "StdAfx.h"
#include "Scene.h"
#include "MainFactory.h"
#include "Stages.h"
#include "Stage_Title.h"
#include "Stage_MusicSelect.h"
#include "Stage_Play.h"
#include "Stage_Result.h"
#include "Stage_Gameover.h"
#include "Stage_NowLoading.h"
#include "Debug_Stage.h"
#include "TATRAFactory/SHS.h"

namespace wiz{




/**************************************************************************
 Scene 定義部
***************************************************************************/

/**************************************************************************
 void Scene::Clear();
 用途: シーンの破棄
 戻り値: なし
***************************************************************************/
void Scene::Clear(){
	SafeDelete(m_pRootStage);
}
/**************************************************************************
 Scene::Scene();
 用途: コンストラクタ
 戻り値: なし
***************************************************************************/
/**************************************************************************
 Scene::Scene(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
 );
 用途: コンストラクタ。シーンを生成
 戻り値: なし。失敗したら例外をthrow
***************************************************************************/
Scene::Scene(LPDIRECT3DDEVICE9 pD3DDevice)
:m_pRootStage(0)
{
    try{
        //無効チェック
        if(!pD3DDevice){
            throw DxException(L"シーンの初期化に失敗しました。デバイスが無効です。",
            L"Scene::Scene()");
        }
#if defined(DEBUG) || defined(_DEBUG)
		//ルートのステージにデバッグメニューを設定
		m_pRootStage = new DebugMenu(pD3DDevice);
#else 
		//ルートのステージにタイトルメニューを設定
		m_pRootStage = new TitleMenu(pD3DDevice);
#endif
        // 両面描画モードの指定
        pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
        // Ｚ比較を行なう
        pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
        // ディザリングを行なう（高品質描画）
        pD3DDevice->SetRenderState( D3DRS_DITHERENABLE, TRUE);
    }
    catch(...){
        //破棄処理
        Clear();
        //再スロー
        throw;
    }
}
/**************************************************************************
 Scene::~Scene();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Scene::~Scene()
{
    //破棄処理
    Clear();
}
/**************************************************************************
 void Scene::Draw(
 LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 インターフェイスへのポインタ
 const CONTROLER_STATE* pCntlState  //コントローラーのステータス
 );
 用途: シーンを描画
 戻り値: なし
***************************************************************************/
void Scene::Draw(LPDIRECT3DDEVICE9 pD3DDevice,const CONTROLER_STATE* pCntlState){
//	Command Com;
	try{
		if(m_pRootStage){
			bool bloopComFlag = false;
			m_pRootStage->getActiveStage()->Draw(pD3DDevice,pCntlState,Com);
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#if defined(DEBUG) || defined(_DEBUG)
			//	: デバッグメニューへ強制移行
			if(pCntlState[0].state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK){
				Com.m_Command = Scene::SC_OPEN_DBGM;
				Com.m_Param1 = 0;
				Com.m_Param2 = 0;
			}
#endif
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
			Script::MLPHeader HeddaBuf;
			ResultFactor Factor;
			Stage*	pReserveStage;
			switch(Com.m_Command){
	///////// /////////
	//ステージ生成
	//

				case Scene::SC_OPEN_TITLE:
					//	: タイトル画面
					if(m_pRootStage){
						SafeDelete(m_pRootStage);
					}
					m_pRootStage = new TitleMenu(pD3DDevice);
				break;
				case Scene::SC_OPEN_MUSICSELECT:
					//	: ミュージックセレクト画面
					if(m_pRootStage){
						SafeDelete(m_pRootStage);
					}
					m_pRootStage = new MusicSelect(pD3DDevice);
				break;
				case Scene::SC_OPEN_PLAY:
					//	: Load画面
					HeddaBuf = *(Script::MLPHeader*)Com.m_Param2;
					if(m_pRootStage){
						SafeDelete(m_pRootStage);
					}
					Com.m_Command = Scene::SC_CREATE_PLAY;
					Com.m_Param2 = (DWORD)&HeddaBuf;
					m_pRootStage = new NowLoading(
						pD3DDevice,
						HeddaBuf,
						Com);
				break;
				case Scene::SC_CREATE_PLAY:
					//	: ゲームプレイ画面
					HeddaBuf		= *(Script::MLPHeader*)Com.m_Param2;
					pReserveStage	= dynamic_cast<NowLoading*>(m_pRootStage)->m_ReserveStage;
					if(m_pRootStage){
						SafeDelete(m_pRootStage);
					}
					m_pRootStage = pReserveStage;
				break;
				case Scene::SC_OPEN_RESULT:
					//	: 結果画面
					if(Com.m_Param2) Factor = *(ResultFactor*)Com.m_Param2;
					if(m_pRootStage){
						SafeDelete(m_pRootStage);
					}
					m_pRootStage = new ResultMenu(pD3DDevice,Com.m_Param1,Factor);
				break;
				case Scene::SC_OPEN_GAMEOVER:
					//	: ゲームオーバー画面
					if(m_pRootStage){
						SafeDelete(m_pRootStage);
					}
					m_pRootStage = new GameOver(pD3DDevice);
				break;
				case Scene::SC_EXIT:
					SafeDelete(m_pRootStage);
					::PostQuitMessage(0);       // アプリケーションを終了する
					Com.Clear();
					return;
				break;
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#if defined(DEBUG) || defined(_DEBUG)
				//	: デバッグ系ステージ
				case Scene::SC_OPEN_DBGM:
					//	: デバッグメニュー画面
					if(m_pRootStage){
						SafeDelete(m_pRootStage);
					}
					m_pRootStage = new DebugMenu(pD3DDevice);
				break;
				case Scene::SC_OPEN_DBGS:
					//	: デバッグ画面
					if(m_pRootStage){
						SafeDelete(m_pRootStage);
					}
					m_pRootStage = new DebugStage(pD3DDevice);
				break;
#endif
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	//
	//ステージ生成
	///////// /////////

				default:
				break;
			}
			//	: コマンド破棄するか保持するか
			if( !bloopComFlag )
				Com.Clear();
		}else{
			throw DxException(
				L"ステージを見失いました ( RootStage is NULL )",
				L"Scene::Draw()"
			);

		}
	}
	catch(...){
		throw;
	}
}

}
//end of namespace wiz.

