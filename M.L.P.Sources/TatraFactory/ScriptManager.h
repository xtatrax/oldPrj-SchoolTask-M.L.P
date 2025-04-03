////////////////////////////// //////////////////////////////
//	ソース名		：ScriptManager
//	ファイル名		：ScriptManager.h
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：tatra
//	内包ﾃﾞｰﾀと備考	：
//
//
#pragma once
#include "../stdafx.h"
#include "bassManager.h"
//#include "SMFactory.h"



namespace wiz{
//	: 
namespace Script{
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
//////////////////////////////
//	: 先頭の空白飛ばし  
int BlankSkip(char* i_wstring, int i_begin = 0);
//////////////////////////////
//	: 先頭の空白飛ばし  
int getBlankPos(std::wstring& i_wstring, unsigned int i_begin = 0);
//////////////////////////////
//	: 先頭の空白削除
std::wstring BlankDelete(std::wstring& i_wstring);
//////////////////////////////
//	: すべての空白削除
std::wstring AllBlankDeleteAll(std::wstring& i_wstring);
//////////////////////////////
//	: パラメータ解析
std::wstring exParameter(std::wstring& i_wstring);
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/


/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
class ScriptManager
{        
//////////////////////////////
//	: private変数
	//	: stream
	static std::wfstream BodyFp;
	//	: 
	static std::wstring SongsDirectory;
	//	: パラメータマップ
	static std::map<std::wstring , bassManager*> m_ScriptMap;
//////////////////////////////
//	: private関数
	//	: コマンド分離
	static Commander ReadCommand(std::wstring& i_wstring);
	//	： 文字列検索と移動
	static void SearchBodyBegin();
	//	: 
	static void SearchSongsDirectory(vector<wstring>& o_PathVec);
public:
	ScriptManager(void);
	~ScriptManager(void);
	//	: 楽曲サーチ
	static void SearchSongs(vector<MLPHeader>& o_vec);
	//	: Header読み込み
	static MLPHeader ReadHeader(std::wstring folderPath, std::wstring fileName);
	//	: ボディ読み込み開始
	static void BodyReadBegin(std::wstring fileName,SCORELEVEL Level);
	//	: ボディ読み込み
	static std::wstring BodyRead();
	//	: ボディ読み込み終了
	static void BodyReadEnd();

};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

}}