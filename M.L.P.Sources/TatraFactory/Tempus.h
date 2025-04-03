/**************************************************************************
 Tempus.h

 class Tempus; 宣言
                                                    2012/04/17　鴫原 徹
****************************************************************************/
#pragma once
namespace wiz{
/**************************************************************************
 class Tempus;
 用途: 時間クラス
****************************************************************************/
class Tempus
{
	static DWORD m_ElapsedFrame;	//	: 経過フレーム
	static float m_ElapsedTime;		//	: 起動からの経過時間
	static float m_fTime;			//	: 1フレームの経過時間
	static float m_fFps;			//	: Frame / Second
	static float m_fFixFpsTime;		//	: FPS制限
//::::: 拾い物 :::::://
	static int	 m_f[60];			//	:
	static int   m_t;				//	:
	static int   m_ave;				//	:
public:
	Tempus(void);
	~Tempus(void);

	static void    TimeUpdate();		//	: 時間を更新
	static float   getOneFrameTime();	//	: 1フレームの経過時間を獲得
	static float   getElapsedTime();	//	: 起動からの経過時間
	static float   getFps();			//	: FPSの獲得
	static double  getClockSec();		//	: 秒の獲得
	static clock_t getClock();			//	: くろっく<-
	//static void  FixedFPS(int i_iFPS);
};
}