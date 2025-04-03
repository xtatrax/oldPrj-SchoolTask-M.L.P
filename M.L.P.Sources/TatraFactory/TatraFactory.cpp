/**************************************************************************
 TatraFactory.cpp

                                                    2012/04/06�@���O ���� �O
****************************************************************************/
#include "StdAfx.h"
#include "../Object.h"
#include "../Scene.h"
#include "../MultiPlate.h"
#include "TatraFactory.h"
#include "JudgeLine.h"
#include "NoteObjects.h"
#include "../MainFactory.h"
#include "../ButtonPlate.h"
#include "../Sprite.h"
namespace wiz{
namespace Tatra{



/**************************************************************************
 TatraFactoryPlay ��`��
****************************************************************************/
/**************************************************************************
 TatraFactoryPlay::TatraFactoryPlay(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	vector<Texture*>& TexVec		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
TatraFactoryPlay::TatraFactoryPlay(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,
					 vector<Texture*>& TexVec){
	try{

		//	: ����X�v���C�g
		Rect ClientRect;
		GetClientRect(NULL, ClientRect);

		//�ڂ���
		vec.push_back( new Sprite(pD3DDevice,
			L"Media/Texture/Play_Button.png",
			&Rect(48*0,0,48*1,48),
			D3DXVECTOR3( 48/2 , 48/2 , 0.0f),
			D3DXVECTOR3( 280 - 16 , 460 , 0),
			g_vZero,
			D3DXVECTOR3(0.5f,0.5f,1.0f),
			g_vZero,
			0xFFFFFFFF
			));
		vec.push_back( new Sprite(pD3DDevice,
			L"Media/Texture/Play_Button.png",
			&Rect(48*2,0,48*3,48),
			D3DXVECTOR3( 48/2 , 48/2 , 0.0f),
			D3DXVECTOR3( 350-16 , 460 , 0),
			g_vZero,
			D3DXVECTOR3(0.5f,0.5f,1.0f),
			g_vZero,
			0xFFFFFFFF
			));
		vec.push_back( new Sprite(pD3DDevice,
			L"Media/Texture/Play_Button.png",
			&Rect(48*1,0,48*2,48),
			D3DXVECTOR3( 48/2 , 48/2 , 0.0f),
			D3DXVECTOR3( 425-16 , 460 , 0),
			g_vZero,
			D3DXVECTOR3(0.5f,0.5f,1.0f),
			g_vZero,
			0xFFFFFFFF
			));
		vec.push_back( new Sprite(pD3DDevice,
			L"Media/Texture/Play_Button.png",
			&Rect(48*3,0,48*4,48),
			D3DXVECTOR3( 48/2 , 48/2 , 0.0f),
			D3DXVECTOR3( 500-16 , 460 , 0),
			g_vZero,
			D3DXVECTOR3(0.5f,0.5f,1.0f),
			g_vZero,
			0xFFFFFFFF
			));


		vec.push_back( new Sprite(pD3DDevice,
			L"Media/Texture/Play_Button.png",
			&Rect(48*0,48,48*1,48*2),
			D3DXVECTOR3( 48/2 , 48/2 , 0.0f),
			D3DXVECTOR3( 280+16 , 460 , 0),
			g_vZero,
			D3DXVECTOR3(0.5f,0.5f,1.0f),
			g_vZero,
			0xFFFFFFFF
			));
		vec.push_back( new Sprite(pD3DDevice,
			L"Media/Texture/Play_Button.png",
			&Rect(48*2,48,48*3,48*2),
			D3DXVECTOR3( 48/2 , 48/2 , 0.0f),
			D3DXVECTOR3( 350+16 , 460 , 0),
			g_vZero,
			D3DXVECTOR3(0.5f,0.5f,1.0f),
			g_vZero,
			0xFFFFFFFF
			));
		vec.push_back( new Sprite(pD3DDevice,
			L"Media/Texture/Play_Button.png",
			&Rect(48*1,48,48*2,48*2),
			D3DXVECTOR3( 48/2 , 48/2 , 0.0f),
			D3DXVECTOR3( 425+16 , 460 , 0),
			g_vZero,
			D3DXVECTOR3(0.5f,0.5f,1.0f),
			g_vZero,
			0xFFFFFFFF
			));
		vec.push_back( new Sprite(pD3DDevice,
			L"Media/Texture/Play_Button.png",
			&Rect(48*3,48,48*4,48*2),
			D3DXVECTOR3( 48/2 , 48/2 , 0.0f),
			D3DXVECTOR3( 500+16 , 460 , 0),
			g_vZero,
			D3DXVECTOR3(0.5f,0.5f,1.0f),
			g_vZero,
			0xFFFFFFFF
			));

	}
	catch(...){
		//��throw
		throw;
	}

}

/**************************************************************************
 TatraFactoryPlay::~TatraFactoryPlay();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
TatraFactoryPlay::~TatraFactoryPlay(){
    //�Ȃɂ����Ȃ�
}


/**************************************************************************
 TatraFactoryDBGS ��`��
****************************************************************************/
/**************************************************************************
 TatraFactoryDBGS::TatraFactoryDBGS(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	vector<Texture*>& TexVec		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
TatraFactoryDBGS::TatraFactoryDBGS(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,
					 vector<Texture*>& TexVec){
	try{

        //���N���X�̃C���X�^���X�\�z
		vec.push_back(new Guide(pD3DDevice));
        //���N���X�̃}�e�B���A��
        D3DCOLORVALUE Plate1Diffuse		= {0.8f,0.8f,0.8f,1.0f};
        D3DCOLORVALUE Plate1Specular	= {0.0f,0.0f,0.0f,0.0f};
        D3DCOLORVALUE Plate1Ambient		= {0.2f,0.2f,0.2f,0.2f};

        //���N���X�̃C���X�^���X�\�z
		vec.push_back(new JudgeLine(pD3DDevice ,
                    D3DXVECTOR3(0.0f,0.0f,0.0f),
					D3DXVECTOR3(0.5f,0.5f,0.5f),
					Plate1Diffuse,Plate1Specular,Plate1Ambient));
		//*/
	}
	catch(...){
		//��throw
		throw;
	}

}
/**************************************************************************
 TatraFactoryDBGS::~TatraFactoryDBGS();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
TatraFactoryDBGS::~TatraFactoryDBGS(){
    //�Ȃɂ����Ȃ�
}

/**************************************************************************
 TatraFactoryDBGM ��`��
****************************************************************************/
/**************************************************************************
 TatraFactoryDBGM::TatraFactoryDBGM(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	vector<Texture*>& TexVec		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
TatraFactoryDBGM::TatraFactoryDBGM(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,
					 vector<Texture*>& TexVec){
	try{

        //���N���X�̃C���X�^���X�\�z
		vec.push_back(new Guide(pD3DDevice));
	}
	catch(...){
		//��throw
		throw;
	}

}
/**************************************************************************
 TatraFactoryDBGM::~TatraFactoryDBGM();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
TatraFactoryDBGM::~TatraFactoryDBGM(){
    //�Ȃɂ����Ȃ�
}


}
}