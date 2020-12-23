#include"CPlayer.h"
#include"CSceneGame.h"

int CPlayer::Life = 100;
int CPlayer::clear = 0;
int CPlayer::Dash = 0;
int CPlayer::Jump = 0;
int CPlayer::Down = 0;
CPlayer *CPlayer::mpPlayer = 0;

//void CPlayer::Init(){
//	mRock.Load("Rock1.obj", "Rock1.mtl");
//}

CPlayer::CPlayer()
:mColBody(this, CVector(0.0f, 1.0f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), 1.5f)
//�T�[�`
, mSearch(this, CVector(0.0f, 0.0f, 5.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), R)
, mVelocityJump(0.0f)
, frame(0), level(100), frameMax(300), frame2(0)
{

	mColBody.mTag = CCollider::EBODY;
	mSearch.mTag = CCollider::ESEARCH;

}


void CPlayer::Update(){

	if (Down == FALSE){
		if (clear < GAMECLEAR){
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
						mPosition = CVector(0.0f, 0.0f, 1.3f)*mMatrix;
						Dash = TRUE;
					}
					else{
						Dash = FALSE;
					}
				}

				if (CKey::Push('S')){
					mPosition = CVector(0.0f, 0.0f, -0.5f)*mMatrix;
					//�_�b�V��
					if (CKey::Push(VK_SHIFT)){
						mPosition = CVector(0.0f, 0.0f, -1.3f)*mMatrix;
						Dash = TRUE;
					}
					else{
						Dash = FALSE;
					}
				}

				if (CKey::Once('J') && mVelocityJump == 0){
					mVelocityJump = JUMPV0;
					Jump = TRUE;
				}

				//���
				if (CKey::Once('H')){
					mSearch.mRadius = R - 7.0f;
				}

				//�A�C�e���g�p(�p���[)
				if (frameMax > frame){
					frame += 1;
				}
				//�A�C�e���������Ă���Ƃ�
				if (CPower::power >= 1){
					//���ʂ���������g����
					if (mSearch.mRadius < 10){
						if (CKey::Once('Q')){
							mSearch.mRadius = R + 3.0f;
							CPower::power -= 1;

						}
					}
				}
				//4�b�Ō��ʐ؂�
				if (frame > 240){
					mSearch.mRadius = R;
					frame = 0;
				}

				//�S�~���
				if (CHome::home == TRUE){
					if (CKey::Push('E')){
						clear = clear + CGomi::GomiCount;
						CGomi::GomiCount = 0;
					}
				}
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
				Jump = FALSE;
			}

			//�ʒu�̍X�V
			mPosition = mPosition - adjust*-1;

			//�s��̍X�V
			CCharacter::Update();
		}

		break;
	}

	//�A�C�e�����
	if (y->mTag == CCollider::EPOWER){
		CPower::power += 1;
	}

	//�{�X�Ƃ̏Փ�
	if (m->mTag == CCollider::EBODY){
		if (y->mTag == CCollider::EBODY2){
			if (CCollider::Collision(m, y)){
				CSceneGame::mTimeNow++;
				frame2++;
				Down = TRUE;
				//�����Ă���S�~������ɏo��������
				switch (CGomi::GomiCount){

				case 1:
					//�v���C���[�̎���ɏo��
					for (int i = 0; i < 1; i++){
						new CGomi(NULL, mPosition + CVector(0.0f, 15.0f, DROP)*matrix.RotateY(DROP_RAND), CVector(), CVector(1.0f, 1.0f, 1.0f));
					}
					CGomi::GomiCount = 0;
					break;

				case 2:
					for (int i = 0; i < 2; i++){
						new CGomi(NULL, mPosition + CVector(0.0f, 15.0f, DROP)*matrix.RotateY(DROP_RAND), CVector(), CVector(1.0f, 1.0f, 1.0f));
					}
					CGomi::GomiCount = 0;
					break;

				case 3:
					for (int i = 0; i < 3; i++){
						new CGomi(NULL, mPosition + CVector(0.0f, 15.0f, DROP)*matrix.RotateY(DROP_RAND), CVector(), CVector(1.0f, 1.0f, 1.0f));
					}
					CGomi::GomiCount = 0;
					break;

				case 4:
					for (int i = 0; i < 4; i++){
						new CGomi(NULL, mPosition + CVector(0.0f, 15.0f, DROP)*matrix.RotateY(DROP_RAND), CVector(), CVector(1.0f, 1.0f, 1.0f));
					}
					CGomi::GomiCount = 0;
					break;

				case 5:
					for (int i = 0; i < 5; i++){
						new CGomi(NULL, mPosition + CVector(0.0f, 15.0f, DROP)*matrix.RotateY(DROP_RAND), CVector(), CVector(1.0f, 1.0f, 1.0f));
					}
					CGomi::GomiCount = 0;
					break;
				}

				//���g���C(�z�[���ɖ߂�)
				if (frame2 > RETRY){
					//�����ʒu
					mPosition = CVector(-50.0f, 10.0f, 0.0f);
					mRotation = CVector(0.0f, 90.0f, 0.0f);
					CSceneGame::mTimeNow = CSceneGame::mTimeMax;
					Down = FALSE;
					frame2 = 0;
				}
			}
		}
	}
}