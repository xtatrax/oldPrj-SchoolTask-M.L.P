/**************************************************************************
 MeshItem.h

 MeshItem ; �錾
                                                    2012/03/04�@���O ���� �O
****************************************************************************/
#pragma once

#include "../StdAfx.h"
#include "../Texture.h"

namespace wiz{ 
/**************************************************************************
 class MeshItem;
 �p�r: ���W�n����}�e���A���Ȃǂ����b�s���O����N���X
****************************************************************************/
class MeshItem{
private:
	// :���ؗp
	
public:
	// :���O
	wstring	m_MeshItemName;
	
	// :�e�N�X�`��/0�`1
	//LPDIRECT3DTEXTURE9		m_pTextuer;

	// :���P�[�g�p�̃N�I�[�^�j�I��
    D3DXQUATERNION	m_RotQt;
	
	// :�^�[���p�̃N�I�[�^�j�I��
    D3DXQUATERNION	m_TurnQt;
	
	// :���̏�̒��S�Ƃ���ʒu
	D3DXVECTOR3		m_vCenter;
	
	// :�I�u�W�F�N�g�̈ʒu
	D3DXVECTOR3		m_vPos;
	
	// :�T�C�Y
	D3DXVECTOR3		m_vSize;

	// :�}�e���A��
	D3DMATERIAL9	m_pMaterial;

public:
/**************************************************************************
 MeshItem(MeshItem& pMeshItem);
 �p�r: �R�s�[�R���X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	MeshItem(MeshItem& pMeshItem);
/**************************************************************************
 MeshItem::MeshItem(
		wstring name,				//	: �I�u�W�F�̖��O
		D3DXVECTOR3& center,		//	: ���S�ƂȂ�ʒu (�I���W�i���[���̂���̃I�t�Z�b�g���W)
		D3DXVECTOR3& pos,			//	: �`��ʒu
		D3DXVECTOR3& size ,			//	: �傫���̔�
		D3DXVECTOR3& turn,			//	: �^�[��	(���])
		D3DXVECTOR3& rot			//	: ���P�[�g	(���])
		D3DCOLORVALUE& Diffuse,		//	: ���쒆�̃f�B�t���[�Y�F
		D3DCOLORVALUE& Specular,	//	: ���쒆�̃X�y�L�����F
		D3DCOLORVALUE& Ambient,		//	: ���쒆�̃A���r�G���g�F
);							   
 �p�r: �R���X�g���N�^(�F�t)
 �߂�l: �Ȃ�
***************************************************************************/
	MeshItem(//wstring name,
		D3DXVECTOR3& center,D3DXVECTOR3& pos,D3DXVECTOR3& size ,
		D3DXVECTOR3& turn,D3DXVECTOR3& rot,
		D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient);
/**************************************************************************
 MeshItem::MeshItem(
		wstring name,				//	: �I�u�W�F�̖��O
		D3DXVECTOR3& center,		//	: ���S�ƂȂ�ʒu (�I���W�i���[���̂���̃I�t�Z�b�g���W)
		D3DXVECTOR3& pos,			//	: �`��ʒu
		D3DXVECTOR3& size ,			//	: �傫���̔�
		D3DXVECTOR3& turn,			//	: �^�[��	(���])
		D3DXVECTOR3& rot			//	: ���P�[�g	(���])
);							   
 �p�r: �R���X�g���N�^(�F��)
		
 �߂�l: �Ȃ�
***************************************************************************/
	MeshItem(//wstring name,
		D3DXVECTOR3& center,D3DXVECTOR3& pos,D3DXVECTOR3& size ,
		D3DXVECTOR3& turn,D3DXVECTOR3& rot);
	void Delete();
/**************************************************************************
~MeshItem();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
	~MeshItem();

/**************************************************************************
D3DXMATRIX getMatrix();
 �p�r: �}�g���b�N�X�Z�o
 �߂�l: �Z�o���ꂽ�}�g���b�N�X
***************************************************************************/
	D3DXMATRIX getMatrix();

/**************************************************************************
D3DXMATRIX getMatrix(
		MeshItem& i_other	//	: �e�ƂȂ���̂̃A�C�e��
	);
 �p�r: ��MeshItem�e���}�g���b�N�X�̎Z�o
 �߂�l: �Z�o���ꂽ�}�g���b�N�X
***************************************************************************/
	D3DXMATRIX getMatrix(MeshItem& i_other);
	
/**************************************************************************
OBB getObb(float size);
 �p�r: OBB�Z�o
 �߂�l: �Z�o���ꂽOBB
***************************************************************************/
	OBB getObb(float size = 0.5f);
/**************************************************************************
D3DMATERIAL9 getMaterial();
 �p�r: �}�e���A����Ԃ�
 �߂�l: �����̃}�e���A��
***************************************************************************/
	D3DMATERIAL9& getMaterial();
/**************************************************************************
void setMaterial(D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient);
 �p�r: Material�̐ݒ�
 �߂�l: �}�e���A��
***************************************************************************/
	void setMaterial(D3DCOLORVALUE& Diffuse,D3DCOLORVALUE& Specular,D3DCOLORVALUE& Ambient);

/**************************************************************************
MeshItem& operator =(MeshItem& i_OtherMeshItem);
 �p�r: �R�s�[
 �߂�l: this
***************************************************************************/
	MeshItem& operator =(MeshItem& i_OtherMeshItem);


	

};
typedef MeshItem FORMITEM;
}