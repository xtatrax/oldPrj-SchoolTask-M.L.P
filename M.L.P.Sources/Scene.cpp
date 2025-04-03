/**************************************************************************
 Scene.cpp

 class Scene; ��`
                                                    2012/04/20�@�����̖��O
****************************************************************************/
#include "StdAfx.h"
#include "Scene.h"
#include "MainFactory.h"
#include "Stages.h"
#include "Stage_Title.h"
#include "Stage_MusicSelect.h"
#include "Stage_Play.h"
#include "Stage_Result.h"
#include "Stage_Gameover.h"
#include "Stage_NowLoading.h"
#include "Debug_Stage.h"
#include "TATRAFactory/SHS.h"

namespace wiz{




/**************************************************************************
 Scene ��`��
***************************************************************************/

/**************************************************************************
 void Scene::Clear();
 �p�r: �V�[���̔j��
 �߂�l: �Ȃ�
***************************************************************************/
void Scene::Clear(){
	SafeDelete(m_pRootStage);
}
/**************************************************************************
 Scene::Scene();
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
/**************************************************************************
 Scene::Scene(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
 );
 �p�r: �R���X�g���N�^�B�V�[���𐶐�
 �߂�l: �Ȃ��B���s�������O��throw
***************************************************************************/
Scene::Scene(LPDIRECT3DDEVICE9 pD3DDevice)
:m_pRootStage(0)
{
    try{
        //�����`�F�b�N
        if(!pD3DDevice){
            throw DxException(L"�V�[���̏������Ɏ��s���܂����B�f�o�C�X�������ł��B",
            L"Scene::Scene()");
        }
#if defined(DEBUG) || defined(_DEBUG)
		//���[�g�̃X�e�[�W�Ƀf�o�b�O���j���[��ݒ�
		m_pRootStage = new DebugMenu(pD3DDevice);
#else 
		//���[�g�̃X�e�[�W�Ƀ^�C�g�����j���[��ݒ�
		m_pRootStage = new TitleMenu(pD3DDevice);
#endif
        // ���ʕ`�惂�[�h�̎w��
        pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
        // �y��r���s�Ȃ�
        pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
        // �f�B�U�����O���s�Ȃ��i���i���`��j
        pD3DDevice->SetRenderState( D3DRS_DITHERENABLE, TRUE);
    }
    catch(...){
        //�j������
        Clear();
        //�ăX���[
        throw;
    }
}
/**************************************************************************
 Scene::~Scene();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Scene::~Scene()
{
    //�j������
    Clear();
}
/**************************************************************************
 void Scene::Draw(
 LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
 const CONTROLER_STATE* pCntlState  //�R���g���[���[�̃X�e�[�^�X
 );
 �p�r: �V�[����`��
 �߂�l: �Ȃ�
***************************************************************************/
void Scene::Draw(LPDIRECT3DDEVICE9 pD3DDevice,const CONTROLER_STATE* pCntlState){
//	Command Com;
	try{
		if(m_pRootStage){
			bool bloopComFlag = false;
			m_pRootStage->getActiveStage()->Draw(pD3DDevice,pCntlState,Com);
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#if defined(DEBUG) || defined(_DEBUG)
			//	: �f�o�b�O���j���[�֋����ڍs
			if(pCntlState[0].state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK){
				Com.m_Command = Scene::SC_OPEN_DBGM;
				Com.m_Param1 = 0;
				Com.m_Param2 = 0;
			}
#endif
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
			Script::MLPHeader HeddaBuf;
			ResultFactor Factor;
			Stage*	pReserveStage;
			switch(Com.m_Command){
	///////// /////////
	//�X�e�[�W����
	//

				case Scene::SC_OPEN_TITLE:
					//	: �^�C�g�����
					if(m_pRootStage){
						SafeDelete(m_pRootStage);
					}
					m_pRootStage = new TitleMenu(pD3DDevice);
				break;
				case Scene::SC_OPEN_MUSICSELECT:
					//	: �~���[�W�b�N�Z���N�g���
					if(m_pRootStage){
						SafeDelete(m_pRootStage);
					}
					m_pRootStage = new MusicSelect(pD3DDevice);
				break;
				case Scene::SC_OPEN_PLAY:
					//	: Load���
					HeddaBuf = *(Script::MLPHeader*)Com.m_Param2;
					if(m_pRootStage){
						SafeDelete(m_pRootStage);
					}
					Com.m_Command = Scene::SC_CREATE_PLAY;
					Com.m_Param2 = (DWORD)&HeddaBuf;
					m_pRootStage = new NowLoading(
						pD3DDevice,
						HeddaBuf,
						Com);
				break;
				case Scene::SC_CREATE_PLAY:
					//	: �Q�[���v���C���
					HeddaBuf		= *(Script::MLPHeader*)Com.m_Param2;
					pReserveStage	= dynamic_cast<NowLoading*>(m_pRootStage)->m_ReserveStage;
					if(m_pRootStage){
						SafeDelete(m_pRootStage);
					}
					m_pRootStage = pReserveStage;
				break;
				case Scene::SC_OPEN_RESULT:
					//	: ���ʉ��
					if(Com.m_Param2) Factor = *(ResultFactor*)Com.m_Param2;
					if(m_pRootStage){
						SafeDelete(m_pRootStage);
					}
					m_pRootStage = new ResultMenu(pD3DDevice,Com.m_Param1,Factor);
				break;
				case Scene::SC_OPEN_GAMEOVER:
					//	: �Q�[���I�[�o�[���
					if(m_pRootStage){
						SafeDelete(m_pRootStage);
					}
					m_pRootStage = new GameOver(pD3DDevice);
				break;
				case Scene::SC_EXIT:
					SafeDelete(m_pRootStage);
					::PostQuitMessage(0);       // �A�v���P�[�V�������I������
					Com.Clear();
					return;
				break;
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#if defined(DEBUG) || defined(_DEBUG)
				//	: �f�o�b�O�n�X�e�[�W
				case Scene::SC_OPEN_DBGM:
					//	: �f�o�b�O���j���[���
					if(m_pRootStage){
						SafeDelete(m_pRootStage);
					}
					m_pRootStage = new DebugMenu(pD3DDevice);
				break;
				case Scene::SC_OPEN_DBGS:
					//	: �f�o�b�O���
					if(m_pRootStage){
						SafeDelete(m_pRootStage);
					}
					m_pRootStage = new DebugStage(pD3DDevice);
				break;
#endif
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	//
	//�X�e�[�W����
	///////// /////////

				default:
				break;
			}
			//	: �R�}���h�j�����邩�ێ����邩
			if( !bloopComFlag )
				Com.Clear();
		}else{
			throw DxException(
				L"�X�e�[�W���������܂��� ( RootStage is NULL )",
				L"Scene::Draw()"
			);

		}
	}
	catch(...){
		throw;
	}
}

}
//end of namespace wiz.

