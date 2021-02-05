#ifndef CMATERIAL_H
#define CMATERIAL_H

#include "CTexture.h"

#include <memory>

class CMaterial {
public:
	//マテリアル名
	char mName[64];
	//拡散光の色RGBA
	float mDiffuse[4];
	//テクスチャのスマートポインタ
	std::shared_ptr<CTexture> mpTexture;
	//マテリアル毎の頂点数
	int mVertexNum;

	//デフォルトコンストラクタ
	CMaterial();
	//マテリアルを有効にする
	void Enabled();
	//マテリアルを無効にする
	void Disabled();
};

#endif
