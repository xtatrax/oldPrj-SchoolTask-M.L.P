/**************************************************************************
 Stages.cpp

                                                    2012/04/20�@�����̖��O
****************************************************************************/
#include "StdAfx.h"
#include "Scene.h"
#include "Stage_GameOver.h"
#include "KoromoebFactory/KoromoebFactory.h"

namespace wiz{
/**************************************************************************
 GameOver ��`��
****************************************************************************/
/**************************************************************************
GameOver::GameOver(
LPDIRECT3DDEVICE9 pD3DDevice	//�f�o�C�X
);
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/

GameOver::GameOver(LPDIRECT3DDEVICE9 pD3DDevice)
:MenuStage(pD3DDevice){
	try{
		wiz::Koromoeb::KoromoebFactoryGO(pD3DDevice,m_Vec,m_TextureVec);
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
//*/
/**************************************************************************
 void GameOver::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    const CONTROLER_STATE* pCntlState,   //�R���g���[���[�̃X�e�[�^�X
	Command& Com					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �X�e�[�W��`��
 �߂�l: �Ȃ��B
***************************************************************************/
void GameOver::Draw(LPDIRECT3DDEVICE9 pD3DDevice,const CONTROLER_STATE* pCntlState,Command& Com){

	if(pCntlState[0].CustomState.wPressedButtons){
		Com.m_Command	= Scene::SC_OPEN_TITLE;
		Com.m_Param1	= 0;
		Com.m_Param2	= 0;
	}

	MenuStage::Draw( pD3DDevice, pCntlState, Com);
}

}
//end of namespace wiz.
