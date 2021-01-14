#include "CKey.h"

bool CKey::Push(char key) {
	
	return (GetKeyState(key) & 0x8000) == 0x8000;
}

bool CKey::Flg[256];

bool CKey::Once(char key) {
	//�L�[��������Ă��邩
	if ((GetKeyState(key) & 0x8000)) {
		//!���Z�q�F�ے�
		//������������
		if (!Flg[key]) {
			//�������ɂ���
			Flg[key] = true;
			//���߂ĉ����ꂽ�̂�true�Ԃ�
			return true;
		}
	}
	else {
		//������Ă��Ȃ��̂�false�ɂ���
		Flg[key] = false;
	}
	//������Ă��Ȃ����A������
	return false;
}
