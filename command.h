#ifndef __COMMAND_H
#define __COMMAND_H

#include <wx/wx.h>
#include <wx/hyperlink.h>
#include "conf.h"

class CCommandPanel: public wxPanel
{
	void *m_DB;
	wxStaticBoxSizer *m_Sizer;
		
public:

	CCommandPanel(void *db, wxWindow *parent);
	~CCommandPanel();
	wxImage GetPicture();
	void Read();
	void Clear();

	DECLARE_EVENT_TABLE();
	

};


#endif