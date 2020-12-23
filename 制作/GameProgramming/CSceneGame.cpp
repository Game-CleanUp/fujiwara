#include "CSceneGame.h"
//
#include "CCamera.h"
//
#include "CText.h"

int CSceneGame::StageCount = 0;
int CSceneGame::mBatteryMax = 60 * 60;
int CSceneGame::mBatteryNow = mBatteryNow + mBatteryMax;
int CSceneGame::mTimeMax = 60 * 60;
int CSceneGame::mTimeNow = mTimeNow + mTimeMax;
int CSceneGame::frame = 0;

CSceneGame::~CSceneGame() {
	
	//�V�[��������
	CTaskManager::Get()->Delete();

	//mEabled�����ׂ�false�ɂ���
	CTaskManager::Get()->AllDelete();
	//CTaskManager::Get()->Delete();

}


void CSceneGame::Init() {

	//�V�[���̐ݒ�
	mScene = EGAME;

	glMatrixMode(GL_PROJECTION);	//�s����v���W�F�N�V�������[�h�֕ύX
	glLoadIdentity();				//�s���������
	//	gluOrtho2D(-width / 2, width / 2, -height / 2, height / 2);	//2D�̉�ʂ�ݒ�
	gluPerspective(75.0, (double)800 / (double)600, 1.0, 10000.0);	//3D�̉�ʂ�ݒ�

	glMatrixMode(GL_MODELVIEW);		//�s������f���r���[���[�h�֕ύX
	glLoadIdentity();				//�s���������



	//�e�L�X�g�t�H���g�̓ǂݍ��݂Ɛݒ�
	CText::mFont.Load("FontG.tga");
	CText::mFont.SetRowCol(1, 4096 / 64);

	mSky.Load("sky.obj", "sky.mtl");
	mRock.Load("Rock1.obj", "Rock1.mtl");
	mRover.Load("Rover1.obj", "Rover1.mtl");
	mCube.Load("cube.obj", "cube.mtl");
	mPlane.Load("plane.obj", "plane.mtl");
	//mSofa.Load("Sofa.obj", "Sofa.mtl");
	mSphere.Load("sphere.obj", "sphere.mtl");
	mPlayer.mpModel = &mCube;

	/* �����n��̕ύX */
	srand((unsigned)time(NULL));

	/*
	rand() % 100 - 50
	%100��100�Ŋ������]������߂�B0~99�܂łɂȂ�B
	-50�������ƂŁA-50~49�܂ł̃����_���l�ɂȂ�B
	*/

	//��
	new CObj(&mCube, CVector(150.0f, 0.0f, 0.0f), CVector(), CVector(W, H, 180.0f));
	//��
	new CObj(&mCube, CVector(-150.0f, 0.0f, 35.0f), CVector(), CVector(W, H, 150.0f));
	new CObj(&mCube, CVector(-145.0f, 0.0f, 35.0f), CVector(), CVector(W, H, 150.0f));

	//�E
	new CObj(&mCube, CVector(0.0f, 0.0f, 180.0f), CVector(), CVector(150.0f, H, W));
	//��
	new CObj(&mCube, CVector(75.0f, 0.0f, -180.0f), CVector(), CVector(75.0f, H, W));
	//��2
	new CObj(&mCube, CVector(-120.0f, 0.0f, -100.0f), CVector(), CVector(30.0f, H, 10.0f));

	//�L���O
	new CObj(&mCube, CVector(-80.0f, 0.0f, -110.0f), CVector(), CVector(75.0f, H, W));

	//��������
	new CObj(&mCube, CVector(0.0f, 0.0f, -100.0f), CVector(), CVector(W, H, 80.0f));
	//�E������
	new CObj(&mCube, CVector(60.0f, 0.0f, 100.0f), CVector(), CVector(W, H, 75.0f));
	new CObj(&mCube, CVector(55.0f, 0.0f, 100.0f), CVector(), CVector(W, H, 75.0f));

	new CObj(&mCube, CVector(115.0f, 0.0f, -20.0f), CVector(), CVector(30.0f, H, W));
	new CObj(&mCube, CVector(25.0f, 0.0f, -20.0f), CVector(), CVector(30.0f, H, W));
	new CObj(&mCube, CVector(15.0f, 0.0f, 20.0f), CVector(), CVector(50.0f, H, W));
	new CObj(&mCube, CVector(15.0f, 0.0f, 25.0f), CVector(), CVector(50.0f, H, W));


	//�g
	new CObj(&mCube, CVector(-95.0f, 0.0f, -150.0f), CVector(), CVector(90.0f, H, W));

	new CObj(&mCube, CVector(-190.0f, 0.0f, -115.0f), CVector(), CVector(W, H, 40.0f));

	//��
	new CObj(&mCube, CVector(-235.0f, 0.0f, -70.0f), CVector(), CVector(50.0f, H, W));

	//��
	new CObj(&mCube, CVector(-290.0f, 0.0f, -15.0f), CVector(), CVector(W, H, 60.0f));

	//�E
	new CObj(&mCube, CVector(-235.0f, 0.0f, 40.0f), CVector(), CVector(50.0f, H, W));

	//������
	new CObj(&mCube, CVector(-190.0f, 0.0f, -45.0f), CVector(), CVector(W, H, 20.0f));

	//�����E
	new CObj(&mCube, CVector(-190.0f, 0.0f, 20.0f), CVector(), CVector(W, H, 20.0f));

	new CObj(&mCube, CVector(-250.0f, 0.0f, 105.0f), CVector(), CVector(W, H, 60.0f));

	new CObj(&mCube, CVector(-200.0f, 0.0f, 160.0f), CVector(), CVector(45.0f, H, W));
	
	
	//�G(�_���[�W������)
	new CEnemy2(&mSphere, CVector(-20.0f, 0.0f, 0.0f), CVector(), CVector(2.0f, 2.0f, 2.0f));
	new CEnemy2(&mSphere, CVector(-30.0f, 0.0f, 0.0f), CVector(), CVector(2.0f, 2.0f, 2.0f));

	//�S�~
	new CGomi(NULL, CVector(20.0f, 1.0f, 10.0f), CVector(), CVector(1.0f, 1.0f, 1.0f));
	new CGomi(NULL, CVector(80.0f, 1.0f, -50.0f), CVector(), CVector(1.0f, 1.0f, 1.0f));
	new CGomi(NULL, CVector(30.0f, 1.0f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f));
	new CGomi(NULL, CVector(20.0f, 1.0f, 10.0f), CVector(), CVector(1.0f, 1.0f, 1.0f));
	new CGomi(NULL, CVector(30.0f, 1.0f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f));

	//�G(�ǔ�)
	new CBoss(&mRover, CVector(100.0f, 0.0f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f));

	//�p���[
	//new CEnemy(&mSofa, CVector(-50.0f, 0.0f, 80.0f), CVector(), CVector(55.0f, 55.0f, 55.0f));

	//�z�[��
	new CHome(&mCube, CVector(-50.0f, -0.7f, 0.0f), CVector(), CVector(0.05f, 0.05f, 0.05f));

	//�n��
	new CObj(&mPlane, CVector(0.0f, -1.5f, 0.0f), CVector(), CVector(300.0f, 1.0f, 200.0f));
	//�V��
	//new CObj(&mPlane, CVector(0.0f, 100.0f, 0.0f), CVector(), CVector(150.0f, 1.0f, 200.0f));

	mPlayer.mPosition = CVector(-50.0f, 10.0f, 0.0f);
	mPlayer.mRotation = CVector(0.0f, 90.0f, 0.0f);
	

	////��Q���e�N�X�`��(���Ⴊ�݁j
	//std::shared_ptr<CTexture>grass(new CTexture("grass.tga"));
	//new CImage(grass, CVector(0.0f, 28.0f, 9.0f),
	//	CVector(180.0f, 0.0f, 0.0f), CVector(69.0f, 13.0f, 1.0f));
}


void CSceneGame::RenderMiniMap(){
	glPushMatrix();
	glViewport(600, 450, 200, 150); //��ʂ̕`��G���A�̎w��
	glLoadIdentity();
	//���_�����K�v
	gluLookAt(0, 150, 0, 0, 0, 0, 0, 0, 1);
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
	//�ő�l�𒴂��Ȃ�
	else if (mBatteryMax >= mBatteryNow){
		mBatteryNow += 15;
	}
	
	//0�ȉ��ɂȂ�Ȃ�
	if (mBatteryNow < 0){
		mBatteryNow = 0;
	}
	//�_�b�V����
	if (CPlayer::Dash == 1){
		mBatteryNow -= 3;
	}
	//�W�����v��
	if (CPlayer::Jump > 0){
		mBatteryNow -= 10;
	}

	//��������
	if (mTimeNow >= 0){
		mTimeNow--;
	}

	//0�ȉ��ɂȂ�Ȃ�
	if (mTimeNow < 0){
		mTimeNow = 0;
	}

	CTaskManager::Get()->Update();
	//�J�����̃p�����[�^���쐬����
	CVector e, c, u;//���_�A�����_�A�����
	//���_�����߂�
	e = CVector(0.0f, 30.0f, -30.0f)*mPlayer.mMatrix;
	//�����_�����߂�
	c = CVector(0.0f, 0.0f, 10.0f)*mPlayer.mMatrix;
	//����������߂�
	u = CVector(0.0f, 1.0f, 0.0f)*mPlayer.mMatrixRotate;

	//�����낵���_
	if (CKey::Push('I')){
		e = CVector(0.0f, 100.0f, 0.0f)*mPlayer.mMatrix;
	}

	//�m�F
	if (CKey::Push('P')){
		e = CVector(0.0f, 300.0f, 0.0f);
	}

	//��l�̎��_
	if (CKey::Push('O')){
		e = CVector(0.0f, 3.0f, -3.0f)*mPlayer.mMatrix;
	}

	//�J�����̐ݒ�
	Camera3D(e.mX, e.mY, e.mZ, c.mX, c.mY, c.mZ, u.mX, u.mY, u.mZ);

	//�w�i�`��(�J�����̌��2D�̑O�ɓ����j
	//mSky.Render();

	CTaskManager::Get()->Render();
	CollisionManager.Render();

	
	frame++;
	if (frame < 1000 && frame % 100 == 0){

		//�S�~�̐���
		//new CGomi(&mRock, CVector(RAND, 1.0f, RAND), CVector(), CVector(1.0f, 1.0f, 1.0f));
	}

	//�R���W�����}�l�[�W���[�̏Փˏ���
	CollisionManager.Collision();

	//�R���W�������X�g����폜
	CTaskManager::Get()->Delete();

	//�~�j�}�b�v�\��
	RenderMiniMap();

	//2D�`��J�n
	Start2D(0, 800, 0, 600);

	if (CKey::Push(VK_RETURN)){
		mScene = ETITLE;
	}

	//CText::DrawString("3D PROGRAMMING", 20, 20, 10, 12);

	//�Q�[���I�[�o�[����(�o�b�e���[�؂�j
	if (mBatteryNow == 0){
		CText::DrawString("GAME OVER", 200, 330, 25, 25);
	}

	//�Q�[���I�[�o�[����(���C�t�[��)
	if (CPlayer::mHPNow <= 0){
		CText::DrawString("GAME OVER", 200, 330, 25, 25);
	}

	//�{�X�Ƃ̏Փ�
	if (CPlayer::Down == TRUE){
		CText::DrawString("OUT!", 330, 450, 25, 25);
	}

	//�N���A����(�S�~�S���)
	if (CPlayer::clear >= GAMECLEAR && CHome::home == 1){
		CText::DrawString("STAGE CLEAR", 155, 330, 25, 25);
	}

	char buf[10];

	/*sprintf(buf, "%d", mBatteryNow / 60);
	CText::DrawString(buf, 30, 550, 20, 20);*/

	//�A�C�e����(�p���[�j
	sprintf(buf, "%d", CPower::power);
	CText::DrawString(buf, 750, 30, 15, 15);

	//�ڕW��
	sprintf(buf, "%d", CPlayer::clear);
	CText::DrawString(buf, 650, 30, 15, 15);

	////�S�~�����
	//sprintf(buf, "%d", CGomi::GomiCount);
	//CText::DrawString(buf, 140, 50, 15, 15);

	////�v���C���[���C�t
	//sprintf(buf, "%d", CPlayer::Life);
	//CText::DrawString(buf, 20, 50, 15, 15);

	//2D�`��I��
	End2D();

	return;
}

//���̃V�[���̎擾
CScene::EScene CSceneGame::GetNextScene() {
	return mScene;
}
