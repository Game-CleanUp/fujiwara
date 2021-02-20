#include"CBoss.h"
#include"CSceneGame.h"

CBoss::CBoss(CModel*model, CVector position, CVector rotation, CVector scale)
:mColBody(this, CVector(1.0f, 1.5f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), 4.0f)
, mSearch(this, CVector(0.0f, 0.0f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), 20.0f)
, ActFrame(0), state(0), mVelocityJump(0.0f), onlyOnce(true)
{
	//モデル、位置、回転、拡縮を設定する
	mpModel = model; //モデルの設定
	mPosition = position; //位置の設定
	mRotation = rotation; //回転の設定
	mScale = scale; //拡縮の設定

	mColBody.mTag = CCollider::EBODY2;
	mSearch.mTag = CCollider::ESEARCH2;

	SoundTrack.Load("Dog.wav");
	SoundDamage.Load("Edamage.wav");
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

		switch (state){

		case Move_Stop:	//立ち止まる
			ActFrame += 1;
			if (ActFrame >STOPTIME){
				state = rand() % STATERAND;
				ActFrame = 0;
			}
			break;

		case Move_Left:	//左方向に移動
			ActFrame += 1;
			if (ActFrame < 20){
				mRotation.mY += rand() % TURN;
			}
			if (ActFrame > 60){
				mPosition = CVector(0.0f, 0.0f, SPEED)*mMatrix;
			}
			if (ActFrame > 120){
				state = rand() % STATERAND;
				ActFrame = 0;
			}
			break;

		case Move_Right:	//右方向に移動
			ActFrame += 1;
			if (ActFrame < 20){
				mRotation.mY -= rand() % TURN;
			}
			if (ActFrame > 60){
				mPosition = CVector(0.0f, 0.0f, SPEED)*mMatrix;
			}
			if (ActFrame > 120){
				state = rand() % STATERAND;
				ActFrame = 0;
			}
			break;

		case Move_Gomi:	//ゴミを出す
			ActFrame += 1;
			if (ActFrame > 180){
				new CGomi(NULL, mPosition, CVector(), CVector(0.5f, 0.5f, 0.5f));
				state = rand() % STATERAND;
				ActFrame = 0;
			}
			break;

		case Move_TrapTracking:	//トラップ追尾
			if (left.Dot(dir_trap) > 0.0f){
				mRotation.mY += Rote;
			}
			else if (left.Dot(dir_trap) < 0.0f){
				mRotation.mY -= Rote;
			}

			mPosition = mPosition + dir_trap.Normalize() * TRACKSPEED;
			state = rand() % STATERAND;
			break;

		case Move_PlayerTracking:	//プレイヤー追尾
			if (left.Dot(dir_player) > 0.0f){
				mRotation.mY += Rote;
			}
			else if (left.Dot(dir_player) < 0.0f){
				mRotation.mY -= Rote;
			}
			
			if (onlyOnce){
				SoundTrack.Repeat();
				onlyOnce = false;
			}

			mPosition = mPosition + dir_player.Normalize() * TRACKSPEED;
			state = rand() % STATERAND;
			break;

		case Move_Damage:	//ダメージ
			ActFrame += 1;
			if (ActFrame > DAMAGETIME){
				mRotation = CVector(0.0f, 0.0f, 0.0f);	//復帰
				ActFrame = 0;
			
				state = rand() % STATERAND;
			}
			break;
		}

	if (CSceneGame::mBatteryNow <= 0 || CSceneGame::mTimeNow <= 0){
		mEnabled = false;
	}

	mVelocityJump = JUMPV0;
	//重力加速度
	mVelocityJump -= G;

	mPosition.mY = mPosition.mY - mVelocityJump;
	
	CCharacter::Update();
}

void CBoss::Render(){
	CCharacter::Render();

	//CScene::Start2D(0, 800, 0, 600);
	//CText::DrawString("BOW", 400, 300, 25, 25);
	//CScene::End2D();
}

void CBoss::Collision(CCollider*m, CCollider*y){

	//プレイヤー発見
	if (m->mTag == CCollider::ESEARCH2 && y->mTag == CCollider::EBODY){
		if (CCollider::Collision(m, y)){
			if (state != Move_TrapTracking && state != Move_Damage){	//トラップ、ダメージ以外
				state = Move_PlayerTracking;
			}
		}
		else{
			onlyOnce = true;
			SoundTrack.Stop();
		}
	}
	
	//トラップ発見
	if (m->mTag == CCollider::ESEARCH2){
		if (y->mTag == CCollider::ETRAP){
			if (CCollider::Collision(m, y)){
				if (state != Move_Damage){	//ダメージ以外
					state = Move_TrapTracking;
				}
			}
		}
		return;
	}

	//プレイヤー弾との衝突判定
	if (m->mTag == CCollider::EBODY2 && y->mTag == CCollider::EBULLET){
		if (CCollider::Collision(m, y)){
			mPosition = CVector(2.0f, 0.0f, 0.0f)*mMatrix;	//跳ねる
			mRotation = CVector(0.0f, 0.0f, 90.0f);	//横になる
			SoundDamage.Play();
			SoundTrack.Stop();
			onlyOnce = true;
			state = Move_Damage;
		}
	}

	//自身のコライダタイプの判定
	switch (m->mType){
	case CCollider::ESPHERE:
		//相手が三角コライダ
		if (y->mType == CCollider::ETRIANGLE){
			CVector adjust;//調整値ベクトル
			//三角形と球の衝突判定
			if (CCollider::CollisionTriangleSphere(y, m, &adjust)){
				//着地
				mVelocityJump = 0;
			}
			//位置の更新
			mPosition = mPosition - adjust*-1;

			CCharacter::Update();
		}
		break;
	}
}