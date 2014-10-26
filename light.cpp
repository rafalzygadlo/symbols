#include "light.h"
#include "conf.h"
#include "tools.h"
#include "db.h"
#include <wx/mstream.h>
#include <wx/colordlg.h>
#include <wx/dataview.h>
#include "images/del.img"
#include "images/add.img"

extern unsigned int	add_size;
extern unsigned char add[]; 
extern unsigned int	del_size;
extern unsigned char del[]; 

BEGIN_EVENT_TABLE(CLightPanel, wxPanel)
	EVT_BUTTON(ID_NEW,CLightPanel::OnNew)
END_EVENT_TABLE()
CLightPanel::CLightPanel(wxWindow *top, wxWindow *parent)
	:wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize)
{
	m_Top = top;
	wxStaticBoxSizer *Sizer = new wxStaticBoxSizer(wxVERTICAL,this,GetMsg(MSG_LIGHT));
	SetSizer(Sizer);
	wxMemoryInputStream in_1((const unsigned char*)add,add_size);
    wxImage myImage_1(in_1, wxBITMAP_TYPE_PNG);
	wxButton *New = new wxBitmapButton(this,ID_NEW,wxBitmap(myImage_1));
	Sizer->Add(New,0,wxALL,1);
			
	SetSizer(Sizer);
				
}

CLightPanel::~CLightPanel()
{
	
}

void CLightPanel::OnNew(wxCommandEvent &event)
{
	AppendPanel();
}
void CLightPanel::OnDelete(CLight *panel)
{
	RemovePanel(panel);
}

void CLightPanel::AppendPanel()
{
	CLight *Light = new CLight(this);
	m_List.Add(Light);
	this->GetSizer()->Insert(1,Light,0,wxALL|wxEXPAND,5);
	this->Layout();
	m_Top->Layout();
}

void CLightPanel::RemovePanel(CLight *panel)
{
	this->GetSizer()->Detach(panel);
	delete panel;
	m_List.Remove(panel);
	this->Layout();
	m_Top->Layout();
}

//void CLightPanel::_Layout()
//{
	//m_Top->Layout();
//}

wxArrayPtrVoid CLightPanel::GetItems()
{
	return m_List;
}

void CLightPanel::Read(wxString query)
{
	if(!my_query(query))
		return;
	
	int rows = 0;
	void *result = db_result();
	char **row;
	
	while(row = (char**)db_fetch_row(result))
	{
		wxString str(row[0],wxConvUTF8);
		wxString name(row[1],wxConvUTF8);
		//CItem *Item = new CItem(this,name);
		//Item->_SetId(str);
		//m_Items.Add(Item);
	}

	db_free_result(result);
	
}

BEGIN_EVENT_TABLE(CLight, wxPanel)
	EVT_BUTTON(ID_NEW,CLight::OnNew)
	EVT_BUTTON(ID_DELETE,CLight::OnDelete)
END_EVENT_TABLE()

CLight::CLight(CLightPanel *parent)
	:wxPanel(parent,wxID_ANY,wxDefaultPosition)
{
	m_Counter = 1;
	m_ItemPanel = parent;
	wxStaticBoxSizer *Sizer = new wxStaticBoxSizer(wxVERTICAL,this,GetMsg(MSG_LIGHT));
	SetSizer(Sizer);
		
	wxMemoryInputStream in_1((const unsigned char*)del,del_size);
    wxImage myImage_1(in_1, wxBITMAP_TYPE_PNG);
	wxButton *Del = new wxBitmapButton(this,ID_DELETE,wxBitmap(myImage_1));
	Sizer->Add(Del,0,wxALL,1);
	
	wxFlexGridSizer *FlexSizer = new wxFlexGridSizer(2);
	Sizer->Add(FlexSizer,0,wxALL|wxEXPAND,2);
		
	wxStaticText *LabelColor = new wxStaticText(this,wxID_ANY,GetMsg(MSG_COLOR));
	FlexSizer->Add(LabelColor,0,wxALL|wxALIGN_CENTER_VERTICAL,1);
	CColorLight *m_ColorPanel = new CColorLight(this);
	m_ColorPanel->SetMinSize(wxSize(PANEL_COLOR_WIDTH,PANEL_COLOR_HEIGHT));
	m_ColorPanel->SetWindowStyle(wxBORDER_SIMPLE);
	FlexSizer->Add(m_ColorPanel,0,wxALL,1);

	wxStaticText *LabelCoverage = new wxStaticText(this,wxID_ANY,GetMsg(MSG_COVERAGE));
	FlexSizer->Add(LabelCoverage,0,wxALL|wxALIGN_CENTER_VERTICAL,1);
	m_CoverageText = new wxTextCtrl(this,wxID_ANY);
	FlexSizer->Add(m_CoverageText,0,wxALL|wxEXPAND,1);
	
	wxStaticText *LabelSector = new wxStaticText(this,wxID_ANY,GetMsg(MSG_SECTOR));
	FlexSizer->Add(LabelSector,0,wxALL|wxALIGN_CENTER_VERTICAL,1);
	FlexSizer->AddSpacer(1);

	wxStaticText *LabelSectorFrom = new wxStaticText(this,wxID_ANY,GetMsg(MSG_FROM));
	FlexSizer->Add(LabelSectorFrom,0,wxALL|wxALIGN_CENTER_VERTICAL,1);
	m_SectorTextFrom = new wxSpinCtrl(this,wxID_ANY);
	FlexSizer->Add(m_SectorTextFrom,0,wxALL|wxEXPAND,1);
	
	wxStaticText *LabelSectorTo = new wxStaticText(this,wxID_ANY,GetMsg(MSG_TO));
	FlexSizer->Add(LabelSectorTo,0,wxALL|wxALIGN_CENTER_VERTICAL,1);
	m_SectorTextTo = new wxSpinCtrl(this,wxID_ANY);
	FlexSizer->Add(m_SectorTextTo,0,wxALL|wxEXPAND,1);
	
		
}

CLight::~CLight()
{

}

void CLight::AppendCombo()
{
//	CComboPanel *ComboPanel = new CComboPanel(this,m_Id);
//	this->GetSizer()->Add(ComboPanel,0,wxALL|wxEXPAND,1);
	
//	m_ItemPanel->_Layout();
//	m_Counter++;

//	m_List.Add(ComboPanel);

}
/*
void CLight::OnDelete(CComboPanel *panel)
{
	this->GetSizer()->Detach(panel);
	delete panel;
	m_List.Remove(panel);
	m_ItemPanel->_Layout();

}
*/
void CLight::OnNew(wxCommandEvent &event)
{
	AppendCombo();
}

void CLight::OnDelete(wxCommandEvent &event)
{
	m_ItemPanel->OnDelete(this);
}

wxString CLight::_GetId()
{
	return m_Id;
}

void CLight::_SetId(wxString v)
{
	m_Id = v;
}

void CLight::_SetName(wxString v)
{
//	m_Name->SetLabel(v);
}

BEGIN_EVENT_TABLE(CColorLight, wxPanel)
	EVT_LEFT_DCLICK(OnDClick)
	EVT_ENTER_WINDOW(OnWindowEnter)
END_EVENT_TABLE()

CColorLight::CColorLight(wxWindow *parent)
:wxPanel(parent)
{
	
}

void CColorLight::OnWindowEnter(wxMouseEvent &event)
{
	SetCursor(wxCursor(wxCURSOR_HAND));
}

void CColorLight::OnDClick(wxMouseEvent &event)
{
	wxColourDialog dialog(this);
	if (dialog.ShowModal() == wxID_OK)
	{
		wxColor color = dialog.GetColourData().GetColour();
		SetBackgroundColour(color);
		Refresh();
	}

}