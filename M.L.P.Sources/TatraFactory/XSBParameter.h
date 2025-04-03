////////////////////////////// //////////////////////////////
//	ソース名		：Script/XSBParameter
//	ファイル名		：XSBParameter.h
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
class XSB :public bassManager{
public:
	XSB(void);
	~XSB(void);
	virtual void Loader(std::wstring Subsequent,MLPHeader&  Header ,void *Option1 = 0);

};
class EASYXSB :public bassManager{
public:
	EASYXSB(void);
	~EASYXSB(void);
	virtual void Loader(std::wstring Subsequent,MLPHeader&  Header ,void *Option1 = 0);

};
class NORMALXSB :public bassManager{
public:
	NORMALXSB(void);
	~NORMALXSB(void);
	virtual void Loader(std::wstring Subsequent,MLPHeader&  Header ,void *Option1 = 0);

};
class HARDXSB :public bassManager{
public:
	HARDXSB(void);
	~HARDXSB(void);
	virtual void Loader(std::wstring Subsequent,MLPHeader&  Header ,void *Option1 = 0);

};
}}