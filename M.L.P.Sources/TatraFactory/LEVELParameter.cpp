////////////////////////////// //////////////////////////////
//	�\�[�X��		�FScript/LEVELParameter
//	�t�@�C����		�FLEVELParameter.cpp
//	�J����		�FMSVC++ 2008
//	�œK�^�u��		�F4
//	�S����			�Ftatra
//	�����ް��Ɣ��l	�F
//
//
#include "stdafx.h"
#include "LEVELParameter.h"
namespace wiz{
namespace Script{
//////////////////////////////
EASYLEVEL::EASYLEVEL(void)
{
}

EASYLEVEL::~EASYLEVEL(void)
{
}
void EASYLEVEL::Loader(std::wstring Subsequent,MLPHeader&  Header,void *Option1)
{
	//char* ch; 
	Header.Level[EASY] = wcstoul( Subsequent.c_str(),NULL,10);
}
//////////////////////////////
NORMALLEVEL::NORMALLEVEL(void)
{
}

NORMALLEVEL::~NORMALLEVEL(void)
{
}
void NORMALLEVEL::Loader(std::wstring Subsequent,MLPHeader&  Header,void *Option1)
{
	//char* ch; 
	Header.Level[NORMAL] = wcstoul( Subsequent.c_str(),NULL,10);
}
//////////////////////////////
HARDLEVEL::HARDLEVEL(void)
{
}

HARDLEVEL::~HARDLEVEL(void)
{
}
void HARDLEVEL::Loader(std::wstring Subsequent,MLPHeader&  Header,void *Option1)
{
	//char* ch; 
	Header.Level[HARD] = wcstoul( Subsequent.c_str(),NULL,10);
}

}}