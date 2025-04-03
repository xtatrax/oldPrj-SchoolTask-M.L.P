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
#include "../CommonMesh.h"
namespace wiz{
namespace Ouji{

/**************************************************************************
 class OujiFactory;
 �p�r: ���C���H��N���X
****************************************************************************/
class OujiFactory2{
public:
/**************************************************************************
 OujiFactory(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	vector<Texture*>& TexVec		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
	OujiFactory2(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,vector<Texture*>& TexVec);
/**************************************************************************
 ~OujiFactory();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	~OujiFactory2();
};

}
}