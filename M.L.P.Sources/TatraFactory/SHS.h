////////////////////////////// //////////////////////////////
//	ソース名        ：ScriptHeaderStruct
//	ファイル名      ：SHS.h
//	開発環境        ：MSVC++ 2008
//	最適タブ数      ：4
//	担当者          ：tatra
//	内包ﾃﾞｰﾀと備考  ：スクリプト関係に必要なヘッダー群
//	                ：実質的にはいろいろな構造体や列挙型の詰め合わせ
//
#pragma once
#include "../stdafx.h"

namespace wiz{
//------- --------- --------- --------- --------- --------- --------- --------- //
//	スクリプト用データ群                                                        //
//------- --------- --------- --------- --------- --------- --------- --------- //
namespace Script{
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*
**	譜面のレベルカテゴリー
**
**★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
enum SCORELEVEL{
	EASY,
	NORMAL,
	HARD
};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*
**	譜面のレベルを記憶しておく構造体
**
**★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
struct Level{
	int Easy;
	int Normal;
	int Hard;
	int& operator[](BYTE lv){
		if(lv == EASY) return Easy;
		if(lv == NORMAL) return Normal;
		if(lv == HARD) return Hard;
		return Easy;
	}
	Level(){}
	Level(int easy,int normal,int hard)
		:Easy(easy),Normal(normal),Hard(hard){}
};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*
**	スクリプトの命令を解読するときとかに必要
**
**★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
struct Commander{
	//	: 命令の種類 ( TITLE見込みとかWAV読み込みとか
	std::wstring m_CommandType;
	//	: 命令内容   ( 読み込み先とか
	std::wstring m_Command;
	//	: 
	Commander(){};
	//	:
	Commander(std::wstring i_CType,std::wstring i_Command)
		:m_CommandType(i_CType),m_Command(i_Command)
	{
	};
};

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*
**	譜面スクリプトのヘッダーでーたを
**	記憶すておく酵素増体
**★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
struct MLPHeader{
	std::wstring FileName;		//	: ファイルの名前
	std::wstring FilePath;		//	: ファイルの場所
	std::wstring SCVersion;		 //	: スクリプトバージョン
	std::wstring Title;			  //	: 曲名
	std::wstring TitleBanner;	   //	: 曲名バナー
	std::wstring ScriptEdit;		//	: 譜面データ製作者
	std::wstring MusicCopyright;	//	: 楽曲制作者
	std::wstring XSBPath ;		   //	: サウンドバンクパス
	std::wstring XWBPath ;		  //	: ウェブバンクパス
	std::wstring EASYXSBPath ;	 //	: サウンドバンクパス
	std::wstring EASYXWBPath ;	 //	: ウェブバンクパス
	std::wstring NORMALXSBPath ;  //	: サウンドバンクパス
	std::wstring NORMALXWBPath ;   //	: ウェブバンクパス
	std::wstring HARDXSBPath ;		//	: サウンドバンクパス
	std::wstring HARDXWBPath ;		 //	: ウェブバンクパス
	Level		 Level ;		    //	: レベル構造体
	unsigned int Bpm ;			  //	: てんぽ
	float        DBGHiSpeed ;	 //	: デバッグ用のHiSpeed
	float		 FirstDelay;	//	: ステージが開始されてから曲が始まるまでの時間
	MLPHeader()
		:Bpm(0),FirstDelay(0),DBGHiSpeed(1)
	{
		
	}

};
typedef std::vector<MLPHeader*> HeaderPVec;

}
//------- --------- --------- --------- --------- --------- --------- --------- //
//	ついでデータ群                                                              //
//------- --------- --------- --------- --------- --------- --------- --------- //

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*
**	判定カテゴリーの列挙型
**
**★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
enum JUDGE{
	NOJUDGE = -1,
	POOR,
	BAD,
	GOOD,
	GREAT,

};

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*
**	ランク計算に必要なデータ群？
**
**★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
struct ResultFactor{
	wstring	m_BannerPath;	//	: タイトルババーのPath
	DWORD	m_dwAllNoteQt;	//	: 音符の数
	DWORD	m_dwGreatQt;	//	: グレートの数
	DWORD	m_dwGoodQt;		//	: グッドの数
	DWORD	m_dwBadQt;		//	: バッドの数
	DWORD	m_dwPoorQt;		//	: プアーの数
	float	m_fGaugePar;	//	: ゲージのパーセンテージ
	ResultFactor()
		:m_dwAllNoteQt(0),
		 m_dwGreatQt(0),
		 m_dwGoodQt(0),
		 m_dwBadQt(0),
		 m_dwPoorQt(0),
		 m_fGaugePar(0.0f)
	{}
};


class JudgeSprite;
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*
**	Play画面で使う
**
**★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
struct PlayCommandPacket{
	float			m_fMeasureChangeDelay;
	float			m_fJudgePosZ;
	JudgeSprite*	m_pJudgeSprite;
	ResultFactor*		m_pRankFactor;
	PlayCommandPacket()
		:m_fMeasureChangeDelay(1.0f),
		 m_fJudgePosZ(0),
		 m_pJudgeSprite(NULL),
		 m_pRankFactor(NULL)
	{}
};

}