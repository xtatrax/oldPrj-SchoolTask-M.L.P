/**************************************************************************
 MainFactory.cpp

                                                    2012/04/06�@���O 
****************************************************************************/
#include "StdAfx.h"
#include "../Object.h"
#include "../Scene.h"
#include "OujiFactory.h"
#include "../Plate.h"
#include "../MainFactory.h"
#include "../MultiPlate.h"
#include "../Sprite.h"

namespace wiz{
namespace Ouji{

/**************************************************************************
 OujiFactory ��`��
****************************************************************************/
/**************************************************************************
 OujiFactory::OujiFactory(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	vector<Texture*>& TexVec		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
OujiFactory::OujiFactory(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,
					 vector<Texture*>& TexVec){
	try{
        //���N���X�̃}�e�B���A��
        D3DCOLORVALUE Plate1Diffuse = {1.0f,1.0f,0.0f,1.0f};
        D3DCOLORVALUE Plate1Specular = {0.0f,0.0f,0.0f,0.0f};
        D3DCOLORVALUE Plate1Ambient = {0.4f,0.4f,0.4f,0.2f};

		//���j���[��}���`�v���[�g�̃}�e�B���A��
        D3DCOLORVALUE MPlateDiffuse2 = {0.5f,0.5f,0.5f,1.0f};
        D3DCOLORVALUE MPlateSpecular2 = {0.0f,0.0f,0.0f,0.0f};
        D3DCOLORVALUE MPlateAmbient2 = {0.2f,0.2f,0.2f,0.2f};

		//���j���[�}���`�v���[�g�̃}�e�B���A��
        D3DCOLORVALUE MPlateDiffuse3 = {0.4f,0.2f,0.0f,1.0f};
        D3DCOLORVALUE MPlateSpecular3 = {0.0f,0.0f,0.0f,0.0f};
        D3DCOLORVALUE MPlateAmbient3 = {0.2f,0.0f,0.0f,0.0f};




	}
	catch(...){
		//��throw
		throw;
	}

}
/**************************************************************************
 OujiFactory::~OujiFactory();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
OujiFactory::~OujiFactory(){
    //�Ȃɂ����Ȃ�
}

}
}