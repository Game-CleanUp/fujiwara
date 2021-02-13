#include "CResult.h"
#include "CKey.h"

CSound CResult::SoundEnter;
CSound CResult::SoundResult;

void CResult::Init() {

	CText::mFont.Load("FontG.tga");
	CText::mFont.SetRowCol(1, 4096 / 64);

	//�V�[���̐ݒ�
	mScene = ERESULT;

	//��ʓ��e�͈͂̐ݒ�
	mLeft = -400;
	mRight = 400;
	mBottom = -300;
	mTop = 300;

	SoundEnter.Load("enter.wav");
	SoundResult.Load("result.wav");

	SoundResult.Play();

}

//�X�V�����̃I�[�o�[���C�h
void CResult::Update() {

	//��ʓ��e�͈͂̕ύX
	//�s����v���W�F�N�V�������[�h�֕ύX
	glMatrixMode(GL_PROJECTION);
	//�s���������
	glLoadIdentity();
	//2D�̉�ʓ��e�͈͂�ݒ�
	gluOrtho2D(mLeft, mRight, mBottom, mTop);
	//�s������f���r���[���[�h�֕ύX
	glMatrixMode(GL_MODELVIEW);
	//�s���������
	glLoadIdentity();

	//2D�`��J�n
	Start2D(0, 800, 0, 600);

	////������̕`��
	CText::DrawString("RESULT", 200, 500, 40, 40);
	//CText::DrawString("PUSH ENTER KEY", 165, 100, 17, 17);
	CText::DrawString("RANK", 350, 400, 15, 15);

	CText::DrawString("SCORE", 280, 150, 15, 15);

	char buf[10];
	//�X�R�A�\��
	sprintf(buf, "%d", CPlayer::Score);
	CText::DrawString(buf, 480, 150, 15, 15);

	if (CPlayer::Score <= 5){
		CText::DrawString("D", 400, 300, 60, 60);
	}
	else if (CPlayer::Score <= 10){
		CText::DrawString("C", 400, 300, 60, 60);
	}
	else if (CPlayer::Score <= 20){
		CText::DrawString("B", 400, 300, 60, 60);
	}
	else if (CPlayer::Score <= 25){
		CText::DrawString("A", 400, 300, 60, 60);
	}
	else{
		CText::DrawString("S", 400, 300, 60, 60);
	}

	//2D�`��I��
	End2D();

	//�^�C�g����
	if (CKey::Once(VK_RETURN)) {
		mScene = ETITLE;
		CPlayer::Score = 0;
		SoundEnter.Play();	//����SE�Đ�
		SoundResult.Stop();
	}
}
//���̃V�[���̎擾
CScene::EScene CResult::GetNextScene() {
	return mScene;
}
