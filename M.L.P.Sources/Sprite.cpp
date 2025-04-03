/**************************************************************************
Sprite.cpp

xlass Sprite;
                                                    2012/04/06　名前 鴫原 徹
****************************************************************************/
#include "StdAfx.h"
#include "Scene.h"
#include "Sprite.h"

namespace wiz{

/**************************************************************************
 Sprite 定義部
***************************************************************************/
/**************************************************************************
 Sprite::Sprite(
		LPDIRECT3DDEVICE9 pD3DDevice,	//	: デバイス
		wstring fileName,				//	: テクスチャー画像へのパス
		Rect* rect,						//	: テクスチャーの描画範囲
		D3DXVECTOR3& vCenter,			//	: 中心となる点
		D3DXVECTOR3& vPos,				//	: 描画位置
		D3DXVECTOR3& vOffsetPos,		//	: ローカル座標
		D3DXVECTOR3& vScale,			//	: 伸縮
		D3DXVECTOR3& vRot,				//	: 回転
		D3DCOLOR color					//	: 色
	);
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
	Sprite::Sprite(
		LPDIRECT3DDEVICE9 pD3DDevice,
		wstring fileName,
		Rect* rect,
		D3DXVECTOR3& vCenter,
		D3DXVECTOR3& vPos,
		D3DXVECTOR3& vOffsetPos,
		D3DXVECTOR3& vScale,
		D3DXVECTOR3& vRot,
		D3DCOLOR color)
		:m_SpriteItem( pD3DDevice, fileName, rect, vCenter, vPos, vOffsetPos, vScale, vRot, color)
{
	try{
		if(FAILED(D3DXCreateSprite(pD3DDevice, &m_pSprite))){
			// 初期化失敗
			throw DxException(
				L"スプライトの作成に失敗しました。",
				L"Sprite::Sprite()"
				);
		}
	}
	catch(...){
		SafeRelease(m_pSprite);
		//再スロー
		throw;
	}
}

/**************************************************************************
 Sprite::~Sprite();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Sprite::~Sprite(){
	SafeRelease(m_pSprite);
}



///*
void Sprite::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
	vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com)
{
	
	if(m_pSprite && m_SpriteItem.m_Textuer.getTexture()){
		m_pSprite->Begin( D3DXSPRITE_ALPHABLEND );
		{

			//D3DXMATRIX mat, m;
			//D3DXMatrixIdentity( &mat );
			//D3DXMatrixScaling( &m, m_vScale.x, m_vScale.y, m_vScale.z );
			//D3DXMatrixMultiply( &mat, &mat, &m );
			//D3DXMatrixRotationYawPitchRoll( &m, D3DXToRadian( m_vRot.x ),
			//	D3DXToRadian( m_vRot.y ), D3DXToRadian( m_vRot.z ) );
			//D3DXMatrixMultiply( &mat, &mat, &m );
			//D3DXMatrixTranslation( &m, m_vPos.x, m_vPos.y, m_vPos.z );
			//D3DXMatrixMultiply( &mat, &mat, &m );

			m_pSprite->SetTransform( &m_SpriteItem.getMatrix());
			m_pSprite->Draw(m_SpriteItem.m_Textuer.getTexture(), m_SpriteItem.m_pRect,
				&m_SpriteItem.m_vCenter, &m_SpriteItem.m_vOffsetPos, m_SpriteItem.m_Color.m_DwordColor );
		}
		m_pSprite->End();
	}
}
//*/

}
//end of namespace wiz.
