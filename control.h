#ifndef __PANEL_H
#define __PANEL_H

#include <wx/wx.h>
#include "conf.h"

class CPanel: public wxPanel
{

public:
	CPanel(wxWindow *parent);
	bool CheckRight(int id_module, int id_action);		
};

class CMenu: public wxMenu
{
	void OnMenu(wxCommandEvent &event);

public:
	CMenu();
	bool CheckRight(int id_module, int id_action,wxMenuItem *item);
	
	DECLARE_EVENT_TABLE();

};




#endif