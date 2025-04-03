/**************************************************************************
 SpriteItem.h

 SpriteItem ; 宣言
                                                    2012/03/04　名前 鴫原 徹
****************************************************************************/
#pragma once

#include "../StdAfx.h"
#include "../Texture.h"
#include "../Prim2D.h"

namespace wiz{ 

/**************************************************************************
 class SpriteItem;
 用途: 座標系情報やマテリアルなどをラッピングするクラス
****************************************************************************/
class SpriteItem{
public:
	// :名前
	wstring				m_SpriteItemName;
		
	// :テクスチャ
	Texture				m_Textuer;

	// :テクスチャ描画範囲
	Rect*				m_pRect;

	// :ロケート用のクオータニオン
    D3DXQUATERNION		m_RotQt;
	
	// :ターン用のクオータニオン
    D3DXQUATERNION		m_TurnQt;
	
	// :物体上の中心とする位置
	D3DXVECTOR3			m_vCenter;
	
	// :オブジェクトの位置
	D3DXVECTOR3			m_vPos;

	// :オフセット
	D3DXVECTOR3			m_vOffsetPos;

	// :サイズ
	D3DXVECTOR3			m_vSize;

	union MLPCOLOR{
		// :色
		D3DCOLOR		m_DwordColor;
		struct{
			BYTE		b;
			BYTE		g;
			BYTE		r;
			BYTE		a;
		}m_ByteColor;
		MLPCOLOR(){};
		MLPCOLOR(D3DCOLOR i_COLOR)
			:m_DwordColor(i_COLOR)
		{};
	}m_Color;

public:
/**************************************************************************
 SpriteItem(SpriteItem& pMeshItem);
 用途: コピーコンストラクタ
 戻り値: なし
***************************************************************************/
	SpriteItem(SpriteItem& pMeshItem);
/**************************************************************************
 SpriteItem::SpriteItem(
		LPDIRECT3DDEVICE9 pD3DDevice,	//	: 
		wstring fileName,				//	: テクスチャの名前
		Rect* rect,						//	: 描画範囲
		D3DXVECTOR3& center,			//	: 中心となる位置 (オリジナルゼロのからのオフセット座標)
		D3DXVECTOR3& pos,				//	: 描画位置
		D3DXVECTOR3& vOffsetPos,		//	: ズレ
		D3DXVECTOR3& size ,				//	: 大きさの比
		D3DXVECTOR3& rot,				//	: ロケート	(公転)
		D3DCOLOR color					//	: 色
);							   
 用途: コンストラクタ(色付)
 戻り値: なし
***************************************************************************/
	SpriteItem(//wstring name,
		LPDIRECT3DDEVICE9 pD3DDevice,
		wstring fileName,
		Rect* rect,
		D3DXVECTOR3& center,
		D3DXVECTOR3& pos,
		D3DXVECTOR3& vOffsetPos,
		D3DXVECTOR3& size ,
		D3DXVECTOR3& rot,
		D3DCOLOR color = 0xFFFFFFFF);
	void Delete();
/**************************************************************************
~SpriteItem();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
	~SpriteItem();

/**************************************************************************
D3DXMATRIX getMatrix();
 用途: マトリックス算出
 戻り値: 算出されたマトリックス
***************************************************************************/
	D3DXMATRIX getMatrix();

/**************************************************************************
D3DXMATRIX getMatrix(
		SpriteItem& i_other	//	: 親となるもののアイテム
	);
 用途: 他SpriteItem影響マトリックスの算出
 戻り値: 算出されたマトリックス
***************************************************************************/
	D3DXMATRIX getMatrix(SpriteItem& i_other);

/**************************************************************************
 SpriteItem& operator =(
	SpriteItem& i_OtherMeshItem		//	: 他のインスタン
 );
 用途: コピー
 戻り値: this
***************************************************************************/
	SpriteItem& operator =(SpriteItem& i_OtherMeshItem);

	

};
}