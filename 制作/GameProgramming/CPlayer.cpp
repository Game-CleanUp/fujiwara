#include"CPlayer.h"
#include"CSceneGame.h"
#include"CEffect.h"

int CPlayer::clear = 0;
int CPlayer::Down = 0;

CPlayer *CPlayer::mpPlayer = 0;

CSound CPlayer::Sound;
CSound CPlayer::Sound2;
CSound CPlayer::Sound3;	//������

//�X�}�[�g�|�C���^�̊O���Q��
extern std::shared_ptr<CTexture>TextureExp(new CTexture());

CPlayer::CPlayer()
:mColBody(this, CVector(0.0f, 0.0f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), 2.0f)
//�T�[�`
, mSearch(this, CVector(0.0f, 0.0f, 5.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), R)
, mVelocityJump(0.0f)
, frame(0), frameMax(300), frame2(0)
{

	mColBody.mTag = CCollider::EBODY;
	mSearch.mTag = CCollider::ESEARCH;
	Sound.Load("jump.wav");	//�W�����v��
	Sound2.Load("act.wav");	//�ړ���
	Sound.Load("Bomb.wav");	//������

	//�����e�N�X�`��
	TextureExp->Load("exp.tga");

	//�N�����̃}�E�X�J�[�\���̍��W���o����
	CInput::GetMousePos(&mMouseX, &mMouseY);
	mMouseX = 1920 / 2;
	mMouseY = 1080 / 2;

	mpPlayer = this;

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
		
					}

					if (CKey::Push('S')){
						mPosition = CVector(0.0f, 0.0f, BACK)*mMatrix;
					}

					//�X�y�[�X�L�[���͂Ŕ���
					if (mVelocityJump == 0){	//�W�����v������
						if (CKey::Once(VK_SPACE)){
							CBullet*bullet = new CBullet();
							bullet->Set(0.3f, 2.0f);
							bullet->mPosition = CVector(0.0f, 0.0f, 0.0f)*mMatrix;
							bullet->mRotation = mRotation;
							bullet->mTag = CCharacter::EBULLET;
							CSceneGame::mBatteryNow -= 100;	//�o�b�e���[����
						}
					}
					if (CTrap::TrapCount > 0){
						if (CKey::Once('Q')){
							//t���b�v�ݒu
							new CTrap(NULL, mPosition, CVector(), CVector(0.7f, 0.7f, 0.7f));
							CTrap::TrapCount -= 1;	//�g���b�v����
						}
					}
					//�W�����v
					if (CKey::Once('J') && mVelocityJump == 0){
						mVelocityJump = JUMPV0;
						CSceneGame::mBatteryNow -= 5 * 60;	//�o�b�e���[����
						Sound.Play();
					}
					
					if (CKey::Push('R')){
						mRotation.mX += 0.3f;
					}
						
					//�S�~���̂Ă�(�z�[���ɂ���Ƃ��A�S�~�������Ă���Ƃ�)
					if (CHome::home == TRUE && CGomi::GomiCount > 0){
						if (CKey::Once('E')){
							clear = clear + CGomi::GomiCount;
							CGomi::GomiCount = 0;
							}
						}

					//// �}�E�X�J�[�\���̍��W���擾
					//	int mx, my;
					//CInput::GetMousePos(&mx, &my);
					//if (mx < mMouseX) {
					//	//�}�E�X�̈ړ��ʂ̕�������]
					//	mRotation.mY += (mMouseX - mx) / 5.0;
					//}
					//if (mMouseX < mx) {
					//	//�}�E�X�̈ړ��ʂ̕�������]
					//	mRotation.mY += (mMouseX - mx) / 5.0;
					//}

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
	if (Down == TRUE){
		//�������Đ�
		Sound3.Play();
	}

	//�{�X�Ƃ̏Փ�
	if (y->mTag == CCollider::EBODY2){
		if (CCollider::Collision(m, y)){

			CSceneGame::mBatteryNow++;
			frame2++;	//���A�܂ł̎���
			Down = TRUE;

			//�G�t�F�N�g����(����)
			new CEffect(mPosition, 8.0f, 8.0f, TextureExp, 4, 4, 1);

			//�������Đ�
			//Sound3.Play();

			//�����Ă���S�~������ɏo��������
			switch (CGomi::GomiCount){

			case 1:
				//�v���C���[�̎���ɏo��
				for (int i = 0; i < 1; i++){
					new CGomi(NULL, mPosition + CVector(0.0f, 15.0f, DROP)*matrix.RotateY(DROP_DIR), CVector(), CVector(1.0f, 1.0f, 1.0f));
				}
				CGomi::GomiCount = 0;
				break;

			case 2:
				for (int i = 0; i < 2; i++){
					new CGomi(NULL, mPosition + CVector(0.0f, 15.0f, DROP)*matrix.RotateY(DROP_DIR), CVector(), CVector(1.0f, 1.0f, 1.0f));
				}
				CGomi::GomiCount = 0;
				break;

			case 3:
				for (int i = 0; i < 3; i++){
					new CGomi(NULL, mPosition + CVector(0.0f, 15.0f, DROP)*matrix.RotateY(DROP_DIR), CVector(), CVector(1.0f, 1.0f, 1.0f));
				}
				CGomi::GomiCount = 0;
				break;

			case 4:
				for (int i = 0; i < 4; i++){
					new CGomi(NULL, mPosition + CVector(0.0f, 15.0f, DROP)*matrix.RotateY(DROP_DIR), CVector(), CVector(1.0f, 1.0f, 1.0f));
				}
				CGomi::GomiCount = 0;
				break;

			case 5:
				for (int i = 0; i < 5; i++){
					new CGomi(NULL, mPosition + CVector(0.0f, 15.0f, DROP)*matrix.RotateY(DROP_DIR), CVector(), CVector(1.0f, 1.0f, 1.0f));
				}
				CGomi::GomiCount = 0;
				break;
			}

			//���g���C(�z�[���ɖ߂�)
			if (frame2 >= RETRY){
				//�����ʒu
				mPosition = CVector(-90.0f, 10.0f, 70.0f);
				mRotation = CVector(0.0f, -225.0f, 0.0f);
				CSceneGame::mBatteryNow = CSceneGame::mBatteryMax;
				Down = FALSE;
				frame2 = 0;
			}
		}
	}
}