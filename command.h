#ifndef __COMMAND_H
#define __COMMAND_H

#include <wx/wx.h>
#include <wx/hyperlink.h>
#include "conf.h"

class CCommandPanel: public wxPanel
{
	void *m_DB;
	wxStaticBoxSizer *m_Sizer;
	wxSlider *m_PowerOfLight;

	void SetGui();

public:

	CCommandPanel(void *db, wxWindow *parent);
	~CCommandPanel();
		

	DECLARE_EVENT_TABLE();
	

};


#endif