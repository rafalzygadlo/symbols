#ifndef __GE64_H
#define __GE64_H

#include <gl/gl.h>
#include "geometrytools.h"
#include "nvfastfont.h"
#include "driver.h"
#include "navibroker.h"


class CGE64 :public CDriver
{
	int m_LightOn;
	int GetLightOn();
	
	
public:

	CGE64(CNaviBroker *broker);
	~CGE64();

	wxString GetDriverHtml(int v) override;
	void ShowAction() override;

		

};

#endif