#include <wx/wrapsizer.h>
#include "color.h"
#include "conf.h"
#include "tools.h"


BEGIN_EVENT_TABLE(CColorPanel, wxPanel)
	EVT_HYPERLINK(ID_ADD,CColorPanel::OnAddColor)
END_EVENT_TABLE()

CColorPanel::CColorPanel(wxWindow *parent)
	:wxPanel(parent,wxID_ANY,wxDefaultPosition,wxSize(-1,100))
{
	m_Parent = parent;
	m_Sizer = new wxBoxSizer(wxVERTICAL);
	SetBackgroundColour(*wxWHITE);

	m_ScrollSizer = new wxWrapSizer(wxHORIZONTAL);
	m_Scroll = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	m_Sizer->Add(m_Scroll,1,wxALL|wxEXPAND,0);
	m_Scroll->SetSizer(m_ScrollSizer);
	m_Scroll->SetFocusIgnoringChildren();
	
	CColor *Color = new CColor(m_Scroll);
	m_ScrollSizer->Add(Color,0,wxALL,2);

	SetSizer(m_Sizer);

	wxHyperlinkCtrl *AddColor = new wxHyperlinkCtrl(this,ID_ADD,GetMsg(MSG_ADD_COLOR),wxEmptyString);
	m_Sizer->Add(AddColor,0,wxALL,5);

	m_Scroll->SetScrollbars(5, 5, 5, 5);
		
}

CColorPanel::~CColorPanel()
{
}

void CColorPanel::OnAddColor(wxHyperlinkEvent &event)
{
	CColor *Color = new CColor(m_Scroll);
	m_ScrollSizer->Add(Color,0,wxALL,2);
	m_ScrollSizer->FitInside(m_Scroll);
}


BEGIN_EVENT_TABLE(CColor, wxPanel)
	//EVT_BUTTON(ID_ADD,CColor::OnAddColor)
	EVT_CONTEXT_MENU(CColor::OnContextMenu)
END_EVENT_TABLE()

CColor::CColor(wxWindow *parent)
	:wxPanel(parent,wxID_ANY,wxDefaultPosition)
{
	m_Parent = parent;
	m_Sizer = new wxBoxSizer(wxHORIZONTAL);
	
	wxPanel *Panel = new wxPanel(this);
	Panel->SetBackgroundColour(*wxBLACK);
	Panel->SetMinSize(wxSize(30,30));
	m_Sizer->Add(Panel,0,wxALL|wxEXPAND,2);
	
	//wxStaticText *Label = new wxStaticText(this,wxID_ANY,_("Default name"));
	//m_Sizer->Add(Label,0,wxALL,2);
		
	//wxBoxSizer *PanelSizer = new wxBoxSizer(wxVERTICAL);
	//Panel->SetSizer(PanelSizer);

	this->SetSizer(m_Sizer);
}

CColor::~CColor()
{

}

void CColor::OnContextMenu(wxContextMenuEvent &event)
{
	wxMenu *Menu = new wxMenu();
	Menu->Append(ID_DELETE,GetMsg(MSG_DELETE));
	Menu->Append(ID_EDIT,GetMsg(MSG_EDIT));

	PopupMenu(Menu);
	delete Menu;
}