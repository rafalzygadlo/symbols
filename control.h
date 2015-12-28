#ifndef __PANEL_H
#define __PANEL_H

#include <wx/wx.h>
#include "conf.h"

class CPanel: public wxPanel
{
	
public:
	CPanel(wxWindow *parent);
	void CheckRight(int id_module, int id_action);
	void CheckRight(const char *module, const char *action);
	
};

class CMenu :public wxMenu
{
	void OnMenu(wxCommandEvent &event);

public:
	CMenu();
	void CheckRight(int id_module, int id_action, wxMenuItem *item);
	void CheckRight(const char *module, const char *action, wxMenuItem *item);

	DECLARE_EVENT_TABLE();

};

#endif