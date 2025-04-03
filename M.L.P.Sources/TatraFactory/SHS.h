////////////////////////////// //////////////////////////////
//	�\�[�X��        �FScriptHeaderStruct
//	�t�@�C����      �FSHS.h
//	�J����        �FMSVC++ 2008
//	�œK�^�u��      �F4
//	�S����          �Ftatra
//	�����ް��Ɣ��l  �F�X�N���v�g�֌W�ɕK�v�ȃw�b�_�[�Q
//	                �F�����I�ɂ͂��낢��ȍ\���̂�񋓌^�̋l�ߍ��킹
//
#pragma once
#include "../stdafx.h"

namespace wiz{
//------- --------- --------- --------- --------- --------- --------- --------- //
//	�X�N���v�g�p�f�[�^�Q                                                        //
//------- --------- --------- --------- --------- --------- --------- --------- //
namespace Script{
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*
**	���ʂ̃��x���J�e�S���[
**
**��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
enum SCORELEVEL{
	EASY,
	NORMAL,
	HARD
};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*
**	���ʂ̃��x�����L�����Ă����\����
**
**��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
struct Level{
	int Easy;
	int Normal;
	int Hard;
	int& operator[](BYTE lv){
		if(lv == EASY) return Easy;
		if(lv == NORMAL) return Normal;
		if(lv == HARD) return Hard;
		return Easy;
	}
	Level(){}
	Level(int easy,int normal,int hard)
		:Easy(easy),Normal(normal),Hard(hard){}
};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*
**	�X�N���v�g�̖��߂���ǂ���Ƃ��Ƃ��ɕK�v
**
**��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
struct Commander{
	//	: ���߂̎�� ( TITLE�����݂Ƃ�WAV�ǂݍ��݂Ƃ�
	std::wstring m_CommandType;
	//	: ���ߓ��e   ( �ǂݍ��ݐ�Ƃ�
	std::wstring m_Command;
	//	: 
	Commander(){};
	//	:
	Commander(std::wstring i_CType,std::wstring i_Command)
		:m_CommandType(i_CType),m_Command(i_Command)
	{
	};
};

/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*
**	���ʃX�N���v�g�̃w�b�_�[�Ł[����
**	�L�����Ă����y�f����
**��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
struct MLPHeader{
	std::wstring FileName;		//	: �t�@�C���̖��O
	std::wstring FilePath;		//	: �t�@�C���̏ꏊ
	std::wstring SCVersion;		 //	: �X�N���v�g�o�[�W����
	std::wstring Title;			  //	: �Ȗ�
	std::wstring TitleBanner;	   //	: �Ȗ��o�i�[
	std::wstring ScriptEdit;		//	: ���ʃf�[�^�����
	std::wstring MusicCopyright;	//	: �y�Ȑ����
	std::wstring XSBPath ;		   //	: �T�E���h�o���N�p�X
	std::wstring XWBPath ;		  //	: �E�F�u�o���N�p�X
	std::wstring EASYXSBPath ;	 //	: �T�E���h�o���N�p�X
	std::wstring EASYXWBPath ;	 //	: �E�F�u�o���N�p�X
	std::wstring NORMALXSBPath ;  //	: �T�E���h�o���N�p�X
	std::wstring NORMALXWBPath ;   //	: �E�F�u�o���N�p�X
	std::wstring HARDXSBPath ;		//	: �T�E���h�o���N�p�X
	std::wstring HARDXWBPath ;		 //	: �E�F�u�o���N�p�X
	Level		 Level ;		    //	: ���x���\����
	unsigned int Bpm ;			  //	: �Ă��
	float        DBGHiSpeed ;	 //	: �f�o�b�O�p��HiSpeed
	float		 FirstDelay;	//	: �X�e�[�W���J�n����Ă���Ȃ��n�܂�܂ł̎���
	MLPHeader()
		:Bpm(0),FirstDelay(0),DBGHiSpeed(1)
	{
		
	}

};
typedef std::vector<MLPHeader*> HeaderPVec;

}
//------- --------- --------- --------- --------- --------- --------- --------- //
//	���Ńf�[�^�Q                                                              //
//------- --------- --------- --------- --------- --------- --------- --------- //

/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*
**	����J�e�S���[�̗񋓌^
**
**��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
enum JUDGE{
	NOJUDGE = -1,
	POOR,
	BAD,
	GOOD,
	GREAT,

};

/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*
**	�����N�v�Z�ɕK�v�ȃf�[�^�Q�H
**
**��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
struct ResultFactor{
	wstring	m_BannerPath;	//	: �^�C�g���o�o�[��Path
	DWORD	m_dwAllNoteQt;	//	: �����̐�
	DWORD	m_dwGreatQt;	//	: �O���[�g�̐�
	DWORD	m_dwGoodQt;		//	: �O�b�h�̐�
	DWORD	m_dwBadQt;		//	: �o�b�h�̐�
	DWORD	m_dwPoorQt;		//	: �v�A�[�̐�
	float	m_fGaugePar;	//	: �Q�[�W�̃p�[�Z���e�[�W
	ResultFactor()
		:m_dwAllNoteQt(0),
		 m_dwGreatQt(0),
		 m_dwGoodQt(0),
		 m_dwBadQt(0),
		 m_dwPoorQt(0),
		 m_fGaugePar(0.0f)
	{}
};


class JudgeSprite;
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*
**	Play��ʂŎg��
**
**��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
struct PlayCommandPacket{
	float			m_fMeasureChangeDelay;
	float			m_fJudgePosZ;
	JudgeSprite*	m_pJudgeSprite;
	ResultFactor*		m_pRankFactor;
	PlayCommandPacket()
		:m_fMeasureChangeDelay(1.0f),
		 m_fJudgePosZ(0),
		 m_pJudgeSprite(NULL),
		 m_pRankFactor(NULL)
	{}
};

}