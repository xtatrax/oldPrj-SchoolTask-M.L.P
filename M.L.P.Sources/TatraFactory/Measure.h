/**************************************************************************
 Measure.h

 class Measure  宣言
                                                    2012/04/20　名前 鴫原 徹
****************************************************************************/
#pragma once

#include "../StdAfx.h"
#include "ScoreNote.h"

namespace wiz{
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/**************************************************************************
 class Measure ;
 用途: 小節クラス
	音符を管理する
****************************************************************************/
class Measure;
typedef vector<Measure*>            MeasureVec;
typedef vector<Measure*>::size_type MeasureSizeType;
class Measure{
protected:
	SNoteVec		m_NotesVec;		//	: 一拍のデータ配列
	SNoteSizeType	m_NoteVecSize;	//	: 小節内の拍数
	DWORD			m_dwNoteQt;		//	: 小節内の音符の総数
/**************************************************************************
 wstring MeasureDec(
	wstring& i_str
 );
 用途  : 渡された命令群からワンセットの命令を取り出す
 戻り値: "END" または １セットに分割された命令 または i_str
***************************************************************************/
	wstring MeasureDec(wstring& i_str){

		//	: 先頭空白を削除
		Script::BlankDelete(i_str);

		//	: 命令開始位置まで読み飛ばし
		while(!i_str.empty() && i_str.at(0) != '['){
			i_str.erase(0,1);
		}

		//	: 命令の最後に到達したら"END"命令を返す
		if(i_str.empty())return L"END";

		//	: 命令の終了位置の獲得
		wstring::size_type sz = i_str.find(']');

		//	: もし見つからなかったら今の状態を返す
		if(sz == i_str.npos)return i_str;

		//	: 今の状態をコピー
		wstring retstr = i_str;

		//	: 読み取った位置を削除
		i_str.erase(0,sz);

		//	: いらないところを削除
		retstr.erase(sz+1);

		//	: 読み取った命令を返す
		return retstr;
	}
public:
/**************************************************************************
 void Clear();
 用途  : ポインター系メンバの全削除
 戻り値: 無し
***************************************************************************/
	void Clear(){
		SNoteVec::iterator it;
		for(it = m_NotesVec.begin();it != m_NotesVec.end();it++){
			SafeDelete(*it);
		}
		m_NotesVec.clear();
	}
/**************************************************************************
 Measure(
	std::wstring i_Score	//	: 
 );
 用途  : コンストラクタ
 戻り値: 無し
***************************************************************************/
	Measure(std::wstring i_Score )
		:m_dwNoteQt(0)
	{	
		wstring str;
		//	: "END"の文字列が帰ってくるまで命令を読み婚で
		//	: 音符データを構築する
		while((str = MeasureDec(i_Score)) != L"END"){

			//	: 一拍のデータを構築
			ScoreNote* pScoreNote = new ScoreNote(str);
			//	: この小節内にある音符のかずを数える
			m_dwNoteQt += pScoreNote->getNoteQt();
			//	: 音符配列へ追加
			m_NotesVec.push_back(pScoreNote);
		}
		m_NoteVecSize = m_NotesVec.size();
	};

/**************************************************************************
 ~Measure();
 用途  : デストラクタ
 戻り値: 無し
***************************************************************************/
	~Measure(){
		Clear();
	};
/**************************************************************************
 ScoreNote::NoneData getAddNotes(
	vector<ScoreNote*>::size_type i_ActiveNoteNum
);
 用途  : 追加すべき音符のデータ
 戻り値: 追加するべき音符
***************************************************************************/
	ScoreNote::NoneData getAddNotes(vector<ScoreNote*>::size_type i_ActiveNoteNum){
		//	: ノートが一つもなかった場合
		if(m_NoteVecSize == 0 || m_NoteVecSize <= i_ActiveNoteNum){
			return ScoreNote::NoneData( MEASUREENDFLAG );
		}

		return m_NotesVec[i_ActiveNoteNum]->getAllNotes();
	};
/**************************************************************************
 SNoteSizeType getNoteSize();
 用途  : 小節内の拍数を返す
 戻り値: 小節内の拍数
***************************************************************************/
	SNoteSizeType getNoteSize(){
		return m_NoteVecSize;
	};
/**************************************************************************
 DWORD getNoteQt();
 用途  : 小節内の音符数を返す
 戻り値: 小説内の音符数
***************************************************************************/
	DWORD getNoteQt(){
		return m_dwNoteQt;
	};
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

};
}
//end of namespace wiz.
