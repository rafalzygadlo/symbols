#ifndef __ICON_H
#define __ICON_H

#include <wx/wx.h>

class CMyIcon: public wxButton
{
	void OnMouse(wxMouseEvent &event);
	void OnWindowLeave(wxMouseEvent &event);
	void OnWindowEnter(wxMouseEvent &event);
	
public:
		
	CMyIcon(wxWindow *Parent,int id,wxString name,wxString tip);
	~CMyIcon();
	DECLARE_EVENT_TABLE();

};


#endif