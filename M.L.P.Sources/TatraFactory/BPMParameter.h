////////////////////////////// //////////////////////////////
//	ソース名		：Script/BPMParameter
//	ファイル名		：BPMParameter.h
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
class BPM :public bassManager{
public:
	BPM(void);
	~BPM(void);
	virtual void Loader(std::wstring Subsequent,MLPHeader&  Header ,void *Option1 = 0);

};
}}