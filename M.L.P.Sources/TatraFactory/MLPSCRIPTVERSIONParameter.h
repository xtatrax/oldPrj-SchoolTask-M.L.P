////////////////////////////// //////////////////////////////
//	ソース名		：Script/MLPSCRIPTVERSIONParameter
//	ファイル名		：MLPSCRIPTVERSIONParameter.h
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
class MLPSCRIPTVERSION :public bassManager{
public:
	MLPSCRIPTVERSION(void);
	~MLPSCRIPTVERSION(void);
	virtual void Loader(std::wstring Subsequent,MLPHeader&  Header ,void *Option1 = 0);

};
}}