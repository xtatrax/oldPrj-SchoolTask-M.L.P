/**************************************************************************
 SimpleText.h

 SimpleText; �錾
                                                    2012/03/04�@���O
****************************************************************************/
#pragma once
#include "../StdAfx.h"

namespace wiz{

/************************************************
class tagDBGSTR

�ړI:�@�ȈՓI�Ƀe�L�X�g��`�悷��
*************************************************/
class SimpleText:public Object
{
	LPD3DXFONT		m_lpFont;        // �t�H���g�I�u�W�F�N
public:
	std::wstring		str;

	SimpleText(LPDIRECT3DDEVICE9 i_pD3DDevice){
		try{
			if (FAILED(D3DXCreateFont(i_pD3DDevice,				/* �f�o�C�X */
							10,									/* �����̍��� */
							0,									/* ������ */
							FW_NORMAL,							/* �t�H���g�̑��� */
							1,									/* MIPMAP�̃��x�� */
							FALSE,								/* �C�^���b�N���H */
							DEFAULT_CHARSET,					/* �����Z�b�g */
							OUT_DEFAULT_PRECIS,					/* �o�͐��x */
							DEFAULT_QUALITY,					/* �o�͕i�� */
							DEFAULT_PITCH | FF_SWISS,			/* �t�H���g�s�b�`�ƃt�@�~�� */
							L"�l�r �o�S�V�b�N",					/* �t�H���g�� */
							&m_lpFont))) {						/* Direct3D�t�H���g�ւ̃|�C���^�ւ̃A�h���X */
				//char		strBuf[2048]={0};
				//sprintf_s(strBuf,sizeof(strBuf), "�t�H���g�����Ɏ��s\n �ꏊ : \"%s(%d) Func:%s\" \n�����܂����H",__FILE__,__LINE__,__FUNCTION__);
			throw DxException(
				L"�e�N�X�g�쐬�Ɏ��s���܂����B",
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