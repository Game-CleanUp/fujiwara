#include"CPlayer.h"
#include"CSceneGame.h"
#include"CEffect.h"

int CPlayer::clear = 0;
int CPlayer::Down = 0;

CPlayer *CPlayer::mpPlayer = 0;

CSound CPlayer::Sound;
CSound CPlayer::Sound2;
CSound CPlayer::Sound3;	//爆発音

//スマートポインタの外部参照
extern std::shared_ptr<CTexture>TextureExp(new CTexture());

CPlayer::CPlayer()
:mColBody(this, CVector(0.0f, 0.0f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), 2.0f)
//サーチ
, mSearch(this, CVector(0.0f, 0.0f, 5.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), R)
, mVelocityJump(0.0f)
, frame(0), frameMax(300), frame2(0)
{

	mColBody.mTag = CCollider::EBODY;
	mSearch.mTag = CCollider::ESEARCH;
	Sound.Load("jump.wav");	//ジャンプ音
	Sound2.Load("act.wav");	//移動音
	Sound.Load("Bomb.wav");	//爆発音

	//爆発テクスチャ
	TextureExp->Load("exp.tga");

	//起動時のマウスカーソルの座標を覚える
	CInput::GetMousePos(&mMouseX, &mMouseY);
	mMouseX = 1920 / 2;
	mMouseY = 1080 / 2;

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

	if (Down == FALSE){
		if (clear < GAMECLEAR){
			if (CSceneGame::mBatteryNow > 0){
				if (CSceneGame::mTimeNow > 0){
					if (CKey::Push('A')){
						mRotation.mY += DIR;
					}

					if (CKey::Push('D')){
						mRotation.mY -= DIR;
					}

					if (CKey::Push('W')){
						mPosition = CVector(0.0f, 0.0f, FORWARD)*mMatrix;
		
					}

					if (CKey::Push('S')){
						mPosition = CVector(0.0f, 0.0f, BACK)*mMatrix;
					}

					//スペースキー入力で発射
					if (mVelocityJump == 0){	//ジャンプ中無効
						if (CKey::Once(VK_SPACE)){
							CBullet*bullet = new CBullet();
							bullet->Set(0.3f, 2.0f);
							bullet->mPosition = CVector(0.0f, 0.0f, 0.0f)*mMatrix;
							bullet->mRotation = mRotation;
							bullet->mTag = CCharacter::EBULLET;
							//CSceneGame::mBatteryNow -= 1;	//バッテリー消費
						}
					}

					if (CKey::Once('Q')){

						//罠設置
						new CTrap(NULL, mPosition + CVector(0.0f, 0.0f, 5.0f)*matrix.RotateY(0), CVector(), CVector(1.5f, 1.5f, 1.5f));

					}

					//ジャンプ
					if (CKey::Once('J') && mVelocityJump == 0){
						mVelocityJump = JUMPV0;
						CSceneGame::mBatteryNow -= 5 * 60;	//バッテリー消費
						Sound.Play();
					}
					
					if (CKey::Push('R')){
						mRotation.mX += 0.3f;
					}
						
					

					//回避
					if (CKey::Once('H')){
						//mSearch.mRadius = mEnabled;
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

					//ゴミ回収(ホームにいるとき、ゴミを持っているとき)
					if (CHome::home == TRUE && CGomi::GomiCount > 0){
						if (CKey::Once('E')){
							clear = clear + CGomi::GomiCount;
							CGomi::GomiCount = 0;
							}
						}

					//// マウスカーソルの座標を取得
					//	int mx, my;
					//CInput::GetMousePos(&mx, &my);
					//if (mx < mMouseX) {
					//	//マウスの移動量の分だけ回転
					//	mRotation.mY += (mMouseX - mx) / 5.0;
					//}
					//if (mMouseX < mx) {
					//	//マウスの移動量の分だけ回転
					//	mRotation.mY += (mMouseX - mx) / 5.0;
					//}

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
			}

			//位置の更新
			mPosition = mPosition - adjust*-1;

			//行列の更新
			CCharacter::Update();
		}

		break;
	}
	if (Down == TRUE){
		//爆発音再生
		Sound3.Play();
	}

	//ボスとの衝突
	//if (m->mTag == CCollider::EBODY){
		if (y->mTag == CCollider::EBODY2){
			if (CCollider::Collision(m, y)){

				CSceneGame::mBatteryNow++;
				frame2++;	//復帰までの時間
				Down = TRUE;
				
				//エフェクト生成(爆発)
				new CEffect(mPosition, 8.0f, 8.0f, TextureExp, 4, 4, 1);

				//爆発音再生
				//Sound3.Play();

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
				if (frame2 >= RETRY){
					//初期位置
					mPosition = CVector(-70.0f, 10.0f, 50.0f);
					mRotation = CVector(0.0f, -225.0f, 0.0f);
					CSceneGame::mBatteryNow = CSceneGame::mBatteryMax;
					Down = FALSE;
					frame2 = 0;
				}
			}
		//}
	}
}