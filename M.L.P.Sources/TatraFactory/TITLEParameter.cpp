////////////////////////////// //////////////////////////////
//	ソース名		：Script/TITLEParameter
//	ファイル名		：TITLEParameter.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：tatra
//	内包ﾃﾞｰﾀと備考	：
//
//
#include "stdafx.h"
#include "TITLEParameter.h"
#include "ScriptManager.h"
namespace wiz{
namespace Script{
TITLE::TITLE(void)
{
}

TITLE::~TITLE(void)
{
}
void TITLE::Loader(std::wstring Subsequent,MLPHeader&  Header,void *Option1)
{
	wiz::Script::BlankDelete(Subsequent);
	if(Subsequent.at(0) == L'\"' ){
		Subsequent.erase(0,1);
		std::wstring::size_type epos = Subsequent.find(L"\"");
		Subsequent.erase(epos);
	}
	Header.Title = Subsequent;
}

}}