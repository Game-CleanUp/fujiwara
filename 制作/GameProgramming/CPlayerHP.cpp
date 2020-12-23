#include"CPlayerHP.h"
#include"CSceneGame.h"


void CPlayerHP::Render(){

	//���f���r���[�s��̑ޔ�
	glPushMatrix();
	//���f���r���[�s��̏�����
	glLoadIdentity();

	//���f���r���[�s�񂩂�
	//�v���W�F�N�V�����s��֐؂�ւ�
	glMatrixMode(GL_PROJECTION);
	//�v���W�F�N�V�����s��̑ޔ�
	glPushMatrix();
	//�v���W�F�N�V�����s��̏�����
	glLoadIdentity();
	//2D�`��̐ݒ�
	gluOrtho2D(-400,400,-300,300);
	//Depth�e�X�g�I�t
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	//��
	glColor3f(0.0f, 1.0f, 0.0f);

	x = -390 + 150 * CSceneGame::mBatteryNow / CSceneGame::mBatteryMax;
	y = -280;
	w = 150 * CSceneGame::mBatteryNow / CSceneGame::mBatteryMax;
	h = 5;
	//mEnabled = true;
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