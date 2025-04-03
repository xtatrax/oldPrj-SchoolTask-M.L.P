/**************************************************************************
 MainFactory.cpp

 class Light : public Object; ��`
 class DirectionalLight : public Light ��`
 class Camera : public Object; ��`
 class LookDownCamera : public Camera; ��`
 class Guide : public Object; ��`
 class Shadow: public Object; ��`
 class MainFactory
                                                    2012/04/17�@�����̖��O
****************************************************************************/
#include "StdAfx.h"
#include "MainFactory.h"
#include "Sprite.h"


namespace wiz{

/**************************************************************************
 Light ��`��
****************************************************************************/
/**************************************************************************
 Light::Light(LPDIRECT3DDEVICE9 pD3DDevice);
 �p�r: �v���e�N�g�R���X�g���N�^
 �߂�l: �Ȃ�
 ����: ���ڍ\�z�ł��Ȃ��悤�ɁA�v���e�N�g�ɂ���
***************************************************************************/
Light::Light(LPDIRECT3DDEVICE9 pD3DDevice){
	try{
		// D3DLIGHT9�\���̂�0�ŃN���A����
		::ZeroMemory(&m_Light, sizeof(D3DLIGHT9));
	}
	catch(...){
		//�ăX���[
		throw;
	}
}
/**************************************************************************
 virtual Light::~Light();
 �p�r: �v���e�N�g�f�X�g���N�^�i���z�f�X�g���N�^�j
 �߂�l: �Ȃ�
***************************************************************************/
Light::~Light(){
//�������Ȃ�
}

/**************************************************************************
 void Light::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState   //�R���g���[���̃X�e�[�^�X
	Command& Com					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �I�u�W�F�N�g��`��i�������z�֐��j
 �߂�l: �Ȃ��B
***************************************************************************/
void Light::Draw(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& Vec,
							const CONTROLER_STATE* pCntlState,Command& Com){
//�������Ȃ�
}

/**************************************************************************
 DirectionalLight ��`��
****************************************************************************/
/**************************************************************************
 DirectionalLight::DirectionalLight(
    LPDIRECT3DDEVICE9 pD3DDevice,   //�f�o�C�X
    D3DCOLORVALUE Diffuse,          //�f�B�t���[�Y�F
    D3DCOLORVALUE Specular,         //�X�y�L�����F
    D3DCOLORVALUE Ambient,          //�A���r�G���g�F
    D3DXVECTOR3 Direction           //���[���h��ԂŌ����w������
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
 ����: �f�B���N�V���i�����C�g���\�z����
***************************************************************************/
DirectionalLight::DirectionalLight(LPDIRECT3DDEVICE9 pD3DDevice,
    D3DCOLORVALUE Diffuse,
    D3DCOLORVALUE Specular,
    D3DCOLORVALUE Ambient,
    D3DXVECTOR3 Direction)
    :Light(pD3DDevice),m_Direction(0,0,0)
{
    m_Light.Type       = D3DLIGHT_DIRECTIONAL;
    m_Light.Diffuse = Diffuse;
    m_Light.Specular = Specular;
    m_Light.Ambient = Ambient;
    D3DXVec3Normalize((D3DXVECTOR3*)&m_Light.Direction, &Direction);
	m_Direction = m_Light.Direction;
    // ���C�g�������_�����O�p�C�v���C���ɐݒ�
    pD3DDevice->SetLight( 0, &m_Light );
    // ���C�g��L���ɂ���
    pD3DDevice->LightEnable( 0, TRUE );
}
/**************************************************************************
 virtual DirectionalLight::~DirectionalLight();
 �p�r: �f�X�g���N�^�i���z�f�X�g���N�^�j
 �߂�l: �Ȃ�
***************************************************************************/
DirectionalLight::~DirectionalLight(){
//�������Ȃ�
}
/**************************************************************************
 Camera ��`��
****************************************************************************/
/**************************************************************************
 Camera::Camera(
    D3DXVECTOR3& At,    //�����_
	FLOAT AbsPosZFromAt,//�����_���猩���A�J�����ʒu��Z�̈ʒu(��Βl�w��)
	FLOAT PosYFromAt,	//�����_���猩���A�J�����ʒu��Y�̈ʒu
    FLOAT Near,         //�ˉe�̎�O���̋���
    FLOAT Far,          //�ˉe�̉����̋���
    FLOAT FovY          //Y���ˉe�p�x
    );
 �p�r: �R���X�g���N�^
 ���J�����ʒu�̏����l�͒��ڂ͎w��ł��Ȃ��B
 �������_����݂āAZ�̎�O�Ɉ������Έʒu��Y�̑��Έʒu���w�肷��BX��0�ɌŒ�
 ��Z�̎�O�Ɉ������Έʒu�iAbsPosZFromAt�j�͐�Βl�������̂ŁA
	�}�C�i�X���w�肵�Ă��Ӗ����Ȃ��B
 �߂�l: �Ȃ�
***************************************************************************/
Camera::Camera(D3DXVECTOR3& At,FLOAT AbsPosZFromAt,FLOAT PosYFromAt,
    FLOAT Near,FLOAT Far,FLOAT FovY)
:Object(),m_Eye(),m_At(At),m_Near(Near),m_Far(Far),m_FovY(FovY)
{
	//�J�����ʒu�̊m��
	m_Eye.x = m_At.x;
	m_Eye.y = m_At.y + PosYFromAt;
	m_Eye.z = m_At.z - fabs(AbsPosZFromAt);
	//�J�����r���[�̍쐬
    D3DXMatrixIdentity(&m_View);
    D3DXMatrixLookAtLH(&m_View,&m_Eye,&m_At,
            &D3DXVECTOR3( 0.0f, 1.0f, 0.0f));
	//�J�����ƒ����_�Ƃ̊ԁiArm�j���O�쐬
    m_Arm = m_At - m_Eye;
	D3DXVECTOR3 m;
	//���K��
	D3DXVec3Normalize(&m,&m_Arm);
	m_TotalAngleXZ = 0;
	//���K�����ꂽY�̒l���獂���̃��W�A���𓾂�
	FLOAT a_c,a_s;
	a_c = acos(m.z);
	a_s = asin(m.y);
	if(a_s < 0.0f){
		m_TotalAngleY = a_c;
	}
	else{
		m_TotalAngleY = D3DX_PI + D3DX_PI - a_c;
	}

}

/**************************************************************************
Camera::Camera(
    D3DXVECTOR3& Eye,    //�J�����̈ʒu
    D3DXVECTOR3& At,    //�����_
    FLOAT Near,         //�ˉe�̎�O���̋���
    FLOAT Far,          //�ˉe�̉����̋���
    FLOAT FovY          //Y���ˉe�p�x
    );
 �p�r: Fix�J�����̎��Ɏg�p����R���X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Camera::Camera(D3DXVECTOR3& Eye,D3DXVECTOR3& At,
	 FLOAT Near,FLOAT Far,FLOAT FovY)
	 :m_View(),m_Proj(),m_Eye(Eye),m_At(At),m_Near(Near),m_Far(Far),m_FovY(FovY)
{
    m_Arm = m_At - m_Eye;
	//Fix�J�����̎��Ɏg�p����R���X�g���N�^�Ȃ̂�
	//�J�����ω��͂Ȃ��Ă��ǂ�
	m_TotalAngleXZ = 0;
	m_TotalAngleY = 0;
}


/**************************************************************************
 Camera::~Camera();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Camera::~Camera(){
}
/**************************************************************************
 void Camera::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    const CONTROLER_STATE* pCntlState   //�R���g���[���[�̃X�e�[�^�X
 );
 �p�r: �J������ݒu
 �߂�l: �Ȃ��B
***************************************************************************/
/**************************************************************************
 void Camera::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState   //�R���g���[���̃X�e�[�^�X
	Command& Com					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �J������ݒu
 �߂�l: �Ȃ��B
***************************************************************************/
void Camera::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
    vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com){
    // �r���[�|�[�g�̎擾
    D3DVIEWPORT9 vp;
    if(FAILED(pD3DDevice->GetViewport(&vp))){
        //���s���s
		//WinMain��Catch�܂Ŕ��
        throw DxException(
            L"�r���[�|�[�g�̎擾�Ɏ��s���܂����B",
            L"Camera::Draw()"
            );
	}
	m_Eye = m_At - m_Arm;
    D3DXMatrixIdentity(&m_View);
    D3DXMatrixLookAtLH(&m_View,&m_Eye,&m_At,
            &D3DXVECTOR3( 0.0f, 1.0f, 0.0f));
    // �A�X�y�N�g��̌v�Z
    float aspect;
    aspect = (float)vp.Width / (float)vp.Height;
    // �ˉe�s��̏�����
    D3DXMatrixIdentity(&m_Proj);
    D3DXMatrixPerspectiveFovLH(&m_Proj, D3DXToRadian(m_FovY), aspect,m_Near,m_Far);
    // �ˉe�s��̐ݒ�
    pD3DDevice->SetTransform(D3DTS_PROJECTION,&m_Proj);
    // �J�����̐ݒ�
    pD3DDevice->SetTransform(D3DTS_VIEW,&m_View);
#ifdef	___MLP_DEBUG_CAMERAPOSDRAW_
	Debugger::DBGSTR::addStr(
		L"�J������� : �ʒu | X= %5.1f Y= %5.1f Z= %5.1f \n"
		L"�@�@�@�@�@�@ ���_ | X= %5.1f Y= %5.1f Z= %5.1f \n"
		L"�@�@�@�@�@�@ �ˉe | �O %5.1f �� %5.1f �p %3.2f \n"
		L"�@�@�@�@������Vec | X= %5.1f Y= %5.1f Z= %5.1f \n"
		L"�@�@�@�@�@�@ ��] | XZ %5.1f y= %5.1f\n",
		m_Eye.x,m_Eye.y,m_Eye.z,
		m_At.x,m_At.y,m_At.z,   
		m_Near,m_Far,m_FovY,
		m_Arm.x,m_Arm.y,m_Arm.z,  
		m_TotalAngleXZ,m_TotalAngleY);
#endif
}


/**************************************************************************
 LookDownCamera ��`��
****************************************************************************/
/**************************************************************************
LookDownCamera::LookDownCamera(
    D3DXVECTOR3& Eye,    //�J�����̈ʒu
    D3DXVECTOR3& At,    //�����_
    FLOAT Near,         //�ˉe�̎�O���̋���
    FLOAT Far,          //�ˉe�̉����̋���
    FLOAT FovY          //Y���ˉe�p�x
    );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
LookDownCamera::LookDownCamera(D3DXVECTOR3& Eye,D3DXVECTOR3& At,
	 FLOAT Near,FLOAT Far,FLOAT FovY)
	 :Camera(Eye,At,Near,Far,FovY)
{
}
/**************************************************************************
 virtual void LookDownCamera::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState   //�R���g���[���̃X�e�[�^�X
	Command& Com					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �J������ݒu
 �߂�l: �Ȃ��B
***************************************************************************/
void LookDownCamera::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
					 vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com){
    // �r���[�|�[�g�̎擾
    D3DVIEWPORT9 vp;
    if(FAILED(pD3DDevice->GetViewport(&vp))){
        //���s���s
		//WinMain��Catch�܂Ŕ��
        throw DxException(
            L"�r���[�|�[�g�̎擾�Ɏ��s���܂����B",
            L"Camera::Draw()"
            );
    }
    D3DXMatrixIdentity(&m_View);
		D3DXMatrixLookAtLH(&m_View,&m_Eye,&m_At,
				&D3DXVECTOR3( 0.0f, 0.0f, 1.0f));
    // �A�X�y�N�g��̌v�Z
    float aspect;
    aspect = (float)vp.Width / (float)vp.Height;
    // �ˉe�s��̏�����
    D3DXMatrixIdentity(&m_Proj);
    D3DXMatrixPerspectiveFovLH(&m_Proj, D3DXToRadian(m_FovY), aspect,m_Near,m_Far);
    // �ˉe�s��̐ݒ�
    pD3DDevice->SetTransform(D3DTS_PROJECTION,&m_Proj);
    // �J�����̐ݒ�
    pD3DDevice->SetTransform(D3DTS_VIEW,&m_View);
#ifdef	___MLP_DEBUG_CAMERAPOSDRAW_
	Debugger::DBGSTR::addStr(
		L"�J������� : �ʒu | X= %5.1f Y= %5.1f Z= %5.1f \n"
		L"�@�@�@�@�@�@ ���_ | X= %5.1f Y= %5.1f Z= %5.1f \n"
		L"�@�@�@�@�@�@ �ˉe | �O %5.1f �� %5.1f �p %3.2f \n"
		L"�@�@�@�@������Vec | X= %5.1f Y= %5.1f Z= %5.1f \n"
		L"�@�@�@�@�@�@ ��] | XZ %5.1f y= %5.1f\n",
		m_Eye.x,m_Eye.y,m_Eye.z,
		m_At.x,m_At.y,m_At.z,   
		m_Near,m_Far,m_FovY,
		m_Arm.x,m_Arm.y,m_Arm.z,  
		m_TotalAngleXZ,m_TotalAngleY);
#endif
}

/**************************************************************************
 class Guide ��`��
****************************************************************************/
/**************************************************************************
 Guide::Guide(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
    );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
Guide::Guide(LPDIRECT3DDEVICE9 pD3DDevice)
    :Object(),m_pVB(0)
{
    try{
        CUSTOMVERTEX Vertices[] = 
        {
            {D3DXVECTOR3(-1000.0,0.0,0.0),D3DCOLOR_ARGB(0xff,0xff,0,0)},
            {D3DXVECTOR3(1000.0,0.0,0.0),D3DCOLOR_ARGB(0xff,0xff,0,0)},
            {D3DXVECTOR3(0.0,-1000.0,0.0),D3DCOLOR_ARGB(0xff,0,0xff,0)},
            {D3DXVECTOR3(0.0,1000.0,0.0),D3DCOLOR_ARGB(0xff,0,0xff,0)},
            {D3DXVECTOR3(0.0,0.0,-1000.0),D3DCOLOR_ARGB(0xff,0,0,0xff)},
            {D3DXVECTOR3(0.0,0.0,1000.0),D3DCOLOR_ARGB(0xff,0,0,0xff)}
        };
        if(FAILED(pD3DDevice->CreateVertexBuffer( 6 * sizeof( CUSTOMVERTEX ),
                                    0,D3DFVF_XYZ|D3DFVF_DIFFUSE,
                                    D3DPOOL_DEFAULT, &m_pVB, NULL)))
        {
            // ���������s
            throw DxException(
                L"���_�o�b�t�@�̍쐬�Ɏ��s���܂����B",
                L"Guide::Guide()"
                );
        }
        //�o�b�t�@�����b�N
        VOID* pVertices;
        if(FAILED( m_pVB->Lock( 0, sizeof(Vertices),( void** )&pVertices, 0 ))){
            // ���������s
            throw DxException(
                L"���_�o�b�t�@�̃��b�N�Ɏ��s���܂����B",
                L"Guide::Guide()"
                );
        }
        //���_�f�[�^���璸�_�o�b�t�@�ɓ]��
        memcpy( pVertices,Vertices, sizeof(Vertices) );
        //���_�o�b�t�@���A�����b�N
        m_pVB->Unlock();
    }
    catch(...){
        //�R���X�g���N�^��O����
        //��n��
        SafeRelease(m_pVB);
        //�ăX���[
        throw;
    }
}
/**************************************************************************
 Guide::~Guide();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Guide::~Guide(){
    SafeRelease(m_pVB);
}
/**************************************************************************
 void Guide::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState   //�R���g���[���̃X�e�[�^�X
	Command& Com					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �K�C�h��ݒu�i�R���g���[���ɂ͔������Ȃ��j
 �߂�l: �Ȃ��B
***************************************************************************/
void Guide::Draw(LPDIRECT3DDEVICE9 pD3DDevice,
    vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com){
    D3DXMATRIX  wm;
    //���W�ϊ�����
    D3DXMatrixIdentity(&wm);
    // �}�g���b�N�X�������_�����O�p�C�v���C���ɐݒ�
    pD3DDevice->SetTransform(D3DTS_WORLD, &wm);
    pD3DDevice->SetStreamSource( 0, m_pVB, 0, sizeof( CUSTOMVERTEX ) );
    pD3DDevice->SetFVF(D3DFVF_XYZ|D3DFVF_DIFFUSE);
    pD3DDevice->SetRenderState( D3DRS_LIGHTING,FALSE);
    pD3DDevice->LightEnable( 0, FALSE );
    pD3DDevice->DrawPrimitive(D3DPT_LINELIST, 0, 3);
    pD3DDevice->SetRenderState( D3DRS_LIGHTING,TRUE);
    pD3DDevice->LightEnable( 0, TRUE );
}

/**************************************************************************
 MainFactory ��`��
****************************************************************************/
/**************************************************************************
 MainFactory::MainFactory(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	vector<Texture*>& TexVec		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�T���v���I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
MainFactory::MainFactory(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,
					 vector<Texture*>& TexVec){
	try{
        // ���C�e�B���O���[�h
        pD3DDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
        //���C�g�̃C���X�^���X������
        D3DCOLORVALUE Diffuse = {1.0f,1.0f,1.0f,0.0f};
        D3DCOLORVALUE Specular = {1.0f,1.0f,1.0f,0.0f};
        D3DCOLORVALUE Ambient = {0.5f,0.5f,0.5f,0.0f};
        vec.push_back(new DirectionalLight(pD3DDevice,Diffuse,Specular,Ambient,
                    D3DXVECTOR3( -0.0f, -1.0f, 0.0f)));
        //�J�����̃C���X�^���X������
        vec.push_back(
			new Camera(D3DXVECTOR3( 0.0f, 0.0f, 5.0f),D3DXVECTOR3( 0.0f, 0.0f, 0.0f),
				    1.0f, 100.0f,30.0f));
        //�K�C�h�̃C���X�^���X������
        vec.push_back(new Guide(pD3DDevice));



	}
	catch(...){
		//��throw
		throw;
	}

}
/**************************************************************************
 MainFactory::~MainFactory();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
MainFactory::~MainFactory(){
    //�Ȃɂ����Ȃ�
}


}
//end of namespace wiz.
