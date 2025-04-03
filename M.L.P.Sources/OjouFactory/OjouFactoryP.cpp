/**************************************************************************
OjouFactoryP.cpp

													2012/04/06�@���O 
													2012/06/18  �C�� ���� �O
****************************************************************************/
#include "StdAfx.h"
#include "OjouFactoryP.h"


namespace wiz{
namespace Ojou{

/**************************************************************************
 SupportMultiPlateDown ��`��
****************************************************************************/
/**************************************************************************
 SupportMultiPlateDown::SupportMultiPlateDown(
    LPDIRECT3DDEVICE9 pD3DDevice   //IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
    );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
SupportMultiPlateDown::SupportMultiPlateDown(LPDIRECT3DDEVICE9 pD3DDevice)
:MultiPlate(pD3DDevice)
{}
/**************************************************************************
 void MultiPlate::Clear();
 �p�r:Item�̔j��
 �߂�l: �Ȃ�
***************************************************************************/
void SupportMultiPlateDown::Clear(){
	vector<PlateItem*>::iterator it;
    for(it = m_ItemVec.begin();it != m_ItemVec.end();it++){
        SafeDelete(*it);
    }
    m_ItemVec.clear();
	//*�e�N�X�`���̓����[�X���Ă͂����Ȃ�
}

/**************************************************************************
 SupportMultiPlateDown::~SupportMultiPlateDown();
 �߂�l: �Ȃ�
***************************************************************************/
SupportMultiPlateDown::~SupportMultiPlateDown(){
}
/**************************************************************************
 void SupportMultiPlateDown::AddPlate(
    D3DXVECTOR3 move,				//�ړ�
    D3DXVECTOR3 size,               //�傫��
    D3DXVECTOR3 pos,                //�ŏ��̈ʒu
	D3DXVECTOR3 rot,				//��](�p�x�P��)�B
    D3DCOLORVALUE Diffuse,          //�f�B�t���[�Y�F
    D3DCOLORVALUE Specular,         //�X�y�L�����F
    D3DCOLORVALUE Ambient           //�A���r�G���g�F
	int SupportButtonL				//�\���L�[�̒l
	int SupportButtonR				//�{�^���̒l
	D3DXVECTOR3 m_BasePos;			//�����ʒu
    );
 �p�r: �v���[�g��ǉ�
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
void SupportMultiPlateDown::AddPlate(D3DXVECTOR3 move,D3DXVECTOR3 center,D3DXVECTOR3 pos,
		D3DXVECTOR3 size ,D3DXVECTOR3 turn,D3DXVECTOR3 rot,
		D3DCOLORVALUE Diffuse,D3DCOLORVALUE Specular,D3DCOLORVALUE Ambient,int SupportButtonL,int SupportButtonR){
	try{
		ButtonMoveItem* pItem = new ButtonMoveItem(g_vZero,pos,size,g_vZero,rot,Diffuse,Specular,Ambient,SupportButtonL,SupportButtonR);
		pItem->m_Move = move;
		pItem->m_MeshItem.m_vSize = size;
		pItem->m_MeshItem.m_vPos = pos;
		pItem->m_BasePos = pos;

		pItem->m_SupportButtonL=SupportButtonL;
		pItem->m_SupportButtonR=SupportButtonR;

		D3DXMATRIX mRot;
		D3DXMatrixIdentity(&mRot);
		D3DXMatrixRotationYawPitchRoll(&mRot,
			D3DXToRadian(rot.y),D3DXToRadian(rot.x),D3DXToRadian(rot.z));
   
		m_ItemVec.push_back(pItem);
	}
	catch(...){
		Clear();
		throw;
	}
}


/**************************************************************************
 void SupportMultiPlateDown::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState   //�R���g���[���̃X�e�[�^�X
 );
 �p�r: �����̂�`��
 �߂�l: �Ȃ��B
***************************************************************************/
void SupportMultiPlateDown::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
	  vector<Object*>& Vec,const CONTROLER_STATE* pCntlState , Command& Com){
    //�z�u�I�u�W�F�N�g�̕`��
    vector<PlateItem*>::size_type sz = m_ItemVec.size();
    for(vector<PlateItem*>::size_type i = 0;i < sz;i++){
		ButtonMoveItem* pItem = dynamic_cast<ButtonMoveItem*>(m_ItemVec[i]);

		//CommonMesh�N���X�̃}�e�B���A����ݒ�
		m_MeshItem = m_ItemVec[i]->m_MeshItem;



		//������Ă���ԉ�����
		if(pCntlState[0].state.Gamepad.wButtons & pItem->m_SupportButtonR 
			||pCntlState[0].state.Gamepad.wButtons & pItem->m_SupportButtonL) 
		{
			if(m_ItemVec[i]->m_MeshItem.m_vPos.y >= -0.0000000001f)
				m_ItemVec[i]->m_MeshItem.m_vPos-=pItem->m_Move;
		}

		//������Ă��Ȃ�
		else
		{
			//�����ʒu�ɖ߂�
			if(m_ItemVec[i]->m_MeshItem.m_vPos != pItem->m_BasePos){
				m_ItemVec[i]->m_MeshItem.m_vPos.y += 0.035f;
				if(m_ItemVec[i]->m_MeshItem.m_vPos.y >= pItem->m_BasePos.y)
					m_ItemVec[i]->m_MeshItem.m_vPos = pItem->m_BasePos;
			}
		}
		// �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
		pD3DDevice->SetTransform(D3DTS_WORLD, &m_MeshItem.getMatrix());
		
		//�R�������b�V����Draw()���Ă�
		CommonMesh::Draw(pD3DDevice,Vec,pCntlState,Com);
    }
}

/**************************************************************************
 Groove ��`��
****************************************************************************/
/**************************************************************************
 Groove::Groove(
    LPDIRECT3DDEVICE9 pD3DDevice,   //  : IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
    D3DXVECTOR3		m_vPos;			//	: �`�悷��ʒu(��ʍ����0,0�Ƃ��s�N�Z���P�ʁA�X�N���[�����W�n)
	D3DXVECTOR3		m_vOffsetPos;	//	: �I�t�Z�b�g���W(�`��ʒu��0,0�Ƃ��s�N�Z���P�ʁA�X�N���[�����W�n)
	D3DXVECTOR3		m_vScale;		//	: �L�k�x����
	D3DXVECTOR3		m_vCenter;		//	: �摜�̒��S�Ƃ���ʒu(�摜�̍����0,0�Ƃ��s�N�Z���P�ʁA�X�N���[�����W�n)
	D3DXVECTOR3		m_vRot;			//	: �`�������Ƃ̉�]�x����
	Rect*			m_Rect;			//	: �\������摜�͈̔�
	SpriteItem		m_SpriteItem;		//	: ���W�f�[�^�Ƃ��}�e���A���Ƃ��B�iSpriteItem�ɕύX�\��j
    );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
****************************************************************************/
Groove::Groove(LPDIRECT3DDEVICE9 pD3DDevice, 
		wstring fileName,
		Rect* rect,
		D3DXVECTOR3& vCenter,
		D3DXVECTOR3& vPos,
		D3DXVECTOR3& vOffsetPos,
		D3DXVECTOR3& vScale,
		D3DXVECTOR3& vRot)
		:Sprite(pD3DDevice, fileName, rect, vCenter, vPos, vOffsetPos, vScale, vRot),
		 m_GaugePercent(20.00f),
		 m_BadQt(0)
{
	m_rectGrooveBorder	= g_rectGroove	= *rect;
	m_rectGrooveBorder.top += rect->bottom;
	m_rectGrooveBorder.bottom = m_rectGrooveBorder.top + rect->bottom;
	g_rectGroove.left	= rect->left	+ 16;
	g_rectGroove.right	= rect->right	- 16;
	m_iTextureWideFive  = (g_rectGroove.right - g_rectGroove.left) / 20;
}
/**************************************************************************
  ~Groove::Groove();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Groove::~Groove(){
}
/**************************************************************************
 void GrooveCalculation(float i_Score);
 �p�r: �Q�[�W�����̌v�Z
 �߂�l: �Ȃ�
***************************************************************************/
void Groove::GrooveCalculation(float i_fDistanceRate,JUDGE i_Judge){
	if(i_Judge == GREAT || i_Judge == GOOD ){
		m_GaugePercent += i_fDistanceRate;
	}else{
		if(++m_BadQt >= 3){
			m_GaugePercent -= 5.0f;
			if(m_GaugePercent < 0.0f)
				m_GaugePercent = 0.0f;
			m_BadQt = 0;
		}
	}
	if(m_GaugePercent <= 0){
		m_GaugePercent = 0;
	}
	if(m_GaugePercent >= 100.0f){
		m_GaugePercent = 100.0f;
	}
}

void Groove::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
	vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com)
{
	if(m_pSprite && m_SpriteItem.m_Textuer.getTexture())
	{
		m_pSprite->Begin( D3DXSPRITE_ALPHABLEND );
		{
			m_pSprite->SetTransform( &m_SpriteItem.getMatrix());

			g_rectGroove.right	= (m_iTextureWideFive * (int(m_GaugePercent / 5) +1 ));

			D3DXVECTOR3	vInFramePos  =  D3DXVECTOR3(16.0f,0.0f,0.0f);
			m_pSprite->Draw(m_SpriteItem.m_Textuer.getTexture(), &g_rectGroove,
				&m_SpriteItem.m_vCenter, &vInFramePos, 0xffffffff );

			m_pSprite->Draw(m_SpriteItem.m_Textuer.getTexture(), &m_rectGrooveBorder,
				&m_SpriteItem.m_vCenter, &m_SpriteItem.m_vOffsetPos, 0xffffffff );
		}
		m_pSprite->End();
	}
}


/**************************************************************************
 Score ��`��
****************************************************************************/
/**************************************************************************
 Score::Score(
    LPDIRECT3DDEVICE9 pD3DDevice,   //  : IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
    D3DXVECTOR3		m_vPos;			//	: �`�悷��ʒu(��ʍ����0,0�Ƃ��s�N�Z���P�ʁA�X�N���[�����W�n)
	D3DXVECTOR3		m_vOffsetPos;	//	: �I�t�Z�b�g���W(�`��ʒu��0,0�Ƃ��s�N�Z���P�ʁA�X�N���[�����W�n)
	D3DXVECTOR3		m_vScale;		//	: �L�k�x����
	D3DXVECTOR3		m_vCenter;		//	: �摜�̒��S�Ƃ���ʒu(�摜�̍����0,0�Ƃ��s�N�Z���P�ʁA�X�N���[�����W�n)
	D3DXVECTOR3		m_vRot;			//	: �`�������Ƃ̉�]�x����
	Rect*			m_Rect;			//	: �\������摜�͈̔�
	SpriteItem		m_SpriteItem;		//	: ���W�f�[�^�Ƃ��}�e���A���Ƃ��B�iSpriteItem�ɕύX�\��j
    );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
****************************************************************************/
Score::Score(LPDIRECT3DDEVICE9 pD3DDevice, 
		wstring fileName,
		Rect* rect,
		D3DXVECTOR3& vCenter,
		D3DXVECTOR3& vPos,
		D3DXVECTOR3& vOffsetPos,
		D3DXVECTOR3& vScale,
		D3DXVECTOR3& vRot)
		:Sprite(pD3DDevice, fileName, rect, vCenter, vPos, vOffsetPos, vScale, vRot),
		 g_iScore()
{
}
/**************************************************************************
  ~Score::Score();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Score::~Score(){
}

void Score::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
	vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com)
{
	if(m_pSprite && m_SpriteItem.m_Textuer.getTexture()){
			m_pSprite->Begin( D3DXSPRITE_ALPHABLEND );
			{
				m_pSprite->SetTransform( &m_SpriteItem.getMatrix());

				////	: �X�R�A�̃f�[�^
				//g_iScore	= 20120523 ;	
				
				//	: �����̕`��͈͂̐ݒ�
				for( int i = 0 ; i < 10 ; i++ )
				{
					g_Rect[ i ].left	= i * NUMBERS_WIDTH ;	
					g_Rect[ i ].top		= 0 ;	
					g_Rect[ i ].right	= g_Rect[ i ].left + NUMBERS_WIDTH ;
					g_Rect[ i ].bottom	= NUMBERS_HEIGHT ;
				}

				//	: �X�R�A��`�悷�鏈��	
				num_places	= 8 ;	//����
				place		= 1 ;	
				for( int i = 0 ; i < num_places ; i++ ) {
					number	= g_iScore / place % 10 ;									
					pos	= D3DXVECTOR3( float((num_places-1-i)*NUMBERS_WIDTH), 0.0f, 0.0f );

				m_pSprite->Draw(m_SpriteItem.m_Textuer.getTexture(),&g_Rect[number] /*m_SpriteItem.m_pRect*/,
					&m_SpriteItem.m_vCenter, &pos, 0xffffffff );
				place	*= 10 ;																
				}
			}
			m_pSprite->End();
		}

	
}	

/**************************************************************************
 OjouFactoryP ��`��
****************************************************************************/
/**************************************************************************
 OjouFactoryP::OjouFactoryP(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	vector<Texture*>& TexVec		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
OjouFactoryP::OjouFactoryP(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,
					 vector<Texture*>& TexVec){
	try{

		//���C���̃}�e�B���A
        D3DCOLORVALUE ButtonLineDiffuse	= {0.0f,0.0f,0.0f,1.0f};
        D3DCOLORVALUE ButtonLineSpecular= {0.0f,0.0f,0.0f,0.3f};
        D3DCOLORVALUE ButtonLineAmbient	= {0.0f,0.0f,0.0f,0.3f};

		//�{�^����
		D3DCOLORVALUE ButtonBDiffuse	= {0.0f,0.0f,1.0f,1.0f};
        D3DCOLORVALUE ButtonBSpecular	= {0.0f,0.0f,1.0f,1.0f};
        D3DCOLORVALUE ButtonBAmbient	= {0.0f,0.0f,1.0f,1.0f};

		//�{�^����
		D3DCOLORVALUE ButtonGDiffuse	= {0.0f,1.0f,0.0f,1.0f};
        D3DCOLORVALUE ButtonGSpecular	= {0.0f,1.0f,0.0f,0.0f};
        D3DCOLORVALUE ButtonGAmbient	= {0.0f,1.0f,0.0f,0.0f};

		//�{�^����
		D3DCOLORVALUE ButtonYDiffuse	= {1.0f,1.0f,0.0f,1.0f};
        D3DCOLORVALUE ButtonYSpecular	= {1.0f,1.0f,0.0f,0.0f};
        D3DCOLORVALUE ButtonYAmbient	= {1.0f,1.0f,0.0f,0.0f};

		//�{�^����
		D3DCOLORVALUE ButtonRDiffuse	= {1.0f,0.0f,0.0f,1.0f};
        D3DCOLORVALUE ButtonRSpecular	= {1.0f,0.0f,0.0f,0.0f};
        D3DCOLORVALUE ButtonRAmbient	= {1.0f,0.0f,0.0f,0.0f};
		
		//�X�R�A
		vec.push_back(
			new Score(pD3DDevice,
			L"Media/Texture/play_scoreF.png",
			&Rect(0,0,NUMBERS_WIDTH,NUMBERS_HEIGHT),
			D3DXVECTOR3(0.0f,0.0f,0.0f),
			D3DXVECTOR3(570.0f,5.0f,0.0f),
			D3DXVECTOR3(0.0f,0.0f,0.0f),
			D3DXVECTOR3(1.0f,1.0f,0.0f),
			D3DXVECTOR3(0.0f,0.0f,0.0f)));

		//�O���[���Q�[�W���g
		vec.push_back(
			new Groove(pD3DDevice,
			L"Media/Texture/Play_groove.png",
			&Rect(0,0,352,64),
			D3DXVECTOR3(0.0f,0.0f,0.0f),
			D3DXVECTOR3(2.5f,5.0f,0.0f),
			D3DXVECTOR3(0.0f,0.0f,0.0f),
			D3DXVECTOR3(1.0f,1.0f,0.0f),
			D3DXVECTOR3(0.0f,0.0f,0.0f)));

		////�O���[���Q�[�W�O�g
		//vec.push_back(
		//	new Sprite(pD3DDevice,
		//	L"Media/Texture/Play_groove.png",
		//	&Rect(0,0,325,78),
		//	D3DXVECTOR3(0.0f,0.0f,0.0f),
		//	D3DXVECTOR3(2.50f,5.0f,0.0f),
		//	D3DXVECTOR3(0.0f,0.0f,0.0f),
		//	D3DXVECTOR3(1.0f,1.0f,0.0f),
		//	D3DXVECTOR3(0.0f,0.0f,0.0f)));

		//�X�R�A�v���[�g
		vec.push_back(
			new Sprite(pD3DDevice,
			L"Media/Texture/play_scoreB.png",
			&Rect(0,0,110,40),
			D3DXVECTOR3(0.0f,0.0f,0.0f),
			D3DXVECTOR3(450.0f,5.0f,0.0f),
			D3DXVECTOR3(0.0f,0.0f,0.0f),
			D3DXVECTOR3(1.0f,1.0f,0.0f),
			D3DXVECTOR3(0.0f,0.0f,0.0f)));

		//�m�[�g����������̃��C��
		vec.push_back(
			new Plate(pD3DDevice,
			D3DXVECTOR3(0.0f,0.090f,-2.1f),
			D3DXVECTOR3(1.5f,0.01f,0.2f),
			ButtonLineDiffuse,ButtonLineSpecular,ButtonLineAmbient));

		SupportMultiPlateDown* mp = new SupportMultiPlateDown(pD3DDevice);

		//��
		mp->AddPlate(D3DXVECTOR3(0.0f,0.03f,0.0f),//�����鑬��
					D3DXVECTOR3(0.0f,0.0f,0.0f),
					D3DXVECTOR3(-0.715f,0.09f,-2.4f),//pos
					D3DXVECTOR3(0.3f,0.15f,0.3f),//size
					D3DXVECTOR3(0.0f,0.0f,0.0f),
					D3DXVECTOR3(0.0f,0.0f,0.0f),
					ButtonBDiffuse,ButtonBSpecular,ButtonBAmbient,
					XINPUT_GAMEPAD_DPAD_LEFT,
					XINPUT_GAMEPAD_X);

		//��
		mp->AddPlate(D3DXVECTOR3(0.0f,0.03f,0.0f),
					D3DXVECTOR3(0.0f,0.0f,0.0f),
					D3DXVECTOR3(-0.28f,0.09f,-2.4f),
					D3DXVECTOR3(0.3f,0.15f,0.3f),
					D3DXVECTOR3(0.0f,0.0f,0.0f),
					D3DXVECTOR3(0.0f,0.0f,0.0f),
					ButtonGDiffuse,ButtonGSpecular,ButtonGAmbient,
					XINPUT_GAMEPAD_DPAD_DOWN,
					XINPUT_GAMEPAD_A);

		//��
		mp->AddPlate(D3DXVECTOR3(0.0f,0.03f,0.0f),
					D3DXVECTOR3(0.0f,0.0f,0.0f),
					D3DXVECTOR3(+0.15f,0.09f,-2.4f),
					D3DXVECTOR3(0.3f,0.15f,0.3f),
					D3DXVECTOR3(0.0f,0.0f,0.0f),
					D3DXVECTOR3(0.0f,0.0f,0.0f),
					ButtonYDiffuse,ButtonYSpecular,ButtonYAmbient,
					XINPUT_GAMEPAD_DPAD_UP,
					XINPUT_GAMEPAD_Y);

		//��
		mp->AddPlate(D3DXVECTOR3(0.0f,0.03f,0.0f),
					D3DXVECTOR3(0.0f,0.0f,0.0f),
					D3DXVECTOR3(+0.58f,0.09f,-2.4f),
					D3DXVECTOR3(0.3f,0.15f,0.3f),
					D3DXVECTOR3(0.0f,0.0f,0.0f),
					D3DXVECTOR3(0.0f,0.0f,0.0f),
					ButtonRDiffuse,ButtonRSpecular,ButtonRAmbient,
					XINPUT_GAMEPAD_DPAD_RIGHT,
					XINPUT_GAMEPAD_B);

		vec.push_back(mp);

	}
	catch(...){
		//��throw
		throw;
	}

}
/**************************************************************************
 OjouFactory::~OjouFactory();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
OjouFactoryP::~OjouFactoryP(){
    //�Ȃɂ����Ȃ�
}



}
}