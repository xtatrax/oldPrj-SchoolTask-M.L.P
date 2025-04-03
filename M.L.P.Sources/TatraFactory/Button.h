/**************************************************************************
 Button.h

 class Button : public Object 宣言
                                                    2012/03/04　名前 鴫原 徹
****************************************************************************/
#pragma once

#include "../StdAfx.h"
#include "../Plate.h"
namespace wiz{


/**************************************************************************
 class Button ;
 用途: ボタン根底クラス
 用法: もしButtonPlateから派生しないクラスをボタンにしたい時は以下のようにす
	ることによってボタン化することができます
	まずこのクラスをクラス内に宣言してください
		例)
		    class CLS{
		    private:
		       Button m_ButtonPrm;
		       ・
		       ・
		       ・
	次にオブジェクト配列追加する際、StageクラスのButton用配列にこのクラスの
	インスタンスへのポインターを追加してください
		例)	m_vec.push_back(pButtonPlate);
			m_ButtonVec.push_back(&pButtonPlate->m_ButtonPrm);
 ****************************************************************************/
class Button {
protected:
	DWORD	m_Index;				//メニュー上のインデックス
	bool	m_IsSelect;				//選択フラグ
	bool	m_IsBoot;				//決定フラグ
	DWORD	m_Command;				//コマンド
	
public:
/**************************************************************************
 Button(
    LPDIRECT3DDEVICE9 pD3DDevice,   ////IDirect3DDevice9インターフェイスへのポインタ
	DWORD Cmd,						//選択実行されたときのコマンド
	DWORD Index,					//メニューステージ上のインデックス
    );
 用途: コンストラクタ
 戻り値: なし
***************************************************************************/
    Button(DWORD Cmd,DWORD Index);
/**************************************************************************
 virtual ~Button();
 用途: デストラクタ
 戻り値: なし
***************************************************************************/
    virtual ~Button();
/**************************************************************************
 void setSelect(
	bool select	//選択状態
 );
 用途: 選択状態を設定
 戻り値: なし。
***************************************************************************/
	void setSelect(bool select){
		m_IsSelect = select;
	}
/**************************************************************************
 void setBoot();
 用途: 決定フラグをセットする
 戻り値: なし。
***************************************************************************/
	void setBoot(){
		m_IsBoot = true;
	}
/**************************************************************************
 bool getSelect();
 用途: 選択されてるかどうか
 戻り値: 0 非選択 / 1 選択
***************************************************************************/
	bool getSelect(){
		return m_IsSelect;
	}
/**************************************************************************
 bool getBoot();
 用途: 決定されたかどうか
 戻り値: 0 非決定 / 1 決定
***************************************************************************/
	bool getBoot(){
		return m_IsBoot;
	}
/**************************************************************************
 void setSelect();
 用途: コマンドの発行
 戻り値: 発行されたコマンド
***************************************************************************/
	Command CommandIssue(){
		Command Com;
		Com.m_Command = m_Command;
		Com.m_Param1  = 0;
		Com.m_Param2  = 0;
		return Com;
	}
/**************************************************************************
 void setSelect();
 用途: コマンドの発行
 戻り値: 発行されたコマンド
***************************************************************************/
	DWORD getIndex(){
		return m_Index;
	}
};

}
//end of namespace wiz.
