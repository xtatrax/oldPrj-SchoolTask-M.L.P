////////////////////////////// //////////////////////////////
//	�\�[�X��		�FScript/TITLEParameter
//	�t�@�C����		�FTITLEParameter.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�Ftatra
//	�����ް��Ɣ��l	�F
//
//
#include "stdafx.h"
#include "TITLEParameter.h"
#include "ScriptManager.h"
namespace wiz{
namespace Script{
TITLE::TITLE(void)
{
}

TITLE::~TITLE(void)
{
}
void TITLE::Loader(std::wstring Subsequent,MLPHeader&  Header,void *Option1)
{
	wiz::Script::BlankDelete(Subsequent);
	if(Subsequent.at(0) == L'\"' ){
		Subsequent.erase(0,1);
		std::wstring::size_type epos = Subsequent.find(L"\"");
		Subsequent.erase(epos);
	}
	Header.Title = Subsequent;
}

}}