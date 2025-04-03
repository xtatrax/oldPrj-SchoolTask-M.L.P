/**************************************************************************
Sp.cpp

                                                    2012/04/06　名前 鴫原 徹
****************************************************************************/
#include "StdAfx.h"
#include "../Scene.h"
#include "Sp.h"
#include "MusicPlate.h"

namespace wiz{

/**************************************************************************
 Sp 定義部
***************************************************************************/
/**************************************************************************
 Sp::Sp(
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
	Sp::Sp(
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
 Sp::~Sp();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
Sp::~Sp(){
	SafeRelease(m_pSprite);
}



///*
void Sp::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
	vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com)
{
	//テクスチャを持っているか
	if(m_pSprite && m_MeshItem.m_Textuer.getTexture()){
		m_pSprite->Begin( D3DXSPRITE_ALPHABLEND );
		{
			//送られてきたレベルに合わせて、レベルバーを表示する
			if(Com.m_Command == MusicPlate::SendLevel){
				m_Rect	= Rect(0,32*(Com.m_Param1),208,32*(Com.m_Param1+1));
			}

			m_pSprite->SetTransform( &m_MeshItem.getMatrix());
			m_pSprite->Draw(m_MeshItem.m_Textuer.getTexture(),m_Rect,
				&m_MeshItem.m_vCenter, &m_MeshItem.m_vOffsetPos, 0xffffffff );
		}
		m_pSprite->End();
	}
}
//*/

}
//end of namespace wiz.
