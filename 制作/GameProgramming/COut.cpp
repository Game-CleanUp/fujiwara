#include"COut.h"

//コンストラクタ
COut::COut(CModel*model, const CVector &position, const CVector &rotation, const CVector &scale)
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
	}
	mTag = EOUT;
}
//デストラクタ
COut::~COut(){
	//コライダがあれば削除
	if (mpCollider){
		delete[] mpCollider;
	}
}