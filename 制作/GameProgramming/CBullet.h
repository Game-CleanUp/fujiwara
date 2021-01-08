#ifndef CBULLET_H
#define CBULLET_H
#include"CCharacter.h"
#include"CTriangle.h"
#include"CCollider.h"

class CBullet :public CCharacter{
public:
	CTriangle mT;
	//幅と奥行きの設定
	//Set(幅、奥行き)
	void Set(float w, float d);
	//更新
	void Update();
	//描画
	void Render();
	//生存時間
	int mLife;
	//デフォルトコンストラクタ
	CBullet();
	CCollider mCollider;

	//衝突判定
	//Collision(コライダ1、コライダ2)
	void Collision(CCollider*m, CCollider*y);

};


#endif