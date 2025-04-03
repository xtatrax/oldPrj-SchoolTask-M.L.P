/**************************************************************************
 MusicScore.h

 class MusicScore  �錾
                                                    2012/04/20�@���O ���� �O
****************************************************************************/
#pragma once

#include "../StdAfx.h"
#include "Measure.h"

namespace wiz{


/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/**************************************************************************
 class MusicScore ;
 �p�r: �y���N���X
	���߂��Ǘ�����
****************************************************************************/
class MusicScore{
private:
	MeasureVec	m_MeasureVec;			//	: ���ߔz��
	MeasureSizeType m_MeasureVecSize;	//	: ���߂̐�
	DWORD		m_ALLNoteQt;			//	: ���̊y���Ɋ܂܂�鉹���̑���
public:
	Script::MLPHeader m_MLPHeader;
/**************************************************************************
 void Clear();
 �p�r  : �|�C���^�n�f�[�^�̑S�폜
 �߂�l: ����
***************************************************************************/
	void Clear(){
		MeasureVec::iterator it;
		for(it = m_MeasureVec.begin();it != m_MeasureVec.end();it++){
			SafeDelete(*it);
		}
		m_MeasureVec.clear();
	}
/**************************************************************************
 MusicScore(
	 Script::MLPHeader  i_MLSheader,	//	: �v���C����y�Ȃ̃w�b�_�[�f�[�^
	 Script::SCORELEVEL i_Level			//	: �v���C���郌�x�����
 );
 �p�r: 
 �߂�l: 
***************************************************************************/
	MusicScore( Script::MLPHeader i_MLSheader, Script::SCORELEVEL i_Level )
		:m_ALLNoteQt(0)
	{
		//	: �w�b�_�[�󂯎��
		m_MLPHeader = i_MLSheader;
		//�y���Ǎ���//////////////////
		//	: �ǂݍ��ރt�@�C���ƃ��x���̎w��
		Script::ScriptManager::BodyReadBegin(m_MLPHeader.FilePath + m_MLPHeader.FileName,i_Level);
		std::wstring wstrScriptBuffer;	//	: �Ǎ��݃o�b�t�@
		//	: END���߂�������܂ň�s�ǂݍ���
		while(( wstrScriptBuffer = Script::ScriptManager::BodyRead()) != L"END"){
			Measure* pMeasure = NULL;
			m_MeasureVec.push_back((pMeasure = new Measure( wstrScriptBuffer )));
			m_ALLNoteQt += pMeasure->getNoteQt();
		}
		//	: �Ǎ��݊����̍��}
		Script::ScriptManager::BodyReadEnd();
		//////////////////////////////
		m_MeasureVecSize = m_MeasureVec.size();
	}
/**************************************************************************
 �p�r: 
 �߂�l: 
***************************************************************************/
	ScoreNote::NoneData getAddNotes(MeasureSizeType i_ActiveMeasureNum,SNoteSizeType i_ActiveNoteNum){
		if(m_MeasureVecSize <= i_ActiveMeasureNum)
			return SCOREENDFLAG;
		return m_MeasureVec[i_ActiveMeasureNum]->getAddNotes(i_ActiveNoteNum);
	
	}
/**************************************************************************
 �p�r: 
 �߂�l: 
***************************************************************************/
	MeasureSizeType getMeasureSize( ){
		return m_MeasureVecSize;
	}
/**************************************************************************
 �p�r: 
 �߂�l: 
***************************************************************************/
	SNoteSizeType getNoteSize(MeasureSizeType i_ActiveMeasureNum){
		if(i_ActiveMeasureNum < m_MeasureVecSize)
			return m_MeasureVec[i_ActiveMeasureNum]->getNoteSize();
		return 0;
	}
/**************************************************************************
 �p�r: 
 �߂�l: 
***************************************************************************/
	DWORD getALLNoteQt(){
		return m_ALLNoteQt;
	}
/**************************************************************************
 �p�r: 
 �߂�l: 
***************************************************************************/
	~MusicScore(){
		Clear();
	}

};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/



}
//end of namespace wiz.
