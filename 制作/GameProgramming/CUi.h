#ifndef CUI_H
#define CUI_H

#include"CRectangle.h"
#include"CScene.h"

class CGaugeBack : public CRectangle{
public:
	void Render();
};

class CTrapUI : public CRectangle{
public:
	void Render();
};

class CTitleUI :public CRectangle{
public:
	void Render();
};

class CGomiUI :public CRectangle{
public:
	void Render();
};


#endif