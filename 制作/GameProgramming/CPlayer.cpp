#include"CPlayer.h"
#include"CSceneGame.h"
#include"CEffect.h"

int CPlayer::Score = 0;
int CPlayer::Down = 0;

CPlayer *CPlayer::mpPlayer = 0;

CSound CPlayer::SoundJump;
CSound CPlayer::SoundBomb;
CSound CPlayer::SoundAttack;
CSound CPlayer::SoundThrow;

//�X�}�[�g�|�C���^�̊O���Q��
extern std::shared_ptr<CTexture>TextureExp(new CTexture());

CPlayer::CPlayer()
:mColBody(this, CVector(0.0f, 0.5f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), 1.5f)
//�T�[�`
, mSearch(this, CVector(0.0f, -3.0f, 5.0f), CVector(), CVector(1.0f, 1.0f, 1.0f), R)
, mVelocityJump(0.0f), frameMax(300), frameRetry(0), onlyOnce(true)
{

	mColBody.mTag = CCollider::EBODY;
	mSearch.mTag = CCollider::ESEARCH;

	SoundJump.Load("jump.wav");	//�W�����v��
	SoundBomb.Load("Bomb.wav");	//������
	SoundAttack.Load("shoot.wav");	//�U����
	SoundThrow.Load("throw.wav");	//�S�~���

	//�����e�N�X�`��
	TextureExp->Load("exp.tga");

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

	if (Down == false){
		if (CSceneGame::mBatteryNow > 0 && CSceneGame::mTimeNow > 0){

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
					CSceneGame::mBatteryNow -= 10;
				}
			}

			if (CKey::Push('S')){
				mPosition = CVector(0.0f, 0.0f, BACK)*mMatrix;
			}

			//�X�y�[�X�L�[���͂Ŕ���
			if (mVelocityJump == 0){	//�W�����v������
				if (CKey::Once(VK_SPACE)){
					CBullet*bullet = new CBullet();
					bullet->Set(0.2f, 5.0f);	//�e�̃T�C�Y
					bullet->mPosition = CVector(0.0f, -0.1f, 0.0f)*mMatrix;
					bullet->mRotation = mRotation;
					bullet->mTag = CCharacter::EBULLET;
					SoundAttack.Play();
					CSceneGame::mBatteryNow -= 100;	//�o�b�e���[����
				}
			}

			//�g���b�v�ݒu
			if (CTrap::TrapCount > 0){
				if (CKey::Once('Q')){
					new CTrap(NULL, mPosition, CVector(), CVector(0.3f, 0.3f, 0.3f));
					SoundThrow.Play();
					CTrap::TrapCount -= 1;	//�g���b�v����
				}
			}
			//�W�����v
			if (CKey::Once('J') && mVelocityJump == 0){
				mVelocityJump = JUMPV0;
				CSceneGame::mBatteryNow -= 300;	//�o�b�e���[����
				SoundJump.Play();
			}

			//�S�~���̂Ă�,�X�R�A���Z(�z�[���ɂ���Ƃ��A�S�~�������Ă���Ƃ�)
			if (CHome::home == true && CGomi::GomiCount > 0){
				if (CKey::Once('E')){
					Score += 1;
					SoundThrow.Play();
					CGomi::GomiCount -= 1;
				}
			}
		}
	}

	//�d�͉����x
	mVelocityJump -= G;
	//�ړ�
	mPosition.mY = mPosition.mY + mVelocityJump;

	if (CHome::home == true){
		onlyOnce = true;
	}

	CCharacter::Update();
}

void CPlayer::Render(){
	CCharacter::Render();
	Back.Render();
	Battery.Render();
	Time.Render();
	TrapUi.Render();
	GomiUI.Render();
}

void CPlayer::Collision(CCollider*m, CCollider*y){

	if (m->mTag == CCollider::ESEARCH){
		return;
	}

	switch (m->mType){
	case CCollider::ESPHERE://���R���C�_
		//���肪�O�p�R���C�_
		if (y->mType == CCollider::ETRIANGLE){
			CVector adjust;//�����l�x�N�g��
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

	//�{�X�Ƃ̏Փ�
	if (m->mTag == CCollider::EBODY && y->mTag == CCollider::EBODY2){
		if (CCollider::Collision(m, y)){

			frameRetry++;	//���A�܂ł̎���
			Down = true;

			if (onlyOnce){
				SoundBomb.Play();	//������
				onlyOnce = false;
			}

			//�G�t�F�N�g����(����)
			new CEffect(mPosition, 10.0f, 10.0f, TextureExp, 4, 4, 1);

			//�����Ă���S�~������ɏo��������
			switch (CGomi::GomiCount){

			case 1:
				//�v���C���[�̎���ɏo��
				for (int i = 0; i < 1; i++){
					new CGomi(NULL, mPosition + CVector(0.0f, 15.0f, DROP)*matrix.RotateY(DROP_DIR), CVector(), CVector(0.5f, 0.5f, 0.5f));
				}
				CGomi::GomiCount = 0;
				break;

			case 2:
				for (int i = 0; i < 2; i++){
					new CGomi(NULL, mPosition + CVector(0.0f, 15.0f, DROP)*matrix.RotateY(DROP_DIR), CVector(), CVector(0.5f, 0.5, 0.5f));
				}
				CGomi::GomiCount = 0;
				break;

			case 3:
				for (int i = 0; i < 3; i++){
					new CGomi(NULL, mPosition + CVector(0.0f, 15.0f, DROP)*matrix.RotateY(DROP_DIR), CVector(), CVector(0.5f, 0.5, 0.5f));
				}
				CGomi::GomiCount = 0;
				break;

			case 4:
				for (int i = 0; i < 4; i++){
					new CGomi(NULL, mPosition + CVector(0.0f, 15.0f, DROP)*matrix.RotateY(DROP_DIR), CVector(), CVector(0.5f, 0.5, 0.5f));
				}
				CGomi::GomiCount = 0;
				break;

			case 5:
				for (int i = 0; i < 5; i++){
					new CGomi(NULL, mPosition + CVector(0.0f, 15.0f, DROP)*matrix.RotateY(DROP_DIR), CVector(), CVector(0.5f, 0.5, 0.5f));
				}
				CGomi::GomiCount = 0;
				break;
			}

			//���g���C(�����ʒu�ɖ߂�)
			if (frameRetry >= RETRY){
				//�����ʒu
				mPosition = CVector(70.0f, 10.0f, 55.0f);
				mRotation = CVector(0.0f, 225.0f, 0.0f);
				CSceneGame::mBatteryNow = CSceneGame::mBatteryMax;
				Down = false;
				frameRetry = 0;
			}
		}
	}
}