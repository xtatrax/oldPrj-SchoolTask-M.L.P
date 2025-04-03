/**************************************************************************
 Measure.h

 class Measure  �錾
                                                    2012/04/20�@���O ���� �O
****************************************************************************/
#pragma once

#include "../StdAfx.h"
#include "ScoreNote.h"

namespace wiz{
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/**************************************************************************
 class Measure ;
 �p�r: ���߃N���X
	�������Ǘ�����
****************************************************************************/
class Measure;
typedef vector<Measure*>            MeasureVec;
typedef vector<Measure*>::size_type MeasureSizeType;
class Measure{
protected:
	SNoteVec		m_NotesVec;		//	: �ꔏ�̃f�[�^�z��
	SNoteSizeType	m_NoteVecSize;	//	: ���ߓ��̔���
	DWORD			m_dwNoteQt;		//	: ���ߓ��̉����̑���
/**************************************************************************
 wstring MeasureDec(
	wstring& i_str
 );
 �p�r  : �n���ꂽ���ߌQ���烏���Z�b�g�̖��߂����o��
 �߂�l: "END" �܂��� �P�Z�b�g�ɕ������ꂽ���� �܂��� i_str
***************************************************************************/
	wstring MeasureDec(wstring& i_str){

		//	: �擪�󔒂��폜
		Script::BlankDelete(i_str);

		//	: ���ߊJ�n�ʒu�܂œǂݔ�΂�
		while(!i_str.empty() && i_str.at(0) != '['){
			i_str.erase(0,1);
		}

		//	: ���߂̍Ō�ɓ��B������"END"���߂�Ԃ�
		if(i_str.empty())return L"END";

		//	: ���߂̏I���ʒu�̊l��
		wstring::size_type sz = i_str.find(']');

		//	: ����������Ȃ������獡�̏�Ԃ�Ԃ�
		if(sz == i_str.npos)return i_str;

		//	: ���̏�Ԃ��R�s�[
		wstring retstr = i_str;

		//	: �ǂݎ�����ʒu���폜
		i_str.erase(0,sz);

		//	: ����Ȃ��Ƃ�����폜
		retstr.erase(sz+1);

		//	: �ǂݎ�������߂�Ԃ�
		return retstr;
	}
public:
/**************************************************************************
 void Clear();
 �p�r  : �|�C���^�[�n�����o�̑S�폜
 �߂�l: ����
***************************************************************************/
	void Clear(){
		SNoteVec::iterator it;
		for(it = m_NotesVec.begin();it != m_NotesVec.end();it++){
			SafeDelete(*it);
		}
		m_NotesVec.clear();
	}
/**************************************************************************
 Measure(
	std::wstring i_Score	//	: 
 );
 �p�r  : �R���X�g���N�^
 �߂�l: ����
***************************************************************************/
	Measure(std::wstring i_Score )
		:m_dwNoteQt(0)
	{	
		wstring str;
		//	: "END"�̕����񂪋A���Ă���܂Ŗ��߂�ǂݍ���
		//	: �����f�[�^���\�z����
		while((str = MeasureDec(i_Score)) != L"END"){

			//	: �ꔏ�̃f�[�^���\�z
			ScoreNote* pScoreNote = new ScoreNote(str);
			//	: ���̏��ߓ��ɂ��鉹���̂����𐔂���
			m_dwNoteQt += pScoreNote->getNoteQt();
			//	: �����z��֒ǉ�
			m_NotesVec.push_back(pScoreNote);
		}
		m_NoteVecSize = m_NotesVec.size();
	};

/**************************************************************************
 ~Measure();
 �p�r  : �f�X�g���N�^
 �߂�l: ����
***************************************************************************/
	~Measure(){
		Clear();
	};
/**************************************************************************
 ScoreNote::NoneData getAddNotes(
	vector<ScoreNote*>::size_type i_ActiveNoteNum
);
 �p�r  : �ǉ����ׂ������̃f�[�^
 �߂�l: �ǉ�����ׂ�����
***************************************************************************/
	ScoreNote::NoneData getAddNotes(vector<ScoreNote*>::size_type i_ActiveNoteNum){
		//	: �m�[�g������Ȃ������ꍇ
		if(m_NoteVecSize == 0 || m_NoteVecSize <= i_ActiveNoteNum){
			return ScoreNote::NoneData( MEASUREENDFLAG );
		}

		return m_NotesVec[i_ActiveNoteNum]->getAllNotes();
	};
/**************************************************************************
 SNoteSizeType getNoteSize();
 �p�r  : ���ߓ��̔�����Ԃ�
 �߂�l: ���ߓ��̔���
***************************************************************************/
	SNoteSizeType getNoteSize(){
		return m_NoteVecSize;
	};
/**************************************************************************
 DWORD getNoteQt();
 �p�r  : ���ߓ��̉�������Ԃ�
 �߂�l: �������̉�����
***************************************************************************/
	DWORD getNoteQt(){
		return m_dwNoteQt;
	};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/

};
}
//end of namespace wiz.
