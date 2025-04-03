/**************************************************************************
Sprite.cpp

xlass Sprite;
                                                    2012/04/06�@���O ���� �O
****************************************************************************/
#include "StdAfx.h"
#include "Scene.h"
#include "Sprite.h"

namespace wiz{

/**************************************************************************
 Sprite ��`��
***************************************************************************/
/**************************************************************************
 Sprite::Sprite(
		LPDIRECT3DDEVICE9 pD3DDevice,	//	: �f�o�C�X
		wstring fileName,				//	: �e�N�X�`���[�摜�ւ̃p�X
		Rect* rect,						//	: �e�N�X�`���[�̕`��͈�
		D3DXVECTOR3& vCenter,			//	: ���S�ƂȂ�_
		D3DXVECTOR3& vPos,				//	: �`��ʒu
		D3DXVECTOR3& vOffsetPos,		//	: ���[�J�����W
		D3DXVECTOR3& vScale,			//	: �L�k
		D3DXVECTOR3& vRot,				//	: ��]
		D3DCOLOR color					//	: �F
	);
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
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
			// ���������s
			throw DxException(
				L"�X�v���C�g�̍쐬�Ɏ��s���܂����B",
				L"Sprite::Sprite()"
				);
		}
	}
	catch(...){
		SafeRelease(m_pSprite);
		//�ăX���[
		throw;
	}
}

/**************************************************************************
 Sprite::~Sprite();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
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
