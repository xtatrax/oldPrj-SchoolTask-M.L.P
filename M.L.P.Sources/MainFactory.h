/**************************************************************************
 MainFactory.h

 class Light : public Object; �錾
 class DirectionalLight : public Light; �錾
 class Camera : public Object; �錾
 class LookDownCamera : public Camera; �錾
 class Guide : public Object; �錾
 class Shadow: public Object; �錾

                                                    2012/04/17�@�����̖��O
****************************************************************************/
#pragma once

#include "StdAfx.h"
namespace wiz{

/**************************************************************************
 class Light : public Object;
 �p�r: ���C�g�N���X
****************************************************************************/
class Light : public Object{
/**************************************************************************
 void Clear();
 �p�r: �I�u�W�F�N�g�̃N���A
 �߂�l: �Ȃ�
***************************************************************************/
    void Clear();
protected:
    D3DLIGHT9   m_Light;
/**************************************************************************
 Light(LPDIRECT3DDEVICE9 pD3DDevice);
 �p�r: �v���e�N�g�R���X�g���N�^
 �߂�l: �Ȃ�
 ����: ���ڍ\�z�ł��Ȃ��悤�ɁA�v���e�N�g�ɂ���
***************************************************************************/
    Light(LPDIRECT3DDEVICE9 pD3DDevice);
/**************************************************************************
 ~virtual ~Light();
 �p�r: �v���e�N�g�f�X�g���N�^�i���z�f�X�g���N�^�j
 �߂�l: �Ȃ�
***************************************************************************/
    virtual ~Light();
public:
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
        const CONTROLER_STATE* pCntlState,Command& Com);

};

/**************************************************************************
 class DirectionalLight : public Light;
 �p�r: �f�B���N�V���i�����C�g�N���X
****************************************************************************/
class DirectionalLight : public Light{
	D3DXVECTOR3 m_Direction;
public:
/**************************************************************************
 DirectionalLight(
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
    DirectionalLight(LPDIRECT3DDEVICE9 pD3DDevice,
        D3DCOLORVALUE Diffuse,
        D3DCOLORVALUE Specular,
        D3DCOLORVALUE Ambient,
        D3DXVECTOR3 Direction);
/**************************************************************************
 virtual ~DirectionalLight();
 �p�r: �f�X�g���N�^�i���z�f�X�g���N�^�j
 �߂�l: �Ȃ�
***************************************************************************/
    virtual ~DirectionalLight();
/**************************************************************************
 D3DXVECTOR3 getDirection();
 �p�r: ���̕����𓾂�
 �߂�l: ���̕���
***************************************************************************/
	D3DXVECTOR3 getDirection(){
		return m_Direction;
	}
};


/**************************************************************************
 class Camera : public Object;
 �p�r: �J�����N���X
****************************************************************************/
class Camera : public Object{
protected:
    D3DXMATRIX  m_View;     // �J�����̔z�u
    D3DXMATRIX  m_Proj;		// �ˉe�s��
    D3DXVECTOR3 m_Eye;      //�J�����̈ʒu
    D3DXVECTOR3 m_At;       //�����_
    FLOAT m_Near;           //�ˉe�̎�O���̋���
    FLOAT m_Far;            //�ˉe�̉����̋���
    FLOAT m_FovY;           //�ˉe�p�x

    D3DXVECTOR3 m_Arm;       //���_�ƒ����_�̊ԁi�r�j�̃x�N�g��
	FLOAT m_TotalAngleXZ;	//�J������XZ��]�̃��W�A���l
	FLOAT m_TotalAngleY;	//�J������Y��]�̃��W�A���l

public:
/**************************************************************************
 Camera(
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
 Camera(D3DXVECTOR3& At,FLOAT PosZFromAt,FLOAT PosYFromAt,
    FLOAT Near,FLOAT Far,FLOAT FovY);
/**************************************************************************
Camera(
    D3DXVECTOR3& Eye,    //�J�����̈ʒu
    D3DXVECTOR3& At,    //�����_
    FLOAT Near,         //�ˉe�̎�O���̋���
    FLOAT Far,          //�ˉe�̉����̋���
    FLOAT FovY          //Y���ˉe�p�x
    );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	Camera(D3DXVECTOR3& Eye,D3DXVECTOR3& At,
		FLOAT Near,FLOAT Far,FLOAT FovY);

/**************************************************************************
 virtual ~Camera();
 �p�r: ���z�f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
    virtual ~Camera();
/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState   //�R���g���[���̃X�e�[�^�X
	Command& Com					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �J������ݒu
 �߂�l: �Ȃ��B
***************************************************************************/
    virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
        vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com);
/**************************************************************************
 void getPos(
 D3DXVECTOR3& Eye,	//�J�����̈ʒu
 D3DXVECTOR3& At	//�����_
 );
 �p�r: �J�����̌��݂̈ʒu�ƒ����_�𓾂�
 �߂�l: �Ȃ��BEye��AT�ɒl����
***************************************************************************/
	void getPos(D3DXVECTOR3& Eye,D3DXVECTOR3& At){
		Eye = m_Eye;
		At = m_At;
	}
/**************************************************************************
 void getMatrix(
 D3DXMATRIX& View,	//�r���[�s��
 D3DXMATRIX& Proj	//�ˉe�s��
 );
 �p�r: �J�����̃r���[�s��Ǝˉe�s��𓾂�
 �߂�l: �Ȃ��BView��Proj�ɒl����
***************************************************************************/
	void getMatrix(D3DXMATRIX& View,D3DXMATRIX& Proj){
		View = m_View;
		Proj = m_Proj;
	}
/**************************************************************************
 FLOAT getFar();
 �p�r: �J������Far�ʒu�𓾂�
 �߂�l: Far�ʒu
***************************************************************************/
	FLOAT getFar(){
		return m_Far;
	}
};

/**************************************************************************
 class LookDownCamera : public Camera;
 �p�r: �^�ォ�猩��J�����N���X
****************************************************************************/
class LookDownCamera : public Camera{
public:
/**************************************************************************
LookDownCamera(
    D3DXVECTOR3& Eye,    //�J�����̈ʒu
    D3DXVECTOR3& At,    //�����_
    FLOAT Near,         //�ˉe�̎�O���̋���
    FLOAT Far,          //�ˉe�̉����̋���
    FLOAT FovY          //Y���ˉe�p�x
    );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	LookDownCamera(D3DXVECTOR3& Eye,D3DXVECTOR3& At,
		FLOAT Near,FLOAT Far,FLOAT FovY);
/**************************************************************************
 virtual ~FixCamera();
 �p�r: ���z�f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	virtual ~LookDownCamera(){}
/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState   //�R���g���[���̃X�e�[�^�X
	Command& Com					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �J������ݒu
 �߂�l: �Ȃ��B
***************************************************************************/
    virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
        vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com);
};




/**************************************************************************
 class Guide : public Object;
 �p�r: �K�C�h�N���X�ix�Ay�Az�����ɐL�т�K�C�h���j
****************************************************************************/
class Guide : public Object{
    IDirect3DVertexBuffer9* m_pVB;
    //�N���X���\����
    //�����ł����g�p���Ȃ��̂ŁA�����Ɏ���
    struct CUSTOMVERTEX
    {
        D3DXVECTOR3 vec;
        DWORD color;
    };

public:
/**************************************************************************
 Guide(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
    );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ��i���s���͗�O��throw�j
***************************************************************************/
    Guide(LPDIRECT3DDEVICE9 pD3DDevice);
/**************************************************************************
 virtual ~Guide();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
    virtual ~Guide();
/**************************************************************************
 virtual void Draw(
    LPDIRECT3DDEVICE9 pD3DDevice    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    vector<Object*>& Vec,            //�I�u�W�F�N�g�̔z��
    const CONTROLER_STATE* pCntlState   //�R���g���[���̃X�e�[�^�X
	Command& Com					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �K�C�h��ݒu�i�R���g���[���ɂ͔������Ȃ��j
 �߂�l: �Ȃ��B
***************************************************************************/
    virtual void Draw(LPDIRECT3DDEVICE9 pD3DDevice,
        vector<Object*>& Vec,const CONTROLER_STATE* pCntlState,Command& Com);
};


/**************************************************************************
 class MainFactory;
 �p�r: ���C���H��N���X
****************************************************************************/
class MainFactory{
public:
/**************************************************************************
 MainFactory(
	LPDIRECT3DDEVICE9 pD3DDevice,	//�f�o�C�X
	vector<Object*>& vec,			//�I�u�W�F�N�g�̔z��
	vector<Texture*>& TexVec		//�e�N�X�`���̔z��
);
 �p�r: �R���X�g���N�^�i�I�u�W�F�N�g��z��ɒǉ�����j
 �߂�l: �Ȃ�
***************************************************************************/
	MainFactory(LPDIRECT3DDEVICE9 pD3DDevice,vector<Object*>& vec,vector<Texture*>& TexVec);
/**************************************************************************
 ~MainFactory();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	~MainFactory();
};


}
//end of namespace wiz.

