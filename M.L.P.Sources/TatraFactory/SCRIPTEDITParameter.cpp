////////////////////////////// //////////////////////////////
//	�\�[�X��		�FScript/SCRIPTEDITParameter
//	�t�@�C����		�FSCRIPTEDITParameter.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�Ftatra
//	�����ް��Ɣ��l	�F
//
//
#include "stdafx.h"
#include "SCRIPTEDITParameter.h"
#include "ScriptManager.h"
namespace wiz{
namespace Script{
SCRIPTEDIT::SCRIPTEDIT(void)
{
}

SCRIPTEDIT::~SCRIPTEDIT(void)
{
}
void SCRIPTEDIT::Loader(std::wstring Subsequent,MLPHeader&  Header,void *Option1)
{
	wiz::Script::BlankDelete(Subsequent);
	if(Subsequent.at(0) == '\"' ){
		Subsequent.erase(0,1);
		std::wstring::size_type epos = Subsequent.find(L"\"");
		Subsequent.erase(epos);
	}
	Header.ScriptEdit = Subsequent;
}

}}