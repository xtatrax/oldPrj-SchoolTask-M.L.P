/**************************************************************************
 Stages.cpp


                                                    2012/04/20���O ���� �O
****************************************************************************/
#include "StdAfx.h"
#include "Debug_Stage.h"
#include "Scene.h"
#include "TatraFactory/TatraFactory.h"

namespace wiz{


/**************************************************************************
 DebugStage ��`��
****************************************************************************/
/**************************************************************************
 DebugStage::DebugStage(
 LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
 Stage* Par = 0					//�e�X�e�[�W
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
DebugStage::DebugStage(LPDIRECT3DDEVICE9 pD3DDevice,Stage* Par)
:MenuStage(pD3DDevice){
	m_pChildStage = 0;
	try{
		Tatra::TatraFactoryDBGS(pD3DDevice,m_Vec,m_TextureVec);
	}
	catch(...){
	}
}

/**************************************************************************
 DebugMenu ��`��
****************************************************************************/
/**************************************************************************
 DebugMenu::DebugMenu(
 LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
 Stage* Par = 0					//�e�X�e�[�W
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
DebugMenu::DebugMenu(LPDIRECT3DDEVICE9 pD3DDevice,Stage* Par)
:MenuStage(pD3DDevice){
	m_pChildStage = 0;
	try{
		//Tatra::TatraFactoryDBGM(pD3DDevice,m_Vec,m_TextureVec);
		Texture* pTitleTx	= new Texture(pD3DDevice,L"Media/Texture/DBG_TT.png");
		Texture* pSelectTx	= new Texture(pD3DDevice,L"Media/Texture/DBG_MS.png");
		Texture* pPlayTx	= new Texture(pD3DDevice,L"Media/Texture/DBG_Play.png");
		Texture* pResultTx	= new Texture(pD3DDevice,L"Media/Texture/DBG_Result.png");
		Texture* pGovTx		= new Texture(pD3DDevice,L"Media/Texture/DBG_GOV.png");
		Texture* pDBGTx		= new Texture(pD3DDevice,L"Media/Texture/DBG_DBG.png");
		m_TextureVec.push_back(pTitleTx);
		m_TextureVec.push_back(pSelectTx);
		m_TextureVec.push_back(pPlayTx);
		m_TextureVec.push_back(pResultTx);
		m_TextureVec.push_back(pGovTx);
		m_TextureVec.push_back(pDBGTx);
		//�{�^���N���X�̃}�e�B���A��
        D3DCOLORVALUE ButtonDiffuse		= {0.8f,0.8f,0.8f,1.0f};
        D3DCOLORVALUE ButtonSpecular	= {0.0f,0.0f,0.0f,0.0f};
        D3DCOLORVALUE ButtonAmbient		= {0.2f,0.2f,0.2f,0.2f};

		//	: �^�C�g���{�^��
		ButtonPlate* pButton = new ButtonPlate(pD3DDevice ,
					Scene::SC_OPEN_TITLE,
					0,
					D3DXVECTOR3(2.0f,1.0f,1.0f),
					D3DXVECTOR3(-2.2f,2.0f,1.5f),
					ButtonDiffuse,ButtonSpecular,ButtonAmbient,
					pTitleTx->getTexture());
		m_ButtonVec.push_back(&pButton->m_ButtonPrm);
		m_Vec.push_back(pButton);

		//	: �~���[�W�b�N�Z���N�g�{�^��
		pButton = new ButtonPlate(pD3DDevice ,
					Scene::SC_OPEN_MUSICSELECT,
					1,
					D3DXVECTOR3(2.0f,1.0f,1.0f),
					D3DXVECTOR3(-2.2f,0.0f,1.5f),
					ButtonDiffuse,ButtonSpecular,ButtonAmbient,
					pSelectTx->getTexture());
		m_ButtonVec.push_back(&pButton->m_ButtonPrm);
		m_Vec.push_back(pButton);

		//	: �Q�[���v���C�{�^��
		pButton = new ButtonPlate(pD3DDevice ,
					Scene::SC_OPEN_PLAY,
					2,
					D3DXVECTOR3(2.0f,1.0f,1.0f),
					D3DXVECTOR3(-2.2f,-2.0f,1.5f),
					ButtonDiffuse,ButtonSpecular,ButtonAmbient,
					pPlayTx->getTexture());
		m_ButtonVec.push_back(&pButton->m_ButtonPrm);
		m_Vec.push_back(pButton);

		//	; ���U���g�{�^��
		pButton = new ButtonPlate(pD3DDevice ,
					Scene::SC_OPEN_RESULT,
					3,
					D3DXVECTOR3(2.0f,1.0f,1.0f),
					D3DXVECTOR3(2.2f,2.0f,1.5f),
					ButtonDiffuse,ButtonSpecular,ButtonAmbient,
					pResultTx->getTexture());
		m_ButtonVec.push_back(&pButton->m_ButtonPrm);
		m_Vec.push_back(pButton);

		//	: �Q�[���I�[�o�[�{�^��
		pButton = new ButtonPlate(pD3DDevice ,
					Scene::SC_OPEN_GAMEOVER,
					4,
					D3DXVECTOR3(2.0f,1.0f,1.0f),
					D3DXVECTOR3(2.2f,0.0f,1.5f),
					ButtonDiffuse,ButtonSpecular,ButtonAmbient,
					pGovTx->getTexture());
		m_ButtonVec.push_back(&pButton->m_ButtonPrm);
		m_Vec.push_back(pButton);

		//	: �f�o�b�O�X�e�[�W
		pButton = new ButtonPlate(pD3DDevice ,
					Scene::SC_OPEN_DBGS,
					5,
					D3DXVECTOR3(2.0f,1.0f,1.0f),
					D3DXVECTOR3(2.2f,-2.0f,1.5f),
					ButtonDiffuse,ButtonSpecular,ButtonAmbient,
					pDBGTx->getTexture());
		m_ButtonVec.push_back(&pButton->m_ButtonPrm);
		m_Vec.push_back(pButton);

        //�{�^���N���X�̃C���X�^���X�\�z
		//AddButton();
        //�{�^���N���X�̃C���X�^���X�\�z
		//AddButton();
	}
	catch(...){
	}
}
}
//end of namespace wiz.
