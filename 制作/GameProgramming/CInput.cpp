#include "CInput.h"
#include <Windows.h>
//�E�B���h�E�|�C���^
GLFWwindow* CInput::mpWindow = 0;
/*
������
Init(�E�B���h�E�|�C���^)
*/
void CInput::Init(GLFWwindow* w) {
	mpWindow = w;
}
/*
�}�E�X�J�[�\���̍��W���擾����
GetMousePos(X���W�|�C���^, Y���W�|�C���^)
�f�B�X�v���C�̍��オ���_(0,0)
��ʉE������X���v���X
��ʉ�������Y���v���X
*/
void CInput::GetMousePos(int *px, int *py) {
	POINT Point;
	//WindowsAPI
	GetCursorPos(&Point);
	*px = Point.x;
	*py = Point.y;
	return;
}
/*
�}�E�X�{�^���̏��
GetMouseButton(�{�^��)
�{�^��:
GLFW_MOUSE_BUTTON_LEFT:���{�^��
GLFW_MOUSE_BUTTON_RIGHT:�E�{�^��
return:
true�F������Ă���
false:������Ă��Ȃ�
*/
bool CInput::GetMouseButton(int button) {
	int state = glfwGetMouseButton(mpWindow, button);
	return state == GLFW_PRESS;
}
/*
�}�E�X�J�[�\���̍��W��ݒ肷��
SetCursorPos(X���W,Y���W)
�f�B�X�v���C�̍��オ���_(0,0)
*/
void CInput::SetMousePos(int x, int y) {
	//WindowsAPI
	SetCursorPos(x, y);
}

/*
�}�E�X�J�[�\���̍��W���擾����
GetMousePosW(X���W�|�C���^, Y���W�|�C���^)
�E�B���h�E�̍��オ���_(0,0)
*/
void CInput::GetMousePosW(int *px, int *py)
{
	double xpos, ypos;
	glfwGetCursorPos(mpWindow, &xpos, &ypos);
	*px = xpos;
	*py = ypos;
	return;
}


