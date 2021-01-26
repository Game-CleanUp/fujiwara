#include"CBoss.h"
#include"CSceneGame.h"


CSound CBoss::Sound;

CBoss::CBoss(CModel*model, CVector position, CVector rotation, CVector scale)
:mColBody(this, CVector(0.0f, 1.0f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), 3.0f)
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

	CVector dir_player = CPlayer::mpPlayer->mPosition - mPosition;	//�v���C���[����
	CVector dir_trap = CTrap::mpTrap->mPosition - mPosition;	//�g���b�v����

	CVector left = CVector(1.0f, 0.0f, 0.0f)  * CMatrix().RotateY(mRotation.mY);

	float Rote = 4.0f;	//�ǔ��Ώۂɕ����]��

	if (CPlayer::clear < GAMECLEAR){
		switch (state){

		case 0:	//�����~�܂�
			ActFrame += 1;
			if (ActFrame > 30){
				state = rand() % STATERAND;
				ActFrame = 0;
			}
			break;

		case 1:	//�������Ɉړ�
			ActFrame += 1;
			if (ActFrame < 20){
				//����]
				mRotation.mY += rand() % TURN;
			}
			if (ActFrame > 30){
				//�O�i
				mPosition = CVector(0.0f, 0.0f, SPEED)*mMatrix;
			}
			if (ActFrame > 120){
				state = rand() % STATERAND;
				ActFrame = 0;
			}
			break;

		case 2:	//�E�����Ɉړ�
			ActFrame += 1;
			if (ActFrame < 20){
				//�E��]
				mRotation.mY -= rand() % TURN;
			}
			if (ActFrame > 30){
				//�O�i
				mPosition = CVector(0.0f, 0.0f, SPEED)*mMatrix;
			}
			if (ActFrame > 120){
				state = rand() % STATERAND;
				ActFrame = 0;
			}
			break;

		case 3:	//�����~�܂�
			ActFrame += 1;
			if (ActFrame > 60){
				state = rand() % STATERAND;
				ActFrame = 0;
			}
			break;

		case 4:	//�S�~���o��
			ActFrame += 1;
			if (ActFrame > 90){
				new CGomi(NULL, mPosition, CVector(), CVector(0.5f, 0.5f, 0.5f));
				state = rand() % STATERAND;
				ActFrame = 0;
			}
			break;

		case 5:	//�g���b�v�ǔ�
			if (left.Dot(dir_trap) > 0.0f){
				mRotation.mY += Rote;
			}
			else if (left.Dot(dir_trap) < 0.0f){
				mRotation.mY -= Rote;
			}

			//���K���i������1�ɂ���jNormalize()
			mPosition = mPosition + dir_trap.Normalize() * 0.3;
			state = rand() % STATERAND;
			break;

		case 6:
			//�v���C���[�ǔ�
			if (left.Dot(dir_player) > 0.0f){
				mRotation.mY += Rote;
			}
			else if (left.Dot(dir_player) < 0.0f){
				mRotation.mY -= Rote;
			}

			//���K���i������1�ɂ���jNormalize()
			mPosition = mPosition + dir_player.Normalize() * 0.3;
			state = rand() % STATERAND;
			break;

		case 7:	//�C��
			ActFrame += 1;
			if (ActFrame > 120){
				mRotation = CVector(0.0f, 0.0f, 0.0f);	//���A
				ActFrame = 0;
				state = rand() % STATERAND;
			}
			break;
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

	//if (m->mTag == CCollider::ESEARCH2){
	//	//return;
	//}

	//�ǔ�(�v���C���[���T�[�`�ɓ����)
	if (m->mTag == CCollider::ESEARCH2){
		if (y->mTag == CCollider::EBODY){
			if (CCollider::Collision(m, y)){
				if (state != 5 && state != 7){	//�g���b�v�A�C��ȊO
					state = 6;	//�v���C���[�ǔ���
				}
			}
		}
	}
	
	//�g���b�v�Ƃ̏Փ�
	if (m->mTag == CCollider::ESEARCH2){
		if (y->mTag == CCollider::ETRAP){
			if (CCollider::Collision(m, y)){
				state = 5;	//�g���b�v�U����
				
			}
			
		}
		return;
	}

	//�v���C���[�e�Ƃ̏Փ˔���
	if (m->mTag == CCollider::EBODY2 && y->mTag == CCollider::EBULLET){

		if (CCollider::Collision(m, y)){
			mRotation = CVector(0.0f, 0.0f, 90.0f);	//���ɂȂ�
			state = 7;	//�C���
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