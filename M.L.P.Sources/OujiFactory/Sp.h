/**************************************************************************
 Sp.h

 class Sp : public Object 宣言
                                                    2012/04/26　名前 鴫原 徹
****************************************************************************/
#pragma once

#include "../StdAfx.h"
#include "../Prim2D.h"
#include "../TatraFactory/SpriteItem.h"
namespace wiz{
/**************************************************************************
 class Sp : public Object;
 用途: ２D環境のスプライトクラス
 ＊直接構築できないように、コンストラクタ、デストラクタをprotectedメンバにする
 ＊Draw()関数も用意しない
****************************************************************************/
class Sp : public Object{
protected:
	LPD3DXSPRITE	m_pSprite;		//	: 描画するためのスプライト
	SpriteItem		m_MeshItem;		//	: 座標データとかマテリアルとか。（SpriteItemに変更予定）
	Rect			m_Rect;			//	: 表示する画像の範囲

public:
/**************************************************************************
 Sp(
		LPDIRECT3DDEVICE9 pD3DDevice,	//	: デバイス
		wstring fileName,				//	: ファイル名
		Rect& m_Rect,					//	: テクスチャの描画範囲
		D3DXVECTOR3& m_vCenter,			//	: 中心位置
		D3DXVECTOR3& m_vPos,			//	: 表示位置
		D3DXVECTOR3& m_vOffsetPos,		//	: ローカル座標
		D3DXVECTOR3& m_vScale,			//	: 伸縮
		D3DXVECTOR3& m_vRot				//	: 回転
	);
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
	Sp(LPDIRECT3DDEVICE9 pD3DDevice,wstring fileName,Rect* Rect,
			D3DXVECTOR3& vCenter,D3DXVECTOR3& vPos,D3DXVECTOR3& vOffsetPos,
			D3DXVECTOR3& vScale,D3DXVECTOR3& vRot);
/**************************************************************************
 ~Sp();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	virtual ~Sp();
	virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
		vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com);




};


}
//end of namespace wiz.
