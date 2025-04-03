/**************************************************************************
 Stages.h

                                                    2012/04/20�@���O ���� �O
****************************************************************************/
#pragma once

#include "../StdAfx.h"

#define	NOTESDATAMASK					 (0x0000000000000FFF)
#define	LINE1NOTEDATAMASK				 (0x0000000000000003)
#define	LINE2NOTEDATAMASK				 (0x000000000000000C)
#define	LINE3NOTEDATAMASK				 (0x0000000000000030)
#define	LINE4NOTEDATAMASK				 (0x00000000000000C0)
#define	ANALOGLINE1NOTEDATAMASK			 (0x0000000000000300)
#define	ANALOGLINE2NOTEDATAMASK			 (0x0000000000000C00)
#define	ANALOGLINE1NOTEDATABYTEMASK		 (0x0000000000000003)
#define	ANALOGLINE2NOTEDATABYTEMASK		 (0x000000000000000C)
#define NOTEENDFLAG						 (0x0000000000001000)
#define MEASUREENDFLAG					 (0x0000000000004000)
#define SCOREENDFLAG					 (0x0000000000008000)
#define	LINE1SOUNDINDEXMASK				 (0x0000000000FF0000)
#define	LINE2SOUNDINDEXMASK				 (0x00000000FF000000)
#define	LINE3SOUNDINDEXMASK				 (0x000000FF00000000)
#define	LINE4SOUNDINDEXMASK				 (0x0000FF0000000000)
#define	ANALOGLINE1SOUNDINDEXMASK		 (0x00FF000000000000)
#define	ANALOGLINE2SOUNDINDEXMASK		 (0xFF00000000000000)
namespace wiz{
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/**************************************************************************
 class ScoreNote ;
 �p�r: �����N���X
	�e�{�^�����Ƃ̉����̕ێ��Ɛ��������
****************************************************************************/
class ScoreNote;
typedef vector<ScoreNote*>            SNoteVec;
typedef vector<ScoreNote*>::size_type SNoteSizeType;
class ScoreNote{
public:
	// union ���Ă݂������������E���E
	union NoneData{
		/******************************************************************	
		**	0xFF FF FF FF FF FF FF FF
		**
		**	BYTE 
		**	 �P �ʏ�{�^���S�̉����f�[�^
		**		1�`2Bit�� �FLine1�ɑΉ����鉹��	
		**		3�`4Bit�� �FLine2�ɑΉ����鉹��	
		**		5�`6Bit�� �FLine3�ɑΉ����鉹��	
		**		7�`8Bit�� �FLine4�ɑΉ����鉹��	
		**	 �Q �A�i���O�X�e�B�b�N�̉����f�[�^�{��
		**		1�`2Bit�� �FAnalogLine1�ɑΉ����鉹��	
		**		3�`4Bit�� �FAnalogLine2�ɑΉ����鉹��	
		**		5�`6Bit�� �F�󂫗̈�
		**		   7Bit�� �FMeasureEndFlag
		**		   8Bit�� �FScoreEndFlag
		**	 �R L1�����ɑΉ����鉹���f�[�^�ԍ�
		**	 �S L2�����ɑΉ����鉹���f�[�^�ԍ�
		**	 �T L3�����ɑΉ����鉹���f�[�^�ԍ�
		**	 �U L4�����ɑΉ����鉹���f�[�^�ԍ�
		**	 �V AL1�����ɑΉ����鉹���f�[�^�ԍ�
		**	 �W AL2�����ɑΉ����鉹���f�[�^�ԍ�
		**
		*******************************************************************/
		UINT64		m_uniNoteQWORD;
		UINT16		m_uniNoteData;
		UINT16		m_uniUINT16[4];
		UINT8		m_uniUINT8[8];
		NoneData(){}
		NoneData(UINT64 i_64){
			m_uniNoteQWORD = i_64;	
		}
		NoneData(UINT16 i_12,UINT16 i_34,UINT16 i_56,UINT16 i_78){
			m_uniUINT16[0] = i_12;	
			m_uniUINT16[1] = i_34;	
			m_uniUINT16[2] = i_56;	
			m_uniUINT16[3] = i_78;	
		}
		NoneData(UINT8 i_1,UINT8 i_2,UINT8 i_3,UINT8 i_4,UINT8 i_5,UINT8 i_6,UINT8 i_7,UINT8 i_8){
			m_uniUINT8[0] = i_1;	
			m_uniUINT8[1] = i_2;	
			m_uniUINT8[2] = i_3;	
			m_uniUINT8[3] = i_4;	
			m_uniUINT8[4] = i_5;	
			m_uniUINT8[5] = i_6;	
			m_uniUINT8[6] = i_7;	
			m_uniUINT8[7] = i_8;	
		}

		BYTE getLine1Note(){
			return ((m_uniUINT8[0] & LINE1NOTEDATAMASK));
		}
		BYTE getLine2Note(){
			return ((m_uniUINT8[0] & LINE2NOTEDATAMASK) >> 2);//
		}
		BYTE getLine3Note(){
			return ((m_uniUINT8[0] & LINE3NOTEDATAMASK) >> 4);//
		}
		BYTE getLine4Note(){
			return ((m_uniUINT8[0] & LINE4NOTEDATAMASK) >> 6);//
		}
		BYTE getAnalogLine1Note(){
			return ((m_uniUINT8[1] & ANALOGLINE1NOTEDATABYTEMASK));
		}
		BYTE getAnalogLine2Note(){
			return ((m_uniUINT8[1] & ANALOGLINE2NOTEDATABYTEMASK) >> 2);//
		}
	}m_NoteData;
	BYTE m_byteNoteQt;
public:
	enum NOTETYPE{
		REST		= 0,	//	: [00]�x��
		NOTE		= 1,	//	: [01]����
		LONGBEGIN	= 2,	//	: [10]�����J�n
		LONGEND		= 3,	//	: [11]�����I��
	};
	ScoreNote(NOTETYPE Line1Note = REST,NOTETYPE Line2Note = REST,NOTETYPE Line3Note = REST,NOTETYPE Line4Note = REST,
		NOTETYPE AnalogLine1Note = REST,NOTETYPE AnalogLine2Note = REST,
		BYTE Line1SoundIndex = REST,BYTE Line2SoundIndex = REST,BYTE Line3SoundIndex = REST,BYTE Line4SoundIndex = REST,
		BYTE AnalogLine1SoundIndex = REST,BYTE AnalogLine2SoundIndex = REST)
	{
		m_NoteData.m_uniNoteQWORD = 0;
		m_NoteData.m_uniUINT8[0] = Line1Note + (Line2Note << 2) + (Line3Note << 4) + (Line4Note << 6);
		m_NoteData.m_uniUINT8[1] = AnalogLine1Note + (AnalogLine1Note << 2);
		m_NoteData.m_uniUINT8[2] = Line1SoundIndex;
		m_NoteData.m_uniUINT8[3] = Line2SoundIndex;
		m_NoteData.m_uniUINT8[4] = Line3SoundIndex;
		m_NoteData.m_uniUINT8[5] = Line4SoundIndex;
		m_NoteData.m_uniUINT8[6] = AnalogLine1SoundIndex;
		m_NoteData.m_uniUINT8[7] = AnalogLine2SoundIndex;
	}
	ScoreNote(wstring i_str)
	{
		m_NoteData.m_uniNoteQWORD = 0;

		Script::AllBlankDeleteAll(i_str);
		wstring sbuf;
		i_str.erase(0,1);
		int Line1Note		= wcstol( &i_str.at(0), NULL , 10 ) & 0x3 ;
		i_str.erase(0,2);
		sbuf = i_str;
		sbuf.erase(2);
		int Line1SoundIndex	= wcstol( sbuf.c_str(), NULL , 16 ) & 0xFF;
		
		i_str.erase(0,3);
		int Line2Note		= wcstol( &i_str.at(0), NULL , 10 ) & 0x3 ;
		i_str.erase(0,2);
		sbuf = i_str;
		sbuf.erase(2);
		int Line2SoundIndex	= wcstol( sbuf.c_str(), NULL , 16 ) & 0xFF;
		
		i_str.erase(0,3);
		int Line3Note		= wcstol( &i_str.at(0), NULL , 10 ) & 0x3 ;
		i_str.erase(0,2);
		sbuf = i_str;
		sbuf.erase(2);
		int Line3SoundIndex	= wcstol( sbuf.c_str(), NULL , 16 ) & 0xFF;

		i_str.erase(0,3);
		int Line4Note		= wcstol( &i_str.at(0), NULL , 10 ) & 0x3 ;
		i_str.erase(0,2);
		sbuf = i_str;
		sbuf.erase(2);
		int Line4SoundIndex	= wcstol( sbuf.c_str(), NULL , 16 ) & 0xFF;

		i_str.erase(0,3);
		int AnalogLine1Note		= wcstol( &i_str.at(0), NULL , 10 ) & 0x3 ;
		i_str.erase(0,2);
		sbuf = i_str;
		sbuf.erase(2);
		int AnalogLine1SoundIndex	= wcstol( sbuf.c_str(), NULL , 16 ) & 0xFF;

		i_str.erase(0,3);
		int AnalogLine2Note		= wcstol( &i_str.at(0), NULL , 10 ) & 0x3 ;
		i_str.erase(0,2);
		sbuf = i_str;
		sbuf.erase(2);
		int AnalogLine2SoundIndex	= wcstol( sbuf.c_str(), NULL , 16 ) & 0xFF;


		m_NoteData.m_uniUINT8[0] = Line1Note + (Line2Note << 2) + (Line3Note << 4) + (Line4Note << 6);
		m_NoteData.m_uniUINT8[1] = AnalogLine1Note + (AnalogLine1Note << 2);
		m_NoteData.m_uniUINT8[2] = Line1SoundIndex;
		m_NoteData.m_uniUINT8[3] = Line2SoundIndex;
		m_NoteData.m_uniUINT8[4] = Line3SoundIndex;
		m_NoteData.m_uniUINT8[5] = Line4SoundIndex;
		m_NoteData.m_uniUINT8[6] = AnalogLine1SoundIndex;
		m_NoteData.m_uniUINT8[7] = AnalogLine2SoundIndex;

		m_byteNoteQt = 	(m_NoteData.getLine1Note() != 0) +
				(m_NoteData.getLine2Note() != 0) +
				(m_NoteData.getLine3Note() != 0) +
				(m_NoteData.getLine4Note() != 0) +
				(m_NoteData.getAnalogLine1Note() != 0) +
				(m_NoteData.getAnalogLine2Note() != 0) ;
	}
	NoneData& getAllNotes(){
		return m_NoteData;
	}
	BYTE getNoteQt(){
		return m_byteNoteQt;
	}
};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/

}