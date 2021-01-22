#include"CBoss.h"
#include"CSceneGame.h"


CSound CBoss::Sound;

CBoss::CBoss(CModel*model, CVector position, CVector rotation, CVector scale)
:mColBody(this, CVector(0.0f, 0.0f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), 3.0f)
, mSearch(this, CVector(0.0f, 0.0f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), 50.0f)	
, ActFrame(0), state(0), mVelocityJump(0.0f), EnemyDown(0), DownFrame(0), traptracking(0)
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
		if (CSceneGame::mBatteryNow <= 0 || CSceneGame::mTimeNow <= 0){
			//�ǔ����ĂȂ��Ƃ�
			if (tracking == FALSE){
				switch (state){

				case 0:
					ActFrame += 1;
					if (ActFrame > 30){
						state = rand() % STATERAND;
						ActFrame = 0;
					}
					break;

				case 1:
					ActFrame += 1;
					if (ActFrame < 20){
						//����]
						mRotation.mY += rand() % TURN;
					}
					if (ActFrame > 30){
						//�O�i
						mPosition = CVector(0.0f, 0.0f, SPEED)*mMatrix;
					}
					if (ActFrame > 90){
						state = rand() % STATERAND;
						ActFrame = 0;
					}
					break;

				case 2:
					ActFrame += 1;
					if (ActFrame < 20){
						//�E��]
						mRotation.mY -= rand() % TURN;
					}
					if (ActFrame > 30){
						//�O�i
						mPosition = CVector(0.0f, 0.0f, SPEED)*mMatrix;
					}
					if (ActFrame > 90){
						state = rand() % STATERAND;
						ActFrame = 0;
					}
					break;

				case 3:
					ActFrame += 1;
					if (ActFrame > 60){
						state = rand() % STATERAND;
						ActFrame = 0;
					}
					break;

				case 4:
					ActFrame += 1;
					if (ActFrame > 90){
						new CGomi(NULL, mPosition, CVector(), CVector(1.0f, 1.0f, 1.0f));
						state = rand() % STATERAND;
						ActFrame = 0;
					}
					break;

				case 6:
					//�v���C���[�{�̂̕���
					CVector dir = mPosition - mPosition;
					CVector left = CVector(1.0f, 0.0f, 0.0f)  * CMatrix().RotateY(mRotation.mY);
					CVector right = CVector(-1.0f, 0.0f, 0.0f) * CMatrix().RotateY(mRotation.mY);
					//���K���i������1�ɂ���jNormalize()
					mPosition = mPosition + dir.Normalize() * 0.3;
				}
			}
		}
	}
	if (CSceneGame::mBatteryNow <= 0 || CSceneGame::mTimeNow <= 0){
		mEnabled = false;
	}

	mVelocityJump = JUMPV0;
	//�d�͉����x
	mVelocityJump -= G;
	//�ړ�
	mPosition.mY = mPosition.mY - mVelocityJump;
	
	CCharacter::Update();
}

void CBoss::Collision(CCollider*m, CCollider*y){

	//�ǔ�(�v���C���[���T�[�`�ɓ����)
	if (m->mTag == CCollider::ESEARCH2){
		if (y->mTag == CCollider::EBODY){
			if (CCollider::Collision(m, y)){
				
				//�v���C���[�{�̂̕���
				CVector dir = y->mpParent->mPosition - mPosition;
				CVector left = CVector(1.0f, 0.0f, 0.0f)  * CMatrix().RotateY(mRotation.mY);
				CVector right = CVector(-1.0f, 0.0f, 0.0f) * CMatrix().RotateY(mRotation.mY);

				float Rote = 4.0f;	//�v���C���[�����ɕ����]��

				if (left.Dot(dir) > 0.0f){
					mRotation.mY += Rote;
				}
				else if (left.Dot(dir) < 0.0f){
					mRotation.mY -= Rote;
				}

				//���K���i������1�ɂ���jNormalize()
				mPosition = mPosition + dir.Normalize() * 0.3;
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
	
	//�g���b�v�Ɉ����񂹂���
	if (m->mTag == CCollider::ESEARCH2){
		if (y->mTag == CCollider::ETRAP){
			if (CCollider::Collision(m, y)){
				state = 6;
				////�v���C���[�{�̂̕���
				//CVector dir = y->mpParent->mPosition - mPosition;
				//CVector left = CVector(1.0f, 0.0f, 0.0f)  * CMatrix().RotateY(mRotation.mY);
				//CVector right = CVector(-1.0f, 0.0f, 0.0f) * CMatrix().RotateY(mRotation.mY);

				//float Rote = 6.0f;	//�g���b�v�����ɕ����]��

				//if (left.Dot(dir) > 0.0f){
				//	mRotation.mY += Rote;
				//}
				//else if (left.Dot(dir) < 0.0f){
				//	mRotation.mY -= Rote;
				//}

				////���K���i������1�ɂ���jNormalize()
				//mPosition = mPosition + dir.Normalize() * 0.5;
				//tracking = TRUE;

			}
		}
		/*else{
			tracking = FALSE;
		}*/
		return;
	}
	
	//�v���C���[�e�Ƃ̏Փ˔���
	if (m->mTag == CCollider::EBODY2 && y->mTag == CCollider::EBULLET){

		if (CCollider::Collision(m, y)){
			mRotation = CVector(0.0f, 0.0f, 90.0f);	//�G�_�E��(�C��)
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
				//���n
				mVelocityJump = 0;
			}
			//�ʒu�̍X�V
			mPosition = mPosition - adjust*-1;

			//�s��̍X�V
			CCharacter::Update();
		}
		break;
	}
}