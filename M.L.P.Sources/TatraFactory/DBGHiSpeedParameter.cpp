////////////////////////////// //////////////////////////////
//	�\�[�X��		�FScript/DBGHiSpeedParameter
//	�t�@�C����		�FDBGHiSpeedParameter.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�Ftatra
//	�����ް��Ɣ��l	�F
//
//
#include <wchar.h>
#include "stdafx.h"
#include "DBGHiSpeedParameter.h"

namespace wiz{
namespace Script{
DBGHiSpeed::DBGHiSpeed(void)
{
}

DBGHiSpeed::~DBGHiSpeed(void)
{
}
void DBGHiSpeed::Loader(std::wstring Subsequent,MLPHeader&  Header,void *Option1)
{
	wistringstream strm;
	strm.str(Subsequent);
	strm >> Header.DBGHiSpeed;
	//Header.DBGHiSpeed = wcstof( Subsequent.c_str(),NULL,10);
}

}}