/**************************************************************************
 TatraFactory.h
 class TatraFactoryDBGS; �錾
 class TatraFactoryDBGM; �錾
                                                    2012/43/06�@���O ���� �O
****************************************************************************/
#pragma once

#include "../StdAfx.h"
#include "../Object.h"
namespace wiz{
namespace Tatra{
/**************************************************************************
 class TatraFactoryPlay;
 �p�r: �f�o�b�O�X�e�[�W�̍H��N���X
****************************************************************************/
class TatraFactoryPlay{
public:
/**************************************************************************
 TatraFactory(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	vector<Texture*>& TexVec		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
	TatraFactoryPlay(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,vector<Texture*>& TexVec);
/**************************************************************************
 ~TatraFactory();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	~TatraFactoryPlay();
};

/**************************************************************************
 class TatraFactoryDBGS;
 �p�r: �f�o�b�O�X�e�[�W�̍H��N���X
****************************************************************************/
class TatraFactoryDBGS{
public:
/**************************************************************************
 TatraFactory(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	vector<Texture*>& TexVec		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
	TatraFactoryDBGS(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,vector<Texture*>& TexVec);
/**************************************************************************
 ~TatraFactory();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	~TatraFactoryDBGS();
};


/**************************************************************************
 class TatraFactoryDBGM;
 �p�r: �f�o�b�O���j���[�̍H��N���X
****************************************************************************/
class TatraFactoryDBGM{
public:
/**************************************************************************
 TatraFactory(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	vector<Texture*>& TexVec		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
	TatraFactoryDBGM(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,vector<Texture*>& TexVec);
/**************************************************************************
 ~TatraFactory();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	~TatraFactoryDBGM();
};

}
}