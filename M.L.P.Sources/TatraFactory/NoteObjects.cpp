/**************************************************************************
 Plate.cpp

 Plate; ��`
                                                    2012/03/04�@���O 
****************************************************************************/
#include "StdAfx.h"
#include "NoteObjects.h"
#include "../Stage_Play.h"
#include "../OjouFactory/OjouFactoryP.h"

namespace wiz{
/**************************************************************************
 NoteObjects ��`��
***************************************************************************/
float NoteObjects::m_fNotationLength = 1.0f;
float NoteObjects::m_fHighSpeed = 1.0f;
float NoteObjects::m_fDeadLineZ = -1.75f;
/**************************************************************************
 void MultiPlate::Clear();
 �p�r:Item�̔j��
 �߂�l: �Ȃ�
***************************************************************************/
void NoteObjects::Clear(){
	//StdVecSafeDelete(m_ItemVec);
	vector<NoteItem*>::iterator it;
    for(it = m_ItemVec.begin();it != m_ItemVec.end();it++){
        SafeDelete(*it);
    }
    m_ItemVec.clear();
	//*�e�N�X�`���̓����[�X���Ă͂����Ȃ�
}

/**************************************************************************
 NoteObjects::NoteObjects(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
	D3DXVECTOR3 i_vPos,				//	: �o���ʒu
	D3DXVECTOR3 i_vSize,			//	: �傫��
	D3DCOLORVALUE Diffuse,			//	: 
	D3DCOLORVALUE Specular,			//	:
	D3DCOLORVALUE Ambient,			//	: 
	LPDIRECT3DTEXTURE9 pTexture = 0	//�e�N�X�`���𒣂�Ƃ��͎w��
    );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
NoteObjects::NoteObjects(LPDIRECT3DDEVICE9 pD3DDevice,
		D3DXVECTOR3 i_vPos,
		D3DXVECTOR3 i_vSize,
		D3DCOLORVALUE i_Diffuse,
		D3DCOLORVALUE i_Specular,
		D3DCOLORVALUE i_Ambient,
		float HiSpeed,
		LPDIRECT3DTEXTURE9 pTexture
		)
	:Plate(pD3DDevice,i_vPos,g_vOne,i_Diffuse,i_Specular,i_Ambient,pTexture),
	 m_BassItem(g_vZero,i_vPos,i_vSize,g_vZero,g_vZero,i_Diffuse,i_Specular,i_Ambient)
{
    try{
		m_fHighSpeed = HiSpeed;
		m_MeshItem = m_BassItem;
    }
    catch(...){
        //�R���X�g���N�^��O����
        //�ăX���[
        throw;
    }
}
/**************************************************************************
 virtual ~NoteObjects();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
NoteObjects::~NoteObjects(){
	//Clear();
}
/**************************************************************************
 bool NoteObjects::FrameUpdate4SingleNote(
 );
 �p�r: �P������Ԃ̉����̍X�V
 �߂�l: �Ȃ��B
***************************************************************************/
bool NoteObjects::FrameUpdate4SingleNote(NoteItem* pTargetItem,float i_fMoveDis){

	pTargetItem->m_vPos.z -= i_fMoveDis;
	//	: ���S�t���O
	if( pTargetItem->m_vPos.z < m_fDeadLineZ ){
		pTargetItem->m_bDead = true;
		return true;
	}
	return false;
}

/**************************************************************************
 void NoteObjects::FrameUpdate4LongNote(
 );
 �p�r: ��������Ԃ̉����̍X�V
 �߂�l: �Ȃ��B
***************************************************************************/
void NoteObjects::FrameUpdate4LongNote(NoteItem* pTargetItem,float i_fMoveDis,float i_fJudgePosZ){

	if(pTargetItem->m_byStatus == NoteItem::LongBegin){
		pTargetItem->m_vPos.z -= i_fMoveDis / 2;
		pTargetItem->m_vScale.z += i_fMoveDis;
	}else{
		pTargetItem->m_vPos.z -= i_fMoveDis;
	}
	float fWkDis;	//	���C������͂ݏo��������
	if( (pTargetItem->m_bBoot && 
		(fWkDis = pTargetItem->m_vPos.z - (pTargetItem->m_vScale.z / 2) - i_fJudgePosZ ) <= 0 ) ||
		(fWkDis = pTargetItem->m_vPos.z - (pTargetItem->m_vScale.z / 2) - m_fDeadLineZ ) <= 0 )
		{
		pTargetItem->m_vPos.z += abs(fWkDis) / 2;
		if((pTargetItem->m_vScale.z -= abs(fWkDis)) <=0.0f){
			pTargetItem->m_bDead = true;
		}
		pTargetItem->m_bLastBoot = pTargetItem->m_bBoot;
		pTargetItem->m_bBoot = false;
	}
}


/**************************************************************************
 virtual void NoteObjects::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState   //�R���g���[���̃X�e�[�^�X
 );
 �p�r: �����̂�`��
 �߂�l: �Ȃ��B
***************************************************************************/
void NoteObjects::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
	  vector<Object*>& Vec,const CONTROLER_STATE* pCntlState , Command& Com){

	//�z�u�I�u�W�F�N�g�̕`��
	PlayCommandPacket*		pPCPacket = NULL;
	Ojou::Groove*			pGroove   = NULL;
	//	: �ꏬ�߂�
	if(Com.m_Command == PlayStage::SENDITEM){
		pPCPacket = (PlayCommandPacket*)Com.m_Param1;
		pGroove   = (Ojou::Groove*)Com.m_Param2;
	}
    NoteItemSizeType sz = m_ItemVec.size();
    for(NoteItemSizeType i = 0;i < sz;i++){
		//	: �������f
		//	: �`�悷�邩
		//	: �������邩
		NoteItem* pTargetItem = m_ItemVec[i];
		if(pTargetItem->m_bDead){

			SafeDelete(pTargetItem);
			m_ItemVec.erase(m_ItemVec.begin() + i--);
			sz = m_ItemVec.size();
		}
		else{
			//	: �ړ������̌v�Z
			float MoveDis = ((m_fNotationLength / (pPCPacket->m_fMeasureChangeDelay * 2 )) * Tempus::getOneFrameTime() );

			//	: �������@�̔��f
			if(pTargetItem->m_byStatus == NoteItem::Single){
				//	: �P���̎�
				if(FrameUpdate4SingleNote(pTargetItem,MoveDis)){
					pPCPacket->m_pJudgeSprite->setJudge(POOR);
					pPCPacket->m_pRankFactor->m_dwPoorQt++;
					pGroove->GrooveCalculation(0.0f,POOR);
				}
			}
			else{
				//	: �����̎�
				FrameUpdate4LongNote(pTargetItem,MoveDis,pPCPacket->m_fJudgePosZ);
			}

			D3DXMATRIX mPos;
			D3DXMatrixTranslation( &mPos , pTargetItem->m_vPos.x , pTargetItem->m_vPos.y ,pTargetItem->m_vPos.z );

			D3DXMATRIX mScale;
			D3DXMatrixScaling( &mScale,pTargetItem->m_vScale.x,pTargetItem->m_vScale.y,pTargetItem->m_vScale.z);
			m_Matrix = mScale * mPos;
			//�e�N�X�`��������ꍇ
			if(m_pTexture){
				DWORD wkdword;
				//���݂̃e�N�X�`���X�e�[�^�X�𓾂�
				pD3DDevice->GetTextureStageState(0,D3DTSS_COLOROP,&wkdword);
				//�X�e�[�W�̐ݒ�
				pD3DDevice->SetTexture(0,m_pTexture);
				//�f�t�B�[�Y�F�ƃe�N�X�`�����|�����킹��ݒ�
				pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE4X );
				pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
				pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );

				pD3DDevice->SetFVF(PlateFVF);
				// �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
				pD3DDevice->SetTransform(D3DTS_WORLD, &m_Matrix);
				//�R�������b�V����Draw()���Ă�
				CommonMesh::Draw(pD3DDevice,Vec,pCntlState,Com);
				pD3DDevice->SetTexture(0,0);
				//�X�e�[�W�����ɖ߂�
				pD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,wkdword);
			}
			else{
			//�e�N�X�`�����Ȃ��ꍇ
				// �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
				pD3DDevice->SetTransform(D3DTS_WORLD, &m_Matrix);
				//�R�������b�V����Draw()���Ă�
				CommonMesh::Draw(pD3DDevice,Vec,pCntlState,Com);
			}
#if defined(DEBUG) || defined(_DEBUG)
			Debugger::DBGSTR::addStr(L"�X�e�[�^�X = %d / SoundNum = %d\n" , m_ItemVec[i]->m_byStatus,m_ItemVec[i]->m_SoundNum);
#endif
		}

		//*/
    }
}
/**************************************************************************
 void NoteObjects::AddNote();
 �p�r: �m�[�g��ǉ�
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
void NoteObjects::AddNote(BYTE i_SoundNum,BYTE i_StatusNum){
	try{
		NoteItem* pItem = new NoteItem(
			m_BassItem.m_vPos,
			m_BassItem.m_vSize,
			i_SoundNum);
		pItem->m_bDead = false;
		pItem->m_byStatus  = i_SoundNum;
		m_ItemVec.push_back(pItem);
	}
	catch(...){
		Clear();
		throw;
	}
}

}