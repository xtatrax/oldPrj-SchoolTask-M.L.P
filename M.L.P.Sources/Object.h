/**************************************************************************
 Object.h

 struct CONTROLER_STATE; �錾
 class XBoxController; �錾�A��`
 struct Command; �錾�A��`
 class Object; �錾�A��`
 class Stage; �錾
 class ShadowVolume; �錾
****************************************************************************/
#pragma once

#include "StdAfx.h"
#include "Texture.h"
#include "Prim2D.h"
namespace wiz{


/**************************************************************************
 struct CONTROLER_STATE;
 �p�r: XBox�R���g���[���[�̃X�e�[�^�X
****************************************************************************/
struct CUSTOM_CONTROLER_STATE
{

    //	: ���l���ύX��[-1,+1]
    float fThumbRX;
    float fThumbRY;
    float fThumbLX;
    float fThumbLY;

	//	: ��t���[���̂ݗL��
	WORD wPressedButtons;
    bool bPressedLeftTrigger;
    bool bPressedRightTrigger;

    //	: �Ō�ɉ����ꂽ�{�^��CONTROLER_STATE
    WORD wLastButtons;
    bool bLastLeftTrigger;
    bool bLastRightTrigger;

};
/**************************************************************************
 struct CONTROLER_STATE;
 �p�r: XBox�R���g���[���[�̃X�e�[�^�X
****************************************************************************/
struct CONTROLER_STATE
{
	CUSTOM_CONTROLER_STATE CustomState;
    XINPUT_STATE state;
    bool   bConnected;
	WPARAM KeyBoardState;
	Point  MousePoint;
};
/**************************************************************************
 class XBoxController;
 �p�r: XBox�R���g���[���[
****************************************************************************/
class XBoxController{
    static const DWORD MAX_CONTROLLERS = 4;
    CONTROLER_STATE m_State[MAX_CONTROLLERS];
public:
	static WPARAM KeyBoardState;
	static Point  MousePoint;
/**************************************************************************
 XBoxController();
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
    XBoxController(){
		::ZeroMemory(m_State,sizeof(CONTROLER_STATE));
	}
/**************************************************************************
 ~XBoxController();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
    ~XBoxController(){}
/**************************************************************************
 const CONTROLER_STATE* GetState();
 �p�r: �R���g���[���[�̏�Ԃ𓾂�
 �߂�l: �R���g���[���[�̃X�e�[�^�X
***************************************************************************/
    const CONTROLER_STATE* GetState(){
        DWORD dwResult;
        for( DWORD i = 0; i < MAX_CONTROLLERS; i++ )
        {
			m_State[i].KeyBoardState = KeyBoardState;
			KeyBoardState = 0;
			m_State[i].MousePoint = MousePoint;
			m_State[i].CustomState.wLastButtons = m_State[i].state.Gamepad.wButtons;

            // XInput���猻�݂̃X�e�[�^�X�𓾂�
            dwResult = XInputGetState( i, &m_State[i].state );

			if( dwResult == ERROR_SUCCESS ){
                m_State[i].bConnected = true;
                //���o�[�̃f�b�h�]�[���̐ݒ�
                if((m_State[i].state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && 
                     m_State[i].state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) && 
                    (m_State[i].state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && 
                     m_State[i].state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) )
                {   
                   m_State[i].state.Gamepad.sThumbLX = 0;
                   m_State[i].state.Gamepad.sThumbLY = 0;
                }

                if( (m_State[i].state.Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && 
                     m_State[i].state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) && 
                    (m_State[i].state.Gamepad.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && 
                    m_State[i].state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) ) 
                {
                   m_State[i].state.Gamepad.sThumbRX = 0;
                   m_State[i].state.Gamepad.sThumbRY = 0;
                }
				m_State[i].CustomState.wPressedButtons = (m_State[i].CustomState.wLastButtons ^ m_State[i].state.Gamepad.wButtons) & m_State[i].state.Gamepad.wButtons;
            }
            else{
                m_State[i].bConnected = false;
            }
        }
        return m_State;
    }
/**************************************************************************
 const DWORD getMaxControllers() const;
 �p�r: �R���g���[���[�̍ő吔�𓾂�
 �߂�l: ���o�[�W�����ł͒萔���Ԃ�i4�j
***************************************************************************/
    const DWORD getMaxControllers() const{
        return MAX_CONTROLLERS;
    }
};



/**************************************************************************
 struct Command;
 �p�r: �V�[�����A�X�e�[�W���ł���肳���R�}���h
 ���R�}���h���e�̒�`�́A�e�R���e���c�ɂ܂�����
****************************************************************************/
struct Command{
	DWORD m_Command;
	DWORD m_Param1;
	DWORD m_Param2;
	DWORD m_Param3;
	Command()
		:m_Command(0),m_Param1(0),m_Param2(0),m_Param3(0)
	{}
	void Clear(){
		m_Command = m_Param1 = m_Param2 = m_Param3 = 0;
	}
	~Command(){
		Clear();
	}
};



/**************************************************************************
 class Object;
 �p�r: �V�[���z�u�I�u�W�F�N�g�̊��N���X�i���ۃN���X�j
****************************************************************************/
class Object{
public:
/**************************************************************************
 Object();
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
    Object(){}
/**************************************************************************
 virtual ~Object();
 �p�r: ���z�f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
    virtual ~Object(){}
/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState,   //�R���g���[���̃X�e�[�^�X
	Command& Com					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �I�u�W�F�N�g��`��i�������z�֐��j
 �߂�l: �Ȃ��B
***************************************************************************/
    virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& Vec,
        const CONTROLER_STATE* pCntlState,Command& Com) = 0;
/**************************************************************************
	virtual void DrawShadowVolume(
    LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	LPD3DXEFFECT	pEffect,			//�G�t�F�N�g�̃|�C���^
	D3DXMATRIX& mCameraView,			//�J�����̃r���[�s��
	D3DXMATRIX& mCameraProj			//�J�����̃v���W�F�N�V�����s��
	);
 �p�r: �e�{�����[����`��i���z�֐��j
 �߂�l: �Ȃ��B
***************************************************************************/
	virtual void DrawShadowVolume(
    LPDIRECT3DDEVICE9 pD3DDevice,
	LPD3DXEFFECT pEffect,
	D3DXMATRIX& mCameraView,
	D3DXMATRIX& mCameraProj){
		//���N���X�ł͉������Ȃ�
	}
};



/**************************************************************************
 class Stage;
 �p�r: �Q�[�����X�e�[�W�P�ʂŊǗ�����N���X
****************************************************************************/
class Stage{
protected:
	//�e�X�e�[�W
	Stage* m_pParStage;
	//�q�X�e�[�W
	Stage* m_pChildStage;
	//�_�C�A���O�X�e�[�W���ǂ���
	bool m_IsDialog;
    //�z�u�I�u�W�F�N�g�̃|�C���^�̃x�N�g��
    vector<Object*> m_Vec;
    //�e�N�X�`���̃|�C���^�̃x�N�g��
    vector<Texture*> m_TextureVec;
/**************************************************************************
 void Clear();
 �p�r:�I�u�W�F�N�g�̔j��
 �߂�l: �Ȃ�
***************************************************************************/
	void Clear();
public:
/**************************************************************************
 Stage();
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	Stage();
/**************************************************************************
 Stage(
 Stage* Par	//�e�X�e�[�W
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	Stage(Stage* Par);
/**************************************************************************
virtual ~Stage();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	virtual ~Stage();
/**************************************************************************
Stage* getPar();
 �p�r: �e�X�e�[�W�𓾂�
 �߂�l: �e�X�e�[�W�̃|�C���^
***************************************************************************/
	const Stage* getPar() const{
		return m_pParStage;
	}
/**************************************************************************
Stage* geChild();
 �p�r: �q�X�e�[�W�𓾂�
 �߂�l: �q�X�e�[�W�̃|�C���^
***************************************************************************/
	Stage* geChild(){
		return m_pChildStage;
	}
/**************************************************************************
Stage* getLastStage();
 �p�r: ��ԍŌ���̎q�X�e�[�W�𓾂�
 �߂�l: ��ԍŌ���̎q�X�e�[�W�̃|�C���^
***************************************************************************/
	Stage* getLastStage(){
		if(m_pChildStage){
			return m_pChildStage->getLastStage();
		}
		else{
			return this;
		}
	}
/**************************************************************************
Stage* getActiveStage();
 �p�r: ���A�A�N�e�B�u�ȃX�e�[�W�𓾂�
 �߂�l: �A�N�e�B�u�ȃX�e�[�W�̃|�C���^
 ���Ō���̎q���_�C�A���O�^�C�v�������ꍇ
 �@���̃_�C�A���O��ێ�����X�e�[�W�𓾂�
***************************************************************************/
	Stage* getActiveStage(){
		Stage* ret = getLastStage();
		while(ret->m_IsDialog){
			ret = ret->m_pParStage;
		}
		return ret;
	}
/**************************************************************************
 void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    const CONTROLER_STATE* pCntlState   //�R���g���[���[�̃X�e�[�^�X
	Command& Com					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �V�[����`��
 �߂�l: �Ȃ��B
***************************************************************************/
    virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,const CONTROLER_STATE* pCntlState,
				Command& Com);
};


/**************************************************************************
 class ShadowVolume;
 �p�r: �V���h�E�{�����[���N���X
 ��DXUT�T���v�����x�[�X�ɍ쐬
****************************************************************************/
class ShadowVolume{
	/**************************************************************************
	 struct SHADOWVERT;
	 �p�r: �e��FVF�f�[�^
	 ��DXUT�����p
	****************************************************************************/
	struct SHADOWVERT
	{
		D3DXVECTOR3 Position;
		D3DXVECTOR3 Normal;
		const static D3DVERTEXELEMENT9 Decl[3];
	};
	/**************************************************************************
	 struct CEdgeMapping;
	 �p�r: �G�b�W�}�b�s���O�N���X
	 ��DXUT�����p
	****************************************************************************/
	struct CEdgeMapping
	{
		int m_anOldEdge[2];  // vertex index of the original edge
		int m_aanNewEdge[2][2]; // vertex indexes of the new edge
		// First subscript = index of the new edge
		// Second subscript = index of the vertex for the edge
	public:
			CEdgeMapping()
			{
				FillMemory( m_anOldEdge, sizeof( m_anOldEdge ), -1 );
				FillMemory( m_aanNewEdge, sizeof( m_aanNewEdge ), -1 );
			}
	};
	const FLOAT ADJACENCY_EPSILON;
	LPD3DXMESH m_pShadowVolumeMesh;
	IDirect3DVertexDeclaration9*    m_pShadowDecl;
	/**************************************************************************
	 int FindEdgeInMappingTable()�֐�
	 �p�r: �G�b�W�}�b�s���O�֐�
	 ��DXUT�����p
	****************************************************************************/
	//--------------------------------------------------------------------------------------
	// Takes an array of CEdgeMapping objects, then returns an index for the edge in the
	// table if such entry exists, or returns an index at which a new entry for the edge
	// can be written.
	// nV1 and nV2 are the vertex indexes for the old edge.
	// nCount is the number of elements in the array.
	// The function returns -1 if an available entry cannot be found.  In reality,
	// this should never happens as we should have allocated enough memory.
	int FindEdgeInMappingTable( int nV1, int nV2, CEdgeMapping* pMapping, int nCount )
	{
		for( int i = 0; i < nCount; ++i )
		{
			// If both vertex indexes of the old edge in mapping entry are -1, then
			// we have searched every valid entry without finding a match.  Return
			// this index as a newly created entry.
			if( ( pMapping[i].m_anOldEdge[0] == -1 && pMapping[i].m_anOldEdge[1] == -1 ) ||

				// Or if we find a match, return the index.
				( pMapping[i].m_anOldEdge[1] == nV1 && pMapping[i].m_anOldEdge[0] == nV2 ) )
			{
				return i;
			}
		}

		return -1;  // We should never reach this line
	}
/**************************************************************************
 void Clear();
 �p�r:�I�u�W�F�N�g�̔j��
 �߂�l: �Ȃ�
***************************************************************************/
	void Clear();
public:
/**************************************************************************
 ShadowVolume(
 LPDIRECT3DDEVICE9 pd3dDevice,	//�f�o�C�X
 LPD3DXMESH pMesh			//���ƂȂ郁�b�V��
 );
 �p�r: �R���X�g���N�^�i�V���h�E�{�����[�����쐬����j
 �߂�l: �Ȃ�
***************************************************************************/
	ShadowVolume(LPDIRECT3DDEVICE9 pd3dDevice, LPD3DXMESH pMesh);
/**************************************************************************
 ~ShadowVolume();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	~ShadowVolume();
/**************************************************************************
 void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	LPD3DXEFFECT	pEffect			//�G�t�F�N�g�ւ̃|�C���^
 );
 �p�r: �e�{�����[����`��
 �߂�l: �Ȃ��B
***************************************************************************/
    void Draw(LPDIRECT3DDEVICE9 pD3DDevice,LPD3DXEFFECT pEffect);
};


}
//end of namespace wiz.

