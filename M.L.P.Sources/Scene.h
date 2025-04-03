/**************************************************************************
 Scene.h

 class Scene; �錾
                                                    2012/04/17�@���O ���� �O
****************************************************************************/
#pragma once

#include "StdAfx.h"
namespace wiz{

/**************************************************************************
 class Scene;
 �p�r: �V�[���N���X
****************************************************************************/
class Scene
{
	Command Com;
	Stage* m_pRootStage;
	Stage* StgBuf;
	void Clear();
public:
	enum CommandType{
		SC_NONE = 0,
		SC_EXIT,				//	: �I��
		SC_OPEN_TITLE,			//	: �^�C�g����ʂ�
		SC_OPEN_MUSICSELECT,	//	: �~���[�W�b�N�Z���N�g��ʂ�
		SC_OPEN_PLAY,			//	: �v���C���O�X�e�[�W��
		SC_OPEN_RESULT,			//	: ���ʕ\���X�e�[�W��
		SC_OPEN_GAMEOVER,		//	: �Q�[���I�[�o�[�X�e�[�W��
		SC_OPEN_DBGM,			//	: �f�o�b�O�X���j���[��
		SC_OPEN_DBGS,			//	: �f�o�b�O�X�e�[�W��
		SC_RET_GAME,			//	: 
		CREATE_NUM,				//	:
		TITLE_STAGE_COMMAND			= 1000,	//	:
		SELECT_STAGE_COMMAND		= 2000,	//	:
		PLAY_STAGE_COMMAND			= 3000,	//	:
		RESULT_STAGE_COMMAND		= 4000,	//	:
		NOWLOADING_STAGE_COMMAND	= 5000	//	:
		
	};
private:
	enum{
		SC_CREATE_TITLE = CREATE_NUM+1,	//	: �^�C�g����ʂ�
		SC_CREATE_MUSICSELECT,	//	: �~���[�W�b�N�Z���N�g��ʂ�
		SC_CREATE_PLAY,			//	: �v���C���O�X�e�[�W
		SC_CREATE_RESULT,		//	: ���ʕ\���X�e�[�W��
		SC_CREATE_GAMEOVER,		//	: �Q�[���I�[�o�[�X�e�[�W��
		SC_CREATE_DBGM,			//	: �f�o�b�O�X���j���[��
		SC_CREATE_DBGS,			//	: �f�o�b�O�X�e�[�W��
	};
public:
/**************************************************************************
 Scene(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
 );
 �p�r: �R���X�g���N�^�B�V�[���𐶐�
 �߂�l: �Ȃ��B���s�������O��throw
***************************************************************************/
    Scene(LPDIRECT3DDEVICE9 pD3DDevice);
/**************************************************************************
 ~Scene();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
    ~Scene();
/**************************************************************************
 void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    const CONTROLER_STATE* pCntlState   //�R���g���[���[�̃X�e�[�^�X
 );
 �p�r: �V�[����`��
 �߂�l: �Ȃ��B
***************************************************************************/
    void Draw(LPDIRECT3DDEVICE9 pD3DDevice,const CONTROLER_STATE* pCntlState);
};
}
//end of namespace wiz.

