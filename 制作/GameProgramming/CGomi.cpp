#include"CGomi.h"


int CGomi::GomiCount = 0;
CModel CGomi::mModel;

//課題7
CGomi::CGomi(CModel*model, CVector position, CVector rotation, CVector scale)
:mColBody(this, CVector(0.0f, 1.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f),
CVector(1.0f, 1.0f, 1.0f), 1.0f)
{
	//モデル、位置、回転、拡縮を設定する
	mpModel = model; //モデルの設定
	mPosition = position; //位置の設定
	mRotation = rotation; //回転の設定
	mScale = scale; //拡縮の設定

	//モデルが無いときは読み込む
	if (mModel.mTriangles.size() == 0)
	{
		mModel.Load("Rock1.obj", "Rock1.mtl");
	}
	//モデルのポインタ設定
	mpModel = &mModel;
}

void CGomi::Collision(CCollider*m, CCollider*y){

	//ゴミ保有数上限で無効
	//if (GomiCount < 5){
		//相手がプレイヤー
		if (y->mTag == CCollider::EBODY){
			if (CCollider::Collision(m, y)){
				//衝突しているときは無効にする
				mEnabled = false;
				GomiCount += 1;
			}
		}
		//引き寄せ(プレイヤーのサーチに当たった時)
		if (y->mTag == CCollider::ESEARCH){
			if (CCollider::Collision(m, y)){
				//プレイヤーの方向
				CVector dir = y->mpParent->mPosition - mPosition;
				//正規化（長さを1にする）Normalize()
				mPosition = mPosition + dir.Normalize()*1.0;
			}
	//	}
	}
}