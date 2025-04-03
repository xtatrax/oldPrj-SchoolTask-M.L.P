////////////////////////////// //////////////////////////////
//	ソース名		：ScriptManagerFactory
//	ファイル名		：SMFactory.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：tatra
//	内包ﾃﾞｰﾀと備考	：
//
#include "stdafx.h"
#include "SMFactory.h"
#include "MLPSCRIPTVERSIONParameter.h"
#include "TITLEParameter.h"
#include "TITLEBANNERParameter.h"
#include "BPMParameter.h"
#include "SCRIPTEDITParameter.h"
#include "MUSICCOPYRIGHTParameter.h"
#include "XSBParameter.h"
#include "XWBParameter.h"
#include "WAVParameter.h"
#include "DBGHiSpeedParameter.h"
#include "LEVELParameter.h"
#include "FIRSTDELAYParameter.h"
namespace wiz{
namespace Script{


//////////////////////////////
//	:
//	: 
//	: コンストラクタ
SMFactory::SMFactory(std::map<std::wstring , bassManager*>& i_ScriptMap){
	i_ScriptMap[L"MLPSCRIPTVERSION"]	= new MLPSCRIPTVERSION;
	i_ScriptMap[L"BPM"]					= new BPM;
	i_ScriptMap[L"FIRSTDELAY"]			= new FIRSTDELAY;
	i_ScriptMap[L"TITLE"]				= new TITLE;
	i_ScriptMap[L"TITLEBANNER"]			= new TITLEBANNER;
	i_ScriptMap[L"EASYLEVEL"]			= new EASYLEVEL;
	i_ScriptMap[L"HARDLEVEL"]			= new HARDLEVEL;
	i_ScriptMap[L"NORMALLEVEL"]			= new NORMALLEVEL;
	i_ScriptMap[L"SCRIPTEDIT"]			= new SCRIPTEDIT;
	i_ScriptMap[L"MUSICCOPYRIGHT"]		= new MUSICCOPYRIGHT;
	i_ScriptMap[L"XSB"]					= new XSB;
	i_ScriptMap[L"XWB"]					= new XWB;
	i_ScriptMap[L"EASYXSB"]				= new EASYXSB;
	i_ScriptMap[L"EASYXWB"]				= new EASYXWB;
	i_ScriptMap[L"NORMALXSB"]			= new NORMALXSB;
	i_ScriptMap[L"NORMALXWB"]			= new NORMALXWB;
	i_ScriptMap[L"HARDXSB"]				= new HARDXSB;
	i_ScriptMap[L"HARDXWB"]				= new HARDXWB;
	i_ScriptMap[L"WAV"]					= new WAV;
	i_ScriptMap[L"DBGHiSpeed"]			= new DBGHiSpeed;
}
//	: デストラクタ
SMFactory::~SMFactory()
{
}


}//end name
}