#include "CKey.h"

bool CKey::Push(char key) {
	
	return (GetKeyState(key) & 0x8000) == 0x8000;
}

bool CKey::Flg[256];

bool CKey::Once(char key) {
	//キーが押されているか
	if ((GetKeyState(key) & 0x8000)) {
		//!演算子：否定
		//押し中か判定
		if (!Flg[key]) {
			//押し中にする
			Flg[key] = true;
			//初めて押されたのでtrue返す
			return true;
		}
	}
	else {
		//押されていないのでfalseにする
		Flg[key] = false;
	}
	//押されていないか、押し中
	return false;
}
