#include"CHome.h"

int CHome::home = 0;

CHome::CHome(CModel*model, CVector position, CVector rotation, CVector scale)
:mColBody(this, CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(0.2f, 0.2f, 0.2f), 2.0f)
{
	mpModel = model; //ƒ‚ƒfƒ‹‚ÌÝ’è
	mPosition = position; //ˆÊ’u‚ÌÝ’è
	mRotation = rotation; //‰ñ“]‚ÌÝ’è
	mScale = scale; //Šgk‚ÌÝ’è

	mColBody.mTag = CCollider::EHOME;
}

void CHome::TaskCollision()
{
	mColBody.ChangePriority();

	CCollisionManager::Get()->Collision(&mColBody);

}

void CHome::Collision(CCollider*m, CCollider*y){

	//[“dƒGƒŠƒA‚É‚¢‚é‚©”»’è
	if (y->mTag == CCollider::EBODY){
		if (CCollider::Collision(m, y)){
			home = true;
		}
		else{
			home = false;
		}
	}
}