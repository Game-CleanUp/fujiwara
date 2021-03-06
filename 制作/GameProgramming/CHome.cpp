#include"CHome.h"

int CHome::home = 0;

CHome::CHome(CModel*model, CVector position, CVector rotation, CVector scale)
:mColBody(this, CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(0.2f, 0.2f, 0.2f), 2.0f)
{
	mpModel = model; //モデルの設定
	mPosition = position; //位置の設定
	mRotation = rotation; //回転の設定
	mScale = scale; //拡縮の設定

	mColBody.mTag = CCollider::EHOME;
}

void CHome::TaskCollision()
{
	mColBody.ChangePriority();

	CCollisionManager::Get()->Collision(&mColBody);

}

void CHome::Collision(CCollider*m, CCollider*y){

	//充電エリアにいるか判定
	if (y->mTag == CCollider::EBODY){
		if (CCollider::Collision(m, y)){
			home = true;
		}
		else{
			home = false;
		}
	}
}