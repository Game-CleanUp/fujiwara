#include"CTrap.h"


int CTrap::TrapCount = 10;
CTrap *CTrap::mpTrap = 0;
CModel CTrap::mModel;

CSound CTrap::Sound;

CTrap::CTrap(CModel*model, CVector position, CVector rotation, CVector scale)
:mColBody(this, CVector(0.0f, 1.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 5.0f)
{
	//モデル、位置、回転、拡縮を設定する
	mpModel = model; //モデルの設定
	mPosition = position; //位置の設定
	mRotation = rotation; //回転の設定
	mScale = scale; //拡縮の設定

	//モデルが無いときは読み込む
	if (mModel.mTriangles.size() == 0)
	{
		mModel.Load("sphere.obj", "sphere.mtl");
	}
	//モデルのポインタ設定
	mpModel = &mModel;

	mColBody.mTag = CCollider::ETRAP;

	mpTrap = this;
}


void CTrap::TaskCollision()
{
	mColBody.ChangePriority();

	CCollisionManager::Get()->Collision(&mColBody);

}


void CTrap::Update(){

	mVelocityJump = JUMPV0;
	//重力加速度
	mVelocityJump -= G;
	//移動
	mPosition.mY = mPosition.mY - mVelocityJump;

	CCharacter::Update();
}

void CTrap::Collision(CCollider*m, CCollider*y){


	//自身のコライダタイプの判定
	switch (m->mType){
	case CCollider::ESPHERE://球コライダ
		//相手のコライダが三角コライダの時
		if (y->mType == CCollider::ETRIANGLE){
			CVector adjust;//調整値ベクトル
			//三角形と球の衝突判定
			if (CCollider::CollisionTriangleSphere(y, m, &adjust)){
				//着地
				mVelocityJump = 0;

			}

			//位置の更新
			mPosition = mPosition - adjust*-1;

			//行列の更新
			CCharacter::Update();
		}

		break;
	}

	//相手がCBoss(犬と衝突)
	if (y->mTag == CCollider::EBODY2){
		if (CCollider::Collision(m, y)){
			trapframe++;
			mEnabled = false;
		}
	}

	/*if (trapframe > 120){
		mEnabled = false;
	}*/
}