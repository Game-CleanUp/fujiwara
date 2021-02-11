#include "CSceneGame.h"

#include "CCamera.h"

#include "CText.h"


int CSceneGame::mBatteryMax = BATTERY;
int CSceneGame::mBatteryNow = mBatteryNow + mBatteryMax;
int CSceneGame::mTimeMax = TIME;
int CSceneGame::mTimeNow = mTimeNow + mTimeMax;
int CSceneGame::frame = 0;
int CSceneGame::frame2 = 0;

 CSound CSceneGame::Sound;
 CSound CSceneGame::Sound2;
 CSound CSceneGame::Sound3;
 CSound CSceneGame::Sound4;

 CTexture Texture;
 CTexture Texture2;

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
	Sound3.Load("chage.wav");
	Sound4.Load("finish.wav");

	//BGM�Đ�
	//Sound.Repeat();

	bool BatterySE = true;
	bool GameOverSE = true;

	//�e�N�X�`���̓ǂݍ���
	Texture.Load("DogFood.tga");
	Texture2.Load("Gomi.tga");

	glMatrixMode(GL_PROJECTION);	//�s����v���W�F�N�V�������[�h�֕ύX
	glLoadIdentity();				//�s���������
	gluPerspective(75.0, (double)800 / (double)600, 1.0, 10000.0);	//3D�̉�ʂ�ݒ�

	glMatrixMode(GL_MODELVIEW);		//�s������f���r���[���[�h�֕ύX
	glLoadIdentity();				//�s���������

	//�e�L�X�g�t�H���g�̓ǂݍ��݂Ɛݒ�
	CText::mFont.Load("FontG.tga");
	CText::mFont.SetRowCol(1, 4096 / 64);	//�摜�̉���/1�����̉���

	mCube.Load("cube.obj", "cube.mtl");
	mPlane.Load("plane.obj", "plane.mtl");
	mSphere.Load("sphere.obj", "sphere.mtl");

	mDog.Load("Dog.obj", "Dog.mtl");	//��

	mSofa.Load("loungeSofa.obj", "loungeSofa.mtl");	//�\�t�@
	mBed.Load("bedSingle.obj", "bedSingle.mtl");	//�x�b�h
	mChair.Load("stoolBarSquare.obj", "stoolBarSquare.mtl");	//�֎q
	mTVCabinet.Load("cabinetTelevisionDoors.obj", "cabinetTelevisionDoors.mtl");	//�e���r��
	mBedCabinet.Load("cabinetBedDrawerTable.obj", "cabinetBedDrawerTable.mtl");
	mTable.Load("table.obj", "table.mtl");
	mTrashbox.Load("trashbox.obj", "trashbox.mtl");
	mWall.Load("wall.obj", "wall.mtl");
	mDoor.Load("wallDoor.obj", "wallDoor.mtl");
	mKichen.Load("kichen.obj", "kichen.mtl");
	mKitchenCabinet.Load("kichenCabinet.obj", "kichenCabinet.mtl");
	mFrige.Load("frige.obj", "frige.mtl");

	mPlayer.mpModel = &mSphere;	//�v���C���[���f��
	CVector left = CVector(0.0f, -90.0f, 0.0f);

	new CObj(&mBed, CVector(-18.0f, -1.0f, -7.0f), left, CVector(50.0f, 25.0f, 50.0f));

	//new CObj(&mChair, CVector(-10.0f, 0.0f, -20.0f), CVector(), CVector(40.0f, 10.0f, 40.0f));

	new CObj(&mTVCabinet, CVector(-59.0f, -1.0f, 25.0f), left, CVector(50.0f, 25.0f, 65.0f));

	//new CObj(&mBedCabinet, CVector(-70.0f, 0.0f, 10.0f), CVector(), CVector(40.0f, 30.0f, 40.0f));

	new CObj(&mSofa, CVector(-15.0f, -1.0f, -15.0f), CVector(0.0f, 90.0f, 0.0f), CVector(40.0f, 20.0f, 35.0f));

	new CObj(&mTable, CVector(-35.0f, -1.0f, 5.0f), CVector(0.0f, -90.0f, 0.0f), CVector(50.0f, 23.0f, 40.0f));

	new CObj(&mWall, CVector(5.0f, -1.0f, -55.0f), CVector(0.0f, 90.0f, 0.0f), CVector(80.0f, 30.0f, 40.0f));

	new CObj(&mDoor, CVector(5.0f, -1.0f, 20.0f), CVector(0.0f, 90.0f, 0.0f), CVector(35.0f, 25.0f, 40.0f));


	new CObj(&mKichen, CVector(64.0f, -1.0f, -40.0f), CVector(), CVector(90.0f, 30.0f, 50.0f));

	new CObj(&mKitchenCabinet, CVector(26.0f, -1.0f, 20.0f), CVector(0.0f, -90.0f, 0.0f), CVector(120.0f, 30.0f, 40.0f));

	new CObj(&mFrige, CVector(63.0f, -1.0f, -30.0f), CVector(0.0f, 90.0f, 0.0f), CVector(40.0f, 50.0f, 38.0f));

	/* �����n��̕ύX */
	srand((unsigned)time(NULL));

	//�e�N�X�`��(�ǎ�)
	std::shared_ptr<CTexture>Wall(new CTexture("kabe2.tga"));

	//��
	new CObj(&mCube, CVector(80.0f, -1.0f, 0.0f), CVector(), CVector(W, H, 60.0f));
	//new CImage(Wall, CVector(95.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 90.0f), CVector(100.0f, 80.0f, 1.0f));
	//��
	new CObj(&mCube, CVector(-80.0f, -1.0f, 0.0f), CVector(), CVector(W, H, 60.0f));
	//new CImage(Wall, CVector(-95.0f, -1.49f, 0.0f), CVector(-90.0f, 0.0f, 0.0f), CVector(100.0f, 80.0f, 1.0f));
	//�E
	new CObj(&mCube, CVector(0.0f, -1.0f, 60.0f), CVector(), CVector(80.0f, H, W));
	//new CImage(Wall, CVector(0.0f, -1.49f, 0.0f), CVector(-90.0f, 0.0f, 0.0f), CVector(100.0f, 80.0f, 1.0f));
	//��
	new CObj(&mCube, CVector(0.0f, -1.0f, -60.0f), CVector(), CVector(80.0f, H, W));
	//new CImage(Wall, CVector(0.0f, -1.49f, 0.0f), CVector(-90.0f, 0.0f, 0.0f), CVector(100.0f, 80.0f, 1.0f));

	new CObj(&mCube, CVector(40.0f, -1.0f, -55.0f), CVector(), CVector(31.0f, H, 15.0f));
	new CObj(&mCube, CVector(69.0f, -1.0f, -40.0f), CVector(), CVector(W, H, 10.0f));
	new CObj(&mCube, CVector(16.0f, -1.0f, -41.0f), CVector(), CVector(9.0f, H, 9.0f));

	//�G(�ǔ�)
	new CBoss(&mDog, CVector(-20.0f, 0.0f, 50.0f), CVector(), CVector(1.0f, 1.0f, 1.0f));
	//new CBoss(&mDog, CVector(0.0f, 0.0f, -15.0f), CVector(), CVector(1.0f, 1.0f, 1.0f));

	new CTrap(&mSphere, CVector(0.0f, -10.0f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f));
	
	//�z�[��
	new CHome(&mTrashbox, CVector(73.0f, -1.0f, 53.0f), CVector(0.0f, 45.0f, 0.0f), CVector(15.0f, 15.0f, 15.0f));


	//�v���C���[�����ʒu
	mPlayer.mPosition = CVector(70.0f, 10.0f, 55.0f);
	mPlayer.mRotation = CVector(0.0f, 225.0f, 0.0f);
	
	//�e�N�X�`��(���j
	std::shared_ptr<CTexture>floor(new CTexture("yuka.tga"));

	//��
	new CObj(&mPlane, CVector(0.0f, -1.5f, 0.0f), CVector(), CVector(80.0f, 1.0f, 60.0f));
	new CImage(floor, CVector(0.0f, -1.49f, 0.0f), CVector(-90.0f, 0.0f, 0.0f), CVector(80.0f, 60.0f, 1.0f));

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

//���l���Z�b�g
void CSceneGame::ValueReset(){
	Sound.Stop();	//BGM�I��
	mTimeNow = mTimeMax;
	mBatteryNow = mBatteryMax;
	CGomi::GomiCount = 0;
	frame = 0;
}

void CSceneGame::Update() {

	//�o�b�e���[����
	if (mBatteryNow >= 0 && CHome::home == false && mTimeNow > 0){
		mBatteryNow--;
	}

	//�[�d(�ő�l�𒴂��Ȃ��A�o�b�e���[����)
	if (mBatteryMax >= mBatteryNow && CHome::home == 1){

		mBatteryNow += CHAGE;

		if (BatterySE && mBatteryNow < mBatteryMax){
			Sound3.Repeat();	//�[�d��SE
			BatterySE = false;
		}
	}
	else{
		Sound3.Stop();
		BatterySE = true;
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
	if (frame == 1800 || frame == 3600){
		//new CBoss(&mDog, CVector(0.0f, 0.0f, -15.0f), CVector(), CVector(1.0f, 1.0f, 1.0f));
	}

	if (frame < 1000 && frame % 100 == 0){
		//�S�~�̐���
		//new CGomi(NULL, CVector(RAND, 0.0f, RAND), CVector(), CVector(1.0f, 1.0f, 1.0f));
	}
	
	CTaskManager::Get()->Update();

	CVector e, c, u;//���_�A�����_�A�����
	if (CPlayer::Down == FALSE){
		//���_�����߂�
		e = CVector(0.0f, 1.0f, -1.0f)*mPlayer.mMatrix;
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

	//������_
	if (CKey::Push('O')){
		c = CVector(0.0f, 1.0f, -10.0f)*mPlayer.mMatrix;
	}

	//�����낵���_
	if (CKey::Push('I')){
		e = CVector(0.0f, 50.0f, 0.0f)*mPlayer.mMatrix;
	}
	if (CKey::Push('P')){
		e = CVector(0.0f, 1.0f, -1.0f)*mPlayer.mMatrix;
	}

	//�J�����̐ݒ�
	Camera.Set(e, c, u);
	Camera.Render();

	CTaskManager::Get()->Render();
	CCollisionManager::Get()->Render();

	//�R���W�����}�l�[�W���[�̏Փˏ���
	CTaskManager::Get()->TaskCollision();

	//�R���W�������X�g����폜
	CTaskManager::Get()->Delete();

	//�~�j�}�b�v�\��
	//RenderMiniMap();

	//2D�`��J�n(UI�\��)
	Start2D(0, 800, 0, 600);

	//�Q�[���I�[�o�[����(�o�b�e���[�؂�j
	if (mBatteryNow <= 0){
		if (CKey::Once(VK_RETURN)){	//�^�C�g����ʂ�
			mScene = ETITLE;
			ValueReset();
		}

		CText::DrawString("GAME OVER", 200, 330, 25, 25);
	
		if (GameSE){
			Sound2.Play();	//�Q�[���I�[�o�[SE
			GameSE = false;
		}
	}
	
	//�^�C���A�b�v
	if (mTimeNow <= 0){
		if (CKey::Once(VK_RETURN)){	//���U���g��ʂ�
			mScene = ERESULT;
			ValueReset();
		}

		CText::DrawString("TIME UP", 245, 330, 25, 25);

		if (GameSE){
			Sound4.Play();	//�^�C���A�b�vSE
			GameSE = false;
		}
	}

	//�{�X�Ƃ̏Փ�
	if (CPlayer::Down == TRUE){
		CText::DrawString("CRASH!", 280, 450, 25, 25);
	}

	frame2++;
	if (frame2 < 60){
		CText::DrawString("START", 293, 400, 25, 25);
	}

	CText::DrawString("BATTERY", 17, 50, 11, 11);
	CText::DrawString("[", 15, 25, 11, 11);
	CText::DrawString("]", 305, 25, 11, 11);

	//�����𕶎���ɕϊ�����
	char buf[10];

	//��������
	sprintf(buf, "%d", mTimeNow / 60);
	CText::DrawString(buf, 30, 550, 13, 13);

	//�g���b�v������
	sprintf(buf, "%d", CTrap::TrapCount);
	CText::DrawString(buf, 700, 30, 13, 13);

	//�S�~������
	sprintf(buf, "%d", CGomi::GomiCount);
	CText::DrawString(buf, 300, 50, 13, 13);

	End2D();

	return;
}

//���̃V�[���̎擾
CScene::EScene CSceneGame::GetNextScene() {
	return mScene;
}
