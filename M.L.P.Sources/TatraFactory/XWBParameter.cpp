////////////////////////////// //////////////////////////////
//	ソース名		：Script/XWBParameter
//	ファイル名		：XWBParameter.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：tatra
//	内包ﾃﾞｰﾀと備考	：
//
//
#include "stdafx.h"
#include "XWBParameter.h"
#include "ScriptManager.h"
namespace wiz{
namespace Script{
XWB::XWB(void)
{
}

XWB::~XWB(void)
{
}
void XWB::Loader(std::wstring Subsequent,MLPHeader&  Header,void *Option1)
{
	wiz::Script::BlankDelete(Subsequent);
	if(Subsequent.at(0) == L'\"' ){
		Subsequent.erase(0,1);
		std::wstring::size_type epos = Subsequent.find(L"\"");
		Subsequent.erase(epos);
	}
	Header.XWBPath = Subsequent;
}
EASYXWB::EASYXWB(void)
{
}

EASYXWB::~EASYXWB(void)
{
}
void EASYXWB::Loader(std::wstring Subsequent,MLPHeader&  Header,void *Option1)
{
	wiz::Script::BlankDelete(Subsequent);
	if(Subsequent.at(0) == L'\"' ){
		Subsequent.erase(0,1);
		std::wstring::size_type epos = Subsequent.find(L"\"");
		Subsequent.erase(epos);
	}
	Header.EASYXWBPath = Subsequent;
}
NORMALXWB::NORMALXWB(void)
{
}

NORMALXWB::~NORMALXWB(void)
{
}
void NORMALXWB::Loader(std::wstring Subsequent,MLPHeader&  Header,void *Option1)
{
	wiz::Script::BlankDelete(Subsequent);
	if(Subsequent.at(0) == L'\"' ){
		Subsequent.erase(0,1);
		std::wstring::size_type epos = Subsequent.find(L"\"");
		Subsequent.erase(epos);
	}
	Header.NORMALXWBPath = Subsequent;
}
HARDXWB::HARDXWB(void)
{
}

HARDXWB::~HARDXWB(void)
{
}
void HARDXWB::Loader(std::wstring Subsequent,MLPHeader&  Header,void *Option1)
{
	wiz::Script::BlankDelete(Subsequent);
	if(Subsequent.at(0) == L'\"' ){
		Subsequent.erase(0,1);
		std::wstring::size_type epos = Subsequent.find(L"\"");
		Subsequent.erase(epos);
	}
	Header.HARDXWBPath = Subsequent;
}

}}