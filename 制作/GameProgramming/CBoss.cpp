#include"CBoss.h"
#include"CSceneGame.h"


CSound CBoss::Sound;

CBoss::CBoss(CModel*model, CVector position, CVector rotation, CVector scale)
:mColBody(this, CVector(0.0f, 1.0f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), 3.0f)
, mSearch(this, CVector(0.0f, 0.0f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), 50.0f)	
, ActFrame(0), state(0), mVelocityJump(0.0f), EnemyDown(0), DownFrame(0), traptracking(0)
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

	CVector dir_player = CPlayer::mpPlayer->mPosition - mPosition;	//プレイヤー方向
	CVector dir_trap = CTrap::mpTrap->mPosition - mPosition;	//トラップ方向

	CVector left = CVector(1.0f, 0.0f, 0.0f)  * CMatrix().RotateY(mRotation.mY);

	float Rote = 4.0f;	//追尾対象に方向転換

	if (CPlayer::clear < GAMECLEAR){
		switch (state){

		case 0:	//立ち止まる
			ActFrame += 1;
			if (ActFrame > 30){
				state = rand() % STATERAND;
				ActFrame = 0;
			}
			break;

		case 1:	//左方向に移動
			ActFrame += 1;
			if (ActFrame < 20){
				//左回転
				mRotation.mY += rand() % TURN;
			}
			if (ActFrame > 60){
				//前進
				mPosition = CVector(0.0f, 0.0f, SPEED)*mMatrix;
			}
			if (ActFrame > 120){
				state = rand() % STATERAND;
				ActFrame = 0;
			}
			break;

		case 2:	//右方向に移動
			ActFrame += 1;
			if (ActFrame < 20){
				//右回転
				mRotation.mY -= rand() % TURN;
			}
			if (ActFrame > 60){
				//前進
				mPosition = CVector(0.0f, 0.0f, SPEED)*mMatrix;
			}
			if (ActFrame > 120){
				state = rand() % STATERAND;
				ActFrame = 0;
			}
			break;

		case 3:	//立ち止まる
			ActFrame += 1;
			if (ActFrame > 60){
				state = rand() % STATERAND;
				ActFrame = 0;
			}
			break;

		case 4:	//ゴミを出す
			ActFrame += 1;
			if (ActFrame > 90){
				new CGomi(NULL, mPosition, CVector(), CVector(0.5f, 0.5f, 0.5f));
				state = rand() % STATERAND;
				ActFrame = 0;
			}
			break;

		case 5:	//トラップ追尾
			if (left.Dot(dir_trap) > 0.0f){
				mRotation.mY += Rote;
			}
			else if (left.Dot(dir_trap) < 0.0f){
				mRotation.mY -= Rote;
			}

			//正規化（長さを1にする）Normalize()
			mPosition = mPosition + dir_trap.Normalize() * 0.3;
			state = rand() % STATERAND;
			break;

		case 6:
			//プレイヤー追尾
			if (left.Dot(dir_player) > 0.0f){
				mRotation.mY += Rote;
			}
			else if (left.Dot(dir_player) < 0.0f){
				mRotation.mY -= Rote;
			}
			

			//正規化（長さを1にする）Normalize()
			mPosition = mPosition + dir_player.Normalize() * 0.3;
			state = rand() % STATERAND;
			break;

		case 7:	//気絶
			ActFrame += 1;
			if (ActFrame > 120){
				mRotation = CVector(0.0f, 0.0f, 0.0f);	//復帰
				ActFrame = 0;
				state = rand() % STATERAND;
			}
			break;
		}
	}

	if (CSceneGame::mBatteryNow <= 0 || CSceneGame::mTimeNow <= 0){
		mEnabled = false;
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
	if (m->mTag == CCollider::ESEARCH2 && y->mTag == CCollider::EBODY){
		if (CCollider::Collision(m, y)){
			if (state != 5 && state != 7){	//トラップ、気絶以外
				state = 6;	//プレイヤー追尾へ
				Sound.Repeat();
			}
		}
	}
	
	//トラップとの衝突
	if (m->mTag == CCollider::ESEARCH2){
		if (y->mTag == CCollider::ETRAP){
			if (CCollider::Collision(m, y)){
				if (state != 7){	//気絶以外
					state = 5;	//トラップ誘導へ
				}
			}
		}
		return;
	}

	//プレイヤー弾との衝突判定
	if (m->mTag == CCollider::EBODY2 && y->mTag == CCollider::EBULLET){
		if (CCollider::Collision(m, y)){
			mRotation = CVector(0.0f, 0.0f, 90.0f);	//横になる
			//Sound.Play();
			state = 7;	//気絶へ
			
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