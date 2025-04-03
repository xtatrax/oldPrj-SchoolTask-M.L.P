/**************************************************************************
 Tempus.h

 class Tempus; �錾
                                                    2012/04/17�@���� �O
****************************************************************************/
#pragma once
namespace wiz{
/**************************************************************************
 class Tempus;
 �p�r: ���ԃN���X
****************************************************************************/
class Tempus
{
	static DWORD m_ElapsedFrame;	//	: �o�߃t���[��
	static float m_ElapsedTime;		//	: �N������̌o�ߎ���
	static float m_fTime;			//	: 1�t���[���̌o�ߎ���
	static float m_fFps;			//	: Frame / Second
	static float m_fFixFpsTime;		//	: FPS����
//::::: �E���� :::::://
	static int	 m_f[60];			//	:
	static int   m_t;				//	:
	static int   m_ave;				//	:
public:
	Tempus(void);
	~Tempus(void);

	static void    TimeUpdate();		//	: ���Ԃ��X�V
	static float   getOneFrameTime();	//	: 1�t���[���̌o�ߎ��Ԃ��l��
	static float   getElapsedTime();	//	: �N������̌o�ߎ���
	static float   getFps();			//	: FPS�̊l��
	static double  getClockSec();		//	: �b�̊l��
	static clock_t getClock();			//	: �������<-
	//static void  FixedFPS(int i_iFPS);
};
}