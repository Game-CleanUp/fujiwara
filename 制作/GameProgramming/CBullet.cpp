#include"CBullet.h"

//���Ɖ��s���̐ݒ�
//Set(���A���s��)
void CBullet::Set(float w, float d){
	//�X�P�[���ݒ�
	mScale = CVector(1.0f, 1.0f, 1.0f);
	//�O�p�`�̒��_�ݒ�
	mT.SetVertex(CVector(w, 0.0f, 0.0f), CVector(0.0f, 0.0f, -d), CVector(-w, 0.0f, 0.0f));
	//�O�p�`�̖@���ݒ�
	mT.SetNormal(CVector(0.0f, 1.0f, 0.0f));
}

void CBullet::Update(){
	CCharacter::Update();
	//�������Ԃ̔���
	if (mLife-- > 0){
		CCharacter::Update();
		//�ʒu�X�V
		mPosition = CVector(0.0f, 0.0f, 1.0f)*mMatrix;
	}
	else{
		//�����ɂ���
		mEnabled = false;
	}
}
void CBullet::Render(){
	//DIFFUSE���F�ݒ�
	float c[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	//�O�p�`�`��
	mT.Render(mMatrix);
}
CBullet::CBullet() :mLife(50)
, mCollider(this, CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 0.1f){
	//mCollider.mTag = CCollider::EBODY;
}
//�Փ˔���
//Collision(�R���C�_1�A�R���C�_2)
void CBullet::Collision(CCollider*m, CCollider*y){
	//�Ƃ��ɋ��R���C�_�̎�
	if (m->mType == CCollider::ESPHERE&&y->mType == CCollider::ESPHERE){
		//�R���C�_��m��y���Փ˂��Ă��邩����
		if (CCollider::Collision(m, y)){
			//�@�̂̎�
			if (y->mTag == CCollider::EBODY){
				//�Փ˂��Ă���Ƃ��͖����ɂ���
				mEnabled = false;
			}
		}
	}
}
