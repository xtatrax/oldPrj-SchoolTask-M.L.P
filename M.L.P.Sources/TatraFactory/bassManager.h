////////////////////////////// //////////////////////////////
//	ソース名		：bassScriptManager
//	ファイル名		：bassManager.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：tatra
//	内包ﾃﾞｰﾀと備考	：
//
//
#ifndef  TLIB_SCRIPT_MANAGER
#define  TLIB_SCRIPT_MANAGER
#include "../stdafx.h"
#include "SHS.h"
namespace wiz{
namespace Script{
class bassManager;
class bassManager{
protected:
	std::wstring ParameterName;
public:
	virtual void Loader(std::wstring Subsequent,MLPHeader&  Header,void *Option1 = 0) = 0;
	//	: イニシャライザ( Parameter値とthisを受け取る
	bassManager();
};
}
}
#endif