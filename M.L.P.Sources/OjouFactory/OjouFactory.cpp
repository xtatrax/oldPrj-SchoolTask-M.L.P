/**************************************************************************
OjouFactory.cpp

                                                    2012/04/06�@���O 
****************************************************************************/
#include "StdAfx.h"
#include "../Object.h"
#include "../Scene.h"
#include "../Plate.h"
#include "OjouFactory.h"
#include "../Sprite.h"
#include "../TatraFactory/SpriteItem.h"




namespace wiz{
namespace Ojou{


/**************************************************************************
 IconMove ��`��
****************************************************************************/
/**************************************************************************
 IconMove::IconMove(
    LPDIRECT3DDEVICE9 pD3DDevice,   //  : IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	DWORD Cmd,						//  : �I�����s���ꂽ�Ƃ��̃R�}���h
	DWORD Index,					//  : ���j���[�X�e�[�W��̃C���f�b�N�X
    D3DXVECTOR3		m_vPos;			//	: �`�悷��ʒu(��ʍ����0,0�Ƃ��s�N�Z���P�ʁA�X�N���[�����W�n)
	D3DXVECTOR3		m_vOffsetPos;	//	: �I�t�Z�b�g���W(�`��ʒu��0,0�Ƃ��s�N�Z���P�ʁA�X�N���[�����W�n)
	D3DXVECTOR3		m_vScale;		//	: �L�k�x����
	D3DXVECTOR3		m_vCenter;		//	: �摜�̒��S�Ƃ���ʒu(�摜�̍����0,0�Ƃ��s�N�Z���P�ʁA�X�N���[�����W�n)
	D3DXVECTOR3		m_vRot;			//	: �`�������Ƃ̉�]�x����
	Rect*			m_Rect;			//	: �\������摜�͈̔�
	LPD3DXSPRITE	m_pSprite;		//	: �`�悷�邽�߂̃X�v���C�g
	SpriteItem		m_SpriteItem;		//	: ���W�f�[�^�Ƃ��}�e���A���Ƃ��B�iSpriteItem�ɕύX�\��j
    );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
****************************************************************************/
IconMove::IconMove(LPDIRECT3DDEVICE9 pD3DDevice,
		wstring fileName,
		Rect* rect,
		D3DXVECTOR3& vCenter,
		D3DXVECTOR3& vPos,
		D3DXVECTOR3& vOffsetPos,
		D3DXVECTOR3& vScale,
		D3DXVECTOR3& vRot)
		:Sprite(pD3DDevice, fileName, rect, vCenter, vPos, vOffsetPos, vScale, vRot)
{
}
/**************************************************************************
  ~IconMove::IconMove();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
IconMove::~IconMove(){
}
void IconMove::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
	vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com)
{
	
	
	//�R�}���h���󂯎��
	if(Com.m_Command == ButtonSprite::SELECT_ITEM){
		if(Com.m_Param1)
		{
			//Icon�̈ʒu���ړ�
			m_SpriteItem.m_vPos.x = 420;
			
		}
		else
		{
			
			m_SpriteItem.m_vPos.x = 60;
		}
	}
	
	if(m_pSprite && m_SpriteItem.m_Textuer.getTexture()){
		m_pSprite->Begin( D3DXSPRITE_ALPHABLEND );
		{

			m_pSprite->SetTransform( &m_SpriteItem.getMatrix());
			m_pSprite->Draw(m_SpriteItem.m_Textuer.getTexture(), m_SpriteItem.m_pRect,
				&m_SpriteItem.m_vCenter, &m_SpriteItem.m_vOffsetPos, 0xffffffff );
		}
		m_pSprite->End();
	}

	
}

/**************************************************************************
 ButtonSprite ��`��
****************************************************************************/
/**************************************************************************
 ButtonSprite::ButtonSprite(
    LPDIRECT3DDEVICE9 pD3DDevice,   //  : IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	DWORD Cmd,						//  : �I�����s���ꂽ�Ƃ��̃R�}���h
	DWORD Index,					//  : ���j���[�X�e�[�W��̃C���f�b�N�X
    D3DXVECTOR3		m_vPos;			//	: �`�悷��ʒu(��ʍ����0,0�Ƃ��s�N�Z���P�ʁA�X�N���[�����W�n)
	D3DXVECTOR3		m_vOffsetPos;	//	: �I�t�Z�b�g���W(�`��ʒu��0,0�Ƃ��s�N�Z���P�ʁA�X�N���[�����W�n)
	D3DXVECTOR3		m_vScale;		//	: �L�k�x����
	D3DXVECTOR3		m_vCenter;		//	: �摜�̒��S�Ƃ���ʒu(�摜�̍����0,0�Ƃ��s�N�Z���P�ʁA�X�N���[�����W�n)
	D3DXVECTOR3		m_vRot;			//	: �`�������Ƃ̉�]�x����
	Rect*			m_Rect;			//	: �\������摜�͈̔�
	LPD3DXSPRITE	m_pSprite;		//	: �`�悷�邽�߂̃X�v���C�g
	SpriteItem		m_SpriteItem;		//	: ���W�f�[�^�Ƃ��}�e���A���Ƃ��B�iSpriteItem�ɕύX�\��j
    );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
****************************************************************************/
ButtonSprite::ButtonSprite(LPDIRECT3DDEVICE9 pD3DDevice,wstring fileName,
		Rect* rect,
		DWORD Cmd, 
		DWORD Index,
		D3DXVECTOR3& vCenter,
		D3DXVECTOR3& vPos,
		D3DXVECTOR3& vOffsetPos,
		D3DXVECTOR3& vScale,
		D3DXVECTOR3& vRot)
		:Sprite(pD3DDevice,fileName, rect, vCenter, vPos, vOffsetPos, vScale, vRot),m_ButtonPrm(Cmd,Index)

{
}

/**************************************************************************
  ~ButtonSprite::ButtonSprite();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
ButtonSprite::~ButtonSprite(){
}
void ButtonSprite::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
	vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com)
{
	

	D3DXMATRIX mTurn;
	D3DXQUATERNION mTurnQt;
	
	// �F �I������Ă�����
	if(m_ButtonPrm.getSelect())
	{

		//�R�}���h��n��
		Com.m_Command = this->SELECT_ITEM;
		Com.m_Param1 = m_ButtonPrm.getIndex();

		//���邭��
		static int flg = false;
		static float RotZ = 1.0f;
		D3DXMATRIX mRotZ;
		D3DXMatrixIdentity(&mRotZ);

		if(!flg && RotZ <= 58.0f)
		{
			RotZ += 1.0f;
			////D3DXQuaternionRotationYawPitchRoll(&m_SpriteItem.m_RotQt,
            //D3DXToRadian(0),D3DXToRadian(0),D3DXToRadian(0));
			m_SpriteItem.m_RotQt=D3DXQUATERNION(0.0f,D3DXToRadian(RotZ),0.0f,0.0f);
		}	
	

		else if (flg && RotZ <= 1.0f)
		{
			flg = false;
		}
		else if (!flg && RotZ >= 59.0f)
		{
			RotZ -= 1.0f;
			m_SpriteItem.m_RotQt=D3DXQUATERNION(0.0f,D3DXToRadian(RotZ),0.0f,0.0f);
			flg = true;
		}

		else 
		{
			RotZ -= 1.0f;	
			m_SpriteItem.m_RotQt=D3DXQUATERNION(0.0f,D3DXToRadian(RotZ),0.0f,0.0f);		
		}
		
	}

	
	else
	{	
		//�ʏ�
		m_SpriteItem.m_RotQt=D3DXQUATERNION(0.0f,0.0f,0.0f,0.0f);
		D3DXMATRIX mTurn;
		D3DXMatrixIdentity(&mTurn);
		D3DXMatrixRotationQuaternion(&mTurn,&m_SpriteItem.m_TurnQt);	

	}
	
	if(m_pSprite && m_SpriteItem.m_Textuer.getTexture()){
		m_pSprite->Begin( D3DXSPRITE_ALPHABLEND );
		{
			m_pSprite->SetTransform( &m_SpriteItem.getMatrix());
			m_pSprite->Draw(m_SpriteItem.m_Textuer.getTexture(), m_SpriteItem.m_pRect,
				&m_SpriteItem.m_vCenter, &m_SpriteItem.m_vOffsetPos, 0xffffffff );
		}
		m_pSprite->End();
	}

	if(m_ButtonPrm.getBoot()){
		//�R�}���h���s
		Com = m_ButtonPrm.CommandIssue();
	}
}


/**************************************************************************
 OjouFactory ��`��
****************************************************************************/
/**************************************************************************
 OjouFactory::OjouFactory(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	vector<Texture*>& TexVec		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
OjouFactory::OjouFactory(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,
					 vector<Texture*>& TexVec){
	try{
		
		//�^�C�g��
		vec.push_back(
			new Sprite(pD3DDevice,
			L"Media/Texture/TraecLine.png",
			&Rect(0,0,550,280),
			D3DXVECTOR3(275.0f,140.0f,0.0f),
			D3DXVECTOR3(400.0f,140.0f,0.0f),
			D3DXVECTOR3(0.0f,0.0f,0.0f),
			D3DXVECTOR3(1.0f,1.0f,0.0f),
			D3DXVECTOR3(0.0f,0.0f,0.0f)));

		//�A�C�R��
		vec.push_back(
			new IconMove(pD3DDevice,
			L"Media/Texture/icon.png",
			&Rect(0,0,75,50),
			D3DXVECTOR3(37.5f,25.0f,0.0f),
			D3DXVECTOR3(60.0f,320.0f,0.0f),
			D3DXVECTOR3(0.0f,0.0f,0.0f),
			D3DXVECTOR3(1.0f,1.0f,0.0f),
			D3DXVECTOR3(0.0f,0.0f,0.0f)));

	}
	catch(...){
		//��throw
		throw;
	}

}
/**************************************************************************
 OjouFactory::~OjouFactory();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
OjouFactory::~OjouFactory(){
    //�Ȃɂ����Ȃ�
}



}
}