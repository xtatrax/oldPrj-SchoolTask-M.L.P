/**************************************************************************
 Stages.cpp

                                                    2012/04/20�@�����̖��O
****************************************************************************/
#include "StdAfx.h"
#include "Stage_NowLoading.h"
#include "Stage_Play.h"
#include "Sprite.h"

namespace wiz{
/**************************************************************************
 NowLoading ��`��
****************************************************************************/
/**************************************************************************
NowLoading::NowLoading(
LPDIRECT3DDEVICE9 pD3DDevice	//�f�o�C�X
);
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
NowLoading::NowLoading(LPDIRECT3DDEVICE9 pD3DDevice,Script::MLPHeader& i_Header,Command i_Command)
	:Stage(),m_fTimeAccumulator(0.0f),m_bWhiteout(false)
{
	try{
		this->m_IsDialog = false;
		m_ReserveCommand = i_Command;
		m_ReserveHeader  = i_Header;
		m_Vec.push_back(
			new Sprite(
				pD3DDevice,
				L"Media/Texture/Load_LetsMusic.png",
				NULL,
				g_vZero,
				g_vZero,
				g_vZero,
				g_vOne,
				g_vZero)
		);
		m_Vec.push_back(
			new Sprite(
				pD3DDevice,
				L"Media/Texture/NowLoading.png",
				NULL,
				g_vZero,
				D3DXVECTOR3(___MLP_WINDOWSIZE_WIDTH - 200.0f,___MLP_WINDOWSIZE_HEIGHT - 64.0f,0.0f),
				g_vZero,
				D3DXVECTOR3(0.5f,0.5f,1.0f),
				g_vZero)
		);
		m_Vec.push_back(
			m_pWEffect = new WhiteoutEffect(
				pD3DDevice,
				L"Media/Texture/white.png",
				1.0f,
				0x00000000
			)
		);
	}
	catch(...){
		Clear();
		//�ăX���[
		throw;
	}
}
/**************************************************************************
NowLoading();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
NowLoading::~NowLoading(){
	
}

/**************************************************************************
 void NowLoading::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    const CONTROLER_STATE* pCntlState   //�R���g���[���[�̃X�e�[�^�X
	Command& Com					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �V�[����`��
 �߂�l: �Ȃ��B
***************************************************************************/
void NowLoading::Draw(LPDIRECT3DDEVICE9 pD3DDevice,const CONTROLER_STATE* pCntlState,Command& Com){
	

	Com.m_Command = (DWORD)this;
	Com.m_Param1  = 1;
	vector<Object*>::size_type sz = m_Vec.size();
	for(vector<Object*>::size_type i = 0;i < sz;i++){
		m_Vec[i]->Draw(pD3DDevice,m_Vec,pCntlState,Com);
	}

	m_fTimeAccumulator += wiz::Tempus::getOneFrameTime();
	if(m_bWhiteout){
		if( m_pWEffect->getCompleteFlag() ){
			Com = m_ReserveCommand ;
		}
	}else{
		if( m_fTimeAccumulator >= 3.0f ){
			m_ReserveStage = new PlayStage(pD3DDevice,m_ReserveHeader,((Script::SCORELEVEL)m_ReserveCommand.m_Param1));
			m_pWEffect->setWhiteout();
			m_bWhiteout = true;
		}
	}
}

}
//end of namespace wiz.
