#include"CFall.h"


int FallLife = 0;

//課題7
CFall::CFall(CModel*model, CVector position, CVector rotation, CVector scale)
:mColBody(this, CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f),
CVector(1.0f, 1.0f, 1.0f), 5.0f)
{
	//モデル、位置、回転、拡縮を設定する
	mpModel = model; //モデルの設定
	mPosition = position; //位置の設定
	mRotation = rotation; //回転の設定
	mScale = scale; //拡縮の設定
}
//課題8
void CFall::Collision(CCollider*m, CCollider*y){
	
	//自身のコライダタイプの判定
	switch (m->mType){
	case CCollider::ESPHERE://球コライダ
		//相手のコライダが三角コライダの時
		if (y->mType == CCollider::ETRIANGLE){
			CVector adjust;//調整値ベクトル
			//三角形と球の衝突判定
			if (CCollider::CollisionTriangleSphere(y, m, &adjust)){

				//反射方向
				//mForward = CVector(0.0f, 3.0f, 0.0f);
				if (rand() % 3 - 1 >= 0){
					mForward = CVector(0.5f, 5.0f, 0.0f);
				}
				else{
					mForward = CVector(-0.5f, 5.0f, 0.0f);
				}
			}
			//位置の更新
			mPosition = mPosition - adjust*-1;

			//行列の更新
			CCharacter::Update();
		}
		break;

		if (y->mType == CCollider::ETRIANGLE){
			if (CCollider::Collision(y, m)){
				mForward.mY += 0.5;
			}
		}
	}
	//プレイヤーとの衝突判定
	if (m->mType == CCollider::ESPHERE && y->mType == CCollider::ESPHERE){
		if (y->mpParent->mTag == CCharacter::EPLAYER){
			if (CCollider::Collision(m, y)){
				mEnabled = false;
				
			}
		}
	}
}
void CFall::Update(){
	//落下速度
	mForward.mY -= G;
	mPosition = mPosition + mForward;
}