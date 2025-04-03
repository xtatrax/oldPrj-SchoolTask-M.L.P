/**************************************************************************
 Stages_Play.h

                                                    2012/04/20�@���O ���� �O
****************************************************************************/
#pragma once

#include "StdAfx.h"
#include "Stage_Menu.h"
#include "TatraFactory/ScriptManager.h"
#include "TatraFactory/JudgeLine.h"
#include "TatraFactory/NoteObjects.h"
#include "TatraFactory/MusicScore.h"
#include "TatraFactory/JudgeSprite.h"
#include "OjouFactory/OjouFactoryP.h"
#include "TSound.h"
#include "Scene.h"
namespace wiz{
typedef	Ojou::Groove GrooveGauge;

/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/**************************************************************************
 class PlayStage : public Stage;
 �p�r: �Q�[���X�e�[�W�N���X
****************************************************************************/
class PlayStage : public Stage{
	JudgeLine*		m_pJudgeLine;		// :���胉�C���ւ̃|�C���^�[              ��
	JudgeSprite*	m_pJudgeSprite;		// :�W���b�W������                        ��
	NoteObjects*	m_pNotesLine1;		// :���C��1�̕��ւ̃|�C���^�[             ��
	NoteObjects*	m_pNotesLine2;		// :���C��2�̕��ւ̃|�C���^�[             �� Object�z��ɂ��o�^���邯�ǁA 
	NoteObjects*	m_pNotesLine3;		// :���C��3�̕��ւ̃|�C���^�[             ���T����Ԃ��Ȃ����߂Ɏ����Ŋo���Ă����B
	NoteObjects*	m_pNotesLine4;		// :���C��4�̕��ւ̃|�C���^�[             �� �������̊Ǘ���Object�z��ɊǗ����Ă��炤
	NoteObjects*	m_pAnalogNotesLine1;	// :�A�i���O���C��1�̕��ւ̃|�C���^�[ ��
	NoteObjects*	m_pAnalogNotesLine2;	// :�A�i���O���C��2�̕��ւ̃|�C���^�[ ��
	NoteObjects*	m_pNullNotesSound;	// :�m�[�g�̂Ȃ����̈ꗗ�ւ̃|�C���^�[    ��
	Ojou::Groove*	m_pGroove;			// :�Q�[�W�N���X�ւ̃|�C���^�[            ��
	Ojou::Score*	m_pPlayScore;		// :�_���L��&�`��N���X                   ��

	MusicScore		m_MusicScore;		// :�y��
	XACTSound		m_Sound;			// :�������C�u�����I��
	IXACT3Cue*		m_pBGMCue;
	ScoreNote::NoneData	m_NoteBuffer;	//
	MeasureSizeType		m_ActiveMeasureNum;
	SNoteSizeType		m_ActiveNoteNum;
	ResultFactor		m_ResultFactor;
	float			m_fGreatLine;			// :�O���[�g�ȃ��C��
	float			m_fGoodLine;			// :�O�b�h�ȃ��C��
	float			m_fBadLine;				// :����̍Œ�����C��
	float			m_fTime;				// :�X�e�[�W�ǂݍ��݂���̌o�ߎ���
	float			m_fMeasureFirstTime;	// :
	float			m_fFirstTime;			// :
	float			m_fMeasureChangeDelay;	// :
	bool			m_bFirstFlag;			// :��ԍŏ����̃t���O
	bool			m_bPlayBassSoundFlag;	// :
public:	
	enum {
		PLAYSTAGE = Scene::PLAY_STAGE_COMMAND,
		SENDITEM  ,

	};
/**************************************************************************
PlayStage(
LPDIRECT3DDEVICE9 pD3DDevice	//�f�o�C�X
);
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
	PlayStage(LPDIRECT3DDEVICE9 pD3DDevice,const Script::MLPHeader& Header,const Script::SCORELEVEL Level);
/**************************************************************************
PlayStage();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	~PlayStage();
/**************************************************************************
 JUDGE PlayJudge(int i_Distance);
 �p�r: ���t�̔���
 �߂�l: ����ԍ�
***************************************************************************/
	JUDGE PlayJudge(NoteObjects* i_pNotes,bool i_bPressFlag);
/**************************************************************************
 JUDGE PlayJudge(int i_Distance);
 �p�r: ���t�̔���
 �߂�l: ����ԍ�
***************************************************************************/
	JUDGE PlayJudge2(float i_Distance,float& o_JudgeRate,float& o_DistanceRate);
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
