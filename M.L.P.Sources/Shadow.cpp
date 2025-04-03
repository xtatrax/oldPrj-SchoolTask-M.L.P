/**************************************************************************
 MainFactory.cpp

 class Light : public Object; ��`
 class DirectionalLight : public Light ��`
 class Camera : public Object; ��`
 class LookDownCamera : public Camera; ��`
 class Guide : public Object; ��`
 class Shadow: public Object; ��`

                                                    2012/04/17�@�����̖��O
****************************************************************************/
#include "StdAfx.h"
#include "MainFactory.h"
#include "Shadow.h"
//#include "Camera.h"

namespace wiz{


/**************************************************************************
 Shadow ��`��
****************************************************************************/
/**************************************************************************
 void Clear();
 �p�r:�I�u�W�F�N�g�̔j��
 �߂�l: �Ȃ�
***************************************************************************/
void Shadow::Clear(){
    SafeRelease(m_pBigVB);
    SafeRelease(m_pEffect);
}
/**************************************************************************
 Shadow::Shadow(
 LPDIRECT3DDEVICE9 pD3DDevice	//�f�o�C�X
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Shadow::Shadow(LPDIRECT3DDEVICE9 pD3DDevice)
:m_pBigVB(0),m_pEffect(0),
m_hRenderShadow(0),m_hShowShadow(0),m_hRenderShadowVolumeComplexity(0)
{
	try{
        IDirect3DSurface9* pBackBuffer;
		if(FAILED(pD3DDevice->GetBackBuffer( 0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer ))){
			// ���������s
			throw DxException(
				L"�o�b�N�o�b�t�@�̎擾�Ɏ��s���܂����B",
				L"Shadow::Shadow()"
				);
		}
		D3DSURFACE_DESC desc;
        ZeroMemory(&desc, sizeof( D3DSURFACE_DESC ) );
		pBackBuffer->GetDesc(&desc);
		SafeRelease( pBackBuffer );


	    DWORD dwShaderFlags = D3DXFX_NOT_CLONEABLE;
#if defined( DEBUG ) || defined( _DEBUG )
		dwShaderFlags |= D3DXSHADER_DEBUG;
#endif
#ifdef DEBUG_VS
		dwShaderFlags |= D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT;
#endif
#ifdef DEBUG_PS
		dwShaderFlags |= D3DXSHADER_FORCE_PS_SOFTWARE_NOOPT;
#endif
//***************************************************************************
//���\�[�X���������B
		if(FAILED(D3DXCreateEffectFromFile(pD3DDevice,L"ShadowVolume.fx", NULL, NULL, 
			dwShaderFlags, NULL, &m_pEffect, NULL ))){
//***************************************************************************
			// ���������s
			throw DxException(
				L"�G�t�F�N�g�̍쐬�Ɏ��s���܂����B",
				L"Shadow::Shadow()"
				);
		}
		D3DCAPS9 Caps;
		pD3DDevice->GetDeviceCaps( &Caps );
		m_hRenderShadowVolumeComplexity 
			= m_pEffect->GetTechniqueByName( "RenderShadowVolumeComplexity" );
		// If 2-sided stencil is supported, use it.
		if( Caps.StencilCaps & D3DSTENCILCAPS_TWOSIDED )
		{
			m_hRenderShadow = m_pEffect->GetTechniqueByName( "RenderShadowVolume2Sided" );
			m_hShowShadow = m_pEffect->GetTechniqueByName( "ShowShadowVolume2Sided" );
		}
		else
		{
			m_hRenderShadow = m_pEffect->GetTechniqueByName( "RenderShadowVolume" );
			m_hShowShadow = m_pEffect->GetTechniqueByName( "ShowShadowVolume" );
		}
		if(!m_hRenderShadowVolumeComplexity 
			|| !m_hRenderShadow 
			|| !m_hShowShadow){
			// ���������s
			throw DxException(
				L"�G�t�F�N�g�n���h���̓ǂݍ��݂Ɏ��s���܂����B",
				L"Shadow::Shadow()"
				);
		}
		if( FAILED( pD3DDevice->CreateVertexBuffer(
                                     4*sizeof(BigSquareVertex),
                                     D3DUSAGE_WRITEONLY,
                                     BigSquareFVF,
                                     D3DPOOL_MANAGED,
									 &m_pBigVB, NULL ) ) ){
			// ���������s
			throw DxException(
				L"���_�o�b�t�@�̍쐬�Ɏ��s���܂����B",
				L"Shadow::Shadow()"
				);
		}

		BigSquareVertex* v;
		m_pBigVB->Lock( 0, 0, (void**)&v, 0 );
		v[0].p = D3DXVECTOR4(  0, (FLOAT)desc.Height, 0.0f, 1.0f );
		v[1].p = D3DXVECTOR4(  0,  0, 0.0f, 1.0f );
		v[2].p = D3DXVECTOR4( (FLOAT)desc.Width, (FLOAT)desc.Height, 0.0f, 1.0f );
		v[3].p = D3DXVECTOR4( (FLOAT)desc.Width,  0, 0.0f, 1.0f );
		v[0].color = D3DCOLOR_RGBA(0,0,0,0x7f);
		v[1].color = D3DCOLOR_RGBA(0,0,0,0x7f);
		v[2].color = D3DCOLOR_RGBA(0,0,0,0x7f);
		v[3].color = D3DCOLOR_RGBA(0,0,0,0x7f);
		m_pBigVB->Unlock();
	}
	catch(...){
        //��n��
        Clear();
		//��throw
		throw;
	}
}

/**************************************************************************
 Shadow::~Shadow();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Shadow::~Shadow(){
    Clear();
}

/**************************************************************************
 virtual void Shadow::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState   //�R���g���[���̃X�e�[�^�X
	Command& Com					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �e��`��
 �߂�l: �Ȃ��B
***************************************************************************/
void Shadow::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
				  vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com){
	Camera* pCamera = 0;
	DirectionalLight* pLight = 0;
	//�܂��J�����ƃ��C�g��T��
	vector<Object*>::size_type sz = Vec.size();
	for(vector<Object*>::size_type i = 0;i < sz;i++){
		const type_info& info = typeid(*(Vec[i]));
		if(info == typeid(DirectionalLight)){
			pLight = dynamic_cast<DirectionalLight*>(Vec[i]);
		}
		if(info == typeid(Camera) || info == typeid(LookDownCamera)){
			pCamera = dynamic_cast<Camera*>(Vec[i]);
		}
		if(pLight && pCamera){
			break;
		}
	}
	if(pCamera && pLight && m_pEffect){
		D3DXMATRIX mCameraView;
		D3DXMATRIX mCameraProj;
		//�J�����̍s����擾
		pCamera->getMatrix(mCameraView,mCameraProj);
		//���C�g�̃x�N�g�����擾
		D3DXVECTOR3 lightbaseVec = pLight->getDirection();
		//���C�g���t������
		lightbaseVec *= -1.0f;
		//10�{�ɑ��₷�i���������C�g�̈ʒu�j
		lightbaseVec *= 20.0f;
		//�o�^�p�Ɍ^�ϊ�
		D3DXVECTOR4 vLight(lightbaseVec.x,lightbaseVec.y,lightbaseVec.z,1.0f );
		//���C�g���J�������W�ɕς���
        D3DXVec4Transform( &vLight, &vLight, &mCameraView );
		// �r���[�|�[�g�̎擾
		D3DVIEWPORT9 vp;
		if(FAILED(pD3DDevice->GetViewport(&vp))){
			//���s���s
			//WinMain��Catch�܂Ŕ��
			throw DxException(
				L"�r���[�|�[�g�̎擾�Ɏ��s���܂����B",
				L"Shadow::Draw()"
				);
		}
		// �A�X�y�N�g��̌v�Z
		float aspect;
		aspect = (float)vp.Width / (float)vp.Height;
		// ���C�g�̎ˉe�s��̏�����
		//Z��Far�N���b�v
		m_pEffect->SetFloat( "g_fFarClip", pCamera->getFar() - 0.1f );
		//�G�t�F�N�g�̎ˉe�s���o�^
		m_pEffect->SetMatrix( "g_mProj", &mCameraProj);
		//���C�g�̈ʒu��o�^
		m_pEffect->SetVector( "g_vLightView", &vLight);
		//���C�g�̐F��o�^
		D3DXVECTOR4 mColor(0.8f,0.8f,0.8f,0.4f);
		m_pEffect->SetVector( "g_vLightColor", &mColor);
		//���C�g�̉e�F��o�^
		D3DXVECTOR4 mShadowColor(0.5f,0.0f,0.0f,0.3f);
        m_pEffect->SetVector( "g_vShadowColor", &mShadowColor );
		//�e�N�j�b�N��o�^
		//�e�������̂悤�ɕ\������ꍇ
		m_pEffect->SetTechnique(m_hRenderShadow);
		//�e�̗����\������ꍇ�i�f�o�b�O�p�j
		//	m_pEffect->SetTechnique(m_hShowShadow);
		//�e�{�����[����\������ꍇ�i�f�o�b�O�p�j
		//	m_pEffect->SetTechnique(m_hRenderShadowVolumeComplexity);
		//���ꂼ��̉e�`��֐����Ă�
		vector<Object*>::size_type sz = Vec.size();
		for(vector<Object*>::size_type i = 0;i < sz;i++){
			Vec[i]->DrawShadowVolume(pD3DDevice,m_pEffect,mCameraView,mCameraProj);
		}
		//������Ō�̃X�e�b�v
		// �[�x�e�X�g�͂��Ȃ�
		pD3DDevice->SetRenderState( D3DRS_ZENABLE,          FALSE );
		// �X�e���V���e�X�g�͂���
		pD3DDevice->SetRenderState( D3DRS_STENCILENABLE,  TRUE );
		// �A���t�@�u�����f�B���O�͐��`�Ɋ|����
		pD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
		pD3DDevice->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA );
		pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
		// �|���S����`�悷��Ƃ��ɂ́A�e�N�X�`���ƒ��_�F�̗���������
		pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
		pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
		pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
		pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );
		pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE );
		// �X�e���V���o�b�t�@�̒l���P�ȏ�̂Ƃ��ɏ�������
		pD3DDevice->SetRenderState( D3DRS_STENCILREF,  0x1 );
		pD3DDevice->SetRenderState( D3DRS_STENCILFUNC, D3DCMP_LESSEQUAL );
		pD3DDevice->SetRenderState( D3DRS_STENCILPASS, D3DSTENCILOP_KEEP );
		//�}�X�L���O���ʂ̕\��		         
		pD3DDevice->SetFVF( BigSquareFVF );
		pD3DDevice->SetStreamSource( 0, m_pBigVB, 0, sizeof(BigSquareVertex));
		pD3DDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );
		// ��Ԃ����ɖ߂�
		pD3DDevice->SetRenderState( D3DRS_ZENABLE,          TRUE );
		pD3DDevice->SetRenderState( D3DRS_STENCILENABLE,  FALSE );
		pD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );
	}
}


}
//end of namespace wiz.
