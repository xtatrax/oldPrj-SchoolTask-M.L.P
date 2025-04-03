/**************************************************************************
Object.cpp

 class Texture; ��`
 class Stage; ��`
 class ShadowVolume; ��`
****************************************************************************/
#include "StdAfx.h"

namespace wiz{
	WPARAM XBoxController::KeyBoardState;
	Point  XBoxController::MousePoint;
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/**************************************************************************
 Stage ��`��
****************************************************************************/
/**************************************************************************
 void Stage::Clear();
 �p�r:�I�u�W�F�N�g�̔j��
 �߂�l: �Ȃ�
***************************************************************************/
void Stage::Clear(){
	SafeDelete(m_pChildStage);
	//�z�u�I�u�W�F�N�g�̊J��
	//StdVecSafeDelete(m_Vec);
	vector<Object*>::iterator it;
	for(it = m_Vec.begin();it != m_Vec.end();it++){
		SafeDelete(*it);
	}
	m_Vec.clear();
	//�e�N�X�`���̊J��
	vector<Texture*>::iterator it2;
	for(it2 = m_TextureVec.begin();it2 != m_TextureVec.end();it2++){
		SafeDelete(*it2);
	}
	m_TextureVec.clear();
}


/**************************************************************************
 Stage::Stage();
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Stage::Stage()
:m_pParStage(0),m_pChildStage(0),m_IsDialog(false)
{}
/**************************************************************************
 Stage::Stage(
 Stage* Par	//�e�X�e�[�W
 );
 �p�r: �R���X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Stage::Stage(Stage* Par)
:m_pParStage(Par),m_pChildStage(0),m_IsDialog(false)
{}
/**************************************************************************
virtual Stage::~Stage();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
Stage::~Stage(){
	Clear();
}

/**************************************************************************
 virtual void Stage::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,   //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
    const CONTROLER_STATE* pCntlState   //�R���g���[���[�̃X�e�[�^�X
	Command& Com					//�V�[������X�e�[�W�A�������̓X�e�[�W����I�u�W�F�N�g��
									//�n�����R�}���h�̎Q��
 );
 �p�r: �V�[����`��
 �߂�l: �Ȃ��B
***************************************************************************/
void Stage::Draw(LPDIRECT3DDEVICE9 pD3DDevice,const CONTROLER_STATE* pCntlState,
				 Command& Com)
{
	//�z�u�I�u�W�F�N�g�̕`��
	vector<Object*>::size_type sz = m_Vec.size();
	for(vector<Object*>::size_type i = 0;i < sz;i++){
		m_Vec[i]->Draw(pD3DDevice,m_Vec,pCntlState,Com);
	}
}
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/


/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/
/**************************************************************************
 ShadowVolume�֘A
****************************************************************************/
//�e�{�����[����FVF��`
const D3DVERTEXELEMENT9 ShadowVolume::SHADOWVERT::Decl[3] =
{
    { 0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
    { 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },
    D3DDECL_END()
};

/**************************************************************************
 void ShadowVolume::Clear();
 �p�r:�I�u�W�F�N�g�̔j��
 �߂�l: �Ȃ�
***************************************************************************/
void ShadowVolume::Clear(){
    //��n��
    SafeRelease(m_pShadowVolumeMesh);
	SafeRelease(m_pShadowDecl);
}

/**************************************************************************
 void ShadowVolume::Draw(
    LPDIRECT3DDEVICE9 pD3DDevice,    //IDirect3DDevice9 �C���^�[�t�F�C�X�ւ̃|�C���^
	LPD3DXEFFECT	pEffect			//�G�t�F�N�g�ւ̃|�C���^
 );
 �p�r: �e�{�����[����`��
 �߂�l: �Ȃ��B
***************************************************************************/
void ShadowVolume::Draw(LPDIRECT3DDEVICE9 pD3DDevice,LPD3DXEFFECT pEffect){
    if(m_pShadowVolumeMesh)
    {
        pD3DDevice->SetVertexDeclaration(m_pShadowDecl) ;
        UINT cPasses;
        pEffect->Begin( &cPasses, 0 );
        for( UINT i = 0; i < cPasses; ++i )
        {
            pEffect->BeginPass( i );
            pEffect->CommitChanges();
            m_pShadowVolumeMesh->DrawSubset( 0 );
            pEffect->EndPass() ;
        }
        pEffect->End();
    }
}

/**************************************************************************
 ShadowVolume::ShadowVolume(
 LPDIRECT3DDEVICE9 pd3dDevice,	//�f�o�C�X
 LPD3DXMESH pMesh,			//���ƂȂ郁�b�V��
 );
 �p�r: �R���X�g���N�^�i�V���h�E�{�����[�����쐬����j
 *DXUT��ShadowVolume�T���v��������ς��č쐬
 *GenerateShadowMesh()�֐��ɗ�O��������������
 �߂�l: �Ȃ�
***************************************************************************/
ShadowVolume::ShadowVolume(LPDIRECT3DDEVICE9 pd3dDevice, LPD3DXMESH pMesh)
:m_pShadowVolumeMesh(0),
ADJACENCY_EPSILON(0.0001f),
m_pShadowDecl(0)
{

    ID3DXMesh* pInputMesh = 0;
	SHADOWVERT* pVBData = 0;
	DWORD* pdwIBData = 0;

	DWORD* pdwAdj = 0;
	DWORD* pdwPtRep = 0;
	CEdgeMapping* pMapping = 0;

	ID3DXMesh* pNewMesh = 0;
	SHADOWVERT* pNewVBData = 0;
	DWORD* pdwNewIBData = 0;

	ID3DXMesh* pPatchMesh = 0;
	SHADOWVERT* pPatchVBData = 0;
	DWORD* pdwPatchIBData = 0;

	ID3DXMesh* pFinalMesh = 0;
	SHADOWVERT* pFinalVBData = 0;
	WORD* pwFinalIBData = 0;
	try{
		if(!pd3dDevice || !pMesh){
            // ���������s
            throw DxException(
                L"�f�o�C�X�����ƂȂ郁�b�V�����s��ł�",
                L"ShadowVolume::ShadowVolume()"
                );
		}
		// Convert the input mesh to a format same as the output mesh using 32-bit index.
		if(FAILED(pMesh->CloneMesh( D3DXMESH_32BIT, SHADOWVERT::Decl, pd3dDevice, &pInputMesh))){
            // ���������s
            throw DxException(
                L"�C���v�b�g�N���[�����b�V���쐬�Ɏ��s���܂����B",
                L"ShadowVolume::ShadowVolume()"
                );
		}
		// Generate adjacency information
		pdwAdj = new DWORD[3 * pInputMesh->GetNumFaces()];
		pdwPtRep = new DWORD[pInputMesh->GetNumVertices()];
		if( FAILED(pInputMesh->GenerateAdjacency(ADJACENCY_EPSILON, pdwAdj)))
		{
            // ���������s
            throw DxException(
                L"�C���v�b�g���b�V���G�b�W�̎擾�Ɏ��s���܂����B",
                L"ShadowVolume::ShadowVolume()"
                );
		}
		pInputMesh->ConvertAdjacencyToPointReps( pdwAdj, pdwPtRep );
		//pdwAdj�̊J��
		SafeDeleteArr(pdwAdj);
		if(FAILED(pInputMesh->LockVertexBuffer( 0, ( LPVOID* )&pVBData ))){
            // ���������s
            throw DxException(
                L"�C���v�b�g���b�V�����_�̃��b�N�Ɏ��s���܂����B",
                L"ShadowVolume::ShadowVolume()"
                );
		}
		if(FAILED(pInputMesh->LockIndexBuffer( 0, ( LPVOID* )&pdwIBData ))){
            // ���������s
            throw DxException(
                L"�C���v�b�g���b�V���C���f�b�N�X�̃��b�N�Ɏ��s���܂����B",
                L"ShadowVolume::ShadowVolume()"
                );
		}
		// Maximum number of unique edges = Number of faces * 3
		DWORD dwNumEdges = pInputMesh->GetNumFaces() * 3;
		pMapping = new CEdgeMapping[dwNumEdges];
		int nNumMaps = 0;  // Number of entries that exist in pMapping
		// Create a new mesh
		if(FAILED(D3DXCreateMesh( pInputMesh->GetNumFaces() + dwNumEdges * 2,
							 pInputMesh->GetNumFaces() * 3,
							 D3DXMESH_32BIT,
							 SHADOWVERT::Decl,
							 pd3dDevice,
							 &pNewMesh ))){
			// ���������s
			throw DxException(
				L"�V�������b�V���̃}�b�s���O�Ɏ��s���܂����B",
				L"ShadowVolume::ShadowVolume()"
				);

		}
		if(FAILED(pNewMesh->LockVertexBuffer( 0, ( LPVOID* )&pNewVBData ))){
			// ���������s
			throw DxException(
				L"�V�������b�V�����_�̃��b�N�Ɏ��s���܂����B",
				L"ShadowVolume::ShadowVolume()"
				);
		}
		if(FAILED(pNewMesh->LockIndexBuffer( 0, ( LPVOID* )&pdwNewIBData ))){
			// ���������s
			throw DxException(
				L"�V�������b�V���C���f�b�N�X�̃��b�N�Ɏ��s���܂����B",
				L"ShadowVolume::ShadowVolume()"
				);
		}
		// nNextIndex is the array index in IB that the next vertex index value
		// will be store at.
		int nNextIndex = 0;
		ZeroMemory( pNewVBData, pNewMesh->GetNumVertices() * pNewMesh->GetNumBytesPerVertex() );
		ZeroMemory( pdwNewIBData, sizeof( DWORD ) * pNewMesh->GetNumFaces() * 3 );
		// pNextOutVertex is the location to write the next
		// vertex to.
		SHADOWVERT* pNextOutVertex = pNewVBData;
		// Iterate through the faces.  For each face, output new
		// vertices and face in the new mesh, and write its edges
		// to the mapping table.
		for( UINT f = 0; f < pInputMesh->GetNumFaces(); ++f ){
			// Copy the vertex data for all 3 vertices
			CopyMemory( pNextOutVertex, pVBData + pdwIBData[f * 3], sizeof( SHADOWVERT ) );
			CopyMemory( pNextOutVertex + 1, pVBData + pdwIBData[f * 3 + 1], sizeof( SHADOWVERT ) );
			CopyMemory( pNextOutVertex + 2, pVBData + pdwIBData[f * 3 + 2], sizeof( SHADOWVERT ) );

			// Write out the face
			pdwNewIBData[nNextIndex++] = f * 3;
			pdwNewIBData[nNextIndex++] = f * 3 + 1;
			pdwNewIBData[nNextIndex++] = f * 3 + 2;

			// Compute the face normal and assign it to
			// the normals of the vertices.
			D3DXVECTOR3 v1, v2;  // v1 and v2 are the edge vectors of the face
			D3DXVECTOR3 vNormal;
			v1 = *( D3DXVECTOR3* )( pNextOutVertex + 1 ) - *( D3DXVECTOR3* )pNextOutVertex;
			v2 = *( D3DXVECTOR3* )( pNextOutVertex + 2 ) - *( D3DXVECTOR3* )( pNextOutVertex + 1 );
			D3DXVec3Cross( &vNormal, &v1, &v2 );
			D3DXVec3Normalize( &vNormal, &vNormal );

			pNextOutVertex->Normal = vNormal;
			( pNextOutVertex + 1 )->Normal = vNormal;
			( pNextOutVertex + 2 )->Normal = vNormal;

			pNextOutVertex += 3;

			// Add the face's edges to the edge mapping table

			// Edge 1
			int nIndex;
			int nVertIndex[3] =
			{
				pdwPtRep[pdwIBData[f * 3]],
				pdwPtRep[pdwIBData[f * 3 + 1]],
				pdwPtRep[pdwIBData[f * 3 + 2]]
			};
			nIndex = FindEdgeInMappingTable( nVertIndex[0], nVertIndex[1], pMapping, dwNumEdges );
			// If error, we are not able to proceed, so abort.
			if( -1 == nIndex ){
				// ���������s
				throw DxException(
					L"�G�b�W�P�̃}�b�s���O�Ɏ��s���܂����B",
					L"ShadowVolume::ShadowVolume()"
					);
			}
			if( pMapping[nIndex].m_anOldEdge[0] == -1 && pMapping[nIndex].m_anOldEdge[1] == -1 ){
				// No entry for this edge yet.  Initialize one.
				pMapping[nIndex].m_anOldEdge[0] = nVertIndex[0];
				pMapping[nIndex].m_anOldEdge[1] = nVertIndex[1];
				pMapping[nIndex].m_aanNewEdge[0][0] = f * 3;
				pMapping[nIndex].m_aanNewEdge[0][1] = f * 3 + 1;

				++nNumMaps;
			}
			else{
				// An entry is found for this edge.  Create
				// a quad and output it.

				pMapping[nIndex].m_aanNewEdge[1][0] = f * 3;      // For clarity
				pMapping[nIndex].m_aanNewEdge[1][1] = f * 3 + 1;

				// First triangle
				pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[0][1];
				pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[0][0];
				pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[1][0];

				// Second triangle
				pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[1][1];
				pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[1][0];
				pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[0][0];

				// pMapping[nIndex] is no longer needed. Copy the last map entry
				// over and decrement the map count.

				pMapping[nIndex] = pMapping[nNumMaps - 1];
				FillMemory( &pMapping[nNumMaps - 1], sizeof( pMapping[nNumMaps - 1] ), 0xFF );
				--nNumMaps;
			}
			// Edge 2
			nIndex = FindEdgeInMappingTable( nVertIndex[1], nVertIndex[2], pMapping, dwNumEdges );
			// If error, we are not able to proceed, so abort.
			if( -1 == nIndex ){
				// ���������s
				throw DxException(
					L"�G�b�W�Q�̃}�b�s���O�Ɏ��s���܂����B",
					L"ShadowVolume::ShadowVolume()"
					);
			}
			if( pMapping[nIndex].m_anOldEdge[0] == -1 && pMapping[nIndex].m_anOldEdge[1] == -1 ){
				pMapping[nIndex].m_anOldEdge[0] = nVertIndex[1];
				pMapping[nIndex].m_anOldEdge[1] = nVertIndex[2];
				pMapping[nIndex].m_aanNewEdge[0][0] = f * 3 + 1;
				pMapping[nIndex].m_aanNewEdge[0][1] = f * 3 + 2;

				++nNumMaps;
			}
			else{
				pMapping[nIndex].m_aanNewEdge[1][0] = f * 3 + 1;
				pMapping[nIndex].m_aanNewEdge[1][1] = f * 3 + 2;
				// First triangle
				pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[0][1];
				pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[0][0];
				pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[1][0];
				// Second triangle
				pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[1][1];
				pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[1][0];
				pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[0][0];
				// pMapping[nIndex] is no longer needed. Copy the last map entry
				// over and decrement the map count.
				pMapping[nIndex] = pMapping[nNumMaps - 1];
				FillMemory( &pMapping[nNumMaps - 1], sizeof( pMapping[nNumMaps - 1] ), 0xFF );
				--nNumMaps;
			}
			// Edge 3
			nIndex = FindEdgeInMappingTable( nVertIndex[2], nVertIndex[0], pMapping, dwNumEdges );
			// If error, we are not able to proceed, so abort.
			if( -1 == nIndex ){
				// ���������s
				throw DxException(
					L"�G�b�W�R�̃}�b�s���O�Ɏ��s���܂����B",
					L"ShadowVolume::ShadowVolume()"
					);
			}
			if( pMapping[nIndex].m_anOldEdge[0] == -1 && pMapping[nIndex].m_anOldEdge[1] == -1 ){
				pMapping[nIndex].m_anOldEdge[0] = nVertIndex[2];
				pMapping[nIndex].m_anOldEdge[1] = nVertIndex[0];
				pMapping[nIndex].m_aanNewEdge[0][0] = f * 3 + 2;
				pMapping[nIndex].m_aanNewEdge[0][1] = f * 3;

				++nNumMaps;
			}
			else{
				pMapping[nIndex].m_aanNewEdge[1][0] = f * 3 + 2;
				pMapping[nIndex].m_aanNewEdge[1][1] = f * 3;

				// First triangle
				pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[0][1];
				pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[0][0];
				pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[1][0];

				// Second triangle
				pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[1][1];
				pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[1][0];
				pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[0][0];

				// pMapping[nIndex] is no longer needed. Copy the last map entry
				// over and decrement the map count.

				pMapping[nIndex] = pMapping[nNumMaps - 1];
				FillMemory( &pMapping[nNumMaps - 1], sizeof( pMapping[nNumMaps - 1] ), 0xFF );
				--nNumMaps;
			}
		}

		// Now the entries in the edge mapping table represent
		// non-shared edges.  What they mean is that the original
		// mesh has openings (holes), so we attempt to patch them.
		// First we need to recreate our mesh with a larger vertex
		// and index buffers so the patching geometry could fit.

		// Create a mesh with large enough vertex and
		// index buffers.
		// Make enough room in IB for the face and up to 3 quads for each patching face
		if(FAILED(D3DXCreateMesh( nNextIndex / 3 + nNumMaps * 7,
							 ( pInputMesh->GetNumFaces() + nNumMaps ) * 3,
							 D3DXMESH_32BIT,
							 SHADOWVERT::Decl,
							 pd3dDevice,
							 &pPatchMesh ))){
			// ���������s
			throw DxException(
				L"�p�b�`���b�V���̍쐬�Ɏ��s���܂����B",
				L"ShadowVolume::ShadowVolume()"
				);
		}
		if(FAILED(pPatchMesh->LockVertexBuffer( 0, ( LPVOID* )&pPatchVBData ))){
			// ���������s
			throw DxException(
				L"�p�b�`���b�V���̃��b�N�Ɏ��s���܂����B",
				L"ShadowVolume::ShadowVolume()"
				);
		}
		if(FAILED(pPatchMesh->LockIndexBuffer( 0, ( LPVOID* )&pdwPatchIBData ))){
			// ���������s
			throw DxException(
				L"�p�b�`���b�V���̃C���f�b�N�X���b�N�Ɏ��s���܂����B",
				L"ShadowVolume::ShadowVolume()"
				);
		}
		ZeroMemory( pPatchVBData, sizeof( SHADOWVERT ) * ( pInputMesh->GetNumFaces() + nNumMaps ) *3 );
		ZeroMemory( pdwPatchIBData, sizeof( DWORD ) * ( nNextIndex + 3 * nNumMaps * 7 ) );
		// Copy the data from one mesh to the other
		CopyMemory( pPatchVBData, pNewVBData, sizeof( SHADOWVERT ) * pInputMesh->GetNumFaces() * 3 );
		CopyMemory( pdwPatchIBData, pdwNewIBData, sizeof( DWORD ) * nNextIndex );
		// Replace pNewMesh with the updated one.  Then the code
		// can continue working with the pNewMesh pointer.
		pNewMesh->UnlockVertexBuffer();
		pNewMesh->UnlockIndexBuffer();
		pNewVBData = pPatchVBData;
		pdwNewIBData = pdwPatchIBData;
		pNewMesh->Release();
		pNewMesh = pPatchMesh;
		//�p�b�`�͂�������Ȃ�
		pPatchVBData = 0;
		pdwPatchIBData = 0;
		pPatchMesh = 0;

		// Now, we iterate through the edge mapping table and
		// for each shared edge, we generate a quad.
		// For each non-shared edge, we patch the opening
		// with new faces.

		// nNextVertex is the index of the next vertex.
		int nNextVertex = pInputMesh->GetNumFaces() * 3;

		for( int i = 0; i < nNumMaps; ++i ){
			if( pMapping[i].m_anOldEdge[0] != -1 &&
				pMapping[i].m_anOldEdge[1] != -1 ){
				// If the 2nd new edge indexes is -1,
				// this edge is a non-shared one.
				// We patch the opening by creating new
				// faces.
				if( pMapping[i].m_aanNewEdge[1][0] == -1 ||  // must have only one new edge
					pMapping[i].m_aanNewEdge[1][1] == -1 ){
					// Find another non-shared edge that
					// shares a vertex with the current edge.
					for( int i2 = i + 1; i2 < nNumMaps; ++i2 ){
						if( pMapping[i2].m_anOldEdge[0] != -1 &&       // must have a valid old edge
							pMapping[i2].m_anOldEdge[1] != -1 &&
							( pMapping[i2].m_aanNewEdge[1][0] == -1 || // must have only one new edge
							  pMapping[i2].m_aanNewEdge[1][1] == -1 ) ){
							int nVertShared = 0;
							if( pMapping[i2].m_anOldEdge[0] == pMapping[i].m_anOldEdge[1] )
								++nVertShared;
							if( pMapping[i2].m_anOldEdge[1] == pMapping[i].m_anOldEdge[0] )
								++nVertShared;

							if( 2 == nVertShared ){
								// These are the last two edges of this particular
								// opening. Mark this edge as shared so that a degenerate
								// quad can be created for it.

								pMapping[i2].m_aanNewEdge[1][0] = pMapping[i].m_aanNewEdge[0][0];
								pMapping[i2].m_aanNewEdge[1][1] = pMapping[i].m_aanNewEdge[0][1];
								break;
							}
							else if( 1 == nVertShared ){
								// nBefore and nAfter tell us which edge comes before the other.
								int nBefore, nAfter;
								if( pMapping[i2].m_anOldEdge[0] == pMapping[i].m_anOldEdge[1] ){
									nBefore = i;
									nAfter = i2;
								}
								else{
									nBefore = i2;
									nAfter = i;
								}
								// Found such an edge. Now create a face along with two
								// degenerate quads from these two edges.
								pNewVBData[nNextVertex] = pNewVBData[pMapping[nAfter].m_aanNewEdge[0][1]];
								pNewVBData[nNextVertex + 1] = pNewVBData[pMapping[nBefore].m_aanNewEdge[0][1]];
								pNewVBData[nNextVertex + 2] = pNewVBData[pMapping[nBefore].m_aanNewEdge[0][0]];
								// Recompute the normal
								D3DXVECTOR3 v1
									= pNewVBData[nNextVertex + 1].Position - pNewVBData[nNextVertex].Position;
								D3DXVECTOR3 v2
									= pNewVBData[nNextVertex + 2].Position - pNewVBData[nNextVertex + 1].Position;
								D3DXVec3Normalize( &v1, &v1 );
								D3DXVec3Normalize( &v2, &v2 );
								D3DXVec3Cross( &pNewVBData[nNextVertex].Normal, &v1, &v2 );
								pNewVBData[nNextVertex + 1].Normal = pNewVBData[nNextVertex + 2].Normal = pNewVBData[nNextVertex].Normal;
								pdwNewIBData[nNextIndex] = nNextVertex;
								pdwNewIBData[nNextIndex + 1] = nNextVertex + 1;
								pdwNewIBData[nNextIndex + 2] = nNextVertex + 2;
								// 1st quad
								pdwNewIBData[nNextIndex + 3] = pMapping[nBefore].m_aanNewEdge[0][1];
								pdwNewIBData[nNextIndex + 4] = pMapping[nBefore].m_aanNewEdge[0][0];
								pdwNewIBData[nNextIndex + 5] = nNextVertex + 1;

								pdwNewIBData[nNextIndex + 6] = nNextVertex + 2;
								pdwNewIBData[nNextIndex + 7] = nNextVertex + 1;
								pdwNewIBData[nNextIndex + 8] = pMapping[nBefore].m_aanNewEdge[0][0];
								// 2nd quad
								pdwNewIBData[nNextIndex + 9] = pMapping[nAfter].m_aanNewEdge[0][1];
								pdwNewIBData[nNextIndex + 10] = pMapping[nAfter].m_aanNewEdge[0][0];
								pdwNewIBData[nNextIndex + 11] = nNextVertex;

								pdwNewIBData[nNextIndex + 12] = nNextVertex + 1;
								pdwNewIBData[nNextIndex + 13] = nNextVertex;
								pdwNewIBData[nNextIndex + 14] = pMapping[nAfter].m_aanNewEdge[0][0];

								// Modify mapping entry i2 to reflect the third edge
								// of the newly added face.

								if( pMapping[i2].m_anOldEdge[0] == pMapping[i].m_anOldEdge[1] ){
									pMapping[i2].m_anOldEdge[0] = pMapping[i].m_anOldEdge[0];
								}
								else{
									pMapping[i2].m_anOldEdge[1] = pMapping[i].m_anOldEdge[1];
								}
								pMapping[i2].m_aanNewEdge[0][0] = nNextVertex + 2;
								pMapping[i2].m_aanNewEdge[0][1] = nNextVertex;

								// Update next vertex/index positions

								nNextVertex += 3;
								nNextIndex += 15;

								break;
							}
						}
					}
				}
				else{
					// This is a shared edge.  Create the degenerate quad.

					// First triangle
					pdwNewIBData[nNextIndex++] = pMapping[i].m_aanNewEdge[0][1];
					pdwNewIBData[nNextIndex++] = pMapping[i].m_aanNewEdge[0][0];
					pdwNewIBData[nNextIndex++] = pMapping[i].m_aanNewEdge[1][0];

					// Second triangle
					pdwNewIBData[nNextIndex++] = pMapping[i].m_aanNewEdge[1][1];
					pdwNewIBData[nNextIndex++] = pMapping[i].m_aanNewEdge[1][0];
					pdwNewIBData[nNextIndex++] = pMapping[i].m_aanNewEdge[0][0];
				}
			}
		}

////////////////////
		pNewMesh->UnlockVertexBuffer();
		pNewVBData = 0;
		pNewMesh->UnlockIndexBuffer();
		pdwNewIBData = 0;
		bool bNeed32Bit = ( pInputMesh->GetNumFaces() + nNumMaps ) * 3 > 65535;
		if(FAILED(D3DXCreateMesh( nNextIndex / 3,  // Exact number of faces
							 ( pInputMesh->GetNumFaces() + nNumMaps ) * 3,
							 D3DXMESH_WRITEONLY | ( bNeed32Bit ? D3DXMESH_32BIT : 0 ),
							 SHADOWVERT::Decl,
							 pd3dDevice,
							 &pFinalMesh ))){
			// ���������s
			throw DxException(
				L"���X�g���b�V���̍쐬�Ɏ��s���܂����B",
				L"ShadowVolume::ShadowVolume()"
				);
		}
		if(FAILED(pNewMesh->LockVertexBuffer( 0, ( LPVOID* )&pNewVBData ))){
			// ���������s
			throw DxException(
				L"�V���b�V���̃��b�N�Ɏ��s���܂����B",
				L"ShadowVolume::ShadowVolume()"
				);
		}
		if(FAILED(pNewMesh->LockIndexBuffer( 0, ( LPVOID* )&pdwNewIBData ))){
			// ���������s
			throw DxException(
				L"�V���b�V���C���f�b�N�X�̃��b�N�Ɏ��s���܂����B",
				L"ShadowVolume::ShadowVolume()"
				);
		}
		if(FAILED(pFinalMesh->LockVertexBuffer( 0, ( LPVOID* )&pFinalVBData ))){
			// ���������s
			throw DxException(
				L"���X�g���b�V���̃��b�N�Ɏ��s���܂����B",
				L"ShadowVolume::ShadowVolume()"
				);
		}
		if(FAILED(pFinalMesh->LockIndexBuffer( 0, ( LPVOID* )&pwFinalIBData ))){
			// ���������s
			throw DxException(
				L"���X�g���b�V���C���f�b�N�X�̃��b�N�Ɏ��s���܂����B",
				L"ShadowVolume::ShadowVolume()"
				);
		}
		CopyMemory( pFinalVBData, pNewVBData, sizeof( SHADOWVERT ) *
					( pInputMesh->GetNumFaces() + nNumMaps ) * 3 );
		if( bNeed32Bit )
			CopyMemory( pwFinalIBData, pdwNewIBData, sizeof( DWORD ) * nNextIndex );
		else{
			for( int i = 0; i < nNextIndex; ++i )
				pwFinalIBData[i] = ( WORD )pdwNewIBData[i];
		}
		pNewMesh->UnlockVertexBuffer();
		pNewVBData = 0;
		pNewMesh->UnlockIndexBuffer();
		pdwNewIBData = 0;
		SafeRelease(pNewMesh);
		pFinalMesh->UnlockVertexBuffer();
		pFinalVBData = 0;
		pFinalMesh->UnlockIndexBuffer();
		pwFinalIBData = 0;
		m_pShadowVolumeMesh = pFinalMesh;
		pFinalMesh = 0;
		SafeDeleteArr(pMapping);
		SafeDeleteArr(pdwPtRep);
		pInputMesh->UnlockVertexBuffer();
		pVBData = 0;
		pInputMesh->UnlockIndexBuffer();
		pdwIBData = 0;
		SafeRelease(pInputMesh);

		if(FAILED(pd3dDevice->CreateVertexDeclaration( SHADOWVERT::Decl, &m_pShadowDecl  ))){
			// ���������s
			throw DxException(
				L"���_��`�Ɏ��s���܂���",
				L"ShadowVolume::ShadowVolume()"
				);
		}

	}
	catch(...){
		if(pFinalVBData && pFinalMesh){
			pFinalMesh->UnlockVertexBuffer();
			pFinalVBData = 0;
		}
		if(pwFinalIBData && pFinalMesh){
			pPatchMesh->UnlockIndexBuffer();
			pwFinalIBData = 0;
		}
        SafeRelease(pFinalMesh);
		if(pPatchVBData && pPatchMesh){
			pPatchMesh->UnlockVertexBuffer();
			pPatchVBData = 0;
		}
		if(pdwPatchIBData && pPatchMesh){
			pPatchMesh->UnlockIndexBuffer();
			pdwPatchIBData = 0;
		}
        SafeRelease(pPatchMesh);
		if(pNewVBData && pNewMesh){
			pNewMesh->UnlockVertexBuffer();
			pNewVBData = 0;
		}
		if( pdwNewIBData && pNewMesh){
			pNewMesh->UnlockIndexBuffer();
			pdwNewIBData = 0;
		}
		SafeRelease(pNewMesh);

		SafeDeleteArr(pMapping);
		SafeDeleteArr(pdwPtRep);
		SafeDeleteArr(pdwAdj);

		if( pVBData && pInputMesh){
			pInputMesh->UnlockVertexBuffer();
			pVBData = 0;
		}
		if( pdwIBData && pInputMesh){
			pInputMesh->UnlockIndexBuffer();
			pdwIBData = 0;
		}
        SafeRelease(pInputMesh);
		Clear();
		//�ăX���[
		throw;
	}
	
}

/**************************************************************************
 ShadowVolume::~ShadowVolume();
 �p�r: �f�X�g���N�^
 �߂�l: �Ȃ�
***************************************************************************/
ShadowVolume::~ShadowVolume(){
		Clear();
}
/*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*��*/



}
//end of namespace wiz.

