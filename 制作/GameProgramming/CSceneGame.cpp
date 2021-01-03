#include "CSceneGame.h"
//
#include "CCamera.h"
//
#include "CText.h"

int CSceneGame::StageCount = 0;
int CSceneGame::mBatteryMax = 30 * 60;
int CSceneGame::mBatteryNow = mBatteryNow + mBatteryMax;
int CSceneGame::mTimeMax = 60 * 60;
int CSceneGame::mTimeNow = mTimeNow + mTimeMax;
int CSceneGame::frame = 0;
int CSceneGame::frame2 = 0;

//�O���ϐ�
extern CSound Sound;


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
	//BGM�Đ�
	//Sound.Repeat();

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
	mSphere.Load("sphere.obj", "sphere.mtl");
	mPlayer.mpModel = &mCube;

	mSofa.Load("sofa.obj", "sofa.mtl");
	mPlant.Load("Plant.obj", "Plant.mtl");
	mDog.Load("Dog.obj", "Dog.mtl");
	mTable.Load("Table.obj", "Table.mtl");

	new CObj(&mSofa, CVector(-95.0f, 0.0f, -20.0f), CVector(), CVector(12.0f, 12.0f, 12.0f));

	new CObj(&mTable, CVector(-50.0f, 0.0f, -30.0f), CVector(), CVector(65.0f, 25.0f, 25.0f));
	//new CObj(&mPlant, CVector(-20.0f, 0.0f, -25.0f), CVector(), CVector(5.0f, 5.0f, 5.0f));
	//new CObj(&mPlant, CVector(-20.0f, 0.0f, -10.0f), CVector(), CVector(5.0f, 5.0f, 5.0f));
	

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
	new CObj(&mCube, CVector(130.0f, 0.0f, 0.0f), CVector(), CVector(W, H, 100.0f));
	new CImage(kabe, CVector(124.1f, 0.0f, -50.0f), CVector(180.0f, 90.0f, -90.0f), CVector(50.0f, 50.0f, 0.0f));
	new CImage(kabe, CVector(124.1f, 0.0f, 50.0f), CVector(180.0f, 90.0f, -90.0f), CVector(50.0f, 50.0f, 0.0f));
	

	//��
	new CObj(&mCube, CVector(-130.0f, 0.0f, 0.0f), CVector(), CVector(W, H, 100.0f));
	new CImage(kabe, CVector(-124.9f, 0.0f, -50.0f), CVector(180.0f, -90.0f, -90.0f), CVector(50.0f, 50.0f, 0.0f));
	new CImage(kabe, CVector(-124.9f, 0.0f, 50.0f), CVector(180.0f, -90.0f, -90.0f), CVector(50.0f, 50.0f, 0.0f));

	//�E
	new CObj(&mCube, CVector(0.0f, 0.0f, 100.0f), CVector(), CVector(130.0f, H, W));
	new CImage(kabe, CVector(65.0f, 0.0f, 94.9f), CVector(-180.0f, 0.0f, 0.0f), CVector(65.0f, 50.0f, 0.0f));
	new CImage(kabe, CVector(-65.0f, 0.0f, 94.9f), CVector(180.0f, 0.0f, 0.0f), CVector(65.0f, 50.0f, 0.0f));

	//��
	new CObj(&mCube, CVector(0.0f, 0.0f, -100.0f), CVector(), CVector(130.0f, H, W));
	new CImage(kabe, CVector(65.0f, 0.0f, -94.9f), CVector(180.0f, -180.0f, -90.0f), CVector(50.0f, 65.0f, 0.0f));
	new CImage(kabe, CVector(-65.0f, 0.0f, -94.9f), CVector(180.0f, -180.0f, -90.0f), CVector(50.0f, 65.0f, 0.0f));
	
	
	//�@
	new CObj(&mCube, CVector(15.0f, 0.0f, 5.0f), CVector(), CVector(W, H, 70.0f));
	new CImage(kabe, CVector(9.9f, 0.0f, 5.0f), CVector(180.0f, 90.0f, -90.0f), CVector(50.0f, 70.0f, 0.0f));
	new CImage(kabe, CVector(20.1f, 0.0f, 5.0f), CVector(180.0f, -90.0f, -90.0f), CVector(50.0f, 70.0f, 0.0f));

	//�A
	new CObj(&mCube, CVector(35.0f, 0.0f, 10.0f), CVector(), CVector(25.0f, H, W));
	new CImage(kabe, CVector(35.0f, 0.0f, 4.9f), CVector(180.0f, 0.0f, 0.0f), CVector(25.0f, 50.0f, 0.0f));
	new CImage(kabe, CVector(35.0f, 0.0f, 15.1f), CVector(180.0f, -180.0f, -90.0f), CVector(50.0f, 25.0f, 0.0f));

	//�B
	new CObj(&mCube, CVector(-75.0f, 0.0f, 10.0f), CVector(), CVector(60.0f, H, W));
	new CImage(kabe, CVector(-75.0f, 0.0f, 4.9f), CVector(180.0f, 0.0f, 0.0f), CVector(60.0f, 50.0f, 0.0f));
	new CImage(kabe, CVector(-75.0f, 0.0f, 15.1f), CVector(180.0f, -180.0f, -90.0f), CVector(50.0f, 60.0f, 0.0f));



	/*
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
	*/

	//�G(�_���[�W������)
	/*new CEnemy2(&mSphere, CVector(-20.0f, 0.0f, 0.0f), CVector(), CVector(2.0f, 2.0f, 2.0f));
	new CEnemy2(&mSphere, CVector(-30.0f, 0.0f, 0.0f), CVector(), CVector(2.0f, 2.0f, 2.0f));
*/
	//�G(�ǔ�)
	new CBoss(&mDog, CVector(100.0f, 0.0f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f));
	new CBoss(&mDog, CVector(-50.0f, 0.0f, 70.0f), CVector(), CVector(1.0f, 1.0f,1.0f));
	//new CBoss(&mRover, CVector(-50.0f, 0.0f, 50.0f), CVector(), CVector(1.0f, 1.0f, 1.0f));
	//�z�[��
	new CHome(&mCube, CVector(-120.0f, -0.7f, -90.0f), CVector(), CVector(1.0f, 1.0f, 1.0f));	

	//�V��
	//new CObj(&mPlane, CVector(0.0f, 90.0f, 0.0f), CVector(-180.0f, 0.0f, 0.0f), CVector(150.0f, 1.0f, 200.0f));

	//�v���C���[�����ʒu
	mPlayer.mPosition = CVector(-120.0f, 10.0f, -80.0f);

	//�e�N�X�`��(���j
	std::shared_ptr<CTexture>yuka(new CTexture("yuka.tga"));
	//�n��
	new CObj(&mPlane, CVector(0.0f, -1.5f, 0.0f), CVector(), CVector(130.0f, 1.0f, 100.0f));
	new CImage(yuka, CVector(0.0f, -1.49f, 0.0f), CVector(-90.0f, 0.0f, 0.0f), CVector(130.0f, 100.0f, 1.0f));

}


void CSceneGame::RenderMiniMap(){
	glPushMatrix();
	glViewport(600, 450, 200, 150); //��ʂ̕`��G���A�̎w��
	glLoadIdentity();
	//���_�����K�v
	gluLookAt(0, 180, 0, 0, 0, 0, 0, 0, 1);
	glDisable(GL_DEPTH_TEST);
	//�`��
	CTaskManager::Get()->Render();
	glPopMatrix();
	glViewport(0, 0, 800, 600); //��ʂ̕`��G���A�̎w��
	glEnable(GL_DEPTH_TEST);
}


void CSceneGame::Update() {
	
	

	if (mBatteryNow >= 0 && CHome::home == 0){
		mBatteryNow -= 2;
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
	if (CPlayer::Dash == TRUE){
		mBatteryNow -= 3;
	}
	//�W�����v��
	if (CPlayer::Jump == TRUE){
		mBatteryNow -= 10;
	}

	//��������
	if (mBatteryNow > 0){
		mTimeNow--;
	}

	//0�ȉ��ɂȂ�Ȃ�
	if (mTimeNow < 0){
		mTimeNow = 0;
	}

	frame++;
	if (frame < 1000 && frame % 100 == 0){

		//�S�~�̐���
		//new CGomi(&mRock, CVector(RAND, 0.0f, RAND), CVector(), CVector(1.0f, 1.0f, 1.0f));
	}
	
	CTaskManager::Get()->Update();
	//�J�����̃p�����[�^���쐬����
	CVector e, c, u;//���_�A�����_�A�����
	if (CPlayer::Down == FALSE){
		//���_�����߂�
		e = CVector(0.0f, 10.0f, -15.0f)*mPlayer.mMatrix;
		//�����_�����߂�
		c = CVector(0.0f, 0.0f, 10.0f)*mPlayer.mMatrix;
		//����������߂�
		u = CVector(0.0f, 1.0f, 0.0f)*mPlayer.mMatrixRotate;
	}
	//�_���[�W���A�N�V����
	else{
		//���_�����߂�
		e = CVector(0.0f, 10.0f, -10.0f)*mPlayer.mMatrix;
		//�����_�����߂�
		c = CVector(0.0f, 0.0f, 10.0f)*mPlayer.mMatrix;
		//����������߂�
		u = CVector(0.0f, 1.0f, 0.0f)*mPlayer.mMatrixRotate;
	}


	//�����낵���_
	if (CKey::Push('I')){
		e = CVector(0.0f, 50.0f, 0.0f)*mPlayer.mMatrix;
	}

	//�m�F
	if (CKey::Push('P')){
		e = CVector(0.0f, 350.0f, 0.0f);
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

	//�R���W�����}�l�[�W���[�̏Փˏ���
	CTaskManager::Get()->TaskCollision();

	//�R���W�������X�g����폜
	CTaskManager::Get()->Delete();

	//�~�j�}�b�v�\��
	RenderMiniMap();

	//2D�`��J�n
	Start2D(0, 800, 0, 600);

	if (CKey::Push(VK_RETURN)){
		mScene = ETITLE;
	}

	//�Q�[���I�[�o�[����(�o�b�e���[�؂�j
	if (mBatteryNow == 0 || mTimeNow <= 0){
		CText::DrawString("GAME OVER", 200, 330, 25, 25);
		Sound.Stop();
	}

	//�{�X�Ƃ̏Փ�
	if (CPlayer::Down == TRUE){
		CText::DrawString("CRASH!", 285, 450, 25, 25);
	}

	////�N���A����(�S�~�S���)
	//if (CPlayer::clear >= GAMECLEAR && CHome::home == 1){
	//	CText::DrawString("STAGE CLEAR", 155, 330, 25, 25);
	//}

	frame2++;
	if (frame2 < 120){
		CText::DrawString("WAVE1", 325, 400, 15, 15);
		//frame2 = 0;
	}

	if (CPlayer::clear >= 10){
		CText::DrawString("WAVE2", 325, 400, 15, 15);
		
	}
	//if (CPlayer::clear >= 10){
	//	CText::DrawString("WAVE3", 325, 400, 15, 15);

	//}
	//if (CPlayer::clear >= 10){
	//	CText::DrawString("WAVE4", 325, 400, 15, 15);

	//}
	//if (CPlayer::clear >= 10){
	//	CText::DrawString("WAVE5", 325, 400, 15, 15);

	//}
	CText::DrawString("BATTERY", 17, 40, 13, 13);

	char buf[10];

	//��������
	sprintf(buf, "%d", mTimeNow / 60);
	CText::DrawString(buf, 15, 550, 15, 15);

	//�ڕW��
	sprintf(buf, "%d", CPlayer::clear);
	CText::DrawString(buf, 650, 30, 15, 15);

	////�S�~�����
	//sprintf(buf, "%d", CGomi::GomiCount);
	//CText::DrawString(buf, 140, 50, 15, 15);

	//2D�`��I��
	End2D();

	return;
}

//���̃V�[���̎擾
CScene::EScene CSceneGame::GetNextScene() {
	return mScene;
}
