#include "CSceneGame.h"
//
#include "CCamera.h"
//
#include "CText.h"

#include"CInput.h"

int CSceneGame::StageCount = 0;
int CSceneGame::mBatteryMax = 60 * 60;
int CSceneGame::mBatteryNow = mBatteryNow + mBatteryMax;
int CSceneGame::mTimeMax = 60 * 60;
int CSceneGame::mTimeNow = mTimeNow + mTimeMax;
int CSceneGame::frame = 0;
int CSceneGame::frame2 = 0;

 CSound CSceneGame::Sound;
 CSound CSceneGame::Sound2;

CSceneGame::~CSceneGame(){
	
	//�V�[��������
	CTaskManager::Get()->Delete();

	//mEabled�����ׂ�false�ɂ���
	CTaskManager::Get()->AllDelete();

}

void CSceneGame::Init() {

	//�V�[���̐ݒ�
	mScene = EGAME;

	Sound.Load("bgm.wav");
	Sound2.Load("GameOver.wav");
	//BGM�Đ�
	Sound.Repeat();

	glMatrixMode(GL_PROJECTION);	//�s����v���W�F�N�V�������[�h�֕ύX
	glLoadIdentity();				//�s���������
	gluPerspective(75.0, (double)800 / (double)600, 1.0, 10000.0);	//3D�̉�ʂ�ݒ�

	glMatrixMode(GL_MODELVIEW);		//�s������f���r���[���[�h�֕ύX
	glLoadIdentity();				//�s���������



	//�e�L�X�g�t�H���g�̓ǂݍ��݂Ɛݒ�
	CText::mFont.Load("FontG.tga");
	CText::mFont.SetRowCol(1, 4096 / 64);	//�摜�̉���/1�����̉���

	mSky.Load("sky.obj", "sky.mtl");
	mRock.Load("Rock1.obj", "Rock1.mtl");
	mRover.Load("Rover1.obj", "Rover1.mtl");
	mCube.Load("cube.obj", "cube.mtl");
	mPlane.Load("plane.obj", "plane.mtl");
	mSphere.Load("sphere.obj", "sphere.mtl");


	mSofa.Load("sofa.obj", "sofa.mtl");	//�\�t�@
	mBed.Load("cama.obj", "cama.mtl");	//�x�b�h
	mDog.Load("Dog.obj", "Dog.mtl");	//��
	mTable.Load("Table.obj", "Table.mtl");	//�e�[�u��
	mKitchen.Load("kitchen.obj", "kitchen.mtl");	//�L�b�`��

	mPlayer.mpModel = &mSphere;	//�v���C���[���f��

	//new CObj(&mBed, CVector(-55.0f, -6.0f, 30.0f), CVector(0.0f, 90.0f, 0.0f), CVector(20.0f, 25.0f, 20.0f));

	new CObj(&mTable, CVector(-20.0f, -1.0f, 0.0f), CVector(), CVector(30.0f, 20.0f, 20.0f));

	new CObj(&mKitchen, CVector(50.0f, -1.0f, -20.0f), CVector(0.0f, -90.0f, 0.0f), CVector(8.0f, 10.0f, 10.0f));

	//new CObj(&mSofa, CVector(-55.0f, -1.0f, 10.0f), CVector(), CVector(10.0f, 10.0f, 10.0f));

	


	/* �����n��̕ύX */
	srand((unsigned)time(NULL));

	/*
	rand() % 100 - 50
	%100��100�Ŋ������]������߂�B0~99�܂łɂȂ�B
	-50�������ƂŁA-50~49�܂ł̃����_���l�ɂȂ�B
	*/
	//�e�N�X�`��(�ǎ�)
	std::shared_ptr<CTexture>kabe(new CTexture("kabe.tga"));
	

	//��
	new CObj(&mCube, CVector(100.0f, -1.0f, 0.0f), CVector(), CVector(W, H, 80.0f));
	
	//��
	new CObj(&mCube, CVector(-100.0f, -1.0f, 0.0f), CVector(), CVector(W, H, 80.0f));

	//�E
	new CObj(&mCube, CVector(0.0f, -1.0f, 80.0f), CVector(), CVector(100.0f, H, W));
	
	//��
	new CObj(&mCube, CVector(0.0f, -1.0f, -80.0f), CVector(), CVector(100.0f, H, W));

	//����
	new CObj(&mCube, CVector(0.0f, -1.0f, 0.0f), CVector(), CVector(5.0f, 20.0f, 5.0f));

	//�u���b�N(�ړ������邱�Ƃ��ł���)
	//new CBlock(&mCube, CVector(-20.0f, 3.0f, 40.0f), CVector(), CVector(2.0f, 2.0f, 5.0f));
	//new CBlock(&mCube, CVector(-30.0f, 0.0f, 20.0f), CVector(), CVector(5.0f, 2.0f, 2.0f));

	//�G(�ǔ�)
	new CBoss(&mDog, CVector(-20.0f, 0.0f, 50.0f), CVector(), CVector(1.0f, 1.0f, 1.0f));

	new CTrap(&mSphere, CVector(0.0f, 0.0f, 50.0f), CVector(), CVector(1.0f, 1.0f, 1.0f));

	//�z�[��
	new CHome(&mCube, CVector(-90.0f, -0.7f, 75.0f), CVector(), CVector(1.0f, 1.0f, 1.0f));


	//�v���C���[�����ʒu
	mPlayer.mPosition = CVector(-90.0f, 10.0f, 75.0f);
	mPlayer.mRotation = CVector(0.0f, -225.0f, 0.0f);
	
	//�e�N�X�`��(���j
	std::shared_ptr<CTexture>yuka(new CTexture("yuka.tga"));
	//��
	new CObj(&mPlane, CVector(0.0f, -1.5f, 0.0f), CVector(), CVector(100.0f, 1.0f, 80.0f));
	new CImage(yuka, CVector(0.0f, -1.49f, 0.0f), CVector(-90.0f, 0.0f, 0.0f), CVector(100.0f, 80.0f, 1.0f));

}

//�~�j�}�b�v
void CSceneGame::RenderMiniMap(){
	glPushMatrix();
	glViewport(600, 450, 200, 150); //��ʂ̕`��G���A�̎w��
	glLoadIdentity();
	//���_�����K�v
	gluLookAt(0, 90, 0, 0, 0, 0, 0, 0, 1);
	glDisable(GL_DEPTH_TEST);
	//�`��
	CTaskManager::Get()->Render();
	glPopMatrix();
	glViewport(0, 0, 800, 600); //��ʂ̕`��G���A�̎w��
	glEnable(GL_DEPTH_TEST);
}


void CSceneGame::Update() {

	if (mBatteryNow >= 0 && CHome::home == 0){
		mBatteryNow--;
	}
	//�[�d(�ő�l�𒴂��Ȃ��A�o�b�e���[����)
	else if (mBatteryMax >= mBatteryNow){
		mBatteryNow += 15;
	}
	
	//0�ȉ��ɂȂ�Ȃ�(�o�b�e���[)
	if (mBatteryNow < 0){
		mBatteryNow = 0;
	}
	
	//�������Ԍ���
	if (mBatteryNow > 0){
		mTimeNow--;
	}

	//0�ȉ��ɂȂ�Ȃ�(�^�C��)
	if (mTimeNow < 0){
		mTimeNow = 0;
	}

	frame++;
	//if (frame==300 || frame==500 || frame==700){
	//	new CBoss(&mDog, CVector(0.0f, 0.0f, -15.0f), CVector(), CVector(0.5f, 0.5f, 0.5f));
	//}

	if (frame < 1000 && frame % 100 == 0){
		//�S�~�̐���
		new CGomi(&mRock, CVector(RAND, 0.0f, RAND), CVector(), CVector(1.0f, 1.0f, 1.0f));
	}
	
	CTaskManager::Get()->Update();
	//�J�����̃p�����[�^���쐬����
	CVector e, c, u;//���_�A�����_�A�����
	if (CPlayer::Down == FALSE){
		//���_�����߂�
		e = CVector(0.0f, 2.0f, -1.0f)*mPlayer.mMatrix;
		//�����_�����߂�
		c = CVector(0.0f, 0.0f, 10.0f)*mPlayer.mMatrix;
		//����������߂�
		u = CVector(0.0f, 1.0f, 0.0f)*mPlayer.mMatrixRotate;
	}
	//�_���[�W���A�N�V����
	else{
		//���_�����߂�
		e = CVector(0.0f, 25.0f, -15.0f)*mPlayer.mMatrix;
		//�����_�����߂�
		c = CVector(0.0f, 0.0f, 10.0f)*mPlayer.mMatrix;
		//����������߂�
		u = CVector(0.0f, 1.0f, 0.0f)*mPlayer.mMatrixRotate;
	}

	//�����낵���_
	if (CKey::Push('I')){
		e = CVector(0.0f, 100.0f, 0.0f)*mPlayer.mMatrix;
	}

	//�m�F
	if (CKey::Push('P')){
		e = CVector(0.0f, -100.0f, 10.0f);
		u = CVector(20.0f, 0.0f, 0.0f)*mPlayer.mMatrixRotate;
	}

	//�J�����̐ݒ�
	Camera.Set(e, c, u);
	Camera.Render();

	//�w�i�`��(�J�����̌��2D�̑O�ɓ����j
	//mSky.Render();

	CTaskManager::Get()->Render();
	CCollisionManager::Get()->Render();

	//�R���W�����}�l�[�W���[�̏Փˏ���
	CTaskManager::Get()->TaskCollision();

	//�R���W�������X�g����폜
	CTaskManager::Get()->Delete();

	//�~�j�}�b�v�\��
	RenderMiniMap();

	//2D�`��J�n(UI�\��)
	Start2D(0, 800, 0, 600);

	//�Q�[���I�[�o�[����(�o�b�e���[�؂�,���Ԑ؂�j
	if (mBatteryNow <= 0 || mTimeNow <= 0){
		CText::DrawString("GAME OVER", 200, 330, 25, 25);
		
		Sound2.Play();	//�Q�[���I�[�o�[SE

		//�^�C�g����ʂ�
		if (CKey::Push(VK_RETURN)){
			mScene = ETITLE;
			Sound.Stop();	//BGM�I��
			mTimeNow = mTimeMax;
			mBatteryNow = mBatteryMax;
			CGomi::GomiCount = 0;
			frame = 0;
		}
	}

	//�{�X�Ƃ̏Փ�
	if (CPlayer::Down == TRUE){
		CText::DrawString("CRASH!", 285, 450, 25, 25);
	}

	//�N���A����(�S�~�S���)
	if (CPlayer::clear >= GAMECLEAR){
		CText::DrawString("STAGE CLEAR", 155, 330, 25, 25);
	}

	frame2++;
	if (frame2 < 60){
		CText::DrawString("START", 310, 400, 15, 15);
		//CText::DrawString("CLEAR:5", 290, 300, 15, 15);
		//frame2 = 0;
	}

	CText::DrawString("BATTERY", 17, 50, 11, 11);
	CText::DrawString("[", 15, 25, 11, 11);
	CText::DrawString("]", 305, 25, 11, 11);

	//�����𕶎���ɕϊ�����
	char buf[10];	//9�����܂�OK

	//��������
	sprintf(buf, "%d", mTimeNow / 60);
	CText::DrawString(buf, 15, 550, 15, 15);

	//�ڕW��
	sprintf(buf, "%d", CTrap::TrapCount);
	CText::DrawString(buf, 700, 30, 15, 15);

	//�S�~�ۗL��
	sprintf(buf, "%d", CGomi::GomiCount);
	CText::DrawString(buf, 300, 50, 15, 15);

	//2D�`��I��
	End2D();

	//�}�E�X�J�[�\�����N�����̍��W�Ɉړ�
	//CInput::SetMousePos(CPlayer::mpPlayer->mMouseX, CPlayer::mpPlayer->mMouseY);

	return;
}

//���̃V�[���̎擾
CScene::EScene CSceneGame::GetNextScene() {
	return mScene;
}
