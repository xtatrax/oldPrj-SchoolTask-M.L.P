////////////////////////////// //////////////////////////////
//	ソース名		：Script/LEVELParameter
//	ファイル名		：LEVELParameter.h
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
class EASYLEVEL :public bassManager{
public:
	EASYLEVEL(void);
	~EASYLEVEL(void);
	virtual void Loader(std::wstring Subsequent,MLPHeader&  Header ,void *Option1 = 0);

};
class NORMALLEVEL :public bassManager{
public:
	NORMALLEVEL(void);
	~NORMALLEVEL(void);
	virtual void Loader(std::wstring Subsequent,MLPHeader&  Header ,void *Option1 = 0);

};
class HARDLEVEL :public bassManager{
public:
	HARDLEVEL(void);
	~HARDLEVEL(void);
	virtual void Loader(std::wstring Subsequent,MLPHeader&  Header ,void *Option1 = 0);

};
}}