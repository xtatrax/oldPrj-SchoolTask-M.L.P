////////////////////////////// //////////////////////////////
//	ソース名		：Script/LEVELParameter
//	ファイル名		：LEVELParameter.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：tatra
//	内包ﾃﾞｰﾀと備考	：
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