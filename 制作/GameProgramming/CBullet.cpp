#include"CBullet.h"
#include"CPlayer.h"
#include"CSceneGame.h"
CBullet::CBullet()
:mLife(50), mCollider(this, CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 1.0f)
{
	mpModel = &CSceneGame::mGun;
	if (CPlayer::mpPlayer->mstate == CPlayer::mpPlayer->EAR){
		mLife = 75;
	}
	if (CPlayer::mpPlayer->mstate == CPlayer::mpPlayer->ESR){
		mLife = 100;
	}
	if (CPlayer::mpPlayer->mstate == CPlayer::mpPlayer->ESMG){
		mLife = 40;
	}
	if (CPlayer::mpPlayer->mstate == CPlayer::mpPlayer->EMINE){
		mLife = 120;
	}
	mCollider.mTag = CCollider::EBULLET;
	//mCollider.mTag = CCollider::EPLAYER2;
	//mCollider.mTag = CCollider::EENEMY2;
	//mCollider.mTag = CCollider::EROCK;
}
CBullet::CBullet(CModel *model, CVector position, CVector rotation, CVector scale)
:mLife(50), mCollider(this, CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 0.1f)
{

	mpModel = &CSceneGame::mGun;
	mpModel = model;
	mPosition = position;
	mRotation = rotation;
	mScale = scale;
	if (CPlayer::mpPlayer->mstate == CPlayer::mpPlayer->EAR){
		mLife = 75;
	}
	if (CPlayer::mpPlayer->mstate == CPlayer::mpPlayer->ESR){
		mLife = 100;
	}
	if (CPlayer::mpPlayer->mstate == CPlayer::mpPlayer->ESMG){
		mLife = 40;
	}
	if (CPlayer::mpPlayer->mstate == CPlayer::mpPlayer->EMINE){
		mLife = 120;
	}
	mCollider.mTag = CCollider::EBULLET;
	//mCollider.mTag = CCollider::EPLAYER2;
	//mCollider.mTag = CCollider::EENEMY2;
	//mCollider.mTag = CCollider::EROCK;
}

//幅と奥行きの設定
//Set(幅,奥行)
void CBullet::Set(float w, float d){
	//スケール設定
	mScale = CVector(1.0f, 1.0f, 1.0f);
	//三角形の頂点設定
	mT.SetVertex(CVector(w, 0.0f, 0.0f), CVector(-w, 0.0f, 0.0f), CVector(0.0f, 0.0f, d));
	//三角形の法線設定
	mT.SetNormal(CVector(0.0f, 1.0f, 0.0f));
}

//更新
void CBullet::Update(){

	//生存時間の判定
	if (mLife-- > 0){
		CCharacter::Update();
		//位置更新
		
		//位置更新
		mPosition = CVector(0.0f, 0.0f, 1.0f) * mMatrix;
	}
	else{
		//無効にする
		mEnabled = false;
	}
}

//衝突処理
//Collision(コライダ1,コライダ2)
void CBullet::Collision(CCollider *m, CCollider *y){
	//共に球コライダの時
	if (m->mType == CCollider::ESPHERE && y->mType == CCollider::ESPHERE){
		//コライダのｍとｙが衝突しているか判定
		if (CCollider::Collision(m, y)){
			//プレイヤーの時
			if (y->mTag == CCollider::EPLAYER2){
				//衝突しているときは無効にする
				mEnabled = false;
			}
			//敵の時
			if (y->mTag == CCollider::EENEMY2){
				//衝突しているときは無効にする
				mEnabled = false;
			}
			//岩の時
			if (y->mTag == CCollider::EROCK){
				//衝突しているときは無効にする
				mEnabled = false;
			}
			if (y->mTag == CCollider::EBULLET2){
				mEnabled = false;
			}
		}
	}
}

//描画
void CBullet::Render(){
	CCharacter::Render();
	//DIFUSE黄色設定
	float c[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	//三角形描画
	mT.Render(mMatrix);
	//確認用メソッド
	//mCollider.Render();
}
CBullet3::CBullet3()
:mLife(40), mCollider(this, CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 0.1f)
{
	mpModel = &CSceneGame::mGun;
	
	mCollider.mTag = CCollider::EBULLET3;
	//mCollider.mTag = CCollider::EPLAYER2;
	//mCollider.mTag = CCollider::EENEMY2;
	//mCollider.mTag = CCollider::EROCK;
}
CBullet3::CBullet3(CModel *model, CVector position, CVector rotation, CVector scale)
:mLife(50), mCollider(this, CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 0.1f)
{

	mpModel = &CSceneGame::mGun;
	mpModel = model;
	mPosition = position;
	mRotation = rotation;
	mScale = scale;
	
	mCollider.mTag = CCollider::EBULLET3;
	//mCollider.mTag = CCollider::EPLAYER2;
	//mCollider.mTag = CCollider::EENEMY2;
	//mCollider.mTag = CCollider::EROCK;
}

//幅と奥行きの設定
//Set(幅,奥行)
void CBullet3::Set(float w, float d){
	//スケール設定
	mScale = CVector(1.0f, 1.0f, 1.0f);
	//三角形の頂点設定
	mT.SetVertex(CVector(w, 0.0f, 0.0f), CVector(-w, 0.0f, 0.0f), CVector(0.0f, 0.0f, d));
	//三角形の法線設定
	mT.SetNormal(CVector(0.0f, 1.0f, 0.0f));
}

//更新
void CBullet3::Update(){

	//生存時間の判定
	if (mLife-- > 0){
		CCharacter::Update();
		
		//位置更新
		mPosition = CVector(0.0f, 0.0f, 1.0f) * mMatrix;
	}
	else{
		//無効にする
		mEnabled = false;
	}
}

//衝突処理
//Collision(コライダ1,コライダ2)
void CBullet3::Collision(CCollider *m, CCollider *y){
	//共に球コライダの時
	if (m->mType == CCollider::ESPHERE && y->mType == CCollider::ESPHERE){
		//コライダのｍとｙが衝突しているか判定
		if (CCollider::Collision(m, y)){
			//プレイヤーの時
			if (y->mTag == CCollider::EPLAYER2){
				//衝突しているときは無効にする
				mEnabled = false;
			}
			//敵の時
			if (y->mTag == CCollider::EENEMY2){
				//衝突しているときは無効にする
				mEnabled = false;
			}
			//岩の時
			if (y->mTag == CCollider::EROCK){
				//衝突しているときは無効にする
				mEnabled = false;
			}
		}
	}
}

//描画
void CBullet3::Render(){
	CCharacter::Render();
	//DIFUSE黄色設定
	float c[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	//三角形描画
	mT.Render(mMatrix);
	//確認用メソッド
	//mCollider.Render();
}