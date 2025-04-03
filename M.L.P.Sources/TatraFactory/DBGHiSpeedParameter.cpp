////////////////////////////// //////////////////////////////
//	ソース名		：Script/DBGHiSpeedParameter
//	ファイル名		：DBGHiSpeedParameter.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：tatra
//	内包ﾃﾞｰﾀと備考	：
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