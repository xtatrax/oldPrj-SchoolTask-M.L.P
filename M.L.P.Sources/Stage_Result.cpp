/**************************************************************************
 Stages.cpp

                                                    2012/04/20�@�����̖��O
****************************************************************************/
#include "StdAfx.h"
#include "Scene.h"
//#include "MainFactory.h"
//#include "MyFactory.h"
#include "OtaconFactory/OtaconFactory.h"
#include "Stage_Result.h"
#include "Shadow.h"

namespace wiz{
/**************************************************************************
 ResultMenu ��`��
****************************************************************************/
/**************************************************************************
ResultMenu::ResultMenu(
LPDIRECT3DDEVICE9 pD3DDevice	//�f�o�C�X
);
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
ResultMenu::ResultMenu(LPDIRECT3DDEVICE9 pD3DDevice,int Score,ResultFactor& rankFactor)
:MenuStage(pD3DDevice){
	try{
		
		Otacon::ResultFactory(pD3DDevice,m_Vec,m_TextureVec,Score,rankFactor);

	}
	catch(...){
		//�{�^���z��̃N���A����
		//�|�C���^�͔j�����Ȃ�
		m_ButtonVec.clear();
		//�I�u�W�F�N�g�̃N���A
		//�����Ń|�C���^���j�������
		Clear();
		//��throw
		throw;
	}
}


}
//end of namespace wiz.
