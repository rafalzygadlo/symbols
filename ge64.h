#ifndef __GE64
#define __GE64

#include <gl/gl.h>
#include "geometrytools.h"
#include "nvfastfont.h"
#include "driver.h"
#include "navibroker.h"


class CGE64 :public CDriver
{
	void *m_DB;
	int m_LightOn;
	int GetLightOn();
	
	
public:

	CGE64(void *db,CNaviBroker *broker);
	~CGE64();

	wxString GetDriverHtml(int v) override;
	wxString GetDriverFullHtml() override;
	void ShowAction() override;

		

};

#endif