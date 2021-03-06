#include"CPlayer.h"
#include"CSceneGame.h"
#include"CEffect.h"

int CPlayer::Score = 0;
int CPlayer::Down = 0;

CPlayer *CPlayer::mpPlayer = 0;

CSound CPlayer::SoundJump;
CSound CPlayer::SoundBomb;
CSound CPlayer::SoundAttack;
CSound CPlayer::SoundThrow;

//スマートポインタの外部参照
extern std::shared_ptr<CTexture>TextureExp(new CTexture());

CPlayer::CPlayer()
:mColBody(this, CVector(0.0f, 0.5f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), 1.5f)
//サーチ
, mSearch(this, CVector(0.0f, -3.0f, 5.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), R)
, mVelocityJump(0.0f), frameRetry(0), onlyOnce(true)
{

	mColBody.mTag = CCollider::EBODY;
	mSearch.mTag = CCollider::ESEARCH;

	SoundJump.Load("jump.wav");	//ジャンプ音
	SoundBomb.Load("Bomb.wav");	//爆発音
	SoundAttack.Load("shoot.wav");	//攻撃音
	SoundThrow.Load("throw.wav");	//ゴミ回収

	//爆発テクスチャ
	TextureExp->Load("exp.tga");

	mpPlayer = this;

}

void CPlayer::TaskCollision()
{
	mColBody.ChangePriority();
	mSearch.ChangePriority();
	CCollisionManager::Get()->Collision(&mColBody);
	CCollisionManager::Get()->Collision(&mSearch);
}

void CPlayer::Update(){

	if (Down == false){
		if (CSceneGame::mBatteryNow > 0 && CSceneGame::mTimeNow > 0){

			if (CKey::Push('A')){
				mRotation.mY += DIR;
			}

			if (CKey::Push('D')){
				mRotation.mY -= DIR;
			}

			if (CKey::Push('W')){
				mPosition = CVector(0.0f, 0.0f, FORWARD)*mMatrix;
				//ダッシュ
				if (CKey::Push(VK_SHIFT)){
					mPosition = CVector(0.0f, 0.0f, DASH)*mMatrix;
					CSceneGame::mBatteryNow -= 10;	//バッテリー消費
				}
			}

			if (CKey::Push('S')){
				mPosition = CVector(0.0f, 0.0f, BACK)*mMatrix;
			}

			//スペースキー入力で発射
			if (mVelocityJump == 0){	//ジャンプ中無効
				if (CKey::Once(VK_SPACE)){
					CBullet*bullet = new CBullet();
					bullet->Set(0.2f, 5.0f);	//弾のサイズ
					bullet->mPosition = CVector(0.0f, -0.1f, 0.0f)*mMatrix;
					bullet->mRotation = mRotation;
					bullet->mTag = CCharacter::EBULLET;
					SoundAttack.Play();
					CSceneGame::mBatteryNow -= 300;	//バッテリー消費
				}
			}

			//トラップ設置
			if (CTrap::TrapCount > 0){
				if (CKey::Once('Q')){
					new CTrap(NULL, mPosition, CVector(), CVector(0.3f, 0.3f, 0.3f));
					SoundThrow.Play();
					CTrap::TrapCount -= 1;	//トラップ消費
				}
			}
			//ジャンプ
			if (CKey::Once('J') && mVelocityJump == 0){
				mVelocityJump = JUMPV0;
				CSceneGame::mBatteryNow -= 300;	//バッテリー消費
				SoundJump.Play();
			}

			//ゴミを捨てる,スコア加算(ホームにいるとき、ゴミを持っているとき)
			if (CHome::home == true && CGomi::GomiCount > 0){
				if (CKey::Once('E')){
					if (CGomi::GomiCount == GomiLimit){	//ゴミ最大所持の時タイムを加算
						CSceneGame::mTimeNow += TIMEADD;
					}

					Score = Score + CGomi::GomiCount;
					SoundThrow.Play();
					CGomi::GomiCount = 0;
				}
			}
		}
	}

	//重力加速度
	mVelocityJump -= G;
	//移動
	mPosition.mY = mPosition.mY + mVelocityJump;

	if (CHome::home == true){
		onlyOnce = true;
	}

	CCharacter::Update();
}

void CPlayer::Render(){
	CCharacter::Render();
	Back.Render();
	Battery.Render();
	Time.Render();
	TrapUi.Render();
	GomiUI.Render();
}

void CPlayer::Collision(CCollider*m, CCollider*y){

	if (m->mTag == CCollider::ESEARCH){
		return;
	}

	switch (m->mType){
	case CCollider::ESPHERE://球コライダ
		//相手が三角コライダ
		if (y->mType == CCollider::ETRIANGLE){
			CVector adjust;//調整値ベクトル
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

	//ボスとの衝突
	if (m->mTag == CCollider::EBODY && y->mTag == CCollider::EBODY2){
		if (CCollider::Collision(m, y)){

			frameRetry++;	//復帰までの時間
			Down = true;

			if (onlyOnce){
				SoundBomb.Play();	//爆発音
				onlyOnce = false;
			}

			//エフェクト生成(爆発)
			new CEffect(mPosition, 10.0f, 10.0f, TextureExp, 4, 4, 1);

			//持っているゴミを周りに出現させる
			switch (CGomi::GomiCount){

			case 1:
				//プレイヤーの周りに出現
				for (int i = 0; i < 1; i++){
					new CGomi(NULL, mPosition + CVector(0.0f, 15.0f, DROP)*matrix.RotateY(DROP_DIR), CVector(), CVector(0.5f, 0.5f, 0.5f));
				}
				CGomi::GomiCount = 0;
				break;

			case 2:
				for (int i = 0; i < 2; i++){
					new CGomi(NULL, mPosition + CVector(0.0f, 15.0f, DROP)*matrix.RotateY(DROP_DIR), CVector(), CVector(0.5f, 0.5, 0.5f));
				}
				CGomi::GomiCount = 0;
				break;

			case 3:
				for (int i = 0; i < 3; i++){
					new CGomi(NULL, mPosition + CVector(0.0f, 15.0f, DROP)*matrix.RotateY(DROP_DIR), CVector(), CVector(0.5f, 0.5, 0.5f));
				}
				CGomi::GomiCount = 0;
				break;

			case 4:
				for (int i = 0; i < 4; i++){
					new CGomi(NULL, mPosition + CVector(0.0f, 15.0f, DROP)*matrix.RotateY(DROP_DIR), CVector(), CVector(0.5f, 0.5, 0.5f));
				}
				CGomi::GomiCount = 0;
				break;

			case 5:
				for (int i = 0; i < 5; i++){
					new CGomi(NULL, mPosition + CVector(0.0f, 15.0f, DROP)*matrix.RotateY(DROP_DIR), CVector(), CVector(0.5f, 0.5, 0.5f));
				}
				CGomi::GomiCount = 0;
				break;
			}

			//リトライ(初期位置に戻る)
			if (frameRetry >= RETRY){
				//初期位置
				mPosition = CVector(71.0f, 10.0f, 51.0f);
				mRotation = CVector(0.0f, 225.0f, 0.0f);
				CSceneGame::mBatteryNow = CSceneGame::mBatteryMax;
				Down = false;
				frameRetry = 0;
			}
		}
	}
}