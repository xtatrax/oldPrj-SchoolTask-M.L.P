/**************************************************************************
 Stages.cpp

                                                    2012/04/20�@�����̖��O
****************************************************************************/
#include "StdAfx.h"
#include "Scene.h"
#include "MainFactory.h"
#include "Stages.h"

namespace wiz{
/**************************************************************************
 MenuStage ��`��
****************************************************************************/
/**************************************************************************
 MenuStage::MenuStage(
 LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
 Stage* Par = 0					//�e�X�e�[�W
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
MenuStage::MenuStage(LPDIRECT3DDEVICE9 pD3DDevice,Stage* Par)
:Stage(Par),m_SelectIndex(0),m_SelectLock(true),m_IsAnimetion(false){
	m_pChildStage = 0;
	try{
        // ���C�e�B���O���[�h
        pD3DDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
        //���C�g�̃C���X�^���X������
        D3DCOLORVALUE Diffuse = {1.0f,1.0f,1.0f,0.0f};
        D3DCOLORVALUE Specular = {1.0f,1.0f,1.0f,0.0f};
        D3DCOLORVALUE Ambient = {0.5f,0.5f,0.5f,0.0f};
        m_Vec.push_back(new DirectionalLight(pD3DDevice,Diffuse,Specular,Ambient,
                    D3DXVECTOR3(0.4f, -1.0f, -0.4f)));
        //�J�����̃C���X�^���X������
        m_Vec.push_back(
			new LookDownCamera(D3DXVECTOR3( 0.0f, 0.01f,- 5.0f),D3DXVECTOR3( 0.0f, 0.0f, 0.0f),
				    1.0f, 100.0f,45.0f));
	}
	catch(...){
		//�e�N���X��Clear()���Ă�
		Clear();
		//�ăX���[
		throw;
	}
}

/**************************************************************************
 virtual MenuStage::~MenuStage();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
MenuStage::~MenuStage(){
	//�{�^���z��̂݃N���A����
	//�z�u����Ă�|�C���^�̍폜�͍s�Ȃ�Ȃ�
	m_ButtonVec.clear();
}


/**************************************************************************
 void MenuStage::AddButton(
	void* pButton	//�{�^���̃|�C���^
 );
 �p�r: ���j���[�Ƀ{�^����ǉ�����Bm_Vec�ɂ͒��ړ���Ȃ�
 �߂�l: �Ȃ�
***************************************************************************/
//void MenuStage::AddButton(void* pButton){
//	//�{�^�������̔z��ɒǉ�
//	m_ButtonVec.push_back(pButton);
//	//�I�u�W�F�N�g�z��ɒǉ�
//	m_Vec.push_back(pButton);
//}
/**************************************************************************
 void MenuStage::AddButton(
	void* pButton	//�{�^���̃|�C���^
 );
 �p�r: ���j���[�Ƀ{�^����ǉ�����Bm_Vec�ɂ͒��ړ���Ȃ�
 �߂�l: �Ȃ�
***************************************************************************/
//void MenuStage::AddButton(Button* pButton){
//	//�{�^�������̔z��ɒǉ�
//	m_ButtonVec.push_back(pButton);
//	//�I�u�W�F�N�g�z��ɒǉ�
//	//m_Vec.push_back(pButton);
//}


/**************************************************************************
 void MenuStage::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    const CONTROLER_STATE* pCntlState,   //�R���g���[���[�̃X�e�[�^�X
	Command& Com					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �V�[����`��
 �߂�l: �Ȃ��B
***************************************************************************/
void MenuStage::Draw(LPDIRECT3DDEVICE9 pD3DDevice,const CONTROLER_STATE* pCntlState,Command& Com){
    if(!m_SelectLock){
		//	: ���̃{�^����
		if(pCntlState[0].CustomState.wPressedButtons & XINPUT_GAMEPAD_DPAD_DOWN 
			|| pCntlState[0].state.Gamepad.sThumbLY < 0){
			m_SelectIndex++;
			if(m_ButtonVec.size() <= m_SelectIndex){
				m_SelectIndex = 0;
			}
			m_SelectLock = true;
		}
		//	: �O�̃{�^����
		if(pCntlState[0].CustomState.wPressedButtons & XINPUT_GAMEPAD_DPAD_UP
			|| pCntlState[0].state.Gamepad.sThumbLY > 0){
			if(m_SelectIndex == 0){
				m_SelectIndex = (m_ButtonVec.size() - 1);
			}
			else{
				m_SelectIndex--;
			}
			m_SelectLock = true;
		}
		//�I����Ԃ̐ݒ�
		vector<Button*>::size_type btnsz = m_ButtonVec.size();
		for(vector<Button*>::size_type i = 0;i < btnsz;i++){
			if(i == m_SelectIndex){
				m_ButtonVec[i]->setSelect(true);
			}
			else{
				m_ButtonVec[i]->setSelect(false);
			}
		}
		//�I�������肳�ꂽ
		if(pCntlState[0].CustomState.wPressedButtons & XINPUT_GAMEPAD_A&&
			!m_ButtonVec.empty()
			){
			m_ButtonVec[m_SelectIndex]->setBoot();
			m_SelectLock = true;
		}
	}
	if(!(pCntlState[0].state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
		&&
		!(pCntlState[0].state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
		&&
		pCntlState[0].state.Gamepad.sThumbLY == 0
		&&
		!(pCntlState[0].state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
		&& 
		!m_IsAnimetion
		){
		m_SelectLock = false;
	}
	//�Ō�ɂ��ׂĂ̔z�u�I�u�W�F�N�g�̕`��
	vector<Object*>::size_type sz = m_Vec.size();
	for(vector<Object*>::size_type i = 0;i < sz;i++){
		m_Vec[i]->Draw(pD3DDevice,m_Vec,pCntlState,Com);
	}
}

}
//end of namespace wiz.
