#ifndef __PANEL_H
#define __PANEL_H

#include <wx/wx.h>
#include "conf.h"


class CControl 
{

public:
	
	void CheckRight(int id_module, int id_action);
	
};


class CPanel: public CControl, public wxPanel
{

public:
	 CPanel(wxWindow *parent);
		
};

class CMenu :public CControl, public wxMenu
{
	void OnMenu(wxCommandEvent &event);

public:
	CMenu();
	
	DECLARE_EVENT_TABLE();

};




#endif