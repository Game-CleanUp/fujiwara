#include"CUi.h"
#include"CSceneGame.h"

extern CTexture Texture;
extern CTexture Texture2;

void CGaugeBack::Render(){

	//���f���r���[�s��̑ޔ�
	glPushMatrix();
	//���f���r���[�s��̏�����
	glLoadIdentity();
	//�v���W�F�N�V�����s��֐؂�ւ�
	glMatrixMode(GL_PROJECTION);
	//�v���W�F�N�V�����s��̑ޔ�
	glPushMatrix();
	//�v���W�F�N�V�����s��̏�����
	glLoadIdentity();
	//2D�`��̐ݒ�
	gluOrtho2D(-400, 400, -300, 300);
	//Depth�e�X�g�I�t
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 1.0f);	//��

	x = -240;
	y = -275;
	w = 152;
	h = 7;
	CRectangle::Render();

	//�v���W�F�N�V�����s���߂�
	glPopMatrix();
	//���f���r���[���[�h�֐؂�ւ�
	glMatrixMode(GL_MODELVIEW);
	//���f���r���[�s���߂�
	glPopMatrix();
	//Depth�e�X�g�I��
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}

void CTrapUI::Render(){

	//���f���r���[�s��̑ޔ�
	glPushMatrix();
	//���f���r���[�s��̏�����
	glLoadIdentity();
	//�v���W�F�N�V�����s��֐؂�ւ�
	glMatrixMode(GL_PROJECTION);
	//�v���W�F�N�V�����s��̑ޔ�
	glPushMatrix();
	//�v���W�F�N�V�����s��̏�����
	glLoadIdentity();
	//2D�`��̐ݒ�
	gluOrtho2D(0, 800, 0, 600);
	//Depth�e�X�g�I�t
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	x = 640;
	y = 45;
	w = 20;
	h = 25;
	CRectangle::Render(Texture, 0, 1800, 2770, 0);

	//�v���W�F�N�V�����s���߂�
	glPopMatrix();
	//���f���r���[���[�h�֐؂�ւ�
	glMatrixMode(GL_MODELVIEW);
	//���f���r���[�s���߂�
	glPopMatrix();
	//Depth�e�X�g�I��
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}

void CTitleUI::Render(){

	//���f���r���[�s��̑ޔ�
	glPushMatrix();
	//���f���r���[�s��̏�����
	glLoadIdentity();
	//�v���W�F�N�V�����s��֐؂�ւ�
	glMatrixMode(GL_PROJECTION);
	//�v���W�F�N�V�����s��̑ޔ�
	glPushMatrix();
	//�v���W�F�N�V�����s��̏�����
	glLoadIdentity();
	//2D�`��̐ݒ�
	gluOrtho2D(0, 800, 0, 600);
	//Depth�e�X�g�I�t
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glColor3f(0.0f, 1.0f, 0.0f);

	x = 0;
	y = 0;
	w = 800;
	h = 600;
	CRectangle::Render();

	//�v���W�F�N�V�����s���߂�
	glPopMatrix();
	//���f���r���[���[�h�֐؂�ւ�
	glMatrixMode(GL_MODELVIEW);
	//���f���r���[�s���߂�
	glPopMatrix();
	//Depth�e�X�g�I��
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}

void CGomiUI::Render(){

	//���f���r���[�s��̑ޔ�
	glPushMatrix();
	//���f���r���[�s��̏�����
	glLoadIdentity();
	//�v���W�F�N�V�����s��֐؂�ւ�
	glMatrixMode(GL_PROJECTION);
	//�v���W�F�N�V�����s��̑ޔ�
	glPushMatrix();
	//�v���W�F�N�V�����s��̏�����
	glLoadIdentity();
	//2D�`��̐ݒ�
	gluOrtho2D(0, 800, 0, 600);
	//Depth�e�X�g�I�t
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	x = 250;
	y = 60;
	w = 25;
	h = 25;
	CRectangle::Render(Texture2, 0, 2770, 2314, 0);

	//�v���W�F�N�V�����s���߂�
	glPopMatrix();
	//���f���r���[���[�h�֐؂�ւ�
	glMatrixMode(GL_MODELVIEW);
	//���f���r���[�s���߂�
	glPopMatrix();
	//Depth�e�X�g�I��
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}