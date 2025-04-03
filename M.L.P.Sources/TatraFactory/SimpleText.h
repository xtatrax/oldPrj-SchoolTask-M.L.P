/**************************************************************************
 SimpleText.h

 SimpleText; 宣言
                                                    2012/03/04　名前
****************************************************************************/
#pragma once
#include "../StdAfx.h"

namespace wiz{

/************************************************
class tagDBGSTR

目的:　簡易的にテキストを描画する
*************************************************/
class SimpleText:public Object
{
	LPD3DXFONT		m_lpFont;        // フォントオブジェク
public:
	std::wstring		str;

	SimpleText(LPDIRECT3DDEVICE9 i_pD3DDevice){
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
							L"ＭＳ Ｐゴシック",					/* フォント名 */
							&m_lpFont))) {						/* Direct3Dフォントへのポインタへのアドレス */
				//char		strBuf[2048]={0};
				//sprintf_s(strBuf,sizeof(strBuf), "フォント生成に失敗\n 場所 : \"%s(%d) Func:%s\" \n続けますか？",__FILE__,__LINE__,__FUNCTION__);
			throw DxException(
				L"テクスト作成に失敗しました。",
				L"SimpleText::SimpleText()"
				);
			}
		}
		catch(...){
			throw;
		}
	}
	~SimpleText(void){};
	void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
    vector<Object*>& Vec,const CONTROLER_STATE* pCntlState , Command& Com){
		m_lpFont->DrawText(NULL,str.c_str(), -1, NULL
			, 0 , D3DCOLOR_ARGB(255, 255, 255, 255));
	}
};
}