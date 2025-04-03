/**************************************************************************
 NoteObjects.h

 class NoteObjects : public Plate �錾
                                                    2012/03/04�@���O ���� �O
****************************************************************************/
#pragma once
#include "../MultiPlate.h"

namespace wiz{
/**************************************************************************
 class NoteObjects : public Plate;
 �p�r: �����̒����̃N���X�i�R���g���[���œ��삵�Ȃ��j
****************************************************************************/
class NoteObjects : public Plate{
protected:
	struct NoteItem {
		bool m_bDead;				//	: ���S�t���O
		bool m_bInputReception;		//	: ���͎�t
		bool m_bBoot;				//	:
		bool m_bLastBoot;			//	:
		BYTE		m_SoundNum;		//	: �Đ����鉹���ԍ�
		D3DXVECTOR3	m_vPos;			//	: ���W�f�[�^
		D3DXVECTOR3	m_vScale;		//	: �傫��
		enum {
			ZERO,
			Single,
			LongBegin,
			LongEnd,
		};
		BYTE m_byStatus;
		NoteItem(D3DXVECTOR3& pos,D3DXVECTOR3& scale,BYTE SoundNum)
			:m_vPos(pos),m_vScale(scale),m_SoundNum(SoundNum),
			m_bDead(false),m_bInputReception(true),m_bBoot(false),m_bLastBoot(false)
		{
		}
	};
	vector<NoteItem*> m_ItemVec;
	static float m_fNotationLength;	//	: 60BPM�̍� 1�b��1���߂�����鑬��
	static float m_fHighSpeed;	//	: 
	static float m_fDeadLineZ;	//	: 

	MeshItem	 m_BassItem;	//	: �x�[�X�ƂȂ���W�f�[�^��}�e���A���Ȃ�
	D3DXMATRIX	 m_Matrix;		//	: 
	enum __STATUS{
		Live,					//	: �`�撆
		Dead					//	: �f�[�^�j��
	};
	//BYTE Status;
	typedef vector<NoteItem*>::size_type NoteItemSizeType;
/**************************************************************************
 bool FrameUpdate4SingleNote(
 );
 �p�r: �P������Ԃ̉����̍X�V
 �߂�l: �Ȃ��B
***************************************************************************/
    bool FrameUpdate4SingleNote(NoteItem* pTargetItem,float i_fMoveDis);
/**************************************************************************
 void FrameUpdate4LongNote(
 );
 �p�r: �P������Ԃ̉����̍X�V
 �߂�l: �Ȃ��B
***************************************************************************/
    void FrameUpdate4LongNote(NoteItem* pTargetItem,float i_fMoveDis,float i_fJudgePosZ);
public:
	void Clear();
/**************************************************************************
 NoteObjects(
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
    NoteObjects(LPDIRECT3DDEVICE9 pD3DDevice,
		D3DXVECTOR3 i_vPos,D3DXVECTOR3 i_vSize,
		D3DCOLORVALUE i_Diffuse,D3DCOLORVALUE i_Specular,D3DCOLORVALUE i_Ambient,
		float HiSpeed,
		LPDIRECT3DTEXTURE9 pTexture = 0
		);
/**************************************************************************
 virtual ~NoteObjects();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
    virtual ~NoteObjects();
/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState   //�R���g���[���̃X�e�[�^�X
 );
 �p�r: �����̂�`��
 �߂�l: �Ȃ��B
***************************************************************************/
    virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
        vector<Object*>& Vec,const CONTROLER_STATE* pCntlState , Command& Com);
/**************************************************************************
 void AddNote(BYTE i_SoundNum);
 �p�r: �m�[�g�ǉ�
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
    void AddNote(BYTE i_SoundNum,BYTE i_StatusNum);

//////////
//	: �Z�b�^�[
/**************************************************************************
 void setLastStatus(BYTE i_StatusNum );
 �p�r: �m�[�g�̏�Ԃ�ݒ�
 �߂�l: �Ȃ�
***************************************************************************/
	void setLastStatus(BYTE i_StatusNum){
		m_ItemVec.back()->m_byStatus = i_StatusNum;
	}
/**************************************************************************
 void setFirstBoot();
 �p�r: 
 �߂�l: �Ȃ�
***************************************************************************/
	void setFirstBoot(){
		m_ItemVec[0]->m_bBoot = true;
	}
/**************************************************************************
	void setFirstDead();
 �p�r: ���S�t���O���r���r���ɂ���
 �߂�l: ����
***************************************************************************/
	void setFirstDead(){
		m_ItemVec[0]->m_bDead = true;
	}
/**************************************************************************
	void setFirstDead();
 �p�r: �x�[�X�̑���
 �߂�l: ����
***************************************************************************/
	static void setLineLength(float i_Speed){
		m_fNotationLength = i_Speed;
	}
/**************************************************************************
	void setHiSpeed();
 �p�r: �x�[�X�̑���
 �߂�l: ����
***************************************************************************/
	static void setHiSpeed(float i_Speed){
		m_fHighSpeed = i_Speed;
	}

//////////
//	: �Q�b�^�[
/**************************************************************************
 void getFirstBoot();
 �p�r: 
 �߂�l: �Ȃ�
***************************************************************************/
	const bool getFirstBootFlag(){
		return m_ItemVec[0]->m_bLastBoot;
	}
/**************************************************************************
 const D3DXVECTOR3& setFirstPos();
 �p�r: ��ԍŏ��̃A�C�e���̍��W���l��
 �߂�l: ���W
***************************************************************************/
	const D3DXVECTOR3& getFirstPos(){
		return m_ItemVec[0]->m_vPos;
	}
/**************************************************************************
 const D3DXVECTOR3& setFirstSize();
 �p�r:
 �߂�l: ���W
***************************************************************************/
	const D3DXVECTOR3& setFirstSize(){
		return m_ItemVec[0]->m_vScale;
	}
/**************************************************************************
 BYTE getFirstStatus( );
 �p�r: �m�[�g�̏�Ԃ��l��
 �߂�l: �Ȃ�
***************************************************************************/
	const BYTE getFirstStatus(){
		return m_ItemVec[0]->m_byStatus;
	}
/**************************************************************************
 const OBB getFirstObb();
 �p�r: ��ԍŏ��̃A�C�e����OBB��Ԃ�
 �߂�l: �擪�A�C�e����OBB
***************************************************************************/
	const vector<NoteItem*>::size_type getSize(){
		return m_ItemVec.size();
	}
/**************************************************************************
 const BYTE getFirstSoundNum();
 �p�r: ��ԍŏ��̃A�C�e���̃T�E���h�ԍ��𓾂�
 �߂�l: �擪�A�C�e���̃T�E���h�ԍ�
***************************************************************************/
	const BYTE getFirstSoundNum(){
		if(m_ItemVec.empty())
			return 0;
		return m_ItemVec[0]->m_SoundNum;
	}
/**************************************************************************
 const bool getFirstDeadORLive();
 �p�r:   ��ԍŏ��̃A�C�e���̎��S�t���O�m�F
 �߂�l: ����ł� = true / �����Ă� = false
***************************************************************************/
	const bool getFirstDeadFlag(){
		return m_ItemVec[0]->m_bDead;
	}
};
}