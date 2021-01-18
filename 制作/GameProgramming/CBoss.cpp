#include"CBoss.h"
#include"CSceneGame.h"

int CBoss::tracking = 0;
CSound CBoss::Sound;

CBoss::CBoss(CModel*model, CVector position, CVector rotation, CVector scale)
:mColBody(this, CVector(0.0f, 0.0f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), 3.0f)
, mSearch(this, CVector(0.0f, 0.0f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), 50.0f)	
, frame(0), state(0), mVelocityJump(0.0f)
{
	//モデル、位置、回転、拡縮を設定する
	mpModel = model; //モデルの設定
	mPosition = position; //位置の設定
	mRotation = rotation; //回転の設定
	mScale = scale; //拡縮の設定

	mColBody.mTag = CCollider::EBODY2;
	mSearch.mTag = CCollider::ESEARCH2;

	Sound.Load("Dog.wav");
}

void CBoss::TaskCollision()
{
	mColBody.ChangePriority();
	mSearch.ChangePriority();
	CCollisionManager::Get()->Collision(&mColBody);
	CCollisionManager::Get()->Collision(&mSearch);
}




void CBoss::Update(){

	if (CPlayer::clear < GAMECLEAR){
		if (CSceneGame::mBatteryNow > 0){
			//追尾してないとき
			if (tracking == FALSE){
				switch (state){
				case 0:
					frame += 1;
					if (frame > 30){
						state = rand() % 5;
						frame = 0;
					}
					break;

				case 1:
					frame += 1;
					if (frame < 20){
						//左回転
						mRotation.mY += rand() % TURN;
					}
					if (frame > 30){
						//前進
						mPosition = CVector(SPEED, 0.0f, 0.0f)*mMatrix;
					}
					if (frame > 90){
						state = rand() % 5;
						frame = 0;
					}
					break;

				case 2:
					frame += 1;
					if (frame < 20){
						//右回転
						mRotation.mY -= rand() % TURN;
					}
					if (frame > 30){
						//前進
						mPosition = CVector(SPEED, 0.0f, 0.0f)*mMatrix;
					}
					if (frame > 90){
						state = rand() % 5;
						frame = 0;
					}
					break;

				case 3:
					frame += 1;
					if (frame > 60){
						state = rand() % 5;
						frame = 0;
					}
					break;

				case 4:
					frame += 1;
					if (frame > 30){
						state = rand() % 5;
						frame = 0;
					}
					break;
				}
			}
		}
	}

	mVelocityJump = JUMPV0;
	//重力加速度
	mVelocityJump -= G;
	//移動
	mPosition.mY = mPosition.mY - mVelocityJump;

	CCharacter::Update();
}

void CBoss::Collision(CCollider*m, CCollider*y){

	//追尾(プレイヤーがサーチに入ると)
	if (m->mTag == CCollider::ESEARCH2){
		if (y->mTag == CCollider::EBODY){
			if (CCollider::Collision(m, y)){
				//プレイヤー本体の方向
				CVector dir = y->mpParent->mPosition - mPosition;
				CVector left = CVector(1.0f, 0.0f, 0.0f)  * CMatrix().RotateY(mRotation.mY);
				CVector right = CVector(-1.0f, 0.0f, 0.0f) * CMatrix().RotateY(mRotation.mY);

				if (left.Dot(dir) > 0.0f){
					mRotation.mY += 2.0f;
				}
				else if (left.Dot(dir) < 0.0f){
					mRotation.mY -= 2.0f;
				}

				//正規化（長さを1にする）Normalize()
				mPosition = mPosition + dir.Normalize() * 0.3;
				Sound.Play();
				tracking = TRUE;
			}
		}
		else{
			//追尾をやめる
			tracking = FALSE;
			Sound.Stop();
		}
		return;
	}
	
	//プレイヤー弾との衝突判定
	if (m->mTag == CCollider::EBODY2){
		if (y->mTag == CCollider::EBULLET){
			if (CCollider::Collision(m, y)){
				CVector dir = y->mpParent->mPosition - mPosition;
				//正規化（長さを1にする）Normalize()
				mPosition = mPosition + dir.Normalize() * 0.5;	//機体から遠ざける
			}
		}
	}

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
}