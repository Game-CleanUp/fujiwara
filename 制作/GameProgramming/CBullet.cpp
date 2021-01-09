#include"CBullet.h"
#include"CPlayer.h"
#include"CSceneGame.h"
CBullet::CBullet()
:mLife(50), mCollider(this, CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 1.0f)
{
	mpModel = &CSceneGame::mGun;
	if (CPlayer::mpPlayer->mstate == CPlayer::mpPlayer->EAR){
		mLife = 75;
	}
	if (CPlayer::mpPlayer->mstate == CPlayer::mpPlayer->ESR){
		mLife = 100;
	}
	if (CPlayer::mpPlayer->mstate == CPlayer::mpPlayer->ESMG){
		mLife = 40;
	}
	if (CPlayer::mpPlayer->mstate == CPlayer::mpPlayer->EMINE){
		mLife = 120;
	}
	mCollider.mTag = CCollider::EBULLET;
	//mCollider.mTag = CCollider::EPLAYER2;
	//mCollider.mTag = CCollider::EENEMY2;
	//mCollider.mTag = CCollider::EROCK;
}
CBullet::CBullet(CModel *model, CVector position, CVector rotation, CVector scale)
:mLife(50), mCollider(this, CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 0.1f)
{

	mpModel = &CSceneGame::mGun;
	mpModel = model;
	mPosition = position;
	mRotation = rotation;
	mScale = scale;
	if (CPlayer::mpPlayer->mstate == CPlayer::mpPlayer->EAR){
		mLife = 75;
	}
	if (CPlayer::mpPlayer->mstate == CPlayer::mpPlayer->ESR){
		mLife = 100;
	}
	if (CPlayer::mpPlayer->mstate == CPlayer::mpPlayer->ESMG){
		mLife = 40;
	}
	if (CPlayer::mpPlayer->mstate == CPlayer::mpPlayer->EMINE){
		mLife = 120;
	}
	mCollider.mTag = CCollider::EBULLET;
	//mCollider.mTag = CCollider::EPLAYER2;
	//mCollider.mTag = CCollider::EENEMY2;
	//mCollider.mTag = CCollider::EROCK;
}

//���Ɖ��s���̐ݒ�
//Set(��,���s)
void CBullet::Set(float w, float d){
	//�X�P�[���ݒ�
	mScale = CVector(1.0f, 1.0f, 1.0f);
	//�O�p�`�̒��_�ݒ�
	mT.SetVertex(CVector(w, 0.0f, 0.0f), CVector(-w, 0.0f, 0.0f), CVector(0.0f, 0.0f, d));
	//�O�p�`�̖@���ݒ�
	mT.SetNormal(CVector(0.0f, 1.0f, 0.0f));
}

//�X�V
void CBullet::Update(){

	//�������Ԃ̔���
	if (mLife-- > 0){
		CCharacter::Update();
		//�ʒu�X�V
		
		//�ʒu�X�V
		mPosition = CVector(0.0f, 0.0f, 1.0f) * mMatrix;
	}
	else{
		//�����ɂ���
		mEnabled = false;
	}
}

//�Փˏ���
//Collision(�R���C�_1,�R���C�_2)
void CBullet::Collision(CCollider *m, CCollider *y){
	//���ɋ��R���C�_�̎�
	if (m->mType == CCollider::ESPHERE && y->mType == CCollider::ESPHERE){
		//�R���C�_�̂��Ƃ����Փ˂��Ă��邩����
		if (CCollider::Collision(m, y)){
			//�v���C���[�̎�
			if (y->mTag == CCollider::EPLAYER2){
				//�Փ˂��Ă���Ƃ��͖����ɂ���
				mEnabled = false;
			}
			//�G�̎�
			if (y->mTag == CCollider::EENEMY2){
				//�Փ˂��Ă���Ƃ��͖����ɂ���
				mEnabled = false;
			}
			//��̎�
			if (y->mTag == CCollider::EROCK){
				//�Փ˂��Ă���Ƃ��͖����ɂ���
				mEnabled = false;
			}
			if (y->mTag == CCollider::EBULLET2){
				mEnabled = false;
			}
		}
	}
}

//�`��
void CBullet::Render(){
	CCharacter::Render();
	//DIFUSE���F�ݒ�
	float c[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	//�O�p�`�`��
	mT.Render(mMatrix);
	//�m�F�p���\�b�h
	//mCollider.Render();
}
CBullet3::CBullet3()
:mLife(40), mCollider(this, CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 0.1f)
{
	mpModel = &CSceneGame::mGun;
	
	mCollider.mTag = CCollider::EBULLET3;
	//mCollider.mTag = CCollider::EPLAYER2;
	//mCollider.mTag = CCollider::EENEMY2;
	//mCollider.mTag = CCollider::EROCK;
}
CBullet3::CBullet3(CModel *model, CVector position, CVector rotation, CVector scale)
:mLife(50), mCollider(this, CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 0.1f)
{

	mpModel = &CSceneGame::mGun;
	mpModel = model;
	mPosition = position;
	mRotation = rotation;
	mScale = scale;
	
	mCollider.mTag = CCollider::EBULLET3;
	//mCollider.mTag = CCollider::EPLAYER2;
	//mCollider.mTag = CCollider::EENEMY2;
	//mCollider.mTag = CCollider::EROCK;
}

//���Ɖ��s���̐ݒ�
//Set(��,���s)
void CBullet3::Set(float w, float d){
	//�X�P�[���ݒ�
	mScale = CVector(1.0f, 1.0f, 1.0f);
	//�O�p�`�̒��_�ݒ�
	mT.SetVertex(CVector(w, 0.0f, 0.0f), CVector(-w, 0.0f, 0.0f), CVector(0.0f, 0.0f, d));
	//�O�p�`�̖@���ݒ�
	mT.SetNormal(CVector(0.0f, 1.0f, 0.0f));
}

//�X�V
void CBullet3::Update(){

	//�������Ԃ̔���
	if (mLife-- > 0){
		CCharacter::Update();
		
		//�ʒu�X�V
		mPosition = CVector(0.0f, 0.0f, 1.0f) * mMatrix;
	}
	else{
		//�����ɂ���
		mEnabled = false;
	}
}

//�Փˏ���
//Collision(�R���C�_1,�R���C�_2)
void CBullet3::Collision(CCollider *m, CCollider *y){
	//���ɋ��R���C�_�̎�
	if (m->mType == CCollider::ESPHERE && y->mType == CCollider::ESPHERE){
		//�R���C�_�̂��Ƃ����Փ˂��Ă��邩����
		if (CCollider::Collision(m, y)){
			//�v���C���[�̎�
			if (y->mTag == CCollider::EPLAYER2){
				//�Փ˂��Ă���Ƃ��͖����ɂ���
				mEnabled = false;
			}
			//�G�̎�
			if (y->mTag == CCollider::EENEMY2){
				//�Փ˂��Ă���Ƃ��͖����ɂ���
				mEnabled = false;
			}
			//��̎�
			if (y->mTag == CCollider::EROCK){
				//�Փ˂��Ă���Ƃ��͖����ɂ���
				mEnabled = false;
			}
		}
	}
}

//�`��
void CBullet3::Render(){
	CCharacter::Render();
	//DIFUSE���F�ݒ�
	float c[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	//�O�p�`�`��
	mT.Render(mMatrix);
	//�m�F�p���\�b�h
	//mCollider.Render();
}