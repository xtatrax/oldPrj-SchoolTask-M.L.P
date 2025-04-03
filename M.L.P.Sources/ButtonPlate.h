/**************************************************************************
 ButtonPlate.h

 class ButtonPlate : public Object 宣言
 MyFactory; 宣言
                                                    2012/03/04　名前
****************************************************************************/
#pragma once

#include "StdAfx.h"
#include "Plate.h"
#include "TatraFactory/Button.h"
namespace wiz{


/**************************************************************************
 class ButtonPlate : public  Plate;
 用途: ボタンクラス（メニューステージに配置されコントローラで選択できる）
****************************************************************************/
class ButtonPlate :  public  Plate{
public:
	//	: ボタンパラメーター
	Button m_ButtonPrm; 
/**************************************************************************
 ButtonPlate(
    LPDIRECT3DDEVICE9 pD3DDevice,	////IDirect3DDevice9インターフェイスへのポインタ
	DWORD Cmd,						//選択実行されたときのコマンド
	DWORD Index,					//メニューステージ上のインデックス
    D3DXVECTOR3 size,				//大きさ
    D3DXVECTOR3 pos,				//位置
    D3DCOLORVALUE& Diffuse,			//ディフューズ色
    D3DCOLORVALUE& Specular,		//スペキュラ色
    D3DCOLORVALUE& Ambient,			//アンビエント色
	LPDIRECT3DTEXTURE9 pTexture = 0	//テクスチャを張るときは指定
    );
 用途: コンストラクタ
 戻り値: なし
***************************************************************************/
    ButtonPlate(LPDIRECT3DDEVICE9 pD3DDevice,DWORD Cmd,DWORD Index,
		D3DXVECTOR3 pos,D3DXVECTOR3 size,
        D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
		LPDIRECT3DTEXTURE9 pTexture = 0);
/**************************************************************************
 virtual ~ButtonPlate();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
    virtual ~ButtonPlate();
/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,				//オブジェクトの配列
    const CONTROLER_STATE* pCntlState	//コントローラのステータス
	Command& Com						//シーンからステージ、もしくはステージからオブジェクトに
										//渡されるコマンドの参照
 );
 用途: 直方体を描画
 戻り値: なし。
***************************************************************************/
    virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
        vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com);
/**************************************************************************
	virtual void DrawShadowVolume(
    LPDIRECT3DDEVICE9 pD3DDevice,	//IDirect3DDevice9 インターフェイスへのポインタ
	LPD3DXEFFECT	pEffect,		//エフェクトのポインタ
	D3DXMATRIX& mCameraView,		//カメラのビュー行列
	D3DXMATRIX& mCameraProj			//カメラのプロジェクション行列
	);
 用途: 影ボリュームを描画（仮想関数）
 戻り値: なし。
***************************************************************************/
	virtual void DrawShadowVolume(LPDIRECT3DDEVICE9 pD3DDevice,LPD3DXEFFECT pEffect,
		D3DXMATRIX& mCameraView,D3DXMATRIX& mCameraProj);
};

}
//end of namespace wiz.
