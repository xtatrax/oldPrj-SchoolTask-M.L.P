/**************************************************************************
 Stages.h

                                                    2012/04/20�@���O
****************************************************************************/
#pragma once

#include "StdAfx.h"
#include "Stage_Menu.h"
#include "Stage_Play.h"

namespace wiz{


/**************************************************************************
 class ResultMenu : public MenuStage;
 �p�r: ���C�����j���[�N���X
****************************************************************************/
class ResultMenu : public MenuStage{
public:
/**************************************************************************
ResultMenu(
LPDIRECT3DDEVICE9 pD3DDevice	//�f�o�C�X
);
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
	ResultMenu(LPDIRECT3DDEVICE9 pD3DDevice,int Score,ResultFactor& rankFactor);
};

}
//end of namespace wiz.
