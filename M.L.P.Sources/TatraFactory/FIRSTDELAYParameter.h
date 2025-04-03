////////////////////////////// //////////////////////////////
//	ソース名		：Script/FIRSTDELAYParameter
//	ファイル名		：FIRSTDELAYParameter.h
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
class FIRSTDELAY :public bassManager{
public:
	FIRSTDELAY(void);
	~FIRSTDELAY(void);
	virtual void Loader(std::wstring Subsequent,MLPHeader&  Header ,void *Option1 = 0);

};
}}