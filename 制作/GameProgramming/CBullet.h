#ifndef CBULLET_H
#define CBULLET_H
//キャラクタクラスのインクルード
#include"CCharacter.h"
//三角形クラスのインクルード
#include"CTriangle.h"
#include"CCollider.h"

/*弾クラス
三角形を飛ばす
*/
class CBullet :public CCharacter{
public:
	//コライダ
	CCollider mCollider;
	//三角形
	CTriangle mT;
	//幅と奥行きの設定
	//set(幅,奥行)
	void Set(float w, float d);
	//生存時間
	int mLife;

	CBullet();
	CBullet(CModel *model, CVector position, CVector rotation, CVector scale);
	//更新
	void Update();
	//衝突処理
	//Ccllision(コライダ1,コライダ2)
	void Collision(CCollider*m, CCollider*y);
	//描画
	void Render();

};
#endif