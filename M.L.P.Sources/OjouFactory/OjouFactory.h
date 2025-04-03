/**************************************************************************
 MainFactory.h
 class Camera:: public Object; �錾
 class Guide: public Object; �錾
 class CommonMesh: public Object; �錾
 class Plate public Object: �錾
 class MainFactory; �錾
                                                    2012/43/06�@���O
****************************************************************************/
#pragma once

#include "../StdAfx.h"
#include "../Object.h"
#include "../Sprite.h"
#include "../TatraFactory/Button.h"
#include "../Scene.h"





namespace wiz{
namespace Ojou{


/**************************************************************************
 class IconMove;
 �p�r: �R�}���h�ɂ���ē����N���X
****************************************************************************/
class IconMove : public Sprite{
	
public:
/*************************************************************************
 IconMove(
	LPDIRECT3DDEVICE9 pD3DDevice,   //  : IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
    D3DXVECTOR3		m_vPos;			//	: �`�悷��ʒu(��ʍ����0,0�Ƃ��s�N�Z���P�ʁA�X�N���[�����W�n)
	D3DXVECTOR3		m_vOffsetPos;	//	: �I�t�Z�b�g���W(�`��ʒu��0,0�Ƃ��s�N�Z���P�ʁA�X�N���[�����W�n)
	D3DXVECTOR3		m_vScale;		//	: �L�k�x����
	D3DXVECTOR3		m_vCenter;		//	: �摜�̒��S�Ƃ���ʒu(�摜�̍����0,0�Ƃ��s�N�Z���P�ʁA�X�N���[�����W�n)
	D3DXVECTOR3		m_vRot;			//	: �`�������Ƃ̉�]�x����
	Rect*			m_Rect;			//	: �\������摜�͈̔�
	LPD3DXSPRITE	m_pSprite;		//	: �`�悷�邽�߂̃X�v���C�g
	SpriteItem		m_MeshItem;		//	: ���W�f�[�^�Ƃ��}�e���A���Ƃ��B�iSpriteItem�ɕύX�\��j
    );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
    IconMove(LPDIRECT3DDEVICE9 pD3DDevice,wstring fileName,Rect* Rect,
			D3DXVECTOR3& vCenter,D3DXVECTOR3& vPos,D3DXVECTOR3& vOffsetPos,
			D3DXVECTOR3& vScale,D3DXVECTOR3& vRot);
/**************************************************************************
 virtual ~IconMove();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
    virtual ~IconMove();
/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState   //�R���g���[���̃X�e�[�^�X
	Command& Com					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �`��
 �߂�l: �Ȃ��B
***************************************************************************/
    virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
        vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com);
};

/**************************************************************************
 class ButtonSprite;
 �p�r: 2D�{�^���N���X
****************************************************************************/
class ButtonSprite : public Sprite{
protected:
		
		bool m_IsAnime;	           // : �A�j���[�V�����t���O
		int m_AnimeCounter;	       // : �A�j���[�V�����J�E��
		D3DXVECTOR3 m_BasePos;     // : ��{�̈ʒu

public:
	    Button m_ButtonPrm;		   // : �{�^���̃p�����[�^�[

		enum{
			SELECT_ITEM = 2000,
		};

/*************************************************************************
 ButtonSprite(
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
	SpriteItem		m_MeshItem;		//	: ���W�f�[�^�Ƃ��}�e���A���Ƃ��B�iSpriteItem�ɕύX�\��j
    );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
    ButtonSprite(LPDIRECT3DDEVICE9 pD3DDevice,wstring fileName,Rect* Rect,
		DWORD Cmd,DWORD Index,
			D3DXVECTOR3& vCenter,D3DXVECTOR3& vPos,D3DXVECTOR3& vOffsetPos,
			D3DXVECTOR3& vScale,D3DXVECTOR3& vRot);
/**************************************************************************
 virtual ~ButtonSprite();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
    virtual ~ButtonSprite();
/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState   //�R���g���[���̃X�e�[�^�X
	Command& Com					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �����̂�`��
 �߂�l: �Ȃ��B
***************************************************************************/
    virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
        vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com);
};

/**************************************************************************
 class OjouFactory;
 �p�r: ���C���H��N���X
****************************************************************************/
	class OjouFactory {
	public:

/**************************************************************************
 OjouFactory(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	vector<Texture*>& TexVec		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
	OjouFactory(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,vector<Texture*>& TexVec);
/**************************************************************************
 ~OjouFactory();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	~OjouFactory();
};

	
}
}