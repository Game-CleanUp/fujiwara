#include "CSceneGame.h"

#include "CCamera.h"

#include "CText.h"


int CSceneGame::mBatteryMax = BATTERY;
int CSceneGame::mBatteryNow = mBatteryNow + mBatteryMax;
int CSceneGame::mTimeMax = TIME;
int CSceneGame::mTimeNow = mTimeNow + mTimeMax;
int CSceneGame::frameGame = 0;
int CSceneGame::frameUI = 0;

 CSound CSceneGame::SoundBGM;
 CSound CSceneGame::SoundGameOver;
 CSound CSceneGame::SoundCharge;
 CSound CSceneGame::SoundTimeUp;

 CTexture TextureTrap;
 CTexture TextureGomi;

CSceneGame::~CSceneGame(){
	
	//�V�[��������
	CTaskManager::Get()->Delete();

	//mEabled�����ׂ�false�ɂ���
	CTaskManager::Get()->AllDelete();

}

void CSceneGame::Init() {

	//�V�[���̐ݒ�
	mScene = EGAME;

	SoundBGM.Load("BGM1.wav");
	SoundGameOver.Load("GameOver.wav");
	SoundCharge.Load("chage.wav");
	SoundTimeUp.Load("finish.wav");

	//BGM�Đ�
	SoundBGM.Repeat();

	BatterySE = true;
	GameSE = true;

	//�e�N�X�`���̓ǂݍ���
	TextureTrap.Load("DogFood.tga");
	TextureGomi.Load("Gomi.tga");

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

	mPlayerModel.Load("player.obj", "player.mtl");

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

	mPlayer.mpModel = &mPlayerModel;	//�v���C���[���f��
	CVector left = CVector(0.0f, -90.0f, 0.0f);

	new CObj(&mBed, CVector(-18.0f, -1.0f, -7.0f), CVector(0.0f, -90.0f, 0.0f), CVector(50.0f, 45.0f, 50.0f));

	new CObj(&mChair, CVector(20.0f, -5.0f, 20.0f), CVector(), CVector(50.0f, 20.0f, 50.0f));

	new CObj(&mTVCabinet, CVector(-59.0f, -1.0f, 25.0f), CVector(0.0f, -90.0f, 0.0f), CVector(50.0f, 35.0f, 65.0f));

	new CObj(&mSofa, CVector(-10.0f, -1.0f, -15.0f), CVector(0.0f, 90.0f, 0.0f), CVector(40.0f, 35.0f, 35.0f));

	new CObj(&mTable, CVector(-35.0f, -5.0f, 5.0f), CVector(0.0f, -90.0f, 0.0f), CVector(50.0f, 40.0f, 40.0f));

	new CObj(&mWall, CVector(5.0f, -1.0f, -55.0f), CVector(0.0f, 90.0f, 0.0f), CVector(90.0f, 30.0f, 40.0f));

	new CObj(&mDoor, CVector(5.0f, -1.0f, 25.0f), CVector(0.0f, 90.0f, 0.0f), CVector(35.0f, 25.0f, 40.0f));

	new CObj(&mKichen, CVector(64.0f, -1.0f, -40.0f), CVector(), CVector(90.0f, 30.0f, 50.0f));

	new CObj(&mKitchenCabinet, CVector(26.0f, -1.0f, 20.0f), CVector(0.0f, -90.0f, 0.0f), CVector(120.0f, 30.0f, 40.0f));

	new CObj(&mFrige, CVector(63.0f, -1.0f, -30.0f), CVector(0.0f, 90.0f, 0.0f), CVector(40.0f, 50.0f, 38.0f));

	/* �����n��̕ύX */
	srand((unsigned)time(NULL));

	//��
	new CObj(&mCube, CVector(80.0f, -1.0f, 0.0f), CVector(), CVector(W, H, 60.0f));
	//��
	new CObj(&mCube, CVector(-80.0f, -1.0f, 0.0f), CVector(), CVector(W, H, 60.0f));
	//�E
	new CObj(&mCube, CVector(0.0f, -1.0f, 60.0f), CVector(), CVector(80.0f, H, W));
	//��
	new CObj(&mCube, CVector(0.0f, -1.0f, -60.0f), CVector(), CVector(80.0f, H, W));

	//�G(�ǔ�)
	new CBoss(&mDog, CVector(-20.0f, 0.0f, 50.0f), CVector(), CVector(1.0f, 1.0f, 1.0f));
	new CBoss(&mDog, CVector(30.0f, 0.0f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f));
	
	new CTrap(&mSphere, CVector(0.0f, -10.0f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f));

	//�z�[��
	new CHome(&mTrashbox, CVector(73.0f, -1.0f, 53.0f), CVector(0.0f, 45.0f, 0.0f), CVector(15.0f, 15.0f, 15.0f));

	//�v���C���[�����ʒu
	mPlayer.mPosition = CVector(71.0f, 10.0f, 51.0f);
	mPlayer.mRotation = CVector(0.0f, 225.0f, 0.0f);
	
	//�e�N�X�`��(���j
	std::shared_ptr<CTexture>floor(new CTexture("floor.tga"));

	//��
	new CObj(&mPlane, CVector(0.0f, -1.5f, 0.0f), CVector(), CVector(80.0f, 1.0f, 60.0f));
	new CImage(floor, CVector(0.0f, -1.49f, 0.0f), CVector(-90.0f, 0.0f, 0.0f), CVector(80.0f, 60.0f, 1.0f));

}

//���l���Z�b�g
void CSceneGame::ValueReset(){
	SoundBGM.Stop();	//BGM�I��
	mTimeNow = mTimeMax;
	mBatteryNow = mBatteryMax;
	CPlayer::Down = false;
	CGomi::GomiCount = 0;
	CTrap::TrapCount = 10;
	frameGame = 0;
}

void CSceneGame::Update() {

	//�o�b�e���[����
	if (mBatteryNow >= 0 && CHome::home == false && mTimeNow > 0){
		mBatteryNow--;
	}

	//�[�d(�ő�l�𒴂��Ȃ��A�o�b�e���[����)
	if (mBatteryMax >= mBatteryNow && CHome::home == true){

		mBatteryNow += CHAGE;

		//�o�b�e���[��MAX�ȊO�Ō��ʉ��Đ�
		if (BatterySE && mBatteryNow < mBatteryMax){
			SoundCharge.Repeat();
			BatterySE = false;
		}
	}
	else{
		SoundCharge.Stop();
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

	frameGame++;
	if (frameGame < 5000 && frameGame % 250 == 0){
		//�S�~�̐���
		new CGomi(NULL, CVector(RAND, 20.0f, RAND), CVector(), CVector(0.5f, 0.5, 0.5f));
	}
	
	CTaskManager::Get()->Update();

	CVector e, c, u;//���_�A�����_�A�����
	if (CPlayer::Down == FALSE){
		//���_�����߂�
		e = CVector(0.0f, 1.5f, -3.5f)*mPlayer.mMatrix;
		//�����_�����߂�
		c = CVector(0.0f, 0.0f, 10.0f)*mPlayer.mMatrix;
		//����������߂�
		u = CVector(0.0f, 1.0f, 0.0f)*mPlayer.mMatrixRotate;
	}
	//�_���[�W���A�N�V����
	else{
		//���_�����߂�
		e = CVector(0.0f, 30.0f, -5.0f)*mPlayer.mMatrix;
		//�����_�����߂�
		c = CVector(0.0f, 0.0f, 10.0f)*mPlayer.mMatrix;
		//����������߂�
		u = CVector(0.0f, 1.0f, 0.0f)*mPlayer.mMatrixRotate;
	}

	//������_
	if (CKey::Push('O')){
		e = CVector(0.0f, 30.0f, 0.0f)*mPlayer.mMatrix;
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
			SoundGameOver.Play();
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
			SoundTimeUp.Play();
			GameSE = false;
		}
	}

	//�{�X�Ƃ̏Փ�
	if (CPlayer::Down == TRUE){
		CText::DrawString("CRASH!", 280, 450, 25, 25);
	}

	frameUI++;
	if (frameUI < 60){
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
	CText::DrawString(buf, 740, 30, 13, 13);

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
