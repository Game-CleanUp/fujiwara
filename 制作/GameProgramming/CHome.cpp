#include"CHome.h"

int CHome::home = 0;

CHome::CHome(CModel*model, CVector position, CVector rotation, CVector scale)
:mColBody(this, CVector(0.0f, 1.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f),
CVector(1.0f, 1.0f, 1.0f), 10.0f)
{
	//ƒ‚ƒfƒ‹AˆÊ’uA‰ñ“]AŠgk‚ðÝ’è‚·‚é
	mpModel = model; //ƒ‚ƒfƒ‹‚ÌÝ’è
	mPosition = position; //ˆÊ’u‚ÌÝ’è
	mRotation = rotation; //‰ñ“]‚ÌÝ’è
	mScale = scale; //Šgk‚ÌÝ’è
}
//‰Û‘è8
void CHome::Collision(CCollider*m, CCollider*y){
	//[“d
	if (y->mTag == CCollider::EBODY){
		if (CCollider::Collision(m, y)){
			home = 1;
			}

		else{
			home = 0;
		}
	}
}