////////////////////////////// //////////////////////////////
//	�\�[�X��		�FScript/MLPSCRIPTVERSIONParameter
//	�t�@�C����		�FMLPSCRIPTVERSIONParameter.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�Ftatra
//	�����ް��Ɣ��l	�F
//
//
#include "stdafx.h"
#include "MLPSCRIPTVERSIONParameter.h"
#include "ScriptManager.h"
namespace wiz{
namespace Script{
MLPSCRIPTVERSION::MLPSCRIPTVERSION(void)
{
}

MLPSCRIPTVERSION::~MLPSCRIPTVERSION(void)
{
}
void MLPSCRIPTVERSION::Loader(std::wstring Subsequent,MLPHeader&  Header,void *Option1)
{
	wiz::Script::BlankDelete(Subsequent);
	if(Subsequent.at(0) == '\"' ){
		Subsequent.erase(0,1);
		std::wstring::size_type epos = Subsequent.find(L"\"");
		Subsequent.erase(epos);
	}
	Header.SCVersion = Subsequent;
}

}}