/**************************************************************************
 Stages.h

                                                    2012/04/20�@���O
****************************************************************************/
#pragma once

#include "StdAfx.h"
#include "ButtonPlate.h"
#include "Stage_Result.h"

namespace wiz{

/**************************************************************************
 class DebugStage : public Stage;
 �p�r: ���j���[�^�C�v�̃X�e�[�W�N���X
 �@�@�i���j���[�^�C�v�ł���΁A���̔h���N���X������ă��j���[�ɂ���Ǝg���₷���j
****************************************************************************/
class DebugStage : public MenuStage{
public:
/**************************************************************************
 DebugStage(
 LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
 Stage* Par = 0					//�e�X�e�[�W
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
	DebugStage(LPDIRECT3DDEVICE9 pD3DDevice,Stage* Par = 0);
};


/**************************************************************************
 class DebugMenu : public Stage;
 �p�r: �f�o�b�O�p�X�e�[�W
 �@�@�i������ʂ֒��ڈړ��ł���j
****************************************************************************/
class DebugMenu : public MenuStage{
public:
/**************************************************************************
 DebugStage(
 LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
 Stage* Par = 0					//�e�X�e�[�W
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
	DebugMenu(LPDIRECT3DDEVICE9 pD3DDevice,Stage* Par = 0);
};


//end of namespace wiz.
}
