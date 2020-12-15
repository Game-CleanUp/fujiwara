#include"CGomi.h"

int CGomi::GomiCount = 0;

//課題7
CGomi::CGomi(CModel*model, CVector position, CVector rotation, CVector scale)
:mColBody(this, CVector(0.0f, 1.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f),
CVector(1.0f, 1.0f, 1.0f), 1.0f)
{
	//モデル、位置、回転、拡縮を設定する
	mpModel = model; //モデルの設定
	mPosition = position; //位置の設定
	mRotation = rotation; //回転の設定
	mScale = scale; //拡縮の設定
}

//課題8
void CGomi::Collision(CCollider*m, CCollider*y){

	if (GomiCount < 5){
		//相手がプレイヤー
		if (y->mTag == CCollider::EBODY){
			//衝突
			if (CCollider::Collision(m, y)){
				//衝突しているときは無効にする
				mEnabled = false;
				GomiCount += 1;
			}
		}
		//引き寄せ
		if (y->mTag == CCollider::ESEARCH){
			if (CCollider::Collision(m, y)){
				//プレイヤーの方向
				CVector dir = y->mpParent->mPosition - mPosition;
				//正規化（長さを1にする）Normalize()
				mPosition = mPosition + dir.Normalize()*1.0;
			}
		}
	}
}