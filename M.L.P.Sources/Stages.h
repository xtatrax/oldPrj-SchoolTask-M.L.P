/**************************************************************************
 Stages.h

                                                    2012/04/20�@���O
****************************************************************************/
#pragma once

#include "StdAfx.h"
#include "Stage_Menu.h"

namespace wiz{



/**************************************************************************
 class GameDialog : public MenuStage;
 �p�r: �Q�[���̃_�C�A���O�N���X
****************************************************************************/
class GameDialog : public MenuStage{
public:
/**************************************************************************
GameDialog(
LPDIRECT3DDEVICE9 pD3DDevice	//�f�o�C�X
Stage* Par						//�e�X�e�[�W
);
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
	GameDialog(LPDIRECT3DDEVICE9 pD3DDevice,Stage* Par);
};



}
//end of namespace wiz.
