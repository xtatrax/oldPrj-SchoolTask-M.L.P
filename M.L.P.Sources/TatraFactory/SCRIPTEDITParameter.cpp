////////////////////////////// //////////////////////////////
//	ソース名		：Script/SCRIPTEDITParameter
//	ファイル名		：SCRIPTEDITParameter.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：tatra
//	内包ﾃﾞｰﾀと備考	：
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