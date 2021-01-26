#ifndef CGAUGEBACK_H
#define CGAUGEBACK_H

#include"CRectangle.h"
#include"CTexture.h"

class CGaugeBack : public CRectangle{
public:

	void Render();
	CTexture Texture;
};

#endif