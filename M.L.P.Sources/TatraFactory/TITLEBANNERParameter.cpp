////////////////////////////// //////////////////////////////
//	�\�[�X��		�FScript/TITLEBANNERParameter
//	�t�@�C����		�FTITLEBANNERParameter.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�Ftatra
//	�����ް��Ɣ��l	�F
//
//
#include "stdafx.h"
#include "TITLEBANNERParameter.h"
#include "ScriptManager.h"
namespace wiz{
namespace Script{
TITLEBANNER::TITLEBANNER(void)
{
}

TITLEBANNER::~TITLEBANNER(void)
{
}
void TITLEBANNER::Loader(std::wstring Subsequent,MLPHeader&  Header,void *Option1)
{
	wiz::Script::BlankDelete(Subsequent);
	if(Subsequent.at(0) == L'\"' ){
		Subsequent.erase(0,1);
		std::wstring::size_type epos = Subsequent.find(L"\"");
		Subsequent.erase(epos);
	}
	Header.TitleBanner = Subsequent;
}

}}