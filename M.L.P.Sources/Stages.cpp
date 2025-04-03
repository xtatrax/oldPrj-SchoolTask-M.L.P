/**************************************************************************
 Stages.cpp

                                                    2012/04/20　自分の名前
****************************************************************************/
#include "StdAfx.h"
#include "Scene.h"
#include "MainFactory.h"
//#include "MyFactory.h"
#include "MyFactory2.h"
#include "Stages.h"
#include "Shadow.h"
namespace wiz{


/**************************************************************************
 GameDialog 定義部
****************************************************************************/
/**************************************************************************
GameDialog::GameDialog(
LPDIRECT3DDEVICE9 pD3DDevice	//デバイス
Stage* Par						//親ステージ
);
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
GameDialog::GameDialog(LPDIRECT3DDEVICE9 pD3DDevice,Stage* Par)
:MenuStage(pD3DDevice,Par){
	try{
		//ダイアログタイプの設定
		m_IsDialog = true;
        //平板クラスのマティリアル
        D3DCOLORVALUE Plate1Diffuse = {0.2f,0.2f,0.2f,1.0f};
        D3DCOLORVALUE Plate1Specular = {0.0f,0.0f,0.0f,0.0f};
        D3DCOLORVALUE Plate1Ambient = {0.2f,0.2f,0.2f,0.2f};
		//ボタンプレートのマティリアル
        D3DCOLORVALUE MPlateDiffuse2 = {0.0f,0.3f,0.5f,1.0f};
        D3DCOLORVALUE MPlateSpecular2 = {0.0f,0.0f,0.0f,0.0f};
        D3DCOLORVALUE MPlateAmbient2 = {0.0f,0.1f,0.2f,0.4f};
		//テクスチャの設定
		//フロア
		Texture* pFloorTx = new Texture(pD3DDevice,L"floor_select.jpg");
		//ボタン1（ゲームに戻るボタン）
		Texture* pGameRetTx = new Texture(pD3DDevice,L"game_ret.jpg");
		//ボタン2（メインに戻るボタン）
		Texture* pGameMainTx = new Texture(pD3DDevice,L"game_main.jpg");

		//テクスチャをテクスチャ配列に追加
		m_TextureVec.push_back(pFloorTx);
		m_TextureVec.push_back(pGameRetTx);
		m_TextureVec.push_back(pGameMainTx);

        //平板クラスのインスタンス構築
		//これは直接追加
        m_Vec.push_back(
            new Plate(pD3DDevice,
                    D3DXVECTOR3(11.5f,0.1f,8.5f),
                    D3DXVECTOR3(0.0f,-0.05f,0.0f),
					Plate1Diffuse,Plate1Specular,Plate1Ambient,
					pFloorTx->getTexture()));

		//ボタン作成
		//ボタンは直接追加しない
        AddButton(
            new ButtonPlate(pD3DDevice,
					//ゲームに戻る
					Scene::SC_RET_GAME,
					0,	//インデックス
					D3DXVECTOR3(5.0f,1.0f,1.5f),
					D3DXVECTOR3(0.0f,0.5f,1.5f),
					MPlateDiffuse2,MPlateSpecular2,MPlateAmbient2,
					pGameRetTx->getTexture()));

		//ボタン作成
		//ボタンは直接追加しない
        AddButton(
            new ButtonPlate(pD3DDevice,
					//メインメニューに戻る
					Scene::,
					1,	//インデックス
					D3DXVECTOR3(5.0f,1.0f,1.5f),
					D3DXVECTOR3(0.0f,0.5f,-1.5f),
					MPlateDiffuse2,MPlateSpecular2,MPlateAmbient2,
					pGameMainTx->getTexture()));


		//影オブジェクトの追加
		//これは直接追加
		m_Vec.push_back(
			new Shadow(pD3DDevice));
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
