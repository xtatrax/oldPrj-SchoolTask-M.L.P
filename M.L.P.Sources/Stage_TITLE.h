/**************************************************************************
 Stages.h

                                                    2012/04/20�@���O
****************************************************************************/
#pragma once

#include "StdAfx.h"
#include "Stage_Menu.h"
#include "TatraFactory/Button.h"
#include "OjouFactory/OjouFactory.h"

namespace wiz{


/**************************************************************************
 class TitleMenu : public MenuStage;
 �p�r: ���C�����j���[�N���X
****************************************************************************/
class TitleMenu : public MenuStage{
public:
/**************************************************************************
TitleMenu(
LPDIRECT3DDEVICE9 pD3DDevice	//�f�o�C�X
Stage* Par = 0					//�e�X�e�[�W
);
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
	TitleMenu(LPDIRECT3DDEVICE9 pD3DDevice,Stage* Par = 0);
	void Draw(LPDIRECT3DDEVICE9 pD3DDevice,const CONTROLER_STATE* pCntlState,Command& Com);
};
}
//end of namespace wiz.
