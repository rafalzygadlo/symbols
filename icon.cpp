#include "icon.h"

BEGIN_EVENT_TABLE(CMyIcon,wxButton)
	EVT_MOUSE_EVENTS(OnMouse)
	EVT_LEAVE_WINDOW(OnWindowLeave)
	EVT_ENTER_WINDOW(OnWindowEnter)
	//EVT_PAINT(OnPaint)
END_EVENT_TABLE()

CMyIcon::CMyIcon(wxWindow *Parent, int id,wxString name,wxString tip)
:wxButton(Parent,id,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxBORDER_SIMPLE)
{
	wxFont Font;
	Font.SetWeight(wxBOLD);
	Font.SetPointSize(10);
	SetFont(Font);
	//SetBackgroundColour(wxColor(200,200,200));
	SetCursor(wxCursor(wxCURSOR_HAND));
	SetMinSize(wxSize(35,35));
	SetToolTip(tip);
	SetLabel(name);
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

	event.Skip();
}

void CMyIcon::OnWindowLeave(wxMouseEvent &event)
{
	//SetBackgroundColour(wxColor(200,200,200));
	SetSize(35,35);
	Refresh();
}

void CMyIcon::OnWindowEnter(wxMouseEvent &event)
{
	//SetBackgroundColour(wxColor(220,220,220));
	SetSize(40,40);
	Refresh();
}

void CMyIcon::SetOn(bool v)
{
	if(v)
		SetForegroundColour(wxColor(0,200,0));
	else
		SetForegroundColour(wxColor(200,0,0));


}