#ifndef CTASKMANAGER_H
#define CTASKMANAGER_H
//タスククラスのインクルード
#include "CTask.h"

/*
タスクマネージャ
タスクリストの管理
*/

class CTaskManager {
	static CTaskManager *spInstance;
protected:
	//デフォルトコンストラクタ
	//	CTaskManager();
public:
	//デフォルトコンストラクタ
	CTaskManager();
	CTask *mpHead;	//先頭ポインタ
	//	CTask *mpTail;	//最後ポインタ
	//デストラクタ
	virtual ~CTaskManager();
	//リストに追加
	//Add(タスクのポインタ)
	void Add(CTask *task);
	//更新
	void Update();
	//描画
	void Render();
	//リストから削除
	//Remove(タスクのポインタ)
	void Remove(CTask *task);
	//タスクの削除
	void Delete();
	///U
	void CTaskManager::TaskCollision();
	//
	static CTaskManager* Get();

	void Destory();
	void AllDelete();
};

#endif
