#include"CBlock.h"

CBlock::CBlock(CModel*model, CVector position, CVector rotation, CVector scale)
:mColBody(this, CVector(0.0f, 2.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 5.0f)
{
	//モデル、位置、回転、拡縮を設定する
	mpModel = model; //モデルの設定
	mPosition = position; //位置の設定
	mRotation = rotation; //回転の設定
	mScale = scale; //拡縮の設定

	//モデルの三角形の数分、コライダの配列を作成する
	mpCollider = new CCollider[model->mTriangles.size()];

	//モデルの三角形の数分、コライダの配列を作成する
	BlockTriangle = model->mTriangles.size();
	for (int i = 0; i < model->mTriangles.size(); i++){
		//コライダを三角形コライダで設定していく
		mpCollider[i].SetTriangle(this,
			model->mTriangles[i].mV[0],
			model->mTriangles[i].mV[1],
			model->mTriangles[i].mV[2]);
		mpCollider[i].ChangePriority();
	}

	mColBody.mTag = CCollider::EBLOCK;
}

void CBlock::TaskCollision()
{
	mColBody.ChangePriority();
	for (int i = 0; i < BlockTriangle; i++){
		mpCollider[i].ChangePriority();
	}
	CCollisionManager::Get()->Collision(&mColBody);

}

void CBlock::Update(){
	
	//mVelocityJump = JUMPV0;
	////重力加速度
	//mVelocityJump -= G;
	////移動
	//mPosition.mY = mPosition.mY - mVelocityJump;

	//CCharacter::Update();
}

void CBlock::Collision(CCollider*m, CCollider*y){

	if (y->mTag == CCollider::EBULLET){
		if (CCollider::Collision(m, y)){
			//プレイヤー弾の方向
			CVector dir = y->mpParent->mPosition - mPosition;
			//正規化（長さを1にする）Normalize()
			mPosition = mPosition + dir.Normalize()*1.0;
		}
	}

	switch (m->mType){
	case CCollider::ESPHERE://球コライダ
		//相手のコライダが三角コライダの時
		if (y->mType == CCollider::ETRIANGLE){
			CVector adjust;//調整値ベクトル
			//三角形と球の衝突判定
			if (CCollider::CollisionTriangleSphere(y, m, &adjust)){
				//着地
				//mVelocityJump = 0;
			}

			//位置の更新
			mPosition = mPosition - adjust*-1;

			//行列の更新
			CCharacter::Update();
		}

		break;
	}
}