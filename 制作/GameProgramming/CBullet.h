#ifndef CBULLET_H
#define CBULLET_H
#include"CCharacter.h"
#include"CTriangle.h"
#include"CCollider.h"

class CBullet :public CCharacter{
public:
	CTriangle mT;
	//���Ɖ��s���̐ݒ�
	//Set(���A���s��)
	void Set(float w, float d);
	//�X�V
	void Update();
	//�`��
	void Render();
	//��������
	int mLife;
	//�f�t�H���g�R���X�g���N�^
	CBullet();
	CCollider mCollider;

	//�Փ˔���
	//Collision(�R���C�_1�A�R���C�_2)
	void Collision(CCollider*m, CCollider*y);

};


#endif