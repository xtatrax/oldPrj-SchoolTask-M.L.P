////////////////////////////// //////////////////////////////
//	�\�[�X��		�FScript/FIRSTDELAYParameter
//	�t�@�C����		�FFIRSTDELAYParameter.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�Ftatra
//	�����ް��Ɣ��l	�F
//
//
#include <wchar.h>
#include "stdafx.h"
#include "FIRSTDELAYParameter.h"

namespace wiz{
namespace Script{
FIRSTDELAY::FIRSTDELAY(void)
{
}

FIRSTDELAY::~FIRSTDELAY(void)
{
}
void FIRSTDELAY::Loader(std::wstring Subsequent,MLPHeader&  Header,void *Option1)
{
	wistringstream strm;
	strm.str(Subsequent);
	strm >> Header.FirstDelay;
	//Header.FIRSTDELAY = wcstof( Subsequent.c_str(),NULL,10);
}

}}