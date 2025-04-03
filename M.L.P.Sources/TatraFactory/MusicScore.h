/**************************************************************************
 MusicScore.h

 class MusicScore  宣言
                                                    2012/04/20　名前 鴫原 徹
****************************************************************************/
#pragma once

#include "../StdAfx.h"
#include "Measure.h"

namespace wiz{


/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/**************************************************************************
 class MusicScore ;
 用途: 楽譜クラス
	小節を管理する
****************************************************************************/
class MusicScore{
private:
	MeasureVec	m_MeasureVec;			//	: 小節配列
	MeasureSizeType m_MeasureVecSize;	//	: 小節の数
	DWORD		m_ALLNoteQt;			//	: この楽譜に含まれる音符の総数
public:
	Script::MLPHeader m_MLPHeader;
/**************************************************************************
 void Clear();
 用途  : ポインタ系データの全削除
 戻り値: 無し
***************************************************************************/
	void Clear(){
		MeasureVec::iterator it;
		for(it = m_MeasureVec.begin();it != m_MeasureVec.end();it++){
			SafeDelete(*it);
		}
		m_MeasureVec.clear();
	}
/**************************************************************************
 MusicScore(
	 Script::MLPHeader  i_MLSheader,	//	: プレイする楽曲のヘッダーデータ
	 Script::SCORELEVEL i_Level			//	: プレイするレベル種別
 );
 用途: 
 戻り値: 
***************************************************************************/
	MusicScore( Script::MLPHeader i_MLSheader, Script::SCORELEVEL i_Level )
		:m_ALLNoteQt(0)
	{
		//	: ヘッダー受け取り
		m_MLPHeader = i_MLSheader;
		//楽譜読込み//////////////////
		//	: 読み込むファイルとレベルの指定
		Script::ScriptManager::BodyReadBegin(m_MLPHeader.FilePath + m_MLPHeader.FileName,i_Level);
		std::wstring wstrScriptBuffer;	//	: 読込みバッファ
		//	: END命令を見つけるまで一行読み込み
		while(( wstrScriptBuffer = Script::ScriptManager::BodyRead()) != L"END"){
			Measure* pMeasure = NULL;
			m_MeasureVec.push_back((pMeasure = new Measure( wstrScriptBuffer )));
			m_ALLNoteQt += pMeasure->getNoteQt();
		}
		//	: 読込み完了の合図
		Script::ScriptManager::BodyReadEnd();
		//////////////////////////////
		m_MeasureVecSize = m_MeasureVec.size();
	}
/**************************************************************************
 用途: 
 戻り値: 
***************************************************************************/
	ScoreNote::NoneData getAddNotes(MeasureSizeType i_ActiveMeasureNum,SNoteSizeType i_ActiveNoteNum){
		if(m_MeasureVecSize <= i_ActiveMeasureNum)
			return SCOREENDFLAG;
		return m_MeasureVec[i_ActiveMeasureNum]->getAddNotes(i_ActiveNoteNum);
	
	}
/**************************************************************************
 用途: 
 戻り値: 
***************************************************************************/
	MeasureSizeType getMeasureSize( ){
		return m_MeasureVecSize;
	}
/**************************************************************************
 用途: 
 戻り値: 
***************************************************************************/
	SNoteSizeType getNoteSize(MeasureSizeType i_ActiveMeasureNum){
		if(i_ActiveMeasureNum < m_MeasureVecSize)
			return m_MeasureVec[i_ActiveMeasureNum]->getNoteSize();
		return 0;
	}
/**************************************************************************
 用途: 
 戻り値: 
***************************************************************************/
	DWORD getALLNoteQt(){
		return m_ALLNoteQt;
	}
/**************************************************************************
 用途: 
 戻り値: 
***************************************************************************/
	~MusicScore(){
		Clear();
	}

};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/



}
//end of namespace wiz.
