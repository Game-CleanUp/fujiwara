#include"CEnemy.h"
#include"CSceneGame.h"

//�ۑ�7
CEnemy::CEnemy(CModel*model, CVector position, CVector rotation, CVector scale)
:mColBody(this, CVector(0.0f, 2.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f),
CVector(1.0f, 1.0f, 1.0f), 2.0f)
, state(0), frame(0)
{
	//���f���A�ʒu�A��]�A�g�k��ݒ肷��
	mpModel = model; //���f���̐ݒ�
	mPosition = position; //�ʒu�̐ݒ�
	mRotation = rotation; //��]�̐ݒ�
	mScale = scale; //�g�k�̐ݒ�
}
//�ۑ�8
void CEnemy::Collision(CCollider*m, CCollider*y){
	
	//���g�̃R���C�_�^�C�v�̔���
	switch (m->mType){
	case CCollider::ESPHERE://���R���C�_
		//����̃R���C�_���O�p�R���C�_�̎�
		if (y->mType == CCollider::ETRIANGLE){
			CVector adjust;//�����l�x�N�g��
			//�O�p�`�Ƌ��̏Փ˔���
			if (CCollider::CollisionTriangleSphere(y, m, &adjust)){

			}
			//�ʒu�̍X�V
			mPosition = mPosition - adjust*-1;

			//�s��̍X�V
			CCharacter::Update();
		}
		break;
	}

	//�v���C���[�Ƃ̏Փ˔���
	if (y->mTag == CCollider::EBODY){
		if (CCollider::Collision(m, y)){
			mEnabled = false;
			CSceneGame::mBatteryNow -= 5;
		}
	}
		
	//������
	if (y->mTag == CCollider::ESEARCH){
		if (CCollider::Collision(m, y)){
			//�v���C���[�̕���
			CVector dir = y->mpParent->mPosition - mPosition;
			//���K���i������1�ɂ���jNormalize()
			mPosition = mPosition + dir.Normalize()*1.5;
		}
	}
}

void CEnemy::Update(){

	if (CPlayer::clear < 2){
		if (CSceneGame::mBatteryNow > 0){
			switch (state){
			case 0:
				frame += 1;
				if (frame > 30){
					state = rand() % 4;
					frame = 0;
				}
				break;

			case 1:
				frame += 1;
				if (frame < 20){
					//����]
					mRotation.mY += rand() % 13;
				}
				if (frame > 30){
					//�O�i
					mPosition = CVector(0.0f, 0.0f, 3.0f)*mMatrix;
				}
				if (frame > 90){
					state = rand() % 4;
					frame = 0;
				}
				break;

			case 2:
				frame += 1;
				if (frame < 20){
					//�E��]
					mRotation.mY -= rand() % 13;
				}
				if (frame > 30){
					//�O�i
					mPosition = CVector(0.0f, 0.0f, 3.0f)*mMatrix;
				}
				if (frame > 90){
					state = rand() % 4;
					frame = 0;
				}
				break;

			case 3:
				frame += 1;
				if (frame > 60){
					state = rand() % 4;
					frame = 0;
				}
				break;
			}
		}
	}
}
