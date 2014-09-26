#include <wx/colordlg.h>
#include <wx/mstream.h>
#include "images/add.img"
#include "color.h"
#include "conf.h"
#include "tools.h"


BEGIN_EVENT_TABLE(CColorPanel, wxPanel)
	EVT_BUTTON(ID_NEW,CColorPanel::OnNew)
END_EVENT_TABLE()

CColorPanel::CColorPanel(wxWindow *parent,wxWindow *top)
	:wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize)
{
	m_Parent = parent;
	m_Top = top;
	m_Sizer = new wxBoxSizer(wxVERTICAL);
		
	m_Panel = new wxPanel(this);
	m_Panel->SetWindowStyle(wxBORDER_SIMPLE);
	m_Sizer->Add(m_Panel,1,wxALL|wxEXPAND,0);
	m_PanelSizer = new wxWrapSizer(wxHORIZONTAL);
	m_Panel->SetSizer(m_PanelSizer);
	
	wxMemoryInputStream in_1((const unsigned char*)add,add_size);
    wxImage myImage_1(in_1, wxBITMAP_TYPE_PNG);

	wxButton *Button = new wxBitmapButton(m_Panel,ID_NEW,wxBitmap(myImage_1));
	m_PanelSizer->Add(Button,0,wxALL,3);
			
	SetSizer(m_Sizer);
			
}

CColorPanel::~CColorPanel()
{
}

wxArrayPtrVoid CColorPanel::GetColorPanels()
{
	return m_ColorPanels;
}

void CColorPanel::New(wxColor color)
{
	CColor *Color = new CColor(m_Panel,this);
	Color->SetColor(color);
	m_PanelSizer->Add(Color,0,wxALL,1);
	m_ColorPanels.Add(Color);
}

void CColorPanel::OnNew(wxCommandEvent &event)
{
	wxColourDialog dialog(this);
	if (dialog.ShowModal() == wxID_OK)
	{
		wxColor color = dialog.GetColourData().GetColour();
		New(color);
	}
		
	m_Top->Layout();
	m_Top->GetSizer()->SetSizeHints(m_Top);
	
}

void CColorPanel::OnEdit(CColor *ptr)
{
	wxColourDialog dialog(this);
	if (dialog.ShowModal() == wxID_OK)
	{
		wxColor color = dialog.GetColourData().GetColour();
		ptr->SetColor(color);
		ptr->Refresh();
	}

}

void CColorPanel::OnDelete(CColor *ptr)
{
	m_PanelSizer->Detach(ptr);
	m_Top->Layout();
	m_Top->GetSizer()->SetSizeHints(m_Top);
	m_ColorPanels.Remove(ptr);
	delete ptr;
}

BEGIN_EVENT_TABLE(CColor, wxPanel)
	EVT_CONTEXT_MENU(CColor::OnContextMenu)
	EVT_MENU(ID_DELETE,CColor::OnDelete)
	EVT_MENU(ID_EDIT,CColor::OnEdit)
END_EVENT_TABLE()

CColor::CColor(wxWindow *parent, CColorPanel *panel)
	:wxPanel(parent,wxID_ANY,wxDefaultPosition)
{
	m_Parent = parent;
	m_ColorPanel = panel;
	m_Sizer = new wxBoxSizer(wxHORIZONTAL);
	
	m_Panel = new wxPanel(this);
	m_Panel->SetBackgroundColour(*wxWHITE);
	m_Panel->SetMinSize(wxSize(25,25));
	m_Sizer->Add(m_Panel,0,wxALL|wxEXPAND,2);

	
	
	//wxStaticText *Label = new wxStaticText(this,wxID_ANY,_("Default name"));
	//m_Sizer->Add(Label,0,wxALL,2);
		
	//wxBoxSizer *PanelSizer = new wxBoxSizer(wxVERTICAL);
	//Panel->SetSizer(PanelSizer);

	SetSizer(m_Sizer);
}

CColor::~CColor()
{

}

void CColor::OnContextMenu(wxContextMenuEvent &event)
{
	int count = m_ColorPanel->GetColorPanels().size();

	wxMenu *Menu = new wxMenu();
	Menu->Append(ID_EDIT,GetMsg(MSG_EDIT));
	Menu->Append(ID_DELETE,GetMsg(MSG_DELETE));
	
	PopupMenu(Menu);
	delete Menu;
}

void CColor::OnDelete(wxCommandEvent &event)
{
	m_ColorPanel->OnDelete(this);
}

void CColor::OnEdit(wxCommandEvent &event)
{
	m_ColorPanel->OnEdit(this);
}

void CColor::SetColor(wxColor color)
{
	m_Panel->SetBackgroundColour(color);
}