#include"CTrap.h"


int CTrap::TrapCount = INIT_TRAP;
CTrap *CTrap::mpTrap = 0;
CModel CTrap::mModel;

CSound CTrap::Sound;

CTrap::CTrap(CModel*model, CVector position, CVector rotation, CVector scale)
:mColBody(this, CVector(0.0f, 2.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 3.0f)
, trapframe(0)
{
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
	case CCollider::ESPHERE:
		//相手が三角コライダ
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
			trapframe++;	//停止時間カウント
		}
		//1秒後消滅
		if (trapframe > 60){
			mEnabled = false;
		}
	}
}