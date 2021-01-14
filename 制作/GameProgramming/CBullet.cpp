#include"CBullet.h"
#include"CSceneGame.h"

CBullet::CBullet()
:mLife(15), mCollider(this, CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 2.0f)
{
	
	mCollider.mTag = CCollider::EBULLET;
	
}

//幅と奥行きの設定
//Set(幅,奥行)
void CBullet::Set(float w, float d){
	//スケール設定
	mScale = CVector(1.0f, 1.0f, 1.0f);
	//三角形の頂点設定
	mT.SetVertex(CVector(w, 0.0f, 0.0f), CVector(-w, 0.0f, 0.0f), CVector(0.0f, 0.0f, d));
	//三角形の法線設定
	mT.SetNormal(CVector(0.0f, 5.0f, 0.0f));
}

//更新
void CBullet::Update(){

	//生存時間の判定
	if (mLife-- > 0){
		CCharacter::Update();
		//位置更新
		
		//弾速
		mPosition = CVector(0.0f, 0.0f, 1.5f) * mMatrix;
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
			mEnabled = false;
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
}