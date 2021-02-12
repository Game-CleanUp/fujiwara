#include"CPlayer.h"
#include"CSceneGame.h"
#include"CEffect.h"

int CPlayer::Score = 0;
int CPlayer::Down = 0;

CPlayer *CPlayer::mpPlayer = 0;

CSound CPlayer::Sound;
CSound CPlayer::Sound2;
CSound CPlayer::Sound3;
CSound CPlayer::Sound4;

//スマートポインタの外部参照
extern std::shared_ptr<CTexture>TextureExp(new CTexture());

CPlayer::CPlayer()
:mColBody(this, CVector(0.0f, 0.0f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), 2.0f)
//サーチ
, mSearch(this, CVector(0.0f, -3.0f, 5.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), R)
, mVelocityJump(0.0f)
, frame(0), frameMax(300), frame2(0), state(0), onlyOnce(true)
{

	mColBody.mTag = CCollider::EBODY;
	mSearch.mTag = CCollider::ESEARCH;

	Sound.Load("jump.wav");	//ジャンプ音
	Sound2.Load("Bomb.wav");	//爆発音
	Sound3.Load("shoot.wav");	//攻撃音
	Sound4.Load("throw.wav");	//ゴミ回収

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
					CSceneGame::mBatteryNow -= 10;
				}
			}

			if (CKey::Push('S')){
				mPosition = CVector(0.0f, 0.0f, BACK)*mMatrix;
			}

			//スペースキー入力で発射
			if (mVelocityJump == 0){	//ジャンプ中無効
				if (CKey::Once(VK_SPACE)){
					CBullet*bullet = new CBullet();
					bullet->Set(0.3f, 2.0f);	//弾のサイズ
					bullet->mPosition = CVector(0.0f, 0.0f, 0.0f)*mMatrix;
					bullet->mRotation = mRotation;
					bullet->mTag = CCharacter::EBULLET;
					Sound3.Play();
					CSceneGame::mBatteryNow -= 100;	//バッテリー消費
				}
			}

			//トラップ設置
			if (CTrap::TrapCount > 0){
				if (CKey::Once('Q')){
					new CTrap(NULL, mPosition, CVector(), CVector(0.7f, 0.7f, 0.7f));
					CTrap::TrapCount -= 1;	//トラップ消費
				}
			}
			//ジャンプ
			if (CKey::Once('J') && mVelocityJump == 0){
				mVelocityJump = JUMPV0;
				CSceneGame::mBatteryNow -= 300;	//バッテリー消費
				Sound.Play();
			}

			//ゴミを捨てる,スコア加算(ホームにいるとき、ゴミを持っているとき)
			if (CHome::home == true && CGomi::GomiCount > 0){
				if (CKey::Once('E')){
					Score += 1;
					Sound4.Play();
					CGomi::GomiCount -= 1;
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
	if (m->mTag==CCollider::EBODY && y->mTag == CCollider::EBODY2){
		if (CCollider::Collision(m, y)){

			frame2++;	//復帰までの時間
			Down = true;

			if (onlyOnce){
				Sound2.Play();	//爆発音
				onlyOnce = false;
			}

			//エフェクト生成(爆発)
			new CEffect(mPosition, 10.0f, 10.0f, TextureExp, 4, 4, 1);

			//持っているゴミを周りに出現させる
			switch (CGomi::GomiCount){

			case 1:
				//プレイヤーの周りに出現
				for (int i = 0; i < 1; i++){
					new CGomi(NULL, mPosition + CVector(0.0f, 15.0f, DROP)*matrix.RotateY(DROP_DIR), CVector(), CVector(1.0f, 1.0f, 1.0f));
					CGomi::StageGomi += 1;
				}
				CGomi::GomiCount = 0;
				break;

			case 2:
				for (int i = 0; i < 2; i++){
					new CGomi(NULL, mPosition + CVector(0.0f, 15.0f, DROP)*matrix.RotateY(DROP_DIR), CVector(), CVector(1.0f, 1.0f, 1.0f));
					CGomi::StageGomi += 2;
				}
				CGomi::GomiCount = 0;
				break;

			case 3:
				for (int i = 0; i < 3; i++){
					new CGomi(NULL, mPosition + CVector(0.0f, 15.0f, DROP)*matrix.RotateY(DROP_DIR), CVector(), CVector(1.0f, 1.0f, 1.0f));
					CGomi::StageGomi += 3;
				}
				CGomi::GomiCount = 0;
				break;

			case 4:
				for (int i = 0; i < 4; i++){
					new CGomi(NULL, mPosition + CVector(0.0f, 15.0f, DROP)*matrix.RotateY(DROP_DIR), CVector(), CVector(1.0f, 1.0f, 1.0f));
					CGomi::StageGomi += 4;
				}
				CGomi::GomiCount = 0;
				break;

			case 5:
				for (int i = 0; i < 5; i++){
					new CGomi(NULL, mPosition + CVector(0.0f, 15.0f, DROP)*matrix.RotateY(DROP_DIR), CVector(), CVector(1.0f, 1.0f, 1.0f));
					CGomi::StageGomi += 5;
				}
				CGomi::GomiCount = 0;
				break;
			}

			//リトライ(初期位置に戻る)
			if (frame2 >= RETRY){
				//初期位置
				mPosition = CVector(70.0f, 10.0f, 55.0f);
				mRotation = CVector(0.0f, 225.0f, 0.0f);
				CSceneGame::mBatteryNow = CSceneGame::mBatteryMax;
				Down = false;
				frame2 = 0;
			}
		}
		else {
			onlyOnce = true;
		}
	}

}