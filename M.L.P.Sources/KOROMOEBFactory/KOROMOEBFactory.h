/**************************************************************************
 MainFactory.h
                                                    2012/43/06�@���O
****************************************************************************/
#pragma once

#include "../StdAfx.h"
#include "../Object.h"
#include "../Sprite.h"
#include "../ButtonPlate.h"

namespace wiz{
namespace Koromoeb{

/***************************************************************************
class MoveLevel : pbulic Sprite;
�p�r : ���C�����j���[�N���X
***************************************************************************/
class MoveLevel : public Sprite{
public:

/**************************************************************************
MoveLevel(
LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
LPDIRECT3DTEXTURE9 pTexture	//�e�N�X�`��
);
	�p�r: �R���X�g���N�^
	�߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
MoveLevel(LPDIRECT3DDEVICE9 pD3DDevice,wstring i_filename,
		D3DXVECTOR3& i_vPos,D3DXVECTOR3& i_vOffsetPos,D3DXVECTOR3& i_vScale,
		D3DXVECTOR3& i_vCenter,D3DXVECTOR3& i_vRot,Rect* i_Rect);

/**************************************************************************
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
		vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com);
};


/***************************************************************************
class NameScrew : public ButtonPlate;
�p�r : ���C�����j���[�N���X
***************************************************************************/
//class NameScrew{}	//���ꂪ�N���X�̌`
class NameScrew : public ButtonPlate{
public:

/**************************************************************************
NameScrew(
LPDIRECT3DDEVICE9 pD3DDevice	//�f�o�C�X
);
	�p�r : �R���X�g���N�^
****************************************************************************/
	NameScrew(LPDIRECT3DDEVICE9 pD3DDevice,DWORD Cmd,DWORD Index,
		D3DXVECTOR3 pos,D3DXVECTOR3 size,
        D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient,
		LPDIRECT3DTEXTURE9 pTexture = 0);	//���ꂪ�N���X�̌`

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
class BackGrund : public Sprite;
�p�r : ���C�����j���[�N���X
***************************************************************************/
class BackGrund : public Sprite{
public:

/*************************************************************************
BackGrund(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	vector<Texture*>& TexVec		//�e�N�X�`���̔z��
);
�p�r : �R���X�g���N�^
*************************************************************************/
	BackGrund(LPDIRECT3DDEVICE9 pD3DDevice,wstring i_filename,
			D3DXVECTOR3& i_vPos,D3DXVECTOR3& i_vOffsetPos,D3DXVECTOR3& i_vScale,
			D3DXVECTOR3& i_vCenter,D3DXVECTOR3& i_vRot,Rect* i_Rect);

/**************************************************************************
 ~BackGrund();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	~BackGrund();
};


/**************************************************************************
 class KoromoebFactoryMS;
 �p�r: ���C���H��N���X
****************************************************************************/
class KoromoebFactoryMS{
public:
/**************************************************************************
 KoromoebFactoryMS(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	vector<Texture*>& TexVec		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
	KoromoebFactoryMS(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,vector<Texture*>& TexVec);
/**************************************************************************
 ~KoromoebFactoryMS();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	~KoromoebFactoryMS();
};

/**************************************************************************
 class KoromoebFactoryGO;
 �p�r: �H��N���X
	   �����Ŋ�{�ƂȂ�I�u�W�F�̐������s��
****************************************************************************/
class KoromoebFactoryGO{
public:
/**************************************************************************
 KoromoebFactoryGO(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	vector<Texture*>& TexVec		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
	KoromoebFactoryGO(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,vector<Texture*>& TexVec);
/**************************************************************************
 ~KoromoebFactoryGO();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	~KoromoebFactoryGO();
};

}
}