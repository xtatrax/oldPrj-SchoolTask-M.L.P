////////////////////////////// //////////////////////////////
//	ソース名		：Script/XSBParameter
//	ファイル名		：XSBParameter.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：tatra
//	内包ﾃﾞｰﾀと備考	：
//
//
#include "stdafx.h"
#include "XSBParameter.h"
#include "ScriptManager.h"
namespace wiz{
namespace Script{
XSB::XSB(void)
{
}

XSB::~XSB(void)
{
}
void XSB::Loader(std::wstring Subsequent,MLPHeader&  Header,void *Option1)
{
	wiz::Script::BlankDelete(Subsequent);
	if(Subsequent.at(0) == L'\"' ){
		Subsequent.erase(0,1);
		std::wstring::size_type epos = Subsequent.find(L"\"");
		Subsequent.erase(epos);
	}
	Header.XSBPath = Subsequent;
}
EASYXSB::EASYXSB(void)
{
}

EASYXSB::~EASYXSB(void)
{
}
void EASYXSB::Loader(std::wstring Subsequent,MLPHeader&  Header,void *Option1)
{
	wiz::Script::BlankDelete(Subsequent);
	if(Subsequent.at(0) == L'\"' ){
		Subsequent.erase(0,1);
		std::wstring::size_type epos = Subsequent.find(L"\"");
		Subsequent.erase(epos);
	}
	Header.EASYXSBPath = Subsequent;
}
NORMALXSB::NORMALXSB(void)
{
}

NORMALXSB::~NORMALXSB(void)
{
}
void NORMALXSB::Loader(std::wstring Subsequent,MLPHeader&  Header,void *Option1)
{
	wiz::Script::BlankDelete(Subsequent);
	if(Subsequent.at(0) == L'\"' ){
		Subsequent.erase(0,1);
		std::wstring::size_type epos = Subsequent.find(L"\"");
		Subsequent.erase(epos);
	}
	Header.NORMALXSBPath = Subsequent;
}
HARDXSB::HARDXSB(void)
{
}

HARDXSB::~HARDXSB(void)
{
}
void HARDXSB::Loader(std::wstring Subsequent,MLPHeader&  Header,void *Option1)
{
	wiz::Script::BlankDelete(Subsequent);
	if(Subsequent.at(0) == L'\"' ){
		Subsequent.erase(0,1);
		std::wstring::size_type epos = Subsequent.find(L"\"");
		Subsequent.erase(epos);
	}
	Header.HARDXSBPath = Subsequent;
}


}}