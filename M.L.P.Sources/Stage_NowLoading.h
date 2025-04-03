/**************************************************************************
 Stages.h

                                                    2012/04/20�@���O ���� �O
****************************************************************************/
#pragma once

#include "StdAfx.h"
#include "Scene.h"
#include "TatraFactory/SHS.h"
#include "TatraFactory/WhiteoutEffect.h"
namespace wiz{
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/**************************************************************************
 class NowLoading : public Stage;
 �p�r: �Q�[���X�e�[�W�N���X
****************************************************************************/
class NowLoading : public Stage{
	Command				m_ReserveCommand;
	Script::MLPHeader	m_ReserveHeader;
	float				m_fTimeAccumulator;
	bool				m_bWhiteout;
	WhiteoutEffect*		m_pWEffect;
public:
	Stage*				m_ReserveStage;
/**************************************************************************
NowLoading(
LPDIRECT3DDEVICE9 pD3DDevice	//�f�o�C�X
);
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
	NowLoading(LPDIRECT3DDEVICE9 pD3DDevice,Script::MLPHeader& i_Header,Command i_Command);
/**************************************************************************
NowLoading();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	~NowLoading();
/**************************************************************************
 void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    const CONTROLER_STATE* pCntlState,   //�R���g���[���[�̃X�e�[�^�X
	Command& Com					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �V�[����`��
 �߂�l: �Ȃ��B
***************************************************************************/
    virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,const CONTROLER_STATE* pCntlState,Command& Com);
};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/

}
//end of namespace wiz.
