#ifndef CBULLET_H
#define CBULLET_H
//�L�����N�^�N���X�̃C���N���[�h
#include"CCharacter.h"
//�O�p�`�N���X�̃C���N���[�h
#include"CTriangle.h"
#include"CCollider.h"

/*�e�N���X
�O�p�`���΂�
*/
class CBullet :public CCharacter{
public:
	//�R���C�_
	CCollider mCollider;
	//�O�p�`
	CTriangle mT;
	//���Ɖ��s���̐ݒ�
	//set(��,���s)
	void Set(float w, float d);
	//��������
	int mLife;

	CBullet();
	//�X�V
	void Update();
	//�Փˏ���
	//Ccllision(�R���C�_1,�R���C�_2)
	void Collision(CCollider*m, CCollider*y);
	//�`��
	void Render();

};
#endif