/**************************************************************************
 Stages_Play.cpp

                                                    2012/04/20�@���� �O
****************************************************************************/
#include "StdAfx.h"
#include "Scene.h"
#include "MainFactory.h"
#include "Stage_Play.h"
#include "Shadow.h"
#include "OtaconFactory/OtaconFactory.h"
#include "TatraFactory/TatraFactory.h"
#define  MAX_SCORE (100)
namespace wiz{
/**************************************************************************
 PlayStage ��`��
****************************************************************************/
/**************************************************************************
PlayStage::PlayStage(
LPDIRECT3DDEVICE9 pD3DDevice	//�f�o�C�X
);
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
PlayStage::PlayStage(LPDIRECT3DDEVICE9 pD3DDevice,const Script::MLPHeader& Header,const Script::SCORELEVEL Level)
	:Stage(),
	 m_pJudgeLine(NULL),
	 m_pNotesLine1(NULL),m_pNotesLine2(NULL), m_pNotesLine3(NULL),m_pNotesLine4(NULL),
	 m_MusicScore( Header,Level),
	 m_Sound(m_MusicScore.m_MLPHeader, Level),
	 m_fTime(0),
	 m_bFirstFlag(true),
	 m_NoteBuffer(0),
	 m_ActiveMeasureNum(0),
	 m_ActiveNoteNum(0),
	 m_bPlayBassSoundFlag(false),
	 m_fMeasureChangeDelay( (60.0f / m_MusicScore.m_MLPHeader.Bpm) * 4 ),
	 m_pBGMCue(NULL)
{
	try{
		m_ResultFactor.m_BannerPath = Header.FilePath + Header.TitleBanner;
		this->m_IsDialog = false;
		m_pChildStage = 0;
//----------------------------------------------------------------------
		Ojou::OjouFactoryP(pD3DDevice,m_Vec,m_TextureVec);
//----------------------------------------------------------------------
		Tatra::TatraFactoryPlay(pD3DDevice,m_Vec,m_TextureVec);
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
//
//		�����[
//
		vector<Object*>::size_type sz = m_Vec.size();
		for(vector<Object*>::size_type i = 0;i < sz;i++){
			const type_info& info = typeid(*(m_Vec[i]));
			if(info == typeid(Ojou::Score)){
				m_pPlayScore = dynamic_cast<Ojou::Score*>(m_Vec[i]);
			}
			if(info == typeid(Ojou::Groove)){
				m_pGroove = dynamic_cast<Ojou::Groove*>(m_Vec[i]);
			}
		}
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
		m_ResultFactor.m_dwAllNoteQt = m_MusicScore.getALLNoteQt();
		m_fGreatLine	= 0.60f;
		m_fGoodLine		= 0.3f;
		m_fBadLine		= 0.2f;	

		//�J�����̃C���X�^���X������
        m_Vec.push_back(
			new Camera(D3DXVECTOR3( 0.0f, 3.0f,- 5.0f),D3DXVECTOR3( 0.0f, 0.0f, 0.0f),
				    1.0f, 100.0f,45.0f));

		//���[���̃}�e�B���A��
        D3DCOLORVALUE RainDiffuse	= {0.0f,0.0f,0.0f,0.0f};
        D3DCOLORVALUE RainSpecular	= {0.0f,0.0f,0.0f,0.0f};
        D3DCOLORVALUE RainAmbient	= {0.5f,0.5f,0.5f,1.0f};

		//���胉�C���̂̃}�e�B���A
        D3DCOLORVALUE JudgeLineDiffuse	= {1.0f,0.0f,0.0f,1.0f};
        D3DCOLORVALUE JudgeLineSpecular	= {1.0f,0.0f,0.0f,1.0f};
        D3DCOLORVALUE JudgeLineAmbient	= {1.0f,0.0f,0.0f,1.0f};

		//�m�[�g�̃}�e���A��
		float fPushNotesLineZ = 7.3f;
		float fNoteAnLineSizeZ = 0.2f;
		D3DXVECTOR3 vNotesSize = D3DXVECTOR3(0.35f,0.04f,fNoteAnLineSizeZ * fNoteAnLineSizeZ);
		D3DCOLORVALUE NotesDiffuse	= {0.2f,0.9f,0.9f,1.0f};
        D3DCOLORVALUE NotesSpecular	= {0.0f,0.0f,0.0f,0.0f};
        D3DCOLORVALUE NotesAmbient	= {0.0f,0.0f,0.0f,0.0f};

		//�m�[�g�̃}�e���A��
		D3DCOLORVALUE NullNotesDiffuse	= {0.0f,0.0f,0.0f,0.0f};
        D3DCOLORVALUE NullNotesSpecular	= {0.0f,0.0f,0.0f,0.0f};
        D3DCOLORVALUE NullNotesAmbient	= {0.0f,0.0f,0.0f,0.0f};

		Texture* pRainTx		= new Texture(pD3DDevice,L"Media/Texture/Play_rane2.png");
		m_TextureVec.push_back(pRainTx);
		//	: ���[������
		m_Vec.push_back(new Plate(
					pD3DDevice,
                    D3DXVECTOR3(0.0f,0.0f,2.0f),
					D3DXVECTOR3(1.5f,0.01f,3.4f),
					RainDiffuse,RainSpecular,RainAmbient,
					pRainTx->getTexture()));


		//	: �W���b�W���C������
		float fJudgeLineZ = -1.5;
		m_Vec.push_back((m_pJudgeLine = new JudgeLine(pD3DDevice ,
                    D3DXVECTOR3(-0.07f,0.01f,fJudgeLineZ),
					D3DXVECTOR3(1.45f,0.01f,fNoteAnLineSizeZ),
					JudgeLineDiffuse,JudgeLineSpecular,JudgeLineAmbient)));



		//	: �X�e�[�W��Object�z��̑��Ɏ����ł��z���I���Ă���
		m_Vec.push_back((m_pNotesLine1 = new NoteObjects(pD3DDevice,
			D3DXVECTOR3(-0.75f,0.0f,fPushNotesLineZ),
			vNotesSize,
			NotesDiffuse,
			NotesSpecular,
			NotesAmbient ,
			m_MusicScore.m_MLPHeader.DBGHiSpeed)));
		m_Vec.push_back((m_pNotesLine2 = new NoteObjects(pD3DDevice,
			D3DXVECTOR3(-0.30f,0.0f,fPushNotesLineZ),
			vNotesSize,
			NotesDiffuse,
			NotesSpecular,
			NotesAmbient ,
			m_MusicScore.m_MLPHeader.DBGHiSpeed)));
		m_Vec.push_back((m_pNotesLine3 = new NoteObjects(pD3DDevice,
			D3DXVECTOR3(0.15f,0.0f,fPushNotesLineZ),
			vNotesSize,
			NotesDiffuse,
			NotesSpecular,
			NotesAmbient,
			m_MusicScore.m_MLPHeader.DBGHiSpeed)));
		m_Vec.push_back((m_pNotesLine4 = new NoteObjects(pD3DDevice,
			D3DXVECTOR3(0.6f,0.0f,fPushNotesLineZ),
			vNotesSize,
			NotesDiffuse,
			NotesSpecular,
			NotesAmbient,
			m_MusicScore.m_MLPHeader.DBGHiSpeed)));

		//	: LRNote
		m_Vec.push_back((m_pAnalogNotesLine1 = new NoteObjects(pD3DDevice,
			D3DXVECTOR3(0.0f,-1.0f,fPushNotesLineZ),
			vNotesSize,
			NotesDiffuse,
			NotesSpecular,
			NotesAmbient,
			m_MusicScore.m_MLPHeader.DBGHiSpeed)));
		m_Vec.push_back((m_pAnalogNotesLine2 = new NoteObjects(pD3DDevice,
			D3DXVECTOR3(0.0f,-1.0f,fPushNotesLineZ),
			vNotesSize,
			NotesDiffuse,
			NotesSpecular,
			NotesAmbient,
			m_MusicScore.m_MLPHeader.DBGHiSpeed)));

		//	: OnlySoundNote		
		m_Vec.push_back((m_pNullNotesSound = new NoteObjects(pD3DDevice,
			D3DXVECTOR3(0.0f,-1.0f,fPushNotesLineZ),
			vNotesSize,
			NullNotesDiffuse,
			NullNotesSpecular,
			NullNotesAmbient,
			m_MusicScore.m_MLPHeader.DBGHiSpeed)));
		m_Vec.push_back((m_pJudgeSprite = new JudgeSprite(pD3DDevice,
			L"Media/Texture/Play_Judge.png",
			Rect(0,0,256,32),
			D3DXVECTOR3(256.0f/2.0f,32.0f/2.0f,0.0f),
			D3DXVECTOR3( ___MLP_WINDOWSIZE_WIDTH / 2.0f ,___MLP_WINDOWSIZE_HEIGHT / 2.0f, 0.0f),
			g_vZero,
			g_vOne,
			g_vZero,
			0xFFFFFF00)));

	//�e�I�u�W�F�N�g�̒ǉ�
		m_Vec.push_back(
			new Shadow(pD3DDevice));

		//	: �I�u�W�F�N�g�����n�_���画�胉�C���܂ł̒���
		NoteObjects::setLineLength( (fPushNotesLineZ - fJudgeLineZ) );
		//NoteObjects::setHiSpeed(m_MusicScore.m_MLPHeader.DBGHiSpeed);
	}
	catch(...){
		Clear();
		//�ăX���[
		throw;
	}
}
/**************************************************************************
PlayStage();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
PlayStage::~PlayStage(){
	
}
/**************************************************************************
 JUDGE PlayJudge(
	int i_Distance,
	float& o_JudgeRate,
	float& o_DistanceRate
	);
 �p�r: ���t�̔���
 �߂�l: ����ԍ�
***************************************************************************/
JUDGE PlayStage::PlayJudge2(float i_Distance,float& o_JudgeRate,float& o_DistanceRate){

	o_JudgeRate = 0;
	o_DistanceRate = 0;
	float fDisRate = (1.0f - abs( i_Distance / m_fBadLine) ) / 0.8f;
	if( fDisRate >= 1.0f){
		fDisRate = 1.0f;
	}
	if( fDisRate  >= 0.0f)
	{
		o_DistanceRate = fDisRate;
		if( fDisRate >= m_fGreatLine)
		{
			m_ResultFactor.m_dwGreatQt++;
			o_JudgeRate = 1.0f;
			return GREAT;
		}
		else
		if( fDisRate >= m_fGoodLine)
		{
			m_ResultFactor.m_dwGoodQt++;
			o_JudgeRate = 1.0f;
			return GOOD;
		}
		m_ResultFactor.m_dwBadQt++;
		o_JudgeRate    = 0.0f;
		return BAD;
	}
	m_ResultFactor.m_dwPoorQt++;
	return POOR;
}

/**************************************************************************
 JUDGE PlayJudge(
	int i_Distance,
	float& o_JudgeRate,
	float& o_DistanceRate
	);
 �p�r: ���t�̔���
 �߂�l: ����ԍ�
***************************************************************************/
JUDGE PlayStage::PlayJudge(NoteObjects* i_pNotes,bool i_bPressFlag){

	float judgeScoreRate = 0;
	float DisScoreRate = 0;
	JUDGE judge = POOR;
	//	: �Ή����郉�C���ɃI�u�W�F������
	if(i_pNotes->getSize() != 0 ) {
		//	: ���胉�C������̋���
		float dis1 =  i_pNotes->getFirstPos().z -m_pJudgeLine->getPos().z;
		float dis2 =  (i_pNotes->getFirstPos().z - (i_pNotes->setFirstSize().z / 2)) -m_pJudgeLine->getPos().z;
		if(i_pNotes->getFirstStatus() != 1 ){
			if(	(i_bPressFlag &&
				(judge = PlayJudge2(dis2 , judgeScoreRate , DisScoreRate )) != POOR) ||
				i_pNotes->getFirstBootFlag()
			){
				if(!i_pNotes->getFirstBootFlag()){
					//	: �Ή����鉹�̍Đ�
					if(i_pNotes->getFirstSoundNum())
						m_Sound.PlaySoundB(i_pNotes->getFirstSoundNum());
				}
				i_pNotes->setFirstBoot();
				if(i_pNotes->getFirstDeadFlag()){
					m_ResultFactor.m_dwGreatQt++;
					m_pJudgeSprite->setJudge(GREAT);
					m_pGroove->GrooveCalculation(1,GREAT);
				}
			}
		}
		else
		if(i_bPressFlag && (judge = PlayJudge2(dis1 , judgeScoreRate , DisScoreRate )) != POOR ){
			//	: ���Z�X�R�A�̌v�Z
			m_pPlayScore->g_iScore += int((MAX_SCORE * judgeScoreRate) * DisScoreRate);
			//	: �Ή����鉹�̍Đ�
			if(i_pNotes->getFirstSoundNum())
				m_Sound.PlaySoundB(i_pNotes->getFirstSoundNum());
			//	: ���S�t���O
			i_pNotes->setFirstDead();
			//	: ����̐ݒ�
			m_pJudgeSprite->setJudge(judge);
			//	: �Q�[�W����
			m_pGroove->GrooveCalculation(DisScoreRate,judge);
		}
	}
	return judge;
}

/**************************************************************************
 void PlayStage::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    const CONTROLER_STATE* pCntlState   //�R���g���[���[�̃X�e�[�^�X
	Command& Com					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �V�[����`��
 �߂�l: �Ȃ��B
***************************************************************************/
void PlayStage::Draw(LPDIRECT3DDEVICE9 pD3DDevice,const CONTROLER_STATE* pCntlState,Command& Com){
//	: �f�o�b�O�p
static float s_fLastScore = 0;
static int   s_iLastJudge = 0;
static WORD wLine1Button = XINPUT_GAMEPAD_X | XINPUT_GAMEPAD_DPAD_LEFT;
static WORD wLine2Button = XINPUT_GAMEPAD_A | XINPUT_GAMEPAD_DPAD_DOWN;
static WORD wLine3Button = XINPUT_GAMEPAD_Y | XINPUT_GAMEPAD_DPAD_UP;
static WORD wLine4Button = XINPUT_GAMEPAD_B | XINPUT_GAMEPAD_DPAD_RIGHT;
PlayCommandPacket pPCPacket;

WORD  wButtons = 0;
// �{�^������Ɣ���/////////////
	if( (wButtons = pCntlState[0].state.Gamepad.wButtons) ){
		WORD  wPressedButtons = pCntlState[0].CustomState.wPressedButtons;
		//	: �{�^���������ꂽ
		if( wButtons & (wLine1Button)){
			PlayJudge(m_pNotesLine1 , (wPressedButtons & wLine1Button) != 0);
		}
		if( wButtons & (wLine2Button) ){
			PlayJudge(m_pNotesLine2 , (wPressedButtons & wLine2Button) != 0);
		}
		if( wButtons & (wLine3Button) ){
			PlayJudge(m_pNotesLine3 , (wPressedButtons & wLine3Button) != 0);
		}
		if( wButtons & (wLine4Button) ){
			PlayJudge(m_pNotesLine4 , (wPressedButtons & wLine4Button) != 0);
		}
	}
	if( m_pNotesLine1->getSize() > 0 &&
		m_pNotesLine1->getFirstStatus() == 3 &&
		!m_pNotesLine1->getFirstBootFlag() &&
		m_pNotesLine1->getFirstDeadFlag()
	){
		m_ResultFactor.m_dwBadQt++;
		m_pJudgeSprite->setJudge(BAD);
		m_pGroove->GrooveCalculation(1,BAD);
	}

	if( m_pNotesLine2->getSize() > 0 &&
		m_pNotesLine2->getFirstStatus() == 3 &&
		!m_pNotesLine2->getFirstBootFlag() &&
		m_pNotesLine2->getFirstDeadFlag()
	){
		m_ResultFactor.m_dwBadQt++;
		m_pJudgeSprite->setJudge(BAD);
		m_pGroove->GrooveCalculation(1,BAD);
	}
	if( m_pNotesLine3->getSize() > 0 &&
		m_pNotesLine3->getFirstStatus() == 3 &&
		!m_pNotesLine3->getFirstBootFlag() &&
		m_pNotesLine3->getFirstDeadFlag()
	){
		m_ResultFactor.m_dwBadQt++;
		m_pJudgeSprite->setJudge(BAD);
		m_pGroove->GrooveCalculation(1,BAD);
	}
	if( m_pNotesLine4->getSize() > 0 &&
		m_pNotesLine4->getFirstStatus() == 3 &&
		!m_pNotesLine4->getFirstBootFlag() &&
		m_pNotesLine4->getFirstDeadFlag()
	){
		m_ResultFactor.m_dwBadQt++;
		m_pJudgeSprite->setJudge(BAD);
		m_pGroove->GrooveCalculation(1,BAD);
	}

	//	: �����Ȃ���
	if( m_pNullNotesSound->getSize() != 0 &&
		m_pNullNotesSound->getFirstPos().z <= m_pJudgeLine->getPos().z &&
		m_pNullNotesSound->getFirstSoundNum())
	{
		m_Sound.PlaySound(m_pNullNotesSound->getFirstSoundNum());
		m_pNullNotesSound->setFirstDead();
	}
////////////////////////////////
	bool endFlag = false;
	static float s_fMusicBeginTime = 0;
	static float s_fMusicTime = 0;
	if(m_bFirstFlag){
		//	: �Ȃ��J�n����܂łɏ������Ԃ�u������
		if(m_bFirstFlag && (m_fTime += Tempus::getOneFrameTime()) >=  m_MusicScore.m_MLPHeader.FirstDelay){
			m_bFirstFlag = false;
			m_fMeasureFirstTime = (float)Tempus::getClockSec();
			m_fFirstTime = (float)Tempus::getClockSec();
		}
	}
	else{
		//	: �v���O�������s����̌o�ߎ���
		float fNowTime = (float)Tempus::getClockSec();

		//	: ���Ɣ��̊Ԃ̎���
		float fNoteDelay = m_fMeasureChangeDelay / m_MusicScore.getNoteSize(m_ActiveMeasureNum);
		//	: �x�[�X�������Ă��Ȃ� ���� ��莞�Ԃ��������特��炷
		if(!m_bPlayBassSoundFlag && m_fFirstTime + (m_fMeasureChangeDelay * 2) <= fNowTime){
			m_Sound.PlaySound(0);
			s_fMusicBeginTime = (float)Tempus::getClockSec();
			m_bPlayBassSoundFlag = true;
		}
		//	: ���߈ړ�����
		if(m_fFirstTime + (m_fMeasureChangeDelay * (m_ActiveMeasureNum+1)) <= fNowTime){
			m_ActiveMeasureNum++;
			m_ActiveNoteNum = 0;
			m_fMeasureFirstTime = (float)Tempus::getClockSec();
		}
		//	: ���t�I���t���O
		if(m_ActiveMeasureNum >= m_MusicScore.getMeasureSize()){
			endFlag = true;
		}
		//	: �����̔��s
		if(m_fMeasureFirstTime + (fNoteDelay * m_ActiveNoteNum) <= fNowTime){
			BYTE byteBuf;
			m_NoteBuffer = m_MusicScore.getAddNotes(m_ActiveMeasureNum , m_ActiveNoteNum);
			if((byteBuf = m_NoteBuffer.getLine1Note())){
				if(byteBuf != 3){
					m_pNotesLine1->AddNote(m_NoteBuffer.m_uniUINT8[2],byteBuf);
				}
				m_pNotesLine1->setLastStatus(byteBuf);
			}else if(m_NoteBuffer.m_uniUINT8[2]){
				m_pNullNotesSound->AddNote(m_NoteBuffer.m_uniUINT8[2],byteBuf);
			}
			if((byteBuf = m_NoteBuffer.getLine2Note())){
				if(byteBuf != 3){
					m_pNotesLine2->AddNote(m_NoteBuffer.m_uniUINT8[3],byteBuf);
				}
				m_pNotesLine2->setLastStatus(byteBuf);
			}else if(m_NoteBuffer.m_uniUINT8[3]){
				m_pNullNotesSound->AddNote(m_NoteBuffer.m_uniUINT8[3],byteBuf);
			}
			if((byteBuf = m_NoteBuffer.getLine3Note())){
				if(byteBuf != 3){
					m_pNotesLine3->AddNote(m_NoteBuffer.m_uniUINT8[4],byteBuf);
				}
				m_pNotesLine3->setLastStatus(byteBuf);
			}else if(m_NoteBuffer.m_uniUINT8[4]){
				m_pNullNotesSound->AddNote(m_NoteBuffer.m_uniUINT8[4],byteBuf);
			}
			if((byteBuf = m_NoteBuffer.getLine4Note())){
				if(byteBuf != 3){
					m_pNotesLine4->AddNote(m_NoteBuffer.m_uniUINT8[5],byteBuf);
				}
				m_pNotesLine4->setLastStatus(byteBuf);
			}else if(m_NoteBuffer.m_uniUINT8[5]){
				m_pNullNotesSound->AddNote(m_NoteBuffer.m_uniUINT8[5],byteBuf);
			}
			if((byteBuf = m_NoteBuffer.getAnalogLine1Note())){
				if(byteBuf != 3){
					m_pAnalogNotesLine1->AddNote(m_NoteBuffer.m_uniUINT8[6],byteBuf);
				}
				m_pAnalogNotesLine1->setLastStatus(byteBuf);
			}else if(m_NoteBuffer.m_uniUINT8[6]){
				m_pNullNotesSound->AddNote(m_NoteBuffer.m_uniUINT8[6],byteBuf);
			}
			if((byteBuf = m_NoteBuffer.getAnalogLine2Note())){
				if(byteBuf != 3){
					m_pAnalogNotesLine2->AddNote(m_NoteBuffer.m_uniUINT8[7],byteBuf);
				}
				m_pAnalogNotesLine2->setLastStatus(byteBuf);
			}else if(m_NoteBuffer.m_uniUINT8[7]){
				m_pNullNotesSound->AddNote(m_NoteBuffer.m_uniUINT8[7],byteBuf);
			}
			m_ActiveNoteNum++;
		}
	}
	pPCPacket.m_fJudgePosZ   = m_pJudgeLine->getPos().z;
	pPCPacket.m_fMeasureChangeDelay = m_fMeasureChangeDelay;
	pPCPacket.m_pJudgeSprite = m_pJudgeSprite;
	pPCPacket.m_pRankFactor  = &m_ResultFactor;
	Com.m_Command = SENDITEM;
	Com.m_Param1  = (DWORD)&pPCPacket;
	Com.m_Param2  = (DWORD)m_pGroove;
	//�Q�[����ʂ̕\��
	vector<Object*>::size_type sz = m_Vec.size();
	for(vector<Object*>::size_type i = 0;i < sz;i++){
		m_Vec[i]->Draw(pD3DDevice,m_Vec,pCntlState,Com);
	}

	//���S��ŃR�}���h�̃N���A
	Com.Clear();

	//	: �ⓚ���pGAMEOVER
	if(m_pGroove->getGaugePercent() <= 0.0f){
		Com.m_Command = Scene::SC_OPEN_GAMEOVER;
	}

	//	: ���ʉ�ʂ�
	if( endFlag &&
		m_pNotesLine1->getSize() <= 0&&
		m_pNotesLine2->getSize() <= 0&&
		m_pNotesLine3->getSize() <= 0&&
		m_pNotesLine4->getSize() <= 0
		){
		m_ResultFactor.m_fGaugePar = m_pGroove->getGaugePercent();
		Com.m_Command = Scene::SC_OPEN_RESULT;
		Com.m_Param1  = m_pPlayScore->g_iScore;
		Com.m_Param2  = (DWORD)&m_ResultFactor;
	}
#if defined(DEBUG) || defined(_DEBUG)
	double time = Tempus::getClockSec() - s_fMusicBeginTime;
	int h = (int)(time / (60 * 60)) % 24;
	int m = (int)(time / 60) % 60;
	int S = (int)(time) % 60;

	wiz::Debugger::DBGSTR::addStr(
		L"PlayStageTime			= %f\n"
		L"%d�� %d�� %d�b %d�_\n"
		L"m_ActiveMeasureNum	= %d\n"
		L"m_ActiveNoteNum		= %d\n"
		L"LastScore				= %f\n"
		L"LastJudge				= %d\n"
		L"Active��Pitch         = %d\n"
		L"Mouse %04d / %04d\n",
		m_fTime,
		h,m,S,int(time * 100) % 100,
		m_ActiveMeasureNum,
		m_ActiveNoteNum,
		s_fLastScore,
		s_iLastJudge,
		pCntlState[0].MousePoint.x,
		pCntlState[0].MousePoint.y
		);
#endif
}

}
//end of namespace wiz.
