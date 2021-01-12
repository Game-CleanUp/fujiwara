#include "CTaskManager.h"

CTaskManager *CTaskManager::spInstance = 0;

CTaskManager* CTaskManager::Get()
{
	if (spInstance == 0)
	{
		spInstance = new CTaskManager();
	}
	return spInstance;
}

CTaskManager::CTaskManager()
//: mpHead(0)//, mpTail(0)
{
	mpHead = new CTask();
}

CTaskManager::~CTaskManager() {
	delete mpHead;
}

//リストに追加
//Add(タスクのポインタ)
void CTaskManager::Add(CTask *task) {
	CTask *current = mpHead->mpNext;
	CTask *prev = mpHead;
	while (current) {
		if (task->mPriority >= current->mPriority) {
			break;
		}
		prev = current;
		current = current->mpNext;
	}
	if (current) {
		prev->mpNext = task;
		current->mpPrev = task;
		task->mpPrev = prev;
		task->mpNext = current;
	}
	else {
		prev->mpNext = task;
		task->mpPrev = prev;
		task->mpNext = 0;
	}
	return;
	//リストが空（先頭が0）
	if (mpHead == 0) {
		//リストの先頭にする
		mpHead = task;
		task->mpPrev = 0;
		//リストの最後にする
		//mpTail = task;
		task->mpNext = 0;
	}
	else {
		//リストの先頭にする
		task->mpNext = mpHead;
		mpHead->mpPrev = task;
		mpHead = task;
		task->mpPrev = 0;
	}
}

//リストから削除
//Remove(タスクのポインタ)
void CTaskManager::Remove(CTask *task) {
	//taskが先頭の時
	if (task->mpPrev == 0) {
		mpHead = task->mpNext;
	}
	else {
		task->mpPrev->mpNext = task->mpNext;
	}
	//taskが最後の時
	if (task->mpNext == 0) {
		//		mpTail = task->mpPrev;
	}
	else {
		task->mpNext->mpPrev = task->mpPrev;
	}
}

//更新
void CTaskManager::Update() {
	//先頭から最後まで繰り返し
	CTask *pos = mpHead->mpNext;
	while (pos) {
		//更新処理を呼ぶ
		pos->Update();
		//次へ
		pos = pos->mpNext;
	}
}

//描画
void CTaskManager::Render() {
	//先頭から最後まで繰り返し
	CTask *pos = mpHead->mpNext;
	while (pos) {
		//描画処理を呼ぶ
		pos->Render();
		//次へ
		pos = pos->mpNext;
	}
}

//タスクの削除
void CTaskManager::Delete() {
	//先頭から最後まで繰り返し
	CTask *pos = mpHead->mpNext;
	while (pos) {
		CTask *del = pos;
		//次へ
		pos = pos->mpNext;
		//mEnabledがfalseなら削除
		if (del->mEnabled == false) {
			delete del;
		}
	}
}
///U
void CTaskManager::TaskCollision()
{
	//先頭から最後まで繰り返し
	CTask *pos = mpHead->mpNext;
	while (pos) {
		//衝突処理を呼ぶ
		pos->TaskCollision();
		//次へ
		pos = pos->mpNext;
	}
}

//インスタンスの破棄
void CTaskManager::Destory(){
	if (spInstance){
		delete spInstance;
		spInstance = 0;
	}
}

void CTaskManager::AllDelete(){
	//先頭から最後まで繰り返し
	CTask *pos = mpHead->mpNext;
	while (pos) {
		//
		pos->mEnabled = false;
		//次へ
		pos = pos->mpNext;
	}
}