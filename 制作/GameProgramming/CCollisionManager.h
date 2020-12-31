#ifndef CCOLLISIONMANAGER_H
#define CCOLLISIONMANAGER_H
//�^�X�N�}�l�[�W���̃C���N���[�h
#include "CTaskManager.h"

class CCollider;
/*
�R���W�����}�l�[�W��
�R���C�_�̃��X�g�Ǘ�
*/
class CCollisionManager : public CTaskManager {
	static CCollisionManager *spInstance;
protected:
public:
	//�Փˏ���
	void Collision();
	///U
	//Collision(�R���C�_�j
	//�R���C�_�Ƃ̏Փˏ��������s����
	void CCollisionManager::Collision(CCollider *collider);
	//
	static CCollisionManager* Get();
};
//���Ŏg����悤�ɊO���Q��
extern CCollisionManager CollisionManager;

#endif