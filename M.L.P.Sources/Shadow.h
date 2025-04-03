/**************************************************************************
 MainFactory.h

 class Shadow: public Object; 宣言

                                                    2012/04/17　自分の名前
****************************************************************************/
#pragma once

#include "StdAfx.h"
#include "Object.h"
namespace wiz{

/**************************************************************************
 class Shadow: public Object;
 用途: 影クラス
****************************************************************************/
class Shadow: public Object{
	struct BigSquareVertex{
		D3DXVECTOR4 p;
		D3DCOLOR    color;
	};
	LPDIRECT3DVERTEXBUFFER9 m_pBigVB;
	//BigSquareFVF用のFVFをDIrectXAPIに渡すときのパラメータ
	enum { BigSquareFVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE };
	// シェーダ
	LPD3DXEFFECT	m_pEffect;     // シェーダが書かれたエフェクト
	// テクニックハンドル
	D3DXHANDLE	m_hRenderShadow;   //シャドウをレンダリングするエフェクト// Technique handle for rendering shadow
	D3DXHANDLE	m_hShowShadow;     //シャドウを表示するTechnique handle for showing shadow volume
	D3DXHANDLE	m_hRenderShadowVolumeComplexity; //シャドウボリュームを表示する
/**************************************************************************
 void Clear();
 用途:オブジェクトの破棄
 戻り値: なし
***************************************************************************/
	void Clear();
public:
/**************************************************************************
 Shadow(
 LPDIRECT3DDEVICE9 pD3DDevice	//デバイス
 );
 用途: コンストラクタ
 戻り値: なし
***************************************************************************/
	Shadow(LPDIRECT3DDEVICE9 pD3DDevice);
/**************************************************************************
 ~Shadow();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	~Shadow();
/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,            //オブジェクトの配列
    const CONTROLER_STATE* pCntlState,   //コントローラのステータス
	Command& Com					//シーンからステージ、もしくはステージからオブジェクトに
									//渡されるコマンドの参照
 );
 用途: 影を描画
 戻り値: なし。
***************************************************************************/
    virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
        vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com);
};


}
//end of namespace wiz.

