////////////////////////////// //////////////////////////////
//	ソース名		：Script/MUSICCOPYRIGHTParameter
//	ファイル名		：MUSICCOPYRIGHTParameter.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：tatra
//	内包ﾃﾞｰﾀと備考	：
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