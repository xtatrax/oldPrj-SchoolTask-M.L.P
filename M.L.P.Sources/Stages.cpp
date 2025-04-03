/**************************************************************************
 Stages.cpp

                                                    2012/04/20�@�����̖��O
****************************************************************************/
#include "StdAfx.h"
#include "Scene.h"
#include "MainFactory.h"
//#include "MyFactory.h"
#include "MyFactory2.h"
#include "Stages.h"
#include "Shadow.h"
namespace wiz{


/**************************************************************************
 GameDialog ��`��
****************************************************************************/
/**************************************************************************
GameDialog::GameDialog(
LPDIRECT3DDEVICE9 pD3DDevice	//�f�o�C�X
Stage* Par						//�e�X�e�[�W
);
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
GameDialog::GameDialog(LPDIRECT3DDEVICE9 pD3DDevice,Stage* Par)
:MenuStage(pD3DDevice,Par){
	try{
		//�_�C�A���O�^�C�v�̐ݒ�
		m_IsDialog = true;
        //���N���X�̃}�e�B���A��
        D3DCOLORVALUE Plate1Diffuse = {0.2f,0.2f,0.2f,1.0f};
        D3DCOLORVALUE Plate1Specular = {0.0f,0.0f,0.0f,0.0f};
        D3DCOLORVALUE Plate1Ambient = {0.2f,0.2f,0.2f,0.2f};
		//�{�^���v���[�g�̃}�e�B���A��
        D3DCOLORVALUE MPlateDiffuse2 = {0.0f,0.3f,0.5f,1.0f};
        D3DCOLORVALUE MPlateSpecular2 = {0.0f,0.0f,0.0f,0.0f};
        D3DCOLORVALUE MPlateAmbient2 = {0.0f,0.1f,0.2f,0.4f};
		//�e�N�X�`���̐ݒ�
		//�t���A
		Texture* pFloorTx = new Texture(pD3DDevice,L"floor_select.jpg");
		//�{�^��1�i�Q�[���ɖ߂�{�^���j
		Texture* pGameRetTx = new Texture(pD3DDevice,L"game_ret.jpg");
		//�{�^��2�i���C���ɖ߂�{�^���j
		Texture* pGameMainTx = new Texture(pD3DDevice,L"game_main.jpg");

		//�e�N�X�`�����e�N�X�`���z��ɒǉ�
		m_TextureVec.push_back(pFloorTx);
		m_TextureVec.push_back(pGameRetTx);
		m_TextureVec.push_back(pGameMainTx);

        //���N���X�̃C���X�^���X�\�z
		//����͒��ڒǉ�
        m_Vec.push_back(
            new Plate(pD3DDevice,
                    D3DXVECTOR3(11.5f,0.1f,8.5f),
                    D3DXVECTOR3(0.0f,-0.05f,0.0f),
					Plate1Diffuse,Plate1Specular,Plate1Ambient,
					pFloorTx->getTexture()));

		//�{�^���쐬
		//�{�^���͒��ڒǉ����Ȃ�
        AddButton(
            new ButtonPlate(pD3DDevice,
					//�Q�[���ɖ߂�
					Scene::SC_RET_GAME,
					0,	//�C���f�b�N�X
					D3DXVECTOR3(5.0f,1.0f,1.5f),
					D3DXVECTOR3(0.0f,0.5f,1.5f),
					MPlateDiffuse2,MPlateSpecular2,MPlateAmbient2,
					pGameRetTx->getTexture()));

		//�{�^���쐬
		//�{�^���͒��ڒǉ����Ȃ�
        AddButton(
            new ButtonPlate(pD3DDevice,
					//���C�����j���[�ɖ߂�
					Scene::,
					1,	//�C���f�b�N�X
					D3DXVECTOR3(5.0f,1.0f,1.5f),
					D3DXVECTOR3(0.0f,0.5f,-1.5f),
					MPlateDiffuse2,MPlateSpecular2,MPlateAmbient2,
					pGameMainTx->getTexture()));


		//�e�I�u�W�F�N�g�̒ǉ�
		//����͒��ڒǉ�
		m_Vec.push_back(
			new Shadow(pD3DDevice));
	}
	catch(...){
		//�{�^���z��̃N���A����
		//�|�C���^�͔j�����Ȃ�
		m_ButtonVec.clear();
		//�I�u�W�F�N�g�̃N���A
		//�����Ń|�C���^���j�������
		Clear();
		//��throw
		throw;
	}
}







}
//end of namespace wiz.
