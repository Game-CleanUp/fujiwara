#ifndef CMATERIAL_H
#define CMATERIAL_H

#include "CTexture.h"

#include <memory>

class CMaterial {
public:
	//�}�e���A����
	char mName[64];
	//�g�U���̐FRGBA
	float mDiffuse[4];
	//�e�N�X�`���̃X�}�[�g�|�C���^
	std::shared_ptr<CTexture> mpTexture;
	//�}�e���A�����̒��_��
	int mVertexNum;

	//�f�t�H���g�R���X�g���N�^
	CMaterial();
	//�}�e���A����L���ɂ���
	void Enabled();
	//�}�e���A���𖳌��ɂ���
	void Disabled();
};

#endif
