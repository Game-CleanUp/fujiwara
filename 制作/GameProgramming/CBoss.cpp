#include"CBoss.h"
#include"CSceneGame.h"

int CBoss::tracking = 0;
CSound CBoss::Sound;

CBoss::CBoss(CModel*model, CVector position, CVector rotation, CVector scale)
:mColBody(this, CVector(0.0f, 0.0f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), 5.0f)
, mSearch(this, CVector(0.0f, 0.0f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), 50.0f)	
, frame(0), state(0), mVelocityJump(0.0f)
{
	//���f���A�ʒu�A��]�A�g�k��ݒ肷��
	mpModel = model; //���f���̐ݒ�
	mPosition = position; //�ʒu�̐ݒ�
	mRotation = rotation; //��]�̐ݒ�
	mScale = scale; //�g�k�̐ݒ�

	mColBody.mTag = CCollider::EBODY2;
	mSearch.mTag = CCollider::ESEARCH2;

	Sound.Load("Dog.wav");
}

void CBoss::TaskCollision()
{
	mColBody.ChangePriority();
	mSearch.ChangePriority();
	CCollisionManager::Get()->Collision(&mColBody);
	CCollisionManager::Get()->Collision(&mSearch);
}




void CBoss::Update(){

	if (CPlayer::clear < GAMECLEAR){
		if (CSceneGame::mBatteryNow > 0){
			//�ǔ����ĂȂ��Ƃ�
			if (tracking == FALSE){
				switch (state){
				case 0:
					frame += 1;
					if (frame > 30){
						state = rand() % 5;
						frame = 0;
					}
					break;

				case 1:
					frame += 1;
					if (frame < 20){
						//����]
						mRotation.mY += rand() % TURN;
					}
					if (frame > 30){
						//�O�i
						mPosition = CVector(SPEED, 0.0f, 0.0f)*mMatrix;
					}
					if (frame > 90){
						state = rand() % 5;
						frame = 0;
					}
					break;

				case 2:
					frame += 1;
					if (frame < 20){
						//�E��]
						mRotation.mY -= rand() % TURN;
					}
					if (frame > 30){
						//�O�i
						mPosition = CVector(SPEED, 0.0f, 0.0f)*mMatrix;
					}
					if (frame > 90){
						state = rand() % 5;
						frame = 0;
					}
					break;

				case 3:
					frame += 1;
					if (frame > 60){
						state = rand() % 5;
						frame = 0;
					}
					break;

				case 4:
					frame += 1;
					if (frame > 30){
						state = rand() % 5;
						frame = 0;
					}
					break;
				}
			}
		}
	}
}

void CBoss::Collision(CCollider*m, CCollider*y){

	//�ǔ�(�v���C���[���T�[�`�ɓ����)
	if (m->mTag == CCollider::ESEARCH2){
		if (y->mTag == CCollider::EBODY){
			if (CCollider::Collision(m, y)){
				//�v���C���[�̕���
				CVector dir = y->mpParent->mPosition - mPosition;
				//���K���i������1�ɂ���jNormalize()
				mPosition = mPosition + dir.Normalize() * 0.5;
				Sound.Play();
				tracking = TRUE;
			}
		}
		else{
			//�ǔ�����߂�
			tracking = FALSE;
			Sound.Stop();
		}
		return;
	}
	
	

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
}