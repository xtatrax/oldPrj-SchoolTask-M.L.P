////////////////////////////// //////////////////////////////
//	ソース名		：Script/XWBParameter
//	ファイル名		：XWBParameter.h
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
class XWB :public bassManager{
public:
	XWB(void);
	~XWB(void);
	virtual void Loader(std::wstring Subsequent,MLPHeader&  Header ,void *Option1 = 0);

};
class EASYXWB :public bassManager{
public:
	EASYXWB(void);
	~EASYXWB(void);
	virtual void Loader(std::wstring Subsequent,MLPHeader&  Header ,void *Option1 = 0);

};
class NORMALXWB :public bassManager{
public:
	NORMALXWB(void);
	~NORMALXWB(void);
	virtual void Loader(std::wstring Subsequent,MLPHeader&  Header ,void *Option1 = 0);

};
class HARDXWB :public bassManager{
public:
	HARDXWB(void);
	~HARDXWB(void);
	virtual void Loader(std::wstring Subsequent,MLPHeader&  Header ,void *Option1 = 0);

};
}}