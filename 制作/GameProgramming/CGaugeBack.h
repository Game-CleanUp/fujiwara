#ifndef CGAUGEBACK_H
#define CGAUGEBACK_H

#include"CRectangle.h"

extern CTexture Texture;

class CGaugeBack : public CRectangle{
public:

	void Render();
	
};

class CUI : public CRectangle{
public:

	void Render();
};

#endif