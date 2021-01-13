#include "CSceneTitle.h"
#include "CKey.h"

void CSceneTitle::Init() {

	//�e�L�X�g�t�H���g�̓ǂݍ��݂Ɛݒ�
	CText::mFont.Load("FontG.tga");
	CText::mFont.SetRowCol(1, 4096 / 64);

	//�V�[���̐ݒ�
	mScene = ETITLE;

	//��ʓ��e�͈͂̐ݒ�
	mLeft = -400;
	mRight = 400;
	mBottom = -300;
	mTop = 300;
}

//�X�V�����̃I�[�o�[���C�h
void CSceneTitle::Update() {

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
	CText::DrawString("CLEAN UP", 250, 400, 20, 20);
	CText::DrawString("PUSH ENTER KEY", 165, 200, 17, 17);

	//2D�`��I��
	End2D();

	if (CKey::Once(VK_RETURN)) {
		//���̃V�[���̓Q�[��
		mScene = EGAME;
	}
	if (CKey::Once('N')) {
		//���̃V�[���̓Q�[��3
		mScene = EGAME3;
	}
	if (CKey::Once('B')) {
		//���̃V�[���̓Q�[��2
		mScene = EGAME2;
	}
}
//���̃V�[���̎擾
CScene::EScene CSceneTitle::GetNextScene() {
	return mScene;
}
