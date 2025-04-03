////////////////////////////// //////////////////////////////
//	ソース名		：Script/TITLEBANNERParameter
//	ファイル名		：TITLEBANNERParameter.h
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
class TITLEBANNER :public bassManager{
public:
	TITLEBANNER(void);
	~TITLEBANNER(void);
	virtual void Loader(std::wstring Subsequent,MLPHeader&  Header ,void *Option1 = 0);

};
}}