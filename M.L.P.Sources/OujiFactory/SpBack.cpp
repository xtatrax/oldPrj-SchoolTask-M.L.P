/**************************************************************************
SpBack.cpp

                                                    2012/04/06　名前 鴫原 徹
****************************************************************************/
#include "StdAfx.h"
#include "../Scene.h"
#include "SpBack.h"

namespace wiz{

/**************************************************************************
 SpBack 定義部
***************************************************************************/
/**************************************************************************
 SpBack::SpBack(
		LPDIRECT3DDEVICE9 pD3DDevice,	//	: デバイス
		wstring fileName,				//	: テクスチャー画像へのパス
		Rect* rect,						//	: テクスチャーの描画範囲
		D3DXVECTOR3& vCenter,			//	: 中心となる点
		D3DXVECTOR3& vPos,				//	: 描画位置
		D3DXVECTOR3& vOffsetPos,		//	: ローカル座標
		D3DXVECTOR3& vScale,			//	: 伸縮
		D3DXVECTOR3& vRot				//	: 回転
	);
 用途: コンストラクタ
 戻り値: なし（失敗時は例外をthrow）
***************************************************************************/
	SpBack::SpBack(
		LPDIRECT3DDEVICE9 pD3DDevice,
		wstring fileName,
		Rect* rect,
		D3DXVECTOR3& vCenter,
		D3DXVECTOR3& vPos,
		D3DXVECTOR3& vOffsetPos,
		D3DXVECTOR3& vScale,
		D3DXVECTOR3& vRot)
		:m_MeshItem( pD3DDevice, fileName, rect, vCenter, vPos, vOffsetPos, vScale, vRot)
{
	try{
		if(FAILED(D3DXCreateSprite(pD3DDevice, &m_pSprite))){
			// 初期化失敗
			throw DxException(
				L"スプライトの作成に失敗しました。",
				L"SpBack::SpBack()"
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
 SpBack::~SpBack();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
SpBack::~SpBack(){
	SafeRelease(m_pSprite);
}



///*
void SpBack::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
	vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com)
{
	//テクスチャを持っているか
	if(m_pSprite && m_MeshItem.m_Textuer.getTexture()){
		m_pSprite->Begin( D3DXSPRITE_ALPHABLEND );
		{
			//描画位置の設定
			static	int i	= 0;
			int	j	= (i + 800);
			m_Rect	= Rect(i,0,j,480);

			//描画位置の変更
			i	= (i+20)%3200;

			m_pSprite->SetTransform( &m_MeshItem.getMatrix());
			m_pSprite->Draw(m_MeshItem.m_Textuer.getTexture(), m_Rect,
				&m_MeshItem.m_vCenter, &m_MeshItem.m_vOffsetPos, 0xffffffff );
		}
		m_pSprite->End();
	}
}
//*/

}
//end of namespace wiz.
