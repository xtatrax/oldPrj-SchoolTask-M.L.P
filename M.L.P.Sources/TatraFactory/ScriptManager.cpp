////////////////////////////// //////////////////////////////
//	�\�[�X��		�FScriptManager
//	�t�@�C����		�FScriptManager.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�Ftatra
//	�����ް��Ɣ��l	�F
//
//
#include "stdafx.h"
#include "ScriptManager.h"
#include "SMFactory.h"
#include "SHS.h"
namespace wiz{
namespace Script{
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/**************************************************************************
int BlankSkip(char* i_wstring, int i_begin){
 �p�r:		�󔒋�؂�̈ʒu�𒲂ׂ�
 �߂�l:	�󔒋�؂̈ʒu
***************************************************************************/
int BlankSkip(char* i_wstring, int i_begin){
	do{
		if(i_wstring[i_begin] == ' '){
			i_begin++;
		}else
		if( i_wstring[i_begin] == 0x81 && i_wstring[i_begin+1] == 0x40){//127 && i_wstring[i_begin+1] == 0x40
			i_begin += 2;
		}else break;
	}while(true);
	return i_begin;
}
/**************************************************************************
int getBlankPos(std::wstring& i_wstring, int i_begin);
 �p�r:		�󔒋�؂�̈ʒu�𒲂ׂ�
 �߂�l:	�󔒋�؂̈ʒu
***************************************************************************/
int getBlankPos(std::wstring& i_wstring, unsigned int i_begin){
	do{
		//	: ���������̂̏I�[�܂ŋ󔒕������Ȃ���΂O��Ԃ�
		if(	i_wstring.size() <= i_begin || i_wstring.at(i_begin) == '\0')
			return 0;
		//	: �󔒕������������烋�[�v�I��
		if( (i_wstring.at(i_begin) == L' ' )||
			(i_wstring.at(i_begin) == 0x81 && i_wstring.at(i_begin+1) == 0x40 )||//
			(i_wstring.at(i_begin) == L'	')||
			(i_wstring.at(i_begin) == L'\n'))
			break;
		i_begin++;
	}while(true);
	return i_begin;
}
/**************************************************************************
std::wstring BlankDelete(std::wstring& i_wstring);
 �p�r:		�擪�󔒂̍폜
 �߂�l:	�폜��̕�����
***************************************************************************/
std::wstring BlankDelete(std::wstring& i_wstring)
{
	//	: �Ō���m�F
	while( !i_wstring.empty() ){
		//	: �󔒊m�F
		if(i_wstring.at(0) == ' ' || i_wstring.at(0) == '	')
			i_wstring = i_wstring.erase(0,1);
		else
		if(i_wstring.at(0) == 0x81 && i_wstring.at(1) == 0x40)//-127 && i_wstring.at(1) == 0x40
			i_wstring = i_wstring.erase(0,2);
		else break;
	}
	return i_wstring;
}
/**************************************************************************
std::wstring BlankDelete(std::wstring& i_wstring);
 �p�r:		�擪�󔒂̍폜
 �߂�l:	�폜��̕�����
***************************************************************************/
std::wstring AllBlankDeleteAll(std::wstring& i_wstring)
{
	wstring::size_type i = 0;
	//	: �Ō���m�F
	while( !i_wstring.empty() && i < i_wstring.size()){
		//	: �󔒊m�F
		if(i_wstring.at(i) == ' ' || i_wstring.at(i) == '	' || i_wstring.at(i) == '\n')
			i_wstring = i_wstring.erase(0,1);
		else
		if(i_wstring.at(i) == 0x81 && i_wstring.at(1) == 0x40)//-127 && i_wstring.at(i) == 0x40
			i_wstring = i_wstring.erase(0,2);
		else i++;
	}
	return i_wstring;
}
/**************************************************************************
std::wstring exParameter(std::wstring& i_wstring);
 �p�r:		
 �߂�l:	�Ȃ�
***************************************************************************/
//std::wstring exParameter(std::wstring& i_wstring)
//{
//	std::wstring o_wstring;
//	//	: �擪�̋󔒍폜
//	BlankDelete(i_wstring);
//	int i = 0;
//	//	: 
//	while(	i_wstring.at(i) != i_wstring.npos,
//			i_wstring.at(i) != ' '
//	){
//		o_wstring += i_wstring.at(i);
//		i++;
//	}
//	i_wstring.erase(0,i);
//	return o_wstring;
//}



/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/

/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/


//	:
std::wfstream ScriptManager::BodyFp;
//	: �p�����[�^�}�b�v
std::map<std::wstring , bassManager*> ScriptManager::m_ScriptMap;
//	:
std::wstring ScriptManager::SongsDirectory = L"Songs/";


/**************************************************************************
 ScriptManager::ScriptManager();
 �p�r:		�R���X�g���N�^
 �߂�l:	�Ȃ�
***************************************************************************/
ScriptManager::ScriptManager(void)
{
	SMFactory::SMFactory(m_ScriptMap);
}
/**************************************************************************
 ScriptManager::~ScriptManager();
 �p�r:		�f�X�g���N�^
 �߂�l:	�Ȃ�
***************************************************************************/
ScriptManager::~ScriptManager(void)
{
}
void ScriptManager::SearchSongsDirectory(vector<wstring>& o_PathVec){
	HANDLE handle;
	WIN32_FIND_DATA finddata;
	SetCurrentDirectory(SongsDirectory.c_str());
	//	: �T�u�f�B���N�g������
	handle = FindFirstFile(L"*", &finddata );
	do{
		if((finddata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
			wcscmp(finddata.cFileName , L".") &&
			wcscmp(finddata.cFileName , L"..") ){
			o_PathVec.push_back(SongsDirectory + finddata.cFileName + L"/");
		}
	}while(FindNextFile( handle, &finddata ) );
	FindClose( handle );
	SetCurrentDirectory(L"../");

}
/**************************************************************************
 void ScriptManager::SearchSongs(vector<MLPHeader>& o_vec){
 �p�r:		�y�ȃf�[�^��T���ăw�b�_�[���ꗗ���쐬����
 �߂�l:	�Ȃ�
***************************************************************************/
void ScriptManager::SearchSongs(vector<MLPHeader>& o_vec){
//	: �f�B���N�g���ꗗ�̐���
	vector<wstring> PathVec;		//	: Songs�t�H���_�̃T�u�t�H���_�ꗗ
	SearchSongsDirectory(PathVec);
	WIN32_FIND_DATA finddata;
	wstring wstrBuf;
	vector<wstring>::size_type PVSizez = PathVec.size();
	for( vector<wstring>::size_type i = 0 ; i < PVSizez; i++ ){
		wstrBuf = PathVec.at(i) + L"*.MLS";
		if(FindFirstFile(wstrBuf.c_str(), &finddata ) != INVALID_HANDLE_VALUE ){
			o_vec.push_back(ReadHeader(PathVec.at(i) , finddata.cFileName));
		}
	}
//	: 

}
/**************************************************************************
 Commander ScriptManager::ReadCommand(std::wstring& i_wstring)
 �p�r:		��s�̕����񂩂疽�߂�ǂݎ��
 �߂�l:	�ǂݎ�����R�}���h
***************************************************************************/
Commander ScriptManager::ReadCommand(std::wstring& i_wstring){
	//	: ���ߎ���p�ϐ�
	Commander Com;
	//	: �擪�󔒍폜
	BlankDelete(i_wstring);
	//	: ���ߍs�ł��邩
	if(i_wstring.empty() || i_wstring.at(0) != '#'){
		//	: ���ߋƂłȂ���΂��̎|��`����
		return Commander(L"__NC",L"__NC");
	}
	i_wstring.erase(0,1);
	//	: �󔒂ŋ�؂��Ă�ꏊ�𔻒f
	int size	= getBlankPos(i_wstring);
	Com.m_CommandType = i_wstring;
	//	: ��؂蕶���𔭌�������
	if(size){
		Com.m_CommandType.erase(size);
		//	:
		Com.m_Command = i_wstring;
		Com.m_Command.erase(0,size);
		//Com.m_Command.copy(buf,size,1);
		BlankDelete(Com.m_Command);
		if(Com.m_Command.empty()){
			return Commander(Com.m_CommandType,L"NOTHEADER");
		}
		//buf[size-1] = '\0';
		//Com.m_CommandType = buf;
	} 
	else{
		return Commander(Com.m_CommandType,L"NOTHEADER");
	}
	return Com;
}

/**************************************************************************
 Commander ScriptManager::ReadHeader(char* fileName)
 �p�r:		�w�b�_�[�̃f�[�^��ǂݎ��
 �߂�l:	�ǂݎ�����R�}���h
***************************************************************************/
MLPHeader ScriptManager::ReadHeader(std::wstring folderPath, std::wstring fileName )
{
	MLPHeader header;
	header.FileName = fileName;
	header.FilePath = folderPath;
	wstring lineBuf = folderPath + fileName;
	//	: �t�@�C��Open�ƌ���
	std::wfstream fs(lineBuf.c_str());
	if(fs.fail()){
		MessageBox(NULL,L"�ǂݍ��݂Ɏ��s",fileName.c_str(),NULL);
		return MLPHeader();
	}
	std::map<std::wstring , bassManager*>::iterator SMapIte;
	while( !fs.eof() && getline(fs,lineBuf)){
		Commander Com = ReadCommand(lineBuf);
		if(Com.m_Command == L"NOTHEADER") break;
		SMapIte = m_ScriptMap.find(Com.m_CommandType);
		if( SMapIte != m_ScriptMap.end() )
			m_ScriptMap[Com.m_CommandType]->Loader(Com.m_Command,header);
	}
	return header;
}
/**************************************************************************
void ScriptManager::BodyReadBegin(char* fileName){
 �p�r:		�w�b�_�[�̃f�[�^��ǂݎ��
 �߂�l:	�ǂݎ�����R�}���h
***************************************************************************/
void ScriptManager::BodyReadBegin(std::wstring fileName,SCORELEVEL Level){
	//	: �t�@�C��Open�ƌ���
	BodyFp.open(fileName.c_str());
	if(BodyFp.fail()){
		MessageBox(NULL,L"�ǂݍ��݂Ɏ��s",fileName.c_str(),NULL);
		return;
	}
	wstring lineBuf;
	MLPHeader header;
	while( !BodyFp.eof() && getline(BodyFp,lineBuf)){
		Commander Com = ReadCommand(lineBuf);
		if(	(Level == EASY		&& Com.m_CommandType == L"EASY")	||
			(Level == NORMAL	&& Com.m_CommandType == L"NORMAL")	||
			(Level == HARD		&& Com.m_CommandType == L"HARD"))	{
			return;
		}
	}


}
/**************************************************************************
void ScriptManager::BodyReadBegin(char* fileName){
 �p�r:		�w�b�_�[�̃f�[�^��ǂݎ��
 �߂�l:	�ǂݎ�����R�}���h
***************************************************************************/
std::wstring ScriptManager::BodyRead(){
	//	: �ǂݔ�΂�
	wstring lineBuf,retBuf;
	while(!BodyFp.eof() && getline(BodyFp,lineBuf)){
		BlankDelete(lineBuf);
		if(lineBuf.empty()) continue;
		Commander Com = ReadCommand(lineBuf);
		if(Com.m_CommandType == L"END") return L"END";
		if(lineBuf.at(0) == '{')	break;
	
	}
	while( !BodyFp.eof() && getline(BodyFp,lineBuf)){
		BlankDelete(lineBuf);
		if(lineBuf.empty()) continue;
		if(lineBuf.at(0) == '}')	break;
		if(lineBuf.at(0) == '['){
			retBuf += lineBuf + L'\n';		
		}
	}
	return retBuf;
}
/**************************************************************************
void ScriptManager::BodyReadBegin(char* fileName){
 �p�r:		�w�b�_�[�̃f�[�^��ǂݎ��
 �߂�l:	�ǂݎ�����R�}���h
***************************************************************************/
void ScriptManager::BodyReadEnd(){
	BodyFp.close();
}
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/

}}
#ifdef CS_CONS_COMPILE
//	: �e�X�g�p���C��
void main(){
	vector<wiz::Script::MLPHeader> o_vec;

	wiz::Script::ScriptManager::ScriptManager();
	wiz::Script::ScriptManager::SearchSongs(o_vec);
	//wiz::Script::MLPHeader hda = o_vec[0];
	wiz::Script::ScriptManager::BodyReadBegin(o_vec[0].FilePath + o_vec[0].FileName,wiz::Script::EASY);
	wstring st;
	while( (st = wiz::Script::ScriptManager::BodyRead()) != L"END"){
	}
	wiz::Script::ScriptManager::BodyReadEnd();
}
#endif