////////////////////////////// //////////////////////////////
//	ソース名		：ScriptManagerFactory
//	ファイル名		：SMFactory.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：tatra
//	内包ﾃﾞｰﾀと備考	：
//
//
#pragma once
#include "../stdafx.h"
#include "bassManager.h"
namespace wiz{
namespace Script{
//////////////////////////////
//	:
//	: 
class SMFactory{
public:
	//	: コンストラクタ
	SMFactory(std::map<std::wstring , bassManager*>& i_ScriptMap);
	//	: デストラクタ
	~SMFactory();
};

}}