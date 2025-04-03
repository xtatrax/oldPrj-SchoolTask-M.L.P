////////////////////////////// //////////////////////////////
//	ソース名		：ScriptManager
//	ファイル名		：ScriptManager.cpp
//	開発環境		：MSVC++ 2008
//	最適タブ数		：4
//	担当者			：tatra
//	内包ﾃﾞｰﾀと備考	：
//
//
#include "stdafx.h"
#include "ScriptManager.h"
#include "SMFactory.h"
#include "SHS.h"
namespace wiz{
namespace Script{
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/**************************************************************************
int BlankSkip(char* i_wstring, int i_begin){
 用途:		空白区切りの位置を調べる
 戻り値:	空白区切の位置
***************************************************************************/
int BlankSkip(char* i_wstring, int i_begin){
	do{
		if(i_wstring[i_begin] == ' '){
			i_begin++;
		}else
		if( i_wstring[i_begin] == 0x81 && i_wstring[i_begin+1] == 0x40){//127 && i_wstring[i_begin+1] == 0x40
			i_begin += 2;
		}else break;
	}while(true);
	return i_begin;
}
/**************************************************************************
int getBlankPos(std::wstring& i_wstring, int i_begin);
 用途:		空白区切りの位置を調べる
 戻り値:	空白区切の位置
***************************************************************************/
int getBlankPos(std::wstring& i_wstring, unsigned int i_begin){
	do{
		//	: もし文字のの終端まで空白文字がなければ０を返す
		if(	i_wstring.size() <= i_begin || i_wstring.at(i_begin) == '\0')
			return 0;
		//	: 空白文字を見つけたらループ終了
		if( (i_wstring.at(i_begin) == L' ' )||
			(i_wstring.at(i_begin) == 0x81 && i_wstring.at(i_begin+1) == 0x40 )||//
			(i_wstring.at(i_begin) == L'	')||
			(i_wstring.at(i_begin) == L'\n'))
			break;
		i_begin++;
	}while(true);
	return i_begin;
}
/**************************************************************************
std::wstring BlankDelete(std::wstring& i_wstring);
 用途:		先頭空白の削除
 戻り値:	削除後の文字列
***************************************************************************/
std::wstring BlankDelete(std::wstring& i_wstring)
{
	//	: 最後尾確認
	while( !i_wstring.empty() ){
		//	: 空白確認
		if(i_wstring.at(0) == ' ' || i_wstring.at(0) == '	')
			i_wstring = i_wstring.erase(0,1);
		else
		if(i_wstring.at(0) == 0x81 && i_wstring.at(1) == 0x40)//-127 && i_wstring.at(1) == 0x40
			i_wstring = i_wstring.erase(0,2);
		else break;
	}
	return i_wstring;
}
/**************************************************************************
std::wstring BlankDelete(std::wstring& i_wstring);
 用途:		先頭空白の削除
 戻り値:	削除後の文字列
***************************************************************************/
std::wstring AllBlankDeleteAll(std::wstring& i_wstring)
{
	wstring::size_type i = 0;
	//	: 最後尾確認
	while( !i_wstring.empty() && i < i_wstring.size()){
		//	: 空白確認
		if(i_wstring.at(i) == ' ' || i_wstring.at(i) == '	' || i_wstring.at(i) == '\n')
			i_wstring = i_wstring.erase(0,1);
		else
		if(i_wstring.at(i) == 0x81 && i_wstring.at(1) == 0x40)//-127 && i_wstring.at(i) == 0x40
			i_wstring = i_wstring.erase(0,2);
		else i++;
	}
	return i_wstring;
}
/**************************************************************************
std::wstring exParameter(std::wstring& i_wstring);
 用途:		
 戻り値:	なし
***************************************************************************/
//std::wstring exParameter(std::wstring& i_wstring)
//{
//	std::wstring o_wstring;
//	//	: 先頭の空白削除
//	BlankDelete(i_wstring);
//	int i = 0;
//	//	: 
//	while(	i_wstring.at(i) != i_wstring.npos,
//			i_wstring.at(i) != ' '
//	){
//		o_wstring += i_wstring.at(i);
//		i++;
//	}
//	i_wstring.erase(0,i);
//	return o_wstring;
//}



/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/


//	:
std::wfstream ScriptManager::BodyFp;
//	: パラメータマップ
std::map<std::wstring , bassManager*> ScriptManager::m_ScriptMap;
//	:
std::wstring ScriptManager::SongsDirectory = L"Songs/";


/**************************************************************************
 ScriptManager::ScriptManager();
 用途:		コンストラクタ
 戻り値:	なし
***************************************************************************/
ScriptManager::ScriptManager(void)
{
	SMFactory::SMFactory(m_ScriptMap);
}
/**************************************************************************
 ScriptManager::~ScriptManager();
 用途:		デストラクタ
 戻り値:	なし
***************************************************************************/
ScriptManager::~ScriptManager(void)
{
}
void ScriptManager::SearchSongsDirectory(vector<wstring>& o_PathVec){
	HANDLE handle;
	WIN32_FIND_DATA finddata;
	SetCurrentDirectory(SongsDirectory.c_str());
	//	: サブディレクトリ検索
	handle = FindFirstFile(L"*", &finddata );
	do{
		if((finddata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
			wcscmp(finddata.cFileName , L".") &&
			wcscmp(finddata.cFileName , L"..") ){
			o_PathVec.push_back(SongsDirectory + finddata.cFileName + L"/");
		}
	}while(FindNextFile( handle, &finddata ) );
	FindClose( handle );
	SetCurrentDirectory(L"../");

}
/**************************************************************************
 void ScriptManager::SearchSongs(vector<MLPHeader>& o_vec){
 用途:		楽曲データを探してヘッダー情報一覧を作成する
 戻り値:	なし
***************************************************************************/
void ScriptManager::SearchSongs(vector<MLPHeader>& o_vec){
//	: ディレクトリ一覧の生成
	vector<wstring> PathVec;		//	: Songsフォルダのサブフォルダ一覧
	SearchSongsDirectory(PathVec);
	WIN32_FIND_DATA finddata;
	wstring wstrBuf;
	vector<wstring>::size_type PVSizez = PathVec.size();
	for( vector<wstring>::size_type i = 0 ; i < PVSizez; i++ ){
		wstrBuf = PathVec.at(i) + L"*.MLS";
		if(FindFirstFile(wstrBuf.c_str(), &finddata ) != INVALID_HANDLE_VALUE ){
			o_vec.push_back(ReadHeader(PathVec.at(i) , finddata.cFileName));
		}
	}
//	: 

}
/**************************************************************************
 Commander ScriptManager::ReadCommand(std::wstring& i_wstring)
 用途:		一行の文字列から命令を読み取る
 戻り値:	読み取ったコマンド
***************************************************************************/
Commander ScriptManager::ReadCommand(std::wstring& i_wstring){
	//	: 命令受取り用変数
	Commander Com;
	//	: 先頭空白削除
	BlankDelete(i_wstring);
	//	: 命令行であるか
	if(i_wstring.empty() || i_wstring.at(0) != '#'){
		//	: 命令業でなければその旨を伝える
		return Commander(L"__NC",L"__NC");
	}
	i_wstring.erase(0,1);
	//	: 空白で区切られてる場所を判断
	int size	= getBlankPos(i_wstring);
	Com.m_CommandType = i_wstring;
	//	: 区切り文字を発見したら
	if(size){
		Com.m_CommandType.erase(size);
		//	:
		Com.m_Command = i_wstring;
		Com.m_Command.erase(0,size);
		//Com.m_Command.copy(buf,size,1);
		BlankDelete(Com.m_Command);
		if(Com.m_Command.empty()){
			return Commander(Com.m_CommandType,L"NOTHEADER");
		}
		//buf[size-1] = '\0';
		//Com.m_CommandType = buf;
	} 
	else{
		return Commander(Com.m_CommandType,L"NOTHEADER");
	}
	return Com;
}

/**************************************************************************
 Commander ScriptManager::ReadHeader(char* fileName)
 用途:		ヘッダーのデータを読み取る
 戻り値:	読み取ったコマンド
***************************************************************************/
MLPHeader ScriptManager::ReadHeader(std::wstring folderPath, std::wstring fileName )
{
	MLPHeader header;
	header.FileName = fileName;
	header.FilePath = folderPath;
	wstring lineBuf = folderPath + fileName;
	//	: ファイルOpenと結果
	std::wfstream fs(lineBuf.c_str());
	if(fs.fail()){
		MessageBox(NULL,L"読み込みに失敗",fileName.c_str(),NULL);
		return MLPHeader();
	}
	std::map<std::wstring , bassManager*>::iterator SMapIte;
	while( !fs.eof() && getline(fs,lineBuf)){
		Commander Com = ReadCommand(lineBuf);
		if(Com.m_Command == L"NOTHEADER") break;
		SMapIte = m_ScriptMap.find(Com.m_CommandType);
		if( SMapIte != m_ScriptMap.end() )
			m_ScriptMap[Com.m_CommandType]->Loader(Com.m_Command,header);
	}
	return header;
}
/**************************************************************************
void ScriptManager::BodyReadBegin(char* fileName){
 用途:		ヘッダーのデータを読み取る
 戻り値:	読み取ったコマンド
***************************************************************************/
void ScriptManager::BodyReadBegin(std::wstring fileName,SCORELEVEL Level){
	//	: ファイルOpenと結果
	BodyFp.open(fileName.c_str());
	if(BodyFp.fail()){
		MessageBox(NULL,L"読み込みに失敗",fileName.c_str(),NULL);
		return;
	}
	wstring lineBuf;
	MLPHeader header;
	while( !BodyFp.eof() && getline(BodyFp,lineBuf)){
		Commander Com = ReadCommand(lineBuf);
		if(	(Level == EASY		&& Com.m_CommandType == L"EASY")	||
			(Level == NORMAL	&& Com.m_CommandType == L"NORMAL")	||
			(Level == HARD		&& Com.m_CommandType == L"HARD"))	{
			return;
		}
	}


}
/**************************************************************************
void ScriptManager::BodyReadBegin(char* fileName){
 用途:		ヘッダーのデータを読み取る
 戻り値:	読み取ったコマンド
***************************************************************************/
std::wstring ScriptManager::BodyRead(){
	//	: 読み飛ばし
	wstring lineBuf,retBuf;
	while(!BodyFp.eof() && getline(BodyFp,lineBuf)){
		BlankDelete(lineBuf);
		if(lineBuf.empty()) continue;
		Commander Com = ReadCommand(lineBuf);
		if(Com.m_CommandType == L"END") return L"END";
		if(lineBuf.at(0) == '{')	break;
	
	}
	while( !BodyFp.eof() && getline(BodyFp,lineBuf)){
		BlankDelete(lineBuf);
		if(lineBuf.empty()) continue;
		if(lineBuf.at(0) == '}')	break;
		if(lineBuf.at(0) == '['){
			retBuf += lineBuf + L'\n';		
		}
	}
	return retBuf;
}
/**************************************************************************
void ScriptManager::BodyReadBegin(char* fileName){
 用途:		ヘッダーのデータを読み取る
 戻り値:	読み取ったコマンド
***************************************************************************/
void ScriptManager::BodyReadEnd(){
	BodyFp.close();
}
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

}}
#ifdef CS_CONS_COMPILE
//	: テスト用メイン
void main(){
	vector<wiz::Script::MLPHeader> o_vec;

	wiz::Script::ScriptManager::ScriptManager();
	wiz::Script::ScriptManager::SearchSongs(o_vec);
	//wiz::Script::MLPHeader hda = o_vec[0];
	wiz::Script::ScriptManager::BodyReadBegin(o_vec[0].FilePath + o_vec[0].FileName,wiz::Script::EASY);
	wstring st;
	while( (st = wiz::Script::ScriptManager::BodyRead()) != L"END"){
	}
	wiz::Script::ScriptManager::BodyReadEnd();
}
#endif