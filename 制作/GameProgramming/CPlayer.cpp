#include"CPlayer.h"
#include"CSceneGame.h"

int CPlayer::Life = 100;
int CPlayer::clear = 0;
int CPlayer::Dash = 0;
int CPlayer::Jump = 0;
int CPlayer::Esc = 0;
CPlayer *CPlayer::mpPlayer = 0;


CPlayer::CPlayer()
:mColBody(this, CVector(0.0f, 1.0f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), 1.5f)
//サーチ
, mSearch(this, CVector(0.0f, 0.0f, -1.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), R)
, mVelocityJump(0.0f)
, frame(0), level(100)
{

	mColBody.mTag = CCollider::EBODY;
	mSearch.mTag = CCollider::ESEARCH;

	HP.x = -240;
	HP.y = -280;
	HP.w = 150;
	HP.h = 10;

}


void CPlayer::Update(){

	if (clear < 2){
		if (CSceneGame::mTimeNow > 0){
			if (CKey::Push('A')){
				mRotation.mY += 2.0f;
			}

			if (CKey::Push('D')){
				mRotation.mY -= 2.0f;
			}

			if (CKey::Push('W')){
				mPosition = CVector(0.0f, 0.0f, 0.5f)*mMatrix;
				//ダッシュ
				if (CKey::Push(VK_SHIFT)){
					mPosition = CVector(0.0f, 0.0f, 1.0f)*mMatrix;
					Dash = TRUE;
				}
				else{
					Dash = FALSE;
				}
			}

			if (CKey::Push('S')){
				mPosition = CVector(0.0f, 0.0f, -0.5f)*mMatrix;
			}

			if (CKey::Once('J') /*&& mVelocityJump == 0*/){
				mVelocityJump = JUMPV0;
				Jump = TRUE;
			}
			else{
				Jump = FALSE;
			}

			if (CKey::Once('H')){
				Esc = TRUE;
			}

			//アイテム使用(パワー)
			frame += 1;
			if (CPower::power >= 1){
				if (CKey::Once('Q')){
					mSearch.mRadius = R + 4.0f;
					CPower::power -= 1;
				}
			}
			//5秒で効果切れ
			if (frame > 300){
				mSearch.mRadius = R;
				frame = 0;
			}

			//ゴミ回収
			if (CHome::home == TRUE){
				if (CKey::Push(VK_SPACE)){
					clear = clear + CGomi::GomiCount;
					CGomi::GomiCount = 0;
				}
			}
		}
		//重力加速度
		mVelocityJump -= G;
		//移動
		mPosition.mY = mPosition.mY + mVelocityJump;


		CCharacter::Update();
	}
}

void CPlayer::Render(){
	CCharacter::Render();
	Back.Render();
	HP.Render();

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
			}

			//位置の更新
			mPosition = mPosition - adjust*-1;

			//行列の更新
			CCharacter::Update();
		}

		break;
	}

	if (y->mTag == CCollider::EPOWER){
		if (CCollider::Collision(m, y)){
			CPower::power += 1;
		}
	}
}
