/**************************************************************************
 Stages.h

                                                    2012/04/20�@���O
****************************************************************************/
#pragma once

#include "StdAfx.h"
#include "Stage_Menu.h"

namespace wiz{


/**************************************************************************
 class GameOver : public MenuStage;
 �p�r: ���C�����j���[�N���X
****************************************************************************/
class GameOver : public MenuStage{
public:
/**************************************************************************
GameOver(
LPDIRECT3DDEVICE9 pD3DDevice	//�f�o�C�X
);
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
	GameOver(LPDIRECT3DDEVICE9 pD3DDevice);
/**************************************************************************
 void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    const CONTROLER_STATE* pCntlState,   //�R���g���[���[�̃X�e�[�^�X
	Command& Com					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �X�e�[�W��`��
 �߂�l: �Ȃ��B
***************************************************************************/
virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,const CONTROLER_STATE* pCntlState,Command& Com);

};

}
//end of namespace wiz.
