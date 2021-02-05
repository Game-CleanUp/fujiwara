#include "CResult.h"
#include "CKey.h"

CSound CResult::Sound;

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

	Sound.Load("enter.wav");

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
	CText::DrawString("RESULT", 270, 450, 20, 20);
	CText::DrawString("PUSH ENTER KEY", 165, 200, 17, 17);

	char buf[10];
	//��������
	//sprintf(buf, "%d", CSceneGame::mTimeNow / 60);
	//CText::DrawString(buf, 15, 550, 15, 15);

	//2D�`��I��
	End2D();

	//�^�C�g����
	if (CKey::Once(VK_RETURN)) {
		mScene = ETITLE;
		Sound.Play();	//����SE�Đ�
	}
}
//���̃V�[���̎擾
CScene::EScene CResult::GetNextScene() {
	return mScene;
}
