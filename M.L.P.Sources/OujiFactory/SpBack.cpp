/**************************************************************************
SpBack.cpp

                                                    2012/04/06�@���O ���� �O
****************************************************************************/
#include "StdAfx.h"
#include "../Scene.h"
#include "SpBack.h"

namespace wiz{

/**************************************************************************
 SpBack ��`��
***************************************************************************/
/**************************************************************************
 SpBack::SpBack(
		LPDIRECT3DDEVICE9 pD3DDevice,	//	: �f�o�C�X
		wstring fileName,				//	: �e�N�X�`���[�摜�ւ̃p�X
		Rect* rect,						//	: �e�N�X�`���[�̕`��͈�
		D3DXVECTOR3& vCenter,			//	: ���S�ƂȂ�_
		D3DXVECTOR3& vPos,				//	: �`��ʒu
		D3DXVECTOR3& vOffsetPos,		//	: ���[�J�����W
		D3DXVECTOR3& vScale,			//	: �L�k
		D3DXVECTOR3& vRot				//	: ��]
	);
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
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
			// ���������s
			throw DxException(
				L"�X�v���C�g�̍쐬�Ɏ��s���܂����B",
				L"SpBack::SpBack()"
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
 SpBack::~SpBack();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
SpBack::~SpBack(){
	SafeRelease(m_pSprite);
}



///*
void SpBack::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
	vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com)
{
	//�e�N�X�`���������Ă��邩
	if(m_pSprite && m_MeshItem.m_Textuer.getTexture()){
		m_pSprite->Begin( D3DXSPRITE_ALPHABLEND );
		{
			//�`��ʒu�̐ݒ�
			static	int i	= 0;
			int	j	= (i + 800);
			m_Rect	= Rect(i,0,j,480);

			//�`��ʒu�̕ύX
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
