#include"CBullet.h"
#include"CSceneGame.h"

//デフォルトコンストラクタ
CBullet::CBullet(CModel *model, CVector position, CVector rotation, CVector scale)
:mCollider(this, CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 1.0f)
, mLife(50)
{
	mpModel = &CSceneGame::mBullet;	//弾モデル
	mpModel = model;
	mPosition = position;
	mRotation = rotation;
	mScale = scale;
	mCollider.mTag = CCollider::EBULLET;
}

CBullet::CBullet()
:mCollider(this, CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 1.0f)
, mLife(30)
{
	mpModel = &CSceneGame::mBullet;	//弾モデル
	mCollider.mTag = CCollider::EBULLET;
}

//幅と奥行きの設定
//Set(幅、奥行き)
void CBullet::Set(float w, float d){
	//スケール設定
	mScale = CVector(1.0f, 1.0f, 1.0f);
	//三角形の頂点設定
	mT.SetVertex(CVector(w, 0.0f, 0.0f), CVector(-w, 0.0f, 0.0f), CVector(0.0f, 0.0f, d));
	//三角形の法線設定
	mT.SetNormal(CVector(0.0f, 1.0f, 0.0f));
}

void CBullet::Update(){
	
	//生存時間の判定
	if (mLife-- > 0){
		CCharacter::Update();
		//弾速
		mPosition = CVector(0.0f, 0.0f, 1.5f)*mMatrix;
	}
	else{
		//無効にする
		mEnabled = false;
	}
	
}
void CBullet::Render(){
	//DIFFUSE黄色設定
	float c[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	//三角形描画
	mT.Render(mMatrix);
}


//衝突判定
//Collision(コライダ1、コライダ2)
void CBullet::Collision(CCollider*m, CCollider*y){
	//ともに球コライダの時
	if (m->mType == CCollider::ESPHERE&&y->mType == CCollider::ESPHERE){
		//コライダのmとyが衝突しているか判定
		if (CCollider::Collision(m, y)){
			//機体の時
			if (y->mTag == CCollider::EBODY){
				//衝突しているときは無効にする
				mEnabled = false;
			}
		}
	}
}
