/**************************************************************************
 JudgeSprite.h

 class JudgeSprite : public Sprite;
                                                    2012/06/14�@���O ���� �O
****************************************************************************/
#pragma once

#include "../StdAfx.h"
#include "../Sprite.h"

namespace wiz{
/**************************************************************************
 class JudgeSprite : public Sprite;
 �p�r: �����`�悷��N���X
****************************************************************************/
class JudgeSprite : public Sprite{
private:
	bool             m_bDrawFlag;			//	: �����`�悷�邩�ۂ�
	float            m_fTimeAccumulator;	//	: �`����J�n���Ă���̎���
	Rect             m_BassRect;			//	: �x�[�X�ƂȂ�`��͈�
protected:
public:
/**************************************************************************
 JudgeSprite(
		LPDIRECT3DDEVICE9 pD3DDevice,	//	: �f�o�C�X
		wstring fileName,				//	: �t�@�C����
		Rect rect,						//	: �e�N�X�`���̕`��͈�
		D3DXVECTOR3& vCenter,			//	: ���S�ʒu
		D3DXVECTOR3& vPos,				//	: �\���ʒu
		D3DXVECTOR3& vOffsetPos,		//	: ���[�J�����W
		D3DXVECTOR3& vScale,			//	: �L�k
		D3DXVECTOR3& vRot,				//	: ��]
		D3DCOLOR color					//	: �F
	);
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	JudgeSprite(
		LPDIRECT3DDEVICE9 pD3DDevice,
		wstring fileName,
		Rect rect,
		D3DXVECTOR3& vCenter,
		D3DXVECTOR3& vPos,
		D3DXVECTOR3& vOffsetPos,
		D3DXVECTOR3& vScale,
		D3DXVECTOR3& vRot,
		D3DCOLOR color);

/**************************************************************************
 virtual ~JudgeSprite();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	~JudgeSprite();

/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice		//IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,				//�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState,	//�R���g���[���̃X�e�[�^�X
	Command& Com						//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
										//�n�����R�}���h�̎Q��
 );
 �p�r: �I�u�W�F�N�g��`��
 �߂�l: �Ȃ��B
***************************************************************************/
	virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
		vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com);
/**************************************************************************
 void setJudge(
	PlayStage::JUDGE			//	: �`�悷�锻��
 );
 �p�r: �I�u�W�F�N�g��`��
 �߂�l: �Ȃ��B
***************************************************************************/
	void setJudge(BYTE Judge);
};


}