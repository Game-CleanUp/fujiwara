#ifndef CIMAGE_H
#define CIMAGE_H
#include "CBillBoard.h"

class CImage :public CBillBoard{
public:
	CImage(std::shared_ptr<CTexture>texture, const CVector&pos, const CVector&rot, const CVector&sca);
	//使用するテクスチャの座標を指定する
	//原点左上
	void SetUv(float left, float right, float bottom, float top);
	void Update();

};

#endif