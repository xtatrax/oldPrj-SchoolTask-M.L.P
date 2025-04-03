/**************************************************************************
Tempus.cpp
時間関係の関数群
 class Tempus; 定義
                                                    2012/04/17　名前 鴫原 徹
****************************************************************************/
#include "StdAfx.h"
#include "Tempus.h"

namespace wiz{

DWORD Tempus::m_ElapsedFrame	= 0;
float Tempus::m_ElapsedTime		= 0;
float Tempus::m_fTime			= 0;
float Tempus::m_fFps			= 0;
float Tempus::m_fFixFpsTime		= 1.0f/60.0f;
int Tempus::m_f[60];
int Tempus::m_t;
int Tempus::m_ave;
/**************************************************************************
 関数名: Tempus::Tempus();
 用途: コンストラクタ
 戻り値: なし
****************************************************************************/
Tempus::Tempus(void)
{
	m_fFixFpsTime = 1.0f/60.0f;
}
/**************************************************************************
 関数名: Tempus::~Tempus();
 用途: デストラクタ
 戻り値: なし
****************************************************************************/
Tempus::~Tempus(void)
{
}
/**************************************************************************
 関数名: Tempus::TimeUpdate();
 用途: 時間の更新
 戻り値: なし
****************************************************************************/
void  Tempus::TimeUpdate(){
	m_ElapsedFrame++;
	float fElapsoTempore;// = (float)getClockSec();	//	: 開始からの経過時間
	while( ((fElapsoTempore = (float)getClockSec()) - m_ElapsedTime) < m_fFixFpsTime){
		Sleep(1);
	}
	m_fTime =  fElapsoTempore - m_ElapsedTime;
	m_ElapsedTime = fElapsoTempore;
//･･････････････････････････････････････････････････････････････････････････
//拾い物 後で調べる
    //static int t=0,ave=0,f[60];
 
    m_f[m_ElapsedFrame%60]=timeGetTime()-m_t;
    m_t=timeGetTime();
    if(m_ElapsedFrame%60==59){
        m_ave=0;
        for(int i=0;i<60;i++)
            m_ave+=m_f[i];
        m_ave/=60;
    }
    if(m_ave!=0){
        m_fFps = 1000.0f/(float)m_ave;
    }
//･･････････････････････････････････････････････････････････････････････････

#ifdef ___MLP_DEBUG_TIMEDRAW_
	int h = (int)(m_ElapsedTime / (60 * 60)) % 24;
	int m = (int)(m_ElapsedTime / 60) % 60;
	int S = (int)(m_ElapsedTime) % 60;
	int	iBuf = (int)(m_ElapsedTime);

	//float ms = (int)(m_ElapsedTime) % 60;
	wiz::Debugger::DBGSTR::addStr(
		L"時間:\n"
		L"FPS = %2.2f \n"
		L"%02d時 %02d分 %02d秒 %02d㍉秒\n"
		L"m_fElapsoTempore = %f\n"
		L"m_fTempore       = %f\n",
		m_fFps,
		h,m,S,int(m_ElapsedTime * 100) % 100,
		m_ElapsedTime,
		m_fTime
		);
#endif
}

/**************************************************************************
 関数名: Tempus::getOneFrameTime();
 用途: １フレームの経過時間を返す
 戻り値: 経過時間
****************************************************************************/
float Tempus::getOneFrameTime(){
	return m_fTime;
}
/**************************************************************************
 関数名: Tempus::getElapsedTime();
 用途: 起動からの経過時間(TimeUpdate時現在)
 戻り値: 起動からの経過時間
****************************************************************************/
float Tempus::getElapsedTime(){
	return m_ElapsedTime;
}
double Tempus::getClockSec(){
	return double( clock()) / double( CLOCKS_PER_SEC);
}
/**************************************************************************
 関数名: Tempus::getFps();
 用途: フレームレートの計算
 戻り値: フレームレート
****************************************************************************/
float Tempus::getFps(){
	return m_fFps;
};
clock_t Tempus::getClock(){
	return clock();
}
//	: 未実装
//void Tempus::FixedFPS(int i_iFPS){
//	
//	
//}

}