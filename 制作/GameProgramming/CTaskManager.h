#ifndef CTASKMANAGER_H
#define CTASKMANAGER_H
//�^�X�N�N���X�̃C���N���[�h
#include "CTask.h"

/*
�^�X�N�}�l�[�W��
�^�X�N���X�g�̊Ǘ�
*/

class CTaskManager {
	static CTaskManager *spInstance;
protected:
	//�f�t�H���g�R���X�g���N�^
	//	CTaskManager();
public:
	//�f�t�H���g�R���X�g���N�^
	CTaskManager();
	CTask *mpHead;	//�擪�|�C���^
	//	CTask *mpTail;	//�Ō�|�C���^
	//�f�X�g���N�^
	virtual ~CTaskManager();
	//���X�g�ɒǉ�
	//Add(�^�X�N�̃|�C���^)
	void Add(CTask *task);
	//�X�V
	void Update();
	//�`��
	void Render();
	//���X�g����폜
	//Remove(�^�X�N�̃|�C���^)
	void Remove(CTask *task);
	//�^�X�N�̍폜
	void Delete();
	///U
	void CTaskManager::TaskCollision();
	//
	static CTaskManager* Get();

	void Destory();
	void AllDelete();
};



//class CTaskManager {
//public:
//	CTask *mpHead;	//�擪�|�C���^
////	CTask *mpTail;	//�Ō�|�C���^
//	
//	//�f�t�H���g�R���X�g���N�^
//	CTaskManager();
//	//�f�X�g���N�^
//	virtual ~CTaskManager();
//	//���X�g�ɒǉ�
//	//Add(�^�X�N�̃|�C���^)
//	void Add(CTask *task);
//	//�X�V
//	void Update();
//	//�`��
//	void Render();
//	//22
//	//���X�g����폜
//	//Remove(�^�X�N�̃|�C���^)
//	void Remove(CTask *task);
//	//22
//	//�^�X�N�̍폜
//	void Delete();
//
//	//�C���X�^���X�̃|�C���^�ϐ�
//	static CTaskManager *CTaskManager::instance;
//	static CTaskManager* Get();
//	void Destory();
//	void AllDelete();
//};
//
////�^�X�N�}�l�[�W���̊O���Q��
////extern CTaskManager TaskManager;
//
//
//
//

#endif
