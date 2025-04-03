/**************************************************************************
 Stage_TITLE.cpp

                                                    2012/04/20�@�����̖��O
****************************************************************************/
#include "StdAfx.h"
#include "Scene.h"
//#include "MainFactory.h"
//#include "MyFactory.h"
//#include "MyFactory2.h"
#include "Stage_Title.h"
#include "OjouFactory/OjouFactory.h"

namespace wiz{
/**************************************************************************
 TitleMenu ��`��
****************************************************************************/
/**************************************************************************
TitleMenu::TitleMenu(
LPDIRECT3DDEVICE9 pD3DDevice	//�f�o�C�X
);
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
TitleMenu::TitleMenu(LPDIRECT3DDEVICE9 pD3DDevice,Stage* Par)
:MenuStage(pD3DDevice){
	try{
		
		//�w�i
		m_Vec.push_back(
			new Sprite(pD3DDevice,
			L"Media/Texture/white.png",
			&Rect(0,0,800,480),
			D3DXVECTOR3(0.0f,0.0f,0.0f),//���S
			D3DXVECTOR3(0.0f,0.0f,0.0f),//�ʒu
			D3DXVECTOR3(0.0f,0.0f,0.0f),
			D3DXVECTOR3(1.0f,1.0f,0.0f),//�傫��
			D3DXVECTOR3(0.0f,0.0f,0.0f)));
		
		//�X�^�[�g�{�^��
		Ojou::ButtonSprite* pSButton = new Ojou::ButtonSprite(pD3DDevice,
			L"Media/Texture/start.png",
			&Rect(0,0,290,190),
			//�Z���N�g��ʂ�
			Scene::SC_OPEN_MUSICSELECT,
			0,
			D3DXVECTOR3(145.0f,95.0f,0.0f),
			D3DXVECTOR3(245.0f,380.0f,0.0f),
			D3DXVECTOR3(0.0f,0.0f,0.0f),
			D3DXVECTOR3(1.0f,1.0f,0.0f),
			D3DXVECTOR3(0.0f,0.0f,0.0f));
		m_ButtonVec.push_back(&pSButton->m_ButtonPrm);
		m_Vec.push_back(pSButton);

		//�I���{�^��
		pSButton = new Ojou::ButtonSprite(pD3DDevice,
			L"Media/Texture/exit.png",
			&Rect(0,0,290,190),
			//�I���
			Scene::SC_EXIT,
			1,
			D3DXVECTOR3(145.0f,95.0f,0.0f),
			D3DXVECTOR3(600.0f,380.0f,0.0f),
			D3DXVECTOR3(0.0f,0.0f,0.0f),
			D3DXVECTOR3(1.0f,1.0f,0.0f),
			D3DXVECTOR3(0.0f,0.0f,0.0f));
		m_ButtonVec.push_back(&pSButton->m_ButtonPrm);
		m_Vec.push_back(pSButton);

		Ojou::OjouFactory(pD3DDevice,m_Vec,m_TextureVec);
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
void TitleMenu::Draw(LPDIRECT3DDEVICE9 pD3DDevice,const CONTROLER_STATE* pCntlState,Command& Com){
    if(!m_SelectLock){
		//	: ���̃{�^����
		if(pCntlState[0].CustomState.wPressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT ){
			m_SelectIndex++;
			if(m_ButtonVec.size() <= m_SelectIndex){
				m_SelectIndex = 0;
			}
			m_SelectLock = true;
		}
		//	: �O�̃{�^����
		if(pCntlState[0].CustomState.wPressedButtons & XINPUT_GAMEPAD_DPAD_LEFT){
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
