#include "icon.h"

BEGIN_EVENT_TABLE(CMyIcon,wxButton)
	//EVT_MOUSE_EVENTS(CMyIcon::OnMouse)
	//EVT_LEAVE_WINDOW(CMyIcon::OnWindowLeave)
	//EVT_ENTER_WINDOW(CMyIcon::OnWindowEnter)
END_EVENT_TABLE()

CMyIcon::CMyIcon(wxWindow *Parent, int id,wxString name,wxString tip)
:wxButton(Parent,id)
{
	//SetBackgroundColour(wxColor(200,200,200));
	SetCursor(wxCursor(wxCURSOR_HAND));
	SetMinSize(wxSize(32,32));
	SetLabel(name);
	SetToolTip(tip);
}

CMyIcon::~CMyIcon()
{
}

void CMyIcon::OnMouse(wxMouseEvent &event)
{
	/*
	if(event.LeftDown())
	{
		
		if(event.GetId() ==  ID_ICON)
		{
			showicons_panel = !showicons_panel;
			m_Frame->ShowIconChanger(showicons_panel);
			return;
		}
	
		if((event.GetId() >= ID_ICONSET) && (event.GetId() < ID_ICONSET + icon_counter))
			m_Frame->SetMarkerIcon(event.GetId() - ID_ICONSET);
		
	}
		*/
}

void CMyIcon::OnWindowLeave(wxMouseEvent &event)
{
	SetBackgroundColour(wxColor(200,200,200));
	SetSize(32,32);
	Refresh();
}

void CMyIcon::OnWindowEnter(wxMouseEvent &event)
{
	SetBackgroundColour(wxColor(255,255,255));
	SetSize(34,34);
	Refresh();
}
