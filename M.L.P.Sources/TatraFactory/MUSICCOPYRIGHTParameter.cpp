////////////////////////////// //////////////////////////////
//	�\�[�X��		�FScript/MUSICCOPYRIGHTParameter
//	�t�@�C����		�FMUSICCOPYRIGHTParameter.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�Ftatra
//	�����ް��Ɣ��l	�F
//
//
#include "stdafx.h"
#include "MUSICCOPYRIGHTParameter.h"
#include "ScriptManager.h"
namespace wiz{
namespace Script{
MUSICCOPYRIGHT::MUSICCOPYRIGHT(void)
{
}

MUSICCOPYRIGHT::~MUSICCOPYRIGHT(void)
{
}
void MUSICCOPYRIGHT::Loader(std::wstring Subsequent,MLPHeader&  Header,void *Option1)
{
	wiz::Script::BlankDelete(Subsequent);
	if(Subsequent.at(0) == '\"' ){
		Subsequent.erase(0,1);
		std::wstring::size_type epos = Subsequent.find(L"\"");
		Subsequent.erase(epos);
	}
	Header.MusicCopyright = Subsequent;
}

}}