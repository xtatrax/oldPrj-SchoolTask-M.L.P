////////////////////////////// //////////////////////////////
//	ソース名		：Script/FIRSTDELAYParameter
//	ファイル名		：FIRSTDELAYParameter.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：tatra
//	内包ﾃﾞｰﾀと備考	：
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