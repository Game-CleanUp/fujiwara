#ifndef CIMAGE_H
#define CIMAGE_H
#include "CBillBoard.h"

class CImage :public CBillBoard{
public:
	CImage(std::shared_ptr<CTexture>texture, const CVector&pos, const CVector&rot, const CVector&sca);
	//�g�p����e�N�X�`���̍��W���w�肷��
	//���_����
	void SetUv(float left, float right, float bottom, float top);
	void Update();

};

#endif