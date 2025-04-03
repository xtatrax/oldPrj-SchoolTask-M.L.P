/**************************************************************************
Tempus.cpp
���Ԋ֌W�̊֐��Q
 class Tempus; ��`
                                                    2012/04/17�@���O ���� �O
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
 �֐���: Tempus::Tempus();
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
****************************************************************************/
Tempus::Tempus(void)
{
	m_fFixFpsTime = 1.0f/60.0f;
}
/**************************************************************************
 �֐���: Tempus::~Tempus();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
****************************************************************************/
Tempus::~Tempus(void)
{
}
/**************************************************************************
 �֐���: Tempus::TimeUpdate();
 �p�r: ���Ԃ̍X�V
 �߂�l: �Ȃ�
****************************************************************************/
void  Tempus::TimeUpdate(){
	m_ElapsedFrame++;
	float fElapsoTempore;// = (float)getClockSec();	//	: �J�n����̌o�ߎ���
	while( ((fElapsoTempore = (float)getClockSec()) - m_ElapsedTime) < m_fFixFpsTime){
		Sleep(1);
	}
	m_fTime =  fElapsoTempore - m_ElapsedTime;
	m_ElapsedTime = fElapsoTempore;
//��������������������������������������������������������������������������
//�E���� ��Œ��ׂ�
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
//��������������������������������������������������������������������������

#ifdef ___MLP_DEBUG_TIMEDRAW_
	int h = (int)(m_ElapsedTime / (60 * 60)) % 24;
	int m = (int)(m_ElapsedTime / 60) % 60;
	int S = (int)(m_ElapsedTime) % 60;
	int	iBuf = (int)(m_ElapsedTime);

	//float ms = (int)(m_ElapsedTime) % 60;
	wiz::Debugger::DBGSTR::addStr(
		L"����:\n"
		L"FPS = %2.2f \n"
		L"%02d�� %02d�� %02d�b %02d�_�b\n"
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
 �֐���: Tempus::getOneFrameTime();
 �p�r: �P�t���[���̌o�ߎ��Ԃ�Ԃ�
 �߂�l: �o�ߎ���
****************************************************************************/
float Tempus::getOneFrameTime(){
	return m_fTime;
}
/**************************************************************************
 �֐���: Tempus::getElapsedTime();
 �p�r: �N������̌o�ߎ���(TimeUpdate������)
 �߂�l: �N������̌o�ߎ���
****************************************************************************/
float Tempus::getElapsedTime(){
	return m_ElapsedTime;
}
double Tempus::getClockSec(){
	return double( clock()) / double( CLOCKS_PER_SEC);
}
/**************************************************************************
 �֐���: Tempus::getFps();
 �p�r: �t���[�����[�g�̌v�Z
 �߂�l: �t���[�����[�g
****************************************************************************/
float Tempus::getFps(){
	return m_fFps;
};
clock_t Tempus::getClock(){
	return clock();
}
//	: ������
//void Tempus::FixedFPS(int i_iFPS){
//	
//	
//}

}