/**************************************************************************
 DxDevice.cpp

 class DxDevice ��`
****************************************************************************/
#include "StdAfx.h"
#include "DxDevice.h"
#include "Scene.h"
#include "TatraFactory/DebugFunks.h"
namespace wiz{
/**************************************************************************
 DxDevice ��`��
***************************************************************************/
/**************************************************************************
 void DxDevice::Clear();
 �p�r: �I�u�W�F�N�g�̃N���A
 �߂�l: �Ȃ�
***************************************************************************/
void DxDevice::Clear(){
    //�R���g���[���[�̊J��
    SafeDelete(m_pController);
    // �f�o�C�X�I�u�W�F�N�g�̉��
    SafeRelease(m_pD3DDevice);
    // DirectXGraphics�̉��
    SafeRelease(m_pD3D);
}
/**************************************************************************
 DxDevice::DxDevice(
    HWND hWnd,          //�E�C���h�E�̃n���h��
    bool isFullScreen,  //�t���X�N���[�����ǂ���
    int Width,          //�̈�̕�
    int Height          //�̈�̍���
);
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��B���s�������O��throw
***************************************************************************/
DxDevice::DxDevice(HWND hWnd,bool isFullScreen,int Width,int Height)
 : m_pD3D(0), m_pD3DDevice(0),m_pController(0)
{
    try{
        D3DDISPLAYMODE d3ddm;
        // Direct3D9�I�u�W�F�N�g�̍쐬
        if((m_pD3D = ::Direct3DCreate9(D3D_SDK_VERSION)) == 0){
            throw DxException(
                L"DirectX�̏������Ɏ��s���܂����BDirectX�C���^�[�t�F�C�X���擾�ł��܂���B",
                L"DxDevice::DxDevice()"
                );
        }
        
        // ���݂̃f�B�X�v���C���[�h���擾
        if(FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm))) {
            throw DxException(
                L"�f�o�C�X�̏������Ɏ��s���܂����B�f�B�X�v���C���[�h���擾�ł��܂���B",
                L"DxDevice::DxDevice()"
                );
        }

        // �f�o�C�X�̃v���[���e�[�V�����p�����[�^��������
        ZeroMemory(&m_D3DPP, sizeof(D3DPRESENT_PARAMETERS));
        m_D3DPP.BackBufferCount         = 1;
        if(isFullScreen) { // �t���X�N���[���̏ꍇ
            m_D3DPP.Windowed                = FALSE;            // �t���X�N���[���\���̎w��
            m_D3DPP.BackBufferWidth         = Width;            // �t���X�N���[�����̉���
            m_D3DPP.BackBufferHeight        = Height;           // �t���X�N���[�����̏c��
        }
        else {
            m_D3DPP.Windowed                = TRUE;             // �E�C���h�E���\���̎w��
        }
        m_D3DPP.BackBufferFormat        = d3ddm.Format;         // �J���[���[�h�̎w��
        m_D3DPP.SwapEffect              = D3DSWAPEFFECT_DISCARD; 
        m_D3DPP.EnableAutoDepthStencil  = TRUE;
        m_D3DPP.AutoDepthStencilFormat  = D3DFMT_D24S8;
        
        // �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
        // �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
        if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
                                        D3DDEVTYPE_HAL, 
                                        hWnd, 
                                        D3DCREATE_HARDWARE_VERTEXPROCESSING, 
                                        &m_D3DPP, &m_pD3DDevice))) {
            // ��L�̐ݒ肪���s������
            // �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
            if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
                                            D3DDEVTYPE_HAL, 
                                            hWnd, 
                                            D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
                                            &m_D3DPP, &m_pD3DDevice))) {
                // ��L�̐ݒ肪���s������
                // �`��ƒ��_������CPU�ōs�Ȃ�
                if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
                                                D3DDEVTYPE_REF, hWnd, 
                                                D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
                                                &m_D3DPP, &m_pD3DDevice))) {
                    // ���������s
                    throw DxException(
                        L"�f�o�C�X�̏������Ɏ��s���܂����B�I�m�ȃf�o�C�X���擾�ł��܂���B",
                        L"DxDevice::DxDevice()"
                        );
                }
            }
        }

        m_pController = new XBoxController;
#if defined(DEBUG) || defined(_DEBUG)
		//	: �f�o�b�O�p������`��֐��̏�����
		wiz::Debugger::DBGSTR::Init(m_pD3DDevice);
#endif
	}
    catch(...){
        //�j������
        Clear();
        //�ăX���[
        throw;
    }
}
/**************************************************************************
 DxDevice::~DxDevice();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
DxDevice::~DxDevice(){
    //�I�u�W�F�N�g�̔j��
    Clear();
}
/**************************************************************************
 void DxDevice::RenderScene(
 Scene* pScene  // �V�[���ւ̃|�C���^
 );
 �p�r: �V�[���̕`��
 �߂�l: �Ȃ�
***************************************************************************/
void DxDevice::RenderScene(Scene* pScene)
{
    try{
        if(!pScene){
            //�V�[���������Ȃ�X���[
            throw DxException(
                L"�V�[����������܂���B",
                L"DxDevice::RenderScene()"
                );
        }
        const CONTROLER_STATE* pCntlState;
        if(m_pController){
            pCntlState = m_pController->GetState();
        }
        // �r���[�|�[�g�Ɛ[�x�o�b�t�@�̏������ƃX�e���V���o�b�t�@�̃N���A
        if(FAILED(m_pD3DDevice->Clear(0,NULL,               // ����������̈�͑S��
                        D3DCLEAR_STENCIL |                  // �X�e���V���o�b�t�@���w��
                        D3DCLEAR_TARGET |                   // �o�b�N�o�b�t�@���w��
                        D3DCLEAR_ZBUFFER,                   // �[�x�o�b�t�@�iZ�o�b�t�@�j���w��
                        D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f),  // ����������F
                        1.0f,                               // ����������[�x�o�b�t�@�iZ�o�b�t�@�j�̒l
                        0))){                               // ����������X�e���V���o�b�t�@�̒l
            //���s������X���[
            throw DxException(
                L"�o�b�t�@���N���A�ł��܂���B",
                L"DxDevice::RenderScene()"
                );
        }
        // �`��J�n�錾
        if(SUCCEEDED(m_pD3DDevice->BeginScene())) {
            // ���f���Ȃǂ̕`��
            pScene->Draw(m_pD3DDevice,pCntlState);
#if defined(DEBUG) || defined(_DEBUG)
			//	: �f�o�b�O�p������̕`��
			wiz::Debugger::DBGSTR::Draw();
#endif
            // �`��I���錾
            m_pD3DDevice->EndScene();
        }
        // �`�挋�ʂ̓]��
        if(FAILED(m_pD3DDevice->Present( 0, 0, 0, 0 ))) {
            // �f�o�C�X�������畜�A
            if(m_pD3DDevice->Reset(&m_D3DPP)!= D3D_OK){
                //�f�o�C�X�̕��A�Ɏ��s������X���[
                throw DxException(
                    L"�f�o�C�X�𕜋A�ł��܂���B",
                    L"DxDevice::RenderScene()"
                    );
            }
        }
        //�^�C�~���O�����킹��
		//::Sleep(10);
    }
    catch(...){
        //�j������
        Clear();
        //�ăX���[
        throw;
    }
}

/**************************************************************************
 LPDIRECT3DDEVICE9 DxDevice::getDevice();
 �p�r: �f�o�C�X�̎擾
 �߂�l: IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^�B���s������0
***************************************************************************/
LPDIRECT3DDEVICE9 DxDevice::getDevice(){
    return m_pD3DDevice;
}
}
//end of namespace wiz.

