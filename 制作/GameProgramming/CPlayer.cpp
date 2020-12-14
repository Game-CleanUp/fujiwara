#include"CPlayer.h"
#include"CSceneGame.h"

int CPlayer::Life = 3;
int CPlayer::clear = 0;
int CPlayer::Dash = 0;
int CPlayer::Jump = 0;
CPlayer *CPlayer::mpPlayer = 0;


CPlayer::CPlayer()
:mColBody(this, CVector(0.0f, 1.0f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), 1.5f)
//�T�[�`
, mSearch(this, CVector(0.0f, 0.0f, -1.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), R)
, mVelocityJump(0.0f)
, frame(0), level(100)
{

	mColBody.mTag = CCollider::EBODY;
	mSearch.mTag = CCollider::ESEARCH;

	HP.x = -240;
	HP.y = -280;
	HP.w = 150;
	HP.h = 10;

}


void CPlayer::Update(){

	if (CSceneGame::mTimeNow > 0){
		if (CKey::Push('A')){
			mRotation.mY += 2.0f;
		}

		if (CKey::Push('D')){
			mRotation.mY -= 2.0f;
		}

		if (CKey::Push('W')){
			mPosition = CVector(0.0f, 0.0f, 0.5f)*mMatrix;
			//�_�b�V��
			if (CKey::Push(VK_SHIFT)){
				mPosition = CVector(0.0f, 0.0f, 1.0f)*mMatrix;
				Dash = TRUE;
			}
			else{
				Dash = FALSE;
			}
		}

		if (CKey::Push('S')){
			mPosition = CVector(0.0f, 0.0f, -0.5f)*mMatrix;
		}

		if (CKey::Once('J') /*&& mVelocityJump == 0*/){
			mVelocityJump = JUMPV0;
			Jump = TRUE;
		}
		else{
			Jump = FALSE;
		}

		//�A�C�e���g�p(�p���[)
		frame += 1;
		if (CPower::power >= 1){
			if (CKey::Once('Q')){
				mSearch.mRadius = R + 5.0f;
				CPower::power -= 1;
			}
		}
		//5�b�Ō��ʐ؂�
		if (frame > 300){
			mSearch.mRadius = R;
			frame = 0;
		}

		//�S�~���
		if (CHome::home == TRUE){
			if (CKey::Push(VK_SPACE)){
				clear = clear + CGomi::GomiCount;
				CGomi::GomiCount = 0;
			}
		}
	}
	//�d�͉����x
	mVelocityJump -= G;
	//�ړ�
	mPosition.mY = mPosition.mY + mVelocityJump;

	
	CCharacter::Update();
}

void CPlayer::Render(){
	CCharacter::Render();
	Back.Render();
	HP.Render();

}



void CPlayer::Collision(CCollider*m, CCollider*y){
	if (m->mTag == CCollider::ESEARCH){
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

	if (y->mTag == CCollider::EPOWER){
		if (CCollider::Collision(m, y)){
			CPower::power += 1;
		}
	}
	if (y->mTag == CCollider::ESPEED){
		if (CCollider::Collision(m, y)){
			CSpeed::speed += 1;
		}
	}
}
