////////////////////////////// //////////////////////////////
//	�\�[�X��		�FScriptManager
//	�t�@�C����		�FScriptManager.h
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�Ftatra
//	�����ް��Ɣ��l	�F
//
//
#pragma once
#include "../stdafx.h"
#include "bassManager.h"
//#include "SMFactory.h"



namespace wiz{
//	: 
namespace Script{
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
//////////////////////////////
//	: �擪�̋󔒔�΂�  
int BlankSkip(char* i_wstring, int i_begin = 0);
//////////////////////////////
//	: �擪�̋󔒔�΂�  
int getBlankPos(std::wstring& i_wstring, unsigned int i_begin = 0);
//////////////////////////////
//	: �擪�̋󔒍폜
std::wstring BlankDelete(std::wstring& i_wstring);
//////////////////////////////
//	: ���ׂĂ̋󔒍폜
std::wstring AllBlankDeleteAll(std::wstring& i_wstring);
//////////////////////////////
//	: �p�����[�^���
std::wstring exParameter(std::wstring& i_wstring);
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/


/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
class ScriptManager
{        
//////////////////////////////
//	: private�ϐ�
	//	: stream
	static std::wfstream BodyFp;
	//	: 
	static std::wstring SongsDirectory;
	//	: �p�����[�^�}�b�v
	static std::map<std::wstring , bassManager*> m_ScriptMap;
//////////////////////////////
//	: private�֐�
	//	: �R�}���h����
	static Commander ReadCommand(std::wstring& i_wstring);
	//	�F �����񌟍��ƈړ�
	static void SearchBodyBegin();
	//	: 
	static void SearchSongsDirectory(vector<wstring>& o_PathVec);
public:
	ScriptManager(void);
	~ScriptManager(void);
	//	: �y�ȃT�[�`
	static void SearchSongs(vector<MLPHeader>& o_vec);
	//	: Header�ǂݍ���
	static MLPHeader ReadHeader(std::wstring folderPath, std::wstring fileName);
	//	: �{�f�B�ǂݍ��݊J�n
	static void BodyReadBegin(std::wstring fileName,SCORELEVEL Level);
	//	: �{�f�B�ǂݍ���
	static std::wstring BodyRead();
	//	: �{�f�B�ǂݍ��ݏI��
	static void BodyReadEnd();

};
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/

}}