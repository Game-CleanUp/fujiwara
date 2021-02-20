#include"CBoss.h"
#include"CSceneGame.h"

CBoss::CBoss(CModel*model, CVector position, CVector rotation, CVector scale)
:mColBody(this, CVector(1.0f, 1.5f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), 4.0f)
, mSearch(this, CVector(0.0f, 0.0f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), 20.0f)
, ActFrame(0), state(0), mVelocityJump(0.0f), onlyOnce(true)
{
	//���f���A�ʒu�A��]�A�g�k��ݒ肷��
	mpModel = model; //���f���̐ݒ�
	mPosition = position; //�ʒu�̐ݒ�
	mRotation = rotation; //��]�̐ݒ�
	mScale = scale; //�g�k�̐ݒ�

	mColBody.mTag = CCollider::EBODY2;
	mSearch.mTag = CCollider::ESEARCH2;

	SoundTrack.Load("Dog.wav");
	SoundDamage.Load("Edamage.wav");
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

		switch (state){

		case Move_Stop:	//�����~�܂�
			ActFrame += 1;
			if (ActFrame >STOPTIME){
				state = rand() % STATERAND;
				ActFrame = 0;
			}
			break;

		case Move_Left:	//�������Ɉړ�
			ActFrame += 1;
			if (ActFrame < 20){
				mRotation.mY += rand() % TURN;
			}
			if (ActFrame > 60){
				mPosition = CVector(0.0f, 0.0f, SPEED)*mMatrix;
			}
			if (ActFrame > 120){
				state = rand() % STATERAND;
				ActFrame = 0;
			}
			break;

		case Move_Right:	//�E�����Ɉړ�
			ActFrame += 1;
			if (ActFrame < 20){
				mRotation.mY -= rand() % TURN;
			}
			if (ActFrame > 60){
				mPosition = CVector(0.0f, 0.0f, SPEED)*mMatrix;
			}
			if (ActFrame > 120){
				state = rand() % STATERAND;
				ActFrame = 0;
			}
			break;

		case Move_Gomi:	//�S�~���o��
			ActFrame += 1;
			if (ActFrame > 180){
				new CGomi(NULL, mPosition, CVector(), CVector(0.5f, 0.5f, 0.5f));
				state = rand() % STATERAND;
				ActFrame = 0;
			}
			break;

		case Move_TrapTracking:	//�g���b�v�ǔ�
			if (left.Dot(dir_trap) > 0.0f){
				mRotation.mY += Rote;
			}
			else if (left.Dot(dir_trap) < 0.0f){
				mRotation.mY -= Rote;
			}

			mPosition = mPosition + dir_trap.Normalize() * TRACKSPEED;
			state = rand() % STATERAND;
			break;

		case Move_PlayerTracking:	//�v���C���[�ǔ�
			if (left.Dot(dir_player) > 0.0f){
				mRotation.mY += Rote;
			}
			else if (left.Dot(dir_player) < 0.0f){
				mRotation.mY -= Rote;
			}
			
			if (onlyOnce){
				SoundTrack.Repeat();
				onlyOnce = false;
			}

			mPosition = mPosition + dir_player.Normalize() * TRACKSPEED;
			state = rand() % STATERAND;
			break;

		case Move_Damage:	//�_���[�W
			ActFrame += 1;
			if (ActFrame > DAMAGETIME){
				mRotation = CVector(0.0f, 0.0f, 0.0f);	//���A
				ActFrame = 0;
			
				state = rand() % STATERAND;
			}
			break;
		}

	if (CSceneGame::mBatteryNow <= 0 || CSceneGame::mTimeNow <= 0){
		mEnabled = false;
	}

	mVelocityJump = JUMPV0;
	//�d�͉����x
	mVelocityJump -= G;

	mPosition.mY = mPosition.mY - mVelocityJump;
	
	CCharacter::Update();
}

void CBoss::Render(){
	CCharacter::Render();

	//CScene::Start2D(0, 800, 0, 600);
	//CText::DrawString("BOW", 400, 300, 25, 25);
	//CScene::End2D();
}

void CBoss::Collision(CCollider*m, CCollider*y){

	//�v���C���[����
	if (m->mTag == CCollider::ESEARCH2 && y->mTag == CCollider::EBODY){
		if (CCollider::Collision(m, y)){
			if (state != Move_TrapTracking && state != Move_Damage){	//�g���b�v�A�_���[�W�ȊO
				state = Move_PlayerTracking;
			}
		}
		else{
			onlyOnce = true;
			SoundTrack.Stop();
		}
	}
	
	//�g���b�v����
	if (m->mTag == CCollider::ESEARCH2){
		if (y->mTag == CCollider::ETRAP){
			if (CCollider::Collision(m, y)){
				if (state != Move_Damage){	//�_���[�W�ȊO
					state = Move_TrapTracking;
				}
			}
		}
		return;
	}

	//�v���C���[�e�Ƃ̏Փ˔���
	if (m->mTag == CCollider::EBODY2 && y->mTag == CCollider::EBULLET){
		if (CCollider::Collision(m, y)){
			mPosition = CVector(2.0f, 0.0f, 0.0f)*mMatrix;	//���˂�
			mRotation = CVector(0.0f, 0.0f, 90.0f);	//���ɂȂ�
			SoundDamage.Play();
			SoundTrack.Stop();
			onlyOnce = true;
			state = Move_Damage;
		}
	}

	//���g�̃R���C�_�^�C�v�̔���
	switch (m->mType){
	case CCollider::ESPHERE:
		//���肪�O�p�R���C�_
		if (y->mType == CCollider::ETRIANGLE){
			CVector adjust;//�����l�x�N�g��
			//�O�p�`�Ƌ��̏Փ˔���
			if (CCollider::CollisionTriangleSphere(y, m, &adjust)){
				//���n
				mVelocityJump = 0;
			}
			//�ʒu�̍X�V
			mPosition = mPosition - adjust*-1;

			CCharacter::Update();
		}
		break;
	}
}