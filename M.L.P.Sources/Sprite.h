/**************************************************************************
 Sprite.h

 class Sprite : public Object 宣言
                                                    2012/04/26　名前 鴫原 徹
****************************************************************************/
#pragma once

#include "StdAfx.h"
#include "Prim2D.h"
#include "TatraFactory/SpriteItem.h"
namespace wiz{
/**************************************************************************
 class Sprite : public Object;
 用途: ２D環境のスプライトクラス
 ＊直接構築できないように、コンストラクタ、デストラクタをprotectedメンバにする
 ＊Draw()関数も用意しない
****************************************************************************/
class Sprite : public Object{
protected:
	LPD3DXSPRITE	m_pSprite;		//	: 描画するためのスプライト
	SpriteItem		m_SpriteItem;	//	: 座標データとかマテリアルとか。（SpriteItemに変更予定）

public:
/**************************************************************************
 Sprite(
		LPDIRECT3DDEVICE9 pD3DDevice,	//	: デバイス
		wstring			fileName,		//	: ファイル名
		Rect&			Rect,			//	: テクスチャの描画範囲
		D3DXVECTOR3&	vCenter,		//	: 中心位置
		D3DXVECTOR3&	vPos,			//	: 表示位置
		D3DXVECTOR3&	vOffsetPos,		//	: ローカル座標
		D3DXVECTOR3&	vScale,			//	: 伸縮
		D3DXVECTOR3&	vRot,			//	: 回転
		D3DCOLOR		color			//	: 色
	);
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
	Sprite(LPDIRECT3DDEVICE9 pD3DDevice,wstring fileName,Rect* Rect,
			D3DXVECTOR3& vCenter,D3DXVECTOR3& vPos,D3DXVECTOR3& vOffsetPos,
			D3DXVECTOR3& vScale,D3DXVECTOR3& vRot,D3DCOLOR color = 0xFFFFFFFF);
/**************************************************************************
 ~Sprite();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	virtual ~Sprite();
/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 インターフェイスへのポインタ
    vector<Object*>& Vec,				//オブジェクトの配列
    const CONTROLER_STATE* pCntlState,	//コントローラのステータス
	Command& Com						//シーンからステージ、もしくはステージからオブジェクトに
										//渡されるコマンドの参照
 );
 用途: オブジェクトを描画
 戻り値: なし。
***************************************************************************/
	virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
		vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com);




};


}
//end of namespace wiz.
