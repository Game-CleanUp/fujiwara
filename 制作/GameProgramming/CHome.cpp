#include"CHome.h"

int CHome::home = 0;

void CHome::TaskCollision()
{
	mColBody.ChangePriority();

	CCollisionManager::Get()->Collision(&mColBody);
	
}

CHome::CHome(CModel*model, CVector position, CVector rotation, CVector scale)
:mColBody(this, CVector(0.0f, 1.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f),
CVector(1.0f, 1.0f, 1.0f), 10.0f)
{
	mpModel = model; //モデルの設定
	mPosition = position; //位置の設定
	mRotation = rotation; //回転の設定
	mScale = scale; //拡縮の設定

	mColBody.mTag = CCollider::EHOME;
}

void CHome::Collision(CCollider*m, CCollider*y){
	//充電
	if (y->mTag == CCollider::EBODY){
		if (CCollider::Collision(m, y)){
			home = true;
			}

		else{
			home = false;
		}
	}
}