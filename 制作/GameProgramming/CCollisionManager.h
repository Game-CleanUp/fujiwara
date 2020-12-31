#ifndef CCOLLISIONMANAGER_H
#define CCOLLISIONMANAGER_H
//タスクマネージャのインクルード
#include "CTaskManager.h"

class CCollider;
/*
コリジョンマネージャ
コライダのリスト管理
*/
class CCollisionManager : public CTaskManager {
	static CCollisionManager *spInstance;
protected:
public:
	//衝突処理
	void Collision();
	///U
	//Collision(コライダ）
	//コライダとの衝突処理を実行する
	void CCollisionManager::Collision(CCollider *collider);
	//
	static CCollisionManager* Get();
};
//他で使えるように外部参照
extern CCollisionManager CollisionManager;

#endif