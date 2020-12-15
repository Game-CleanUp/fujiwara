#include"CBoss.h"


CBoss::CBoss(CModel*model, CVector position, CVector rotation, CVector scale)
:mColBody(this, CVector(0.0f, 1.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f),
CVector(1.0f, 1.0f, 1.0f), 4.0f)
{
	//モデル、位置、回転、拡縮を設定する
	mpModel = model; //モデルの設定
	mPosition = position; //位置の設定
	mRotation = rotation; //回転の設定
	mScale = scale; //拡縮の設定
}


void CBoss::Update(){
	//位置を移動
	//CVector dir = CPlayer::mpPlayer->mPosition - mPosition;
	/*CVector left = CVector(1.0f, 0.0f, 0.0f)  * CMatrix().RotateY(mRotation.mY);
	CVector right = CVector(-1.0f, 0.0f, 0.0f) * CMatrix().RotateY(mRotation.mY);
	if (left.Dot(dir) > 0.0f){
		mRotation.mY += 1.0f;
	}
	else if (left.Dot(dir) < 0.0f){
		mRotation.mY -= 1.0f;
	}
*/
	mPosition = CVector(0.0f, 1.0f, 0.0f);

	//行列を更新
	CCharacter::Update();

}



void CBoss::Collision(CCollider*m, CCollider*y){

	//自身のコライダタイプの判定
	switch (m->mType){
	case CCollider::ESPHERE://球コライダ
		//相手のコライダが三角コライダの時
		if (y->mType == CCollider::ETRIANGLE){
			CVector adjust;//調整値ベクトル
			//三角形と球の衝突判定
			if (CCollider::CollisionTriangleSphere(y, m, &adjust)){

			}
			//位置の更新
			mPosition = mPosition - adjust*-1;

			//行列の更新
			CCharacter::Update();
		}
		break;
	}

	//プレイヤーとの衝突判定
	if (y->mTag == CCollider::EBODY){
		if (CCollider::Collision(m, y)){
			mEnabled = false;
		}
	}

	////引き寄せ
	//if (y->mTag == CCollider::ESEARCH){
	//	if (CCollider::Collision(m, y)){
	//		//プレイヤーの方向
	//		CVector dir = y->mpParent->mPosition - mPosition;
	//		//正規化（長さを1にする）Normalize()
	//		mPosition = mPosition + dir.Normalize()*1.5;
	//	}
	//}
}