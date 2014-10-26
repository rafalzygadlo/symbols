#include <wx/colordlg.h>
#include <wx/mstream.h>
#include "images/add.img"
#include "images/del.img"
#include "color.h"
#include "conf.h"
#include "tools.h"

//extern unsigned int	del_size;
//extern unsigned char del[]; 

//extern unsigned int	add_size;
//extern unsigned char add[]; 

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
	m_PanelSizer = new wxBoxSizer(wxVERTICAL);
	m_Panel->SetSizer(m_PanelSizer);
	
	wxMemoryInputStream in_1((const unsigned char*)add,add_size);
    wxImage myImage_1(in_1, wxBITMAP_TYPE_PNG);
	m_PanelSizer->AddStretchSpacer(1);
	wxButton *Button = new wxBitmapButton(m_Panel,ID_NEW,wxBitmap(myImage_1));
	m_PanelSizer->Add(Button,0,wxALL|wxALIGN_RIGHT,1);
			
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
	EVT_BUTTON(ID_DELETE,CColor::OnDelete)
END_EVENT_TABLE()

CColor::CColor(wxWindow *parent, CColorPanel *panel)
	:wxPanel(parent,wxID_ANY,wxDefaultPosition)
{
	m_Parent = parent;
	m_ColorPanel = panel;
	m_Sizer = new wxBoxSizer(wxHORIZONTAL);
	
	m_Panel = new wxPanel(this);
	m_Panel->SetBackgroundColour(*wxWHITE);
	m_Panel->SetWindowStyle(wxBORDER_SIMPLE);
	m_Sizer->Add(m_Panel,1,wxALL|wxEXPAND,0);

	wxMemoryInputStream in_1((const unsigned char*)del,del_size);
    wxImage myImage_1(in_1, wxBITMAP_TYPE_PNG);

	//wxButton *Delete = new wxBitmapButton(this,ID_DELETE,wxBitmap(myImage_1));
	//m_Sizer->Add(Delete,0,wxALL,1);
	
	SetSizer(m_Sizer);
}

CColor::~CColor()
{

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

wxColor CColor::GetColor()
{
	return m_Panel->GetBackgroundColour();
}