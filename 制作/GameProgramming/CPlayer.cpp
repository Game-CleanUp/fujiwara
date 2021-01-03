#include"CPlayer.h"
#include"CSceneGame.h"

int CPlayer::clear = 0;
int CPlayer::Dash = 0;
int CPlayer::Jump = 0;
int CPlayer::Down = 0;
CPlayer *CPlayer::mpPlayer = 0;

CSound CPlayer::Sound;
CSound CPlayer::Sound2;

CPlayer::CPlayer()
:mColBody(this, CVector(0.0f, 2.0f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), 2.5f)
//サーチ
, mSearch(this, CVector(0.0f, 0.0f, 5.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), R)
, mVelocityJump(0.0f)
, frame(0), level(100), frameMax(300), frame2(0)
{

	mColBody.mTag = CCollider::EBODY;
	mSearch.mTag = CCollider::ESEARCH;
	Sound.Load("jump.wav");
	Sound2.Load("act.wav");
}

void CPlayer::TaskCollision()
{
	mColBody.ChangePriority();
	mSearch.ChangePriority();
	CCollisionManager::Get()->Collision(&mColBody);
	CCollisionManager::Get()->Collision(&mSearch);
}



void CPlayer::Update(){

	if (Down == FALSE){
		if (clear < GAMECLEAR){
			if (CSceneGame::mBatteryNow > 0){
				if (CSceneGame::mTimeNow > 0){
					if (CKey::Push('A')){
						mRotation.mY += DIRECTION;
					}

					if (CKey::Push('D')){
						mRotation.mY -= DIRECTION;
					}

					if (CKey::Push('W')){
						mPosition = CVector(0.0f, 0.0f, FORWARD)*mMatrix;
						//ダッシュ
						if (CKey::Push(VK_SHIFT)){
							mPosition = CVector(0.0f, 0.0f, DASH)*mMatrix;
							Dash = TRUE;
						}
						else{
							Dash = FALSE;
						}
					}

					if (CKey::Push('S')){
						mPosition = CVector(0.0f, 0.0f, BACK)*mMatrix;
						//ダッシュ
						if (CKey::Push(VK_SHIFT)){
							mPosition = CVector(0.0f, 0.0f, -0.8f)*mMatrix;
							Dash = TRUE;
						}
						else{
							Dash = FALSE;
						}
					}
					//ジャンプ
					if (CKey::Once('J') && mVelocityJump == 0){
						mVelocityJump = JUMPV0;
						Jump = TRUE;
						Sound.Play();
					}

					//回避
					if (CKey::Once('H')){
						mSearch.mRadius = R - 7.0f;
					}

					//アイテム使用(パワー)
					if (frameMax > frame){
						frame += 1;
					}
					
					//4秒で効果切れ
					if (frame > 240){
						mSearch.mRadius = R;
						frame = 0;
					}

					//ゴミ回収
					if (CHome::home == TRUE){
						if (CKey::Once('E')){
							clear = clear + CGomi::GomiCount;
							CGomi::GomiCount = 0;
							CSceneGame::mTimeNow += 5 * 60;
						}
					}
				}
			}
		}
	}
	//重力加速度
	mVelocityJump -= G;
	//移動
	mPosition.mY = mPosition.mY + mVelocityJump;

	CCharacter::Update();
}
	

void CPlayer::Render(){
	CCharacter::Render();
	Back.Render();
	Battery.Render();
	Time.Render();
}



void CPlayer::Collision(CCollider*m, CCollider*y){
	if (m->mTag == CCollider::ESEARCH){
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
				//着地
				mVelocityJump = 0;
				Jump = FALSE;
			//	mPosition = CVector(-120.0f, 10.0f, -80.0f);
				//mPosition = CVector(-50.0f, 10.0f, -80.0f);
			}

			//位置の更新
			mPosition = mPosition - adjust*-1;

			//行列の更新
			CCharacter::Update();
		}

		break;
	}

	//ボスとの衝突
	if (m->mTag == CCollider::EBODY){
		if (y->mTag == CCollider::EBODY2){
			if (CCollider::Collision(m, y)){
				CSceneGame::mBatteryNow++;
				frame2++;
				Down = TRUE;
				//持っているゴミを周りに出現させる
				switch (CGomi::GomiCount){

				case 1:
					//プレイヤーの周りに出現
					for (int i = 0; i < 1; i++){
						new CGomi(NULL, mPosition + CVector(0.0f, 15.0f, DROP)*matrix.RotateY(DROP_RAND), CVector(), CVector(1.0f, 1.0f, 1.0f));
					}
					CGomi::GomiCount = 0;
					break;

				case 2:
					for (int i = 0; i < 2; i++){
						new CGomi(NULL, mPosition + CVector(0.0f, 15.0f, DROP)*matrix.RotateY(DROP_RAND), CVector(), CVector(1.0f, 1.0f, 1.0f));
					}
					CGomi::GomiCount = 0;
					break;

				case 3:
					for (int i = 0; i < 3; i++){
						new CGomi(NULL, mPosition + CVector(0.0f, 15.0f, DROP)*matrix.RotateY(DROP_RAND), CVector(), CVector(1.0f, 1.0f, 1.0f));
					}
					CGomi::GomiCount = 0;
					break;

				case 4:
					for (int i = 0; i < 4; i++){
						new CGomi(NULL, mPosition + CVector(0.0f, 15.0f, DROP)*matrix.RotateY(DROP_RAND), CVector(), CVector(1.0f, 1.0f, 1.0f));
					}
					CGomi::GomiCount = 0;
					break;

				case 5:
					for (int i = 0; i < 5; i++){
						new CGomi(NULL, mPosition + CVector(0.0f, 15.0f, DROP)*matrix.RotateY(DROP_RAND), CVector(), CVector(1.0f, 1.0f, 1.0f));
					}
					CGomi::GomiCount = 0;
					break;
				}

				//リトライ(ホームに戻る)
				if (frame2 > RETRY){
					//初期位置
					mPosition = CVector(-120.0f, 10.0f, -80.0f);
					CSceneGame::mBatteryNow = CSceneGame::mBatteryMax;
					Down = FALSE;
					frame2 = 0;
				}
			}
		}
	}
}