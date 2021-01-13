#include"CObj.h"

//コンストラクタ
CObj::CObj(CModel*model, const CVector &position, const CVector &rotation, const CVector &scale)
:mpCollider(0)
{
	mpModel = model;
	mPosition = position;
	mRotation = rotation;
	mScale = scale;
	//モデルの三角形の数分、コライダの配列を作成する
	mpCollider = new CCollider[model->mTriangles.size()];
	for (int i = 0; i< model->mTriangles.size(); i++){
		//コライダを三角形コライダで設定していく
		mpCollider[i].SetTriangle(this,
			model->mTriangles[i].mV[0],
			model->mTriangles[i].mV[1],
			model->mTriangles[i].mV[2]);
		mpCollider[i].ChangePriority();
	}
	
	if (m->mTag == CCollider::EBLOCK){
		if (y->mTag == CCollider::EBULLET){
			if (CCollider::Collision(m, y)){
				//プレイヤーの方向
				CVector dir = y->mpParent->mPosition - mPosition;
				//正規化（長さを1にする）Normalize()
				mPosition = mPosition + dir.Normalize() * 0.5;
			}
		}
	}




//デストラクタ
CObj::~CObj(){
	//コライダがあれば削除
	if (mpCollider){
		delete[] mpCollider;
	}
}