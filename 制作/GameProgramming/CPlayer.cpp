#include"CPlayer.h"
#include"CSceneGame.h"
#include"CEffect.h"

int CPlayer::clear = 0;
int CPlayer::Dash = 0;
int CPlayer::Jump = 0;
int CPlayer::Down = 0;
int CPlayer::levelMax = 100;
int CPlayer::levelNow = 1;
int CPlayer::PlayerLevel = 1;
CPlayer *CPlayer::mpPlayer = 0;

CSound CPlayer::Sound;
CSound CPlayer::Sound2;

//�X�}�[�g�|�C���^�̊O���Q��
extern std::shared_ptr<CTexture>TextureExp(new CTexture());

CPlayer::CPlayer()
:mColBody(this, CVector(0.0f, 2.0f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), 3.0f)
//�T�[�`
, mSearch(this, CVector(0.0f, 0.0f, 5.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), R)
, mVelocityJump(0.0f)
, frame(0), frameMax(300), frame2(0)
{

	mColBody.mTag = CCollider::EBODY;
	mSearch.mTag = CCollider::ESEARCH;
	Sound.Load("jump.wav");
	Sound2.Load("act.wav");
}

void CPlayer::TaskCollision()
{
	mColBody.ChangePriority();
	mSearch.ChangePriority();
	CCollisionManager::Get()->Collision(&mColBody);
	CCollisionManager::Get()->Collision(&mSearch);
}



void CPlayer::Update(){

	if (Down == FALSE){
		if (clear < GAMECLEAR){
			if (CSceneGame::mBatteryNow > 0){
				if (CSceneGame::mTimeNow > 0){
					if (CKey::Push('A')){
						mRotation.mY += DIR;
					}

					if (CKey::Push('D')){
						mRotation.mY -= DIR;
					}

					if (CKey::Push('W')){
						mPosition = CVector(0.0f, 0.0f, FORWARD)*mMatrix;
						//�_�b�V��
						if (CKey::Push(VK_SHIFT)){
							mPosition = CVector(0.0f, 0.0f, DASH)*mMatrix;
							Dash = TRUE;
						}
						else{
							Dash = FALSE;
						}
					}

					if (CKey::Push('S')){
						mPosition = CVector(0.0f, 0.0f, BACK)*mMatrix;
						//�_�b�V��
						if (CKey::Push(VK_SHIFT)){
							mPosition = CVector(0.0f, 0.0f, -0.8f)*mMatrix;
							Dash = TRUE;
						}
						else{
							Dash = FALSE;
						}
					}
					//�W�����v
					if (CKey::Once('J') && mVelocityJump == 0){
						mVelocityJump = JUMPV0;
						Jump = TRUE;
						Sound.Play();
					}

					//���
					if (CKey::Once('H')){
						mSearch.mRadius = R - 7.0f;
					}

					//�A�C�e���g�p(�p���[)
					if (frameMax > frame){
						frame += 1;
					}
					
					//4�b�Ō��ʐ؂�
					if (frame > 240){
						mSearch.mRadius = R;
						frame = 0;
					}

					//�S�~���(�z�[���ɂ���Ƃ��A�S�~�������Ă���Ƃ�)
					if (CHome::home == TRUE && CGomi::GomiCount > 0){
						if (CKey::Once('E')){
							clear = clear + CGomi::GomiCount;
							CGomi::GomiCount = 0;
							CSceneGame::mTimeNow += 5 * 60;
							//�o���l�l��
							levelNow += 100;
							if (levelNow >= levelMax){
								//�o���l�������l�ɂ���
								levelNow = 1;
								//���x���A�b�v
								PlayerLevel += 1;
							}
						}
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
	Battery.Render();
	Time.Render();
	Level.Render();
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

	//�{�X�Ƃ̏Փ�
	if (m->mTag == CCollider::EBODY){
		if (y->mTag == CCollider::EBODY2){
			if (CCollider::Collision(m, y)){
				CSceneGame::mBatteryNow++;
				frame2++;
				Down = TRUE;

				//�G�t�F�N�g����
				new CEffect(mPosition, 5.0f, 5.0f, TextureExp, 4, 4, 1);

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
					mPosition = CVector(-70.0f, 10.0f, 50.0f);
					mRotation = CVector(0.0f, -225.0f, 0.0f);
					CSceneGame::mBatteryNow = CSceneGame::mBatteryMax;
					Down = FALSE;
					frame2 = 0;
				}
			}
		}
	}
}