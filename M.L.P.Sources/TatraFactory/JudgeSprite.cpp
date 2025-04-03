/**************************************************************************
 JudgeSprite.h

                                                    2012/06/14�@���O ���� �O
****************************************************************************/
#include "StdAfx.h"
#include "JudgeSprite.h"
namespace wiz{
/**************************************************************************
 JudgeSprite();
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
JudgeSprite::JudgeSprite(
	LPDIRECT3DDEVICE9 pD3DDevice,
	wstring fileName,
	Rect rect,
	D3DXVECTOR3& vCenter,
	D3DXVECTOR3& vPos,
	D3DXVECTOR3& vOffsetPos,
	D3DXVECTOR3& vScale,
	D3DXVECTOR3& vRot,
	D3DCOLOR color)
	:Sprite( pD3DDevice, fileName, &rect, vCenter, vPos, vOffsetPos, vScale, vRot, color),
	 m_bDrawFlag(false),
	 m_fTimeAccumulator(0),
	 m_BassRect(rect)
{
	try{

	}
	catch(...){
		//�ăX���[
		throw;
	}
}

/**************************************************************************
 virtual ~JudgeSprite();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
JudgeSprite::~JudgeSprite()
{

}

/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,				//�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState,	//�R���g���[���̃X�e�[�^�X
	Command& Com			    		//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
										//�n�����R�}���h�̎Q��
 );
 �p�r: �I�u�W�F�N�g��`��
 �߂�l: �Ȃ��B
***************************************************************************/
void JudgeSprite::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
	vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com)
{
	if(m_bDrawFlag){
		if( (m_fTimeAccumulator += wiz::Tempus::getOneFrameTime()) >= 1.0f){
			m_bDrawFlag = false;
		}
		if( m_SpriteItem.m_Color.m_DwordColor & 0xFF000000){
			m_SpriteItem.m_Color.m_DwordColor &= 0x00FFFFFF;
		} else{
			m_SpriteItem.m_Color.m_DwordColor |= 0xFF000000;
		}

		Sprite::Draw( pD3DDevice, Vec, pCntlState, Com);
	}
}

/**************************************************************************
 void setJudge(
	PlayStage::JUDGE			//	: �`�悷�锻��
 );
 �p�r: �I�u�W�F�N�g��`��
 �߂�l: �Ȃ��B
***************************************************************************/
void JudgeSprite::setJudge(BYTE Judge){
	m_SpriteItem.m_pRect->bottom = m_BassRect.bottom * Judge;
	m_SpriteItem.m_pRect->top    = m_SpriteItem.m_pRect->bottom + m_BassRect.bottom;
	if(Judge >= GOOD){
		m_SpriteItem.m_Color = 0xFFFFFF00;
	}else{
		m_SpriteItem.m_Color = 0xFF888800;
	}
	m_bDrawFlag = true;
	m_fTimeAccumulator = 0.0f;
}


}