/**************************************************************************
 Stages.cpp

                                                    2012/04/20�@�����̖��O
****************************************************************************/
#include "StdAfx.h"
#include "Scene.h"
#include "Stage_MusicSelect.h"
#include "KoromoebFactory/KoromoebFactory.h"
#include "OujiFactory/OujiFactory2.h"

namespace wiz{






/**************************************************************************
 MusicSelect ��`��
****************************************************************************/
/**************************************************************************
MusicSelect::MusicSelect(
LPDIRECT3DDEVICE9 pD3DDevice	//�f�o�C�X
);
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
MusicSelect::MusicSelect(LPDIRECT3DDEVICE9 pD3DDevice)
:MenuStage(pD3DDevice){
	try{
		//wiz::Koromoeb::KoromoebFactoryMS(pD3DDevice,m_Vec,m_TextureVec);

		wiz::Ouji::OujiFactory2(pD3DDevice,m_Vec,m_TextureVec);
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
