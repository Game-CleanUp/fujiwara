#include"CGomi.h"


int CGomi::GomiCount = 0;
CModel CGomi::mModel;

CSound CGomi::Sound;

CGomi::CGomi(CModel*model, CVector position, CVector rotation, CVector scale)
:mColBody(this, CVector(0.0f, 1.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 3.0f)
{
	//モデル、位置、回転、拡縮を設定する
	mpModel = model; //モデルの設定
	mPosition = position; //位置の設定
	mRotation = rotation; //回転の設定
	mScale = scale; //拡縮の設定

	//モデルが無いときは読み込む
	if (mModel.mTriangles.size() == 0)
	{
		mModel.Load("Rock1.obj", "Rock1.mtl");
	}
	//モデルのポインタ設定
	mpModel = &mModel;

	Sound.Load("gomi.wav");

}


void CGomi::TaskCollision()
{
	mColBody.ChangePriority();

	CCollisionManager::Get()->Collision(&mColBody);

}


void CGomi::Update(){

	mVelocityJump = JUMPV0;
	//重力加速度
	mVelocityJump -= 9.8f / 30.0f;
	//移動
	mPosition.mY = mPosition.mY - mVelocityJump;

	CCharacter::Update();
}

void CGomi::Collision(CCollider*m, CCollider*y){


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

	//ゴミ保有数上限で無効
	if (GomiCount < 5){
		//相手がプレイヤー
		if (y->mTag == CCollider::EBODY){
			if (CCollider::Collision(m, y)){
				//衝突しているときは無効にする
				mEnabled = false;
				Sound.Play();
				GomiCount += 1;
			}
		}
		//引き寄せ(プレイヤーのサーチに当たった時)
		if (y->mTag == CCollider::ESEARCH){
			if (CCollider::Collision(m, y)){
				//プレイヤーの方向
				CVector dir = y->mpParent->mPosition - mPosition;
				//正規化（長さを1にする）Normalize()
				mPosition = mPosition + dir.Normalize()*1.5;
				
			}
		}
	}
}
