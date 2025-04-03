/**************************************************************************
 Function.h

 ユーティリティテンプレート／関数
 class DxException; //例外クラス
 class HitTest;  //衝突判定クラス（static呼び出しをする）
****************************************************************************/
#pragma once

#include "StdAfx.h"

namespace wiz{

/************************************************
class DxException : public exception

目的:　STL例外から派生したクラス
*************************************************/
class DxException : public exception{
    //メッセージ変数
    wstring m_Message;
public:
/**************************************************************************
DxException(
    const wchar_t* m1,  //第1メッセージ
    const wchar_t* m2   //第2メッセージ
);
用途: コンストクタ
戻り値: なし
***************************************************************************/
    DxException(const wchar_t* m1,const wchar_t* m2){
        m_Message = m1;
        m_Message += L"\r\n";
        m_Message += m2;
    }
/**************************************************************************
const wchar_t* what_w() const throw()
用途: メッセージの取得
戻り値: メッセージ文字列のポインタ
***************************************************************************/
    const wchar_t* what_w() const throw(){
        return m_Message.c_str();
    }
};

/**************************************************************************
template<typename T>
inline void SafeDelete(
T*& p   // T型のポインタの参照
)
用途: 安全にポインタをdeleteする
戻り値: なし
***************************************************************************/
template<typename T>
inline void SafeDelete(T*& p){
    if(p){
        delete p;
    }
    p = 0;
}
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/
/**************************************************************************
template<typename T>
inline void SafeDelete(
T*& p   // T型のポインタの参照
)
用途: 安全にポインタをdeleteする
戻り値: なし
***************************************************************************/
template<typename T>
inline void StdVecSafeDelete(T& p){
	T::iterator it;
    for(it = p.begin();it != p.end();it++){
        SafeDelete(*it);
    }
    p.clear();

}
/*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*☆*★*/

/**************************************************************************
template<typename T>
inline void SafeDeleteArr(
T*& p   // T型のポインタの参照
)
用途: 安全に配列をdeleteする
戻り値: なし
***************************************************************************/
template<typename T>
inline void SafeDeleteArr(T*& p){
    if(p){
        delete [] p;
    }
    p = 0;
}

/**************************************************************************
template<typename T>
inline void SafeRelease(
T*& p   // T型のインターフェイスのポインタの参照
)
用途: 安全にインターフェイスをreleaseする
戻り値: なし
***************************************************************************/
template<typename T>
inline void SafeRelease(T*& p){
    if(p){
        p->Release();
    }
    p = 0;
}


/**************************************************************************
 struct OBB;
 用途: OBBボリューム境界
****************************************************************************/
struct OBB{
    D3DXVECTOR3 m_Center;     //中心点の座標
    D3DXVECTOR3 m_Rot[3];  //XYZ の各座標軸の傾きを表す方向ベクトル
    D3DXVECTOR3 m_Size;     //OBB の各座標軸に沿った長さの半分（中心点から面までの長さ）
};

/**************************************************************************
 struct Sphere;
 用途: 球データ
****************************************************************************/
struct Sphere
{
    D3DXVECTOR3 m_Center;
    float m_Radius;
};

/**************************************************************************
 class HitTest;
 用途: 衝突判定用のユーティリティ
 　　　static呼び出しをする
****************************************************************************/
class HitTest{
/**************************************************************************
 static void ClosestPtPointOBB(
	const D3DXVECTOR3& point,		//基準点
	const OBB& obb,				//OBB
	D3DXVECTOR3& retvec		//最近接点を返す参照
　);
 用途: pointから見たOBBの最近接点を得る
 戻り値: 無し（retvecに最近接点が代入される）
***************************************************************************/
	static void ClosestPtPointOBB(const D3DXVECTOR3& point,const OBB& obb, D3DXVECTOR3& retvec){
		D3DXVECTOR3 d = point - obb.m_Center;
		retvec = obb.m_Center;
		float dist;
		for(int i = 0; i < 3; i++)
		{
			dist = D3DXVec3Dot(&d, &obb.m_Rot[i]);
			if(dist > obb.m_Size[i])
			{
				dist = obb.m_Size[i];
			}
			if(dist < -obb.m_Size[i])
			{
				dist = -obb.m_Size[i];
			}
			retvec +=  dist * obb.m_Rot[i];
		}
	}
public:
	HitTest(){}
	~HitTest(){}
/**************************************************************************
 static bool Sphere_Sphere(
	const Sphere& sp1,		//球１
	const Sphere& sp2		//球２
);
 用途: 球と球との衝突判定
 戻り値: 衝突していればtrue（retvecに最近接点が代入される）
***************************************************************************/
	static bool Sphere_Sphere(const Sphere& sp1,const Sphere& sp2){
		D3DXVECTOR3 d = sp1.m_Center - sp2.m_Center;
		float dist2 = D3DXVec3Dot(&d,&d);
		float radiussum = sp1.m_Radius + sp2.m_Radius;
		return dist2 <= radiussum * radiussum;
	}
/**************************************************************************
 static bool OBB_Sphere(
	const Sphere& sp,		//球
	const OBB& obb,		//OBB
	D3DXVECTOR3& retvec	//最近接点が代入される参照
);
 用途: OBBと球との衝突判定
 戻り値: 衝突していればtrue（retvecに最近接点が代入される）
***************************************************************************/
	static bool OBB_Sphere(const Sphere& sp,const OBB& obb,D3DXVECTOR3& retvec){
        ClosestPtPointOBB(sp.m_Center,obb,retvec);
        D3DXVECTOR3 v = retvec - sp.m_Center;
        return D3DXVec3Dot(&v,&v) <= sp.m_Radius * sp.m_Radius;
	}
/**************************************************************************
 static bool OBB_OBB(
 const OBB& obb1,
 const OBB& obb2
 );
 用途: OBBとOBBとの衝突判定
 戻り値: 衝突していればtrue
***************************************************************************/
	static bool OBB_OBB(const OBB& obb1,const OBB& obb2){
		const float EPSILON = 1.175494e-37f;
		float R[3][3], AbsR[3][3];
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				R[i][j] = D3DXVec3Dot(&obb1.m_Rot[i], &obb2.m_Rot[j]);
				AbsR[i][j] = fabsf(R[i][j]) + EPSILON;
			}
		}
		D3DXVECTOR3 t = obb2.m_Center - obb1.m_Center;
		t = D3DXVECTOR3(D3DXVec3Dot(&t, &obb1.m_Rot[0]),
						D3DXVec3Dot(&t, &obb1.m_Rot[1]),
						D3DXVec3Dot(&t, &obb1.m_Rot[2]));
		//軸L=A0, L=A1, L=A2判定
		float ra, rb;
		for(int i = 0; i < 3; i++){
			ra = obb1.m_Size[i];
			rb = obb2.m_Size[0] * AbsR[i][0] + obb2.m_Size[1] * AbsR[i][1] + obb2.m_Size[2] * AbsR[i][2];
			if(fabsf(t[i]) > ra + rb){
				return false;
			}
		}
		//軸L=B0, L=B1, L=B2判定
		for(int i = 0; i < 3; i++){
			ra = obb1.m_Size[0] * AbsR[0][i] + obb1.m_Size[1] * AbsR[1][i] + obb1.m_Size[2] * AbsR[2][i];
			rb = obb2.m_Size[i];
			if(fabsf(t[0] * R[0][i] + t[1] * R[1][i] + t[2] * R[2][i]) > ra + rb){
				return false;
			}
		}
		//軸L=A0 X B0判定
		ra = obb1.m_Size[1] * AbsR[2][0] + obb1.m_Size[2] * AbsR[1][0];
		rb = obb2.m_Size[1] * AbsR[0][2] + obb2.m_Size[2] * AbsR[0][1];
		if(fabsf(t[2] * R[1][0] - t[1] * R[2][0]) > ra + rb){
			return false;
		}
		//軸L=A0 X B1判定
		ra = obb1.m_Size[1] * AbsR[2][1] + obb1.m_Size[2] * AbsR[1][1];
		rb = obb2.m_Size[0] * AbsR[0][2] + obb2.m_Size[2] * AbsR[0][0];
		if(fabsf(t[2] * R[1][1] - t[1] * R[2][1]) > ra + rb){
			return false;
		}
		//軸L=A0 X B2判定
		ra = obb1.m_Size[1] * AbsR[2][2] + obb1.m_Size[2] * AbsR[1][2];
		rb = obb2.m_Size[0] * AbsR[0][1] + obb2.m_Size[1] * AbsR[0][0];
		if(fabsf(t[2] * R[1][2] - t[1] * R[2][2]) > ra + rb){
			return false;
		}
		//軸L=A1 X B0判定
		ra = obb1.m_Size[0] * AbsR[2][0] + obb1.m_Size[2] * AbsR[0][0];
		rb = obb2.m_Size[1] * AbsR[1][2] + obb2.m_Size[2] * AbsR[1][1];
		if(fabsf(t[0] * R[2][0] - t[2] * R[0][0]) > ra + rb){
			return false;
		}
		//軸L=A1 X B1判定
		ra = obb1.m_Size[0] * AbsR[2][1] + obb1.m_Size[2] * AbsR[0][1];
		rb = obb2.m_Size[0] * AbsR[1][2] + obb2.m_Size[2] * AbsR[1][0];
		if(fabsf(t[0] * R[2][1] - t[2] * R[0][1]) > ra + rb){
			return false;
		}
		//軸L=A1 X B2判定
		ra = obb1.m_Size[0] * AbsR[2][2] + obb1.m_Size[2] * AbsR[0][2];
		rb = obb2.m_Size[0] * AbsR[1][1] + obb2.m_Size[1] * AbsR[1][0];
		if(fabsf(t[0] * R[2][2] - t[2] * R[0][2]) > ra + rb){
			return false;
		}
		//軸L=A2 X B0判定
		ra = obb1.m_Size[0] * AbsR[1][0] + obb1.m_Size[1] * AbsR[0][0];
		rb = obb2.m_Size[1] * AbsR[2][2] + obb2.m_Size[2] * AbsR[2][1];
		if(fabsf(t[1] * R[0][0] - t[0] * R[1][0]) > ra + rb){
			return false;
		}
		//軸L=A2 X B1判定
		ra = obb1.m_Size[0] * AbsR[1][1] + obb1.m_Size[1] * AbsR[0][1];
		rb = obb2.m_Size[0] * AbsR[2][2] + obb2.m_Size[2] * AbsR[2][0];
		if(fabsf(t[1] * R[0][1] - t[0] * R[1][1]) > ra + rb){
			return false;
		}
		//軸L=A2 X B2判定
		ra = obb1.m_Size[0] * AbsR[1][2] + obb1.m_Size[1] * AbsR[0][2];
		rb = obb2.m_Size[0] * AbsR[2][1] + obb2.m_Size[1] * AbsR[2][0];
		if(fabsf(t[1] * R[0][2] - t[0] * R[1][2]) > ra + rb){
			return false;
		}
		return true;
	}
};



}
//end of namespace wiz.
