#include"CBullet.h"
#include"CSceneGame.h"

CBullet::CBullet()
:mLife(15), mCollider(this, CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 2.0f)
{
	
	mCollider.mTag = CCollider::EBULLET;
	
}

//���Ɖ��s���̐ݒ�
//Set(��,���s)
void CBullet::Set(float w, float d){
	//�X�P�[���ݒ�
	mScale = CVector(1.0f, 1.0f, 1.0f);
	//�O�p�`�̒��_�ݒ�
	mT.SetVertex(CVector(w, 0.0f, 0.0f), CVector(-w, 0.0f, 0.0f), CVector(0.0f, 0.0f, d));
	//�O�p�`�̖@���ݒ�
	mT.SetNormal(CVector(0.0f, 5.0f, 0.0f));
}

//�X�V
void CBullet::Update(){

	//�������Ԃ̔���
	if (mLife-- > 0){
		CCharacter::Update();
		//�ʒu�X�V
		
		//�e��
		mPosition = CVector(0.0f, 0.0f, 1.5f) * mMatrix;
	}
	else{
		//�����ɂ���
		mEnabled = false;
	}
}

//�Փˏ���
//Collision(�R���C�_1,�R���C�_2)
void CBullet::Collision(CCollider *m, CCollider *y){
	//���ɋ��R���C�_�̎�
	if (m->mType == CCollider::ESPHERE && y->mType == CCollider::ESPHERE){
		//�R���C�_�̂��Ƃ����Փ˂��Ă��邩����
		if (CCollider::Collision(m, y)){
			mEnabled = false;
		}
	}

	//���g�̃R���C�_�^�C�v�̔���
	switch (m->mType){
	case CCollider::ESPHERE://���R���C�_
		//����̃R���C�_���O�p�R���C�_�̎�
		if (y->mType == CCollider::ETRIANGLE){
			CVector adjust;//�����l�x�N�g��
			//�O�p�`�Ƌ��̏Փ˔���
			if (CCollider::CollisionTriangleSphere(y, m, &adjust)){
				mEnabled = false;
			}
		}
	}
}

//�`��
void CBullet::Render(){
	CCharacter::Render();
	//DIFUSE���F�ݒ�
	float c[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	//�O�p�`�`��
	mT.Render(mMatrix);
}