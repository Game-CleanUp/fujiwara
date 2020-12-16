#include"CBoss.h"
#include"CSceneGame.h"

CBoss::CBoss(CModel*model, CVector position, CVector rotation, CVector scale)
:mColBody(this, CVector(0.0f, 1.0f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), 4.0f)
, mSearch(this, CVector(0.0f, 0.0f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), 10.0f)
, frame(0), state(0), mVelocityJump(0.0f)
{
	//モデル、位置、回転、拡縮を設定する
	mpModel = model; //モデルの設定
	mPosition = position; //位置の設定
	mRotation = rotation; //回転の設定
	mScale = scale; //拡縮の設定

	mColBody.mTag = CCollider::EBODY2;
	mSearch.mTag = CCollider::ESEARCH2;
}

void CBoss::Update(){

	if (CPlayer::clear < 2){
		if (CSceneGame::mTimeNow > 0){
			switch (state){
			case 0:
				frame += 1;
				if (frame > 30){
					state = rand() % 4;
					frame = 0;
				}
				break;

			case 1:
				frame += 1;
				if (frame < 20){
					//左回転
					mRotation.mY += rand() % 13;
				}
				if (frame > 30){
					//前進
					mPosition = CVector(0.0f, 0.0f, 0.5f)*mMatrix;
				}
				if (frame > 50){
					state = rand() % 4;
					frame = 0;
				}
				break;

			case 2:
				frame += 1;
				if (frame < 20){
					//右回転
					mRotation.mY -= rand() % 13;
				}
				if (frame > 30){
					//前進
					mPosition = CVector(0.0f, 0.0f, 0.5f)*mMatrix;
				}
				if (frame > 50){
					state = rand() % 4;
					frame = 0;
				}
				break;

			case 3:
				frame += 1;
				if (frame > 90){
					state = rand() % 4;
					frame = 0;
				}
				break;
			}
		}

		//重力
		mVelocityJump -= G;
		//移動
		mPosition.mY = mPosition.mY + mVelocityJump;
		CCharacter::Update();
	}
}


void CBoss::Collision(CCollider*m, CCollider*y){

	//追尾(プレイヤーがサーチに入ると)
	if (m->mTag == CCollider::ESEARCH2){
		if (CCollider::Collision(m, y)){
			if (y->mTag == CCollider::ESEARCH){
				//プレイヤーの方向
				CVector dir = y->mpParent->mPosition - mPosition;
				//正規化（長さを1にする）Normalize()
				mPosition = mPosition + dir.Normalize()*0.5;
			}
		}
		return;
	}

	//自身のコライダタイプの判定
	switch (m->mType){
	case CCollider::ESPHERE://球コライダ
		//相手のコライダが三角コライダの時
		if (y->mType == CCollider::ETRIANGLE){
			CVector adjust;//調整値ベクトル
			//三角形と球の衝突判定
			if (CCollider::CollisionTriangleSphere(y, m, &adjust)){
				mRotation = CVector(5.0f, 0.0f, 0.0f)*mMatrix;
			}
			//位置の更新
			mPosition = mPosition - adjust*-1;

			//行列の更新
			CCharacter::Update();
		}
		break;
	}

	if (y->mTag == CCollider::EBODY){
		CVector dir = y->mpParent->mPosition - mPosition;
		mPosition = mPosition - dir.Normalize()*1.0;
	}
}