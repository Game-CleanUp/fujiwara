#include"CEnemy.h"
#include"CSceneGame.h"

//課題7
CEnemy::CEnemy(CModel*model, CVector position, CVector rotation, CVector scale)
:mColBody(this, CVector(0.0f, 5.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f),
CVector(1.0f, 1.0f, 1.0f), 2.0f)
, state(0), frame(0)
{
	//モデル、位置、回転、拡縮を設定する
	mpModel = model; //モデルの設定
	mPosition = position; //位置の設定
	mRotation = rotation; //回転の設定
	mScale = scale; //拡縮の設定
}
//課題8
void CEnemy::Collision(CCollider*m, CCollider*y){
	
	//自身のコライダタイプの判定
	switch (m->mType){
	case CCollider::ESPHERE://球コライダ
		//相手のコライダが三角コライダの時
		if (y->mType == CCollider::ETRIANGLE){
			CVector adjust;//調整値ベクトル
			//三角形と球の衝突判定
			if (CCollider::CollisionTriangleSphere(y, m, &adjust)){

			}
			//位置の更新
			mPosition = mPosition - adjust*-1;

			//行列の更新
			CCharacter::Update();
		}
		break;
	}

	//プレイヤーとの衝突判定
	if (y->mTag == CCollider::EBODY){
		if (CCollider::Collision(m, y)){
			mEnabled = false;
			CSceneGame::mTimeNow -= 5;
		}
	}
		
	//引き寄せ
	if (y->mTag == CCollider::ESEARCH){
		if (CCollider::Collision(m, y)){
			//プレイヤーの方向
			CVector dir = y->mpParent->mPosition - mPosition;
			//正規化（長さを1にする）Normalize()
			mPosition = mPosition + dir.Normalize()*1.5;
		}
	}
}

void CEnemy::Update(){

	if (CSceneGame::mTimeNow > 0){
		switch (state){
		case 0:
			frame += 1;
			if (frame > 30){
				state = rand() % 4;
				frame = 0;
			}
			break;

		case 1:
			frame += 1;
			if (frame < 20){
				//左回転
				mRotation.mY += rand() % 13;
			}
			if (frame > 30){
				//前進
				mPosition = CVector(0.0f, 0.0f, 2.0f)*mMatrix;
			}
			if (frame > 90){
				state = rand() % 4;
				frame = 0;
			}
			break;

		case 2:
			frame += 1;
			if (frame < 20){
				//右回転
				mRotation.mY -= rand() % 13;
			}
			if (frame > 30){
				//前進
				mPosition = CVector(0.0f, 0.0f, 2.0f)*mMatrix;
			}
			if (frame > 90){
				state = rand() % 4;
				frame = 0;
			}
			break;

		case 3:
			frame += 1;
			if (frame > 60){
				state = rand() % 4;
				frame = 0;
			}
			break;
		}
	}
}
