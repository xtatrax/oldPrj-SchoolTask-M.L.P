////////////////////////////// //////////////////////////////
//	ソース名		：Script/BPMParameter
//	ファイル名		：BPMParameter.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：tatra
//	内包ﾃﾞｰﾀと備考	：
//
//
#include "stdafx.h"
#include "BPMParameter.h"
namespace wiz{
namespace Script{
BPM::BPM(void)
{
}

BPM::~BPM(void)
{
}
void BPM::Loader(std::wstring Subsequent,MLPHeader&  Header,void *Option1)
{
	//char* ch; 
	Header.Bpm = wcstoul( Subsequent.c_str(),NULL,10);
}

}}