/**************************************************************************
 DebugFunks.h

 
                                                    2012/03/04　名前 鴫原 徹
****************************************************************************/
#pragma once
#include "StdAfx.h"


namespace wiz{
#if defined(DEBUG) || defined(_DEBUG)
namespace Debugger{
/************************************************
class tagDBGSTR

目的:　簡易的に文字列を画面上に描画
*************************************************/
class DBGSTR{
public:
	static wchar_t			str[4096];
	static LPD3DXFONT		m_lpDebagFont;        // フォントオブジェク

	static void addStr(wchar_t* addStr,...){
		wchar_t strBuf[1024];
		va_list	argp;
		va_start(argp, addStr);
		vswprintf_s( strBuf , 1024 , addStr, argp);
		va_end(argp);
		wsprintf(str,L"%s%s" , str ,strBuf);
	}
	static void Init(LPDIRECT3DDEVICE9	i_pD3DDevice){
		try{
			if (FAILED(D3DXCreateFont(i_pD3DDevice,				/* デバイス */
							10,									/* 文字の高さ */
							0,									/* 文字幅 */
							FW_NORMAL,							/* フォントの太さ */
							1,									/* MIPMAPのレベル */
							FALSE,								/* イタリックか？ */
							DEFAULT_CHARSET,					/* 文字セット */
							OUT_DEFAULT_PRECIS,					/* 出力精度 */
							DEFAULT_QUALITY,					/* 出力品質 */
							DEFAULT_PITCH | FF_SWISS,			/* フォントピッチとファミリ */
							L"ＭＳ ゴシック",					/* フォント名 */
							&m_lpDebagFont))) {					/* Direct3Dフォントへのポインタへのアドレス */
				char		strBuf[2048]={0};
				sprintf_s(strBuf,sizeof(strBuf), "デバッグ用フォントの生成に失敗\n 場所 : \"%s(%d) Func:%s\" \n続けますか？",__FILE__,__LINE__,__FUNCTION__);
				wchar_t		outBuf[4096]={0};
				setlocale( LC_CTYPE, "jpn" );
				size_t nNameSize = 0;
				mbstowcs_s(&nNameSize,outBuf,strlen(strBuf),strBuf,_TRUNCATE);
				if(MessageBox(NULL,outBuf,L"デバッグ関数エラー 場所:tagDBGSTR::Init",MB_YESNO) == IDNO){
					throw 1;
				}
			}
		}
		catch(...){
			throw;
		}
	}
	static void Draw(){
		m_lpDebagFont->DrawText(NULL,str, -1, NULL
			, 0 , D3DCOLOR_ARGB(255, 255, 255, 124));
		wsprintf(str,L"\n\n\n\n\n\n\n\nデバッグ\n\0" );
	}
};
}
#endif
}