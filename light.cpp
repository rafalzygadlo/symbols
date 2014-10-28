#include "light.h"
#include "conf.h"
#include "tools.h"
#include "db.h"
#include <wx/mstream.h>
#include <wx/colordlg.h>
#include <wx/dataview.h>
#include "images/del.img"
#include "images/add.img"
#include <wx/clrpicker.h>

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
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	SetSizer(Sizer);
					
	//wxMemoryInputStream in_1((const unsigned char*)add,add_size);
    //wxImage myImage_1(in_1, wxBITMAP_TYPE_PNG);
	//wxButton *New = new wxBitmapButton(this,ID_NEW,wxBitmap(myImage_1));
	//Sizer->Add(New,0,wxALL,1);
	
	CLightDraw *LightDraw = new CLightDraw(this);
	//CLight *Light = new CLight(this);
	m_List.Add(LightDraw);
	Sizer->Add(LightDraw,1,wxALL|wxEXPAND,1);
	
}

CLightPanel::~CLightPanel()
{
	
}

size_t CLightPanel::GetCount()
{
	return m_List.size();
}

CLight *CLightPanel::GetLight(int id)
{
	return (CLight*)m_List.Item(id);
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
	CLightDraw *LightDraw = new CLightDraw(this);
	//CLight *Light = new CLight(this);
	m_List.Add(LightDraw);
	this->GetSizer()->Add(LightDraw,1,wxALL|wxEXPAND,1);
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

void CLightPanel::OnNewSector()
{
	this->Layout();
	m_Top->Layout();
}

void CLightPanel::OnDeleteSector()
{
	this->Layout();
	m_Top->Layout();
}

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
	EVT_BUTTON(ID_NEW_SECTOR,CLight::OnNewSector)
	//EVT_BUTTON(ID_DELETE_SECTOR,CLight::OnDeleteSector)
	EVT_BUTTON(ID_DELETE,CLight::OnDelete)
END_EVENT_TABLE()

CLight::CLight(CLightPanel *parent)
	:wxPanel(parent,wxID_ANY,wxDefaultPosition)
{
	m_Counter = 1;
	m_ItemPanel = parent;
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);//,this,GetMsg(MSG_LIGHT));
	SetSizer(Sizer);
		
	wxMemoryInputStream in_1((const unsigned char*)del,del_size);
    wxImage myImage_1(in_1, wxBITMAP_TYPE_PNG);
	wxButton *Del = new wxBitmapButton(this,ID_DELETE,wxBitmap(myImage_1));
	Sizer->Add(Del,0,wxALL,1);
	
	wxFlexGridSizer *FlexSizer = new wxFlexGridSizer(2);
	Sizer->Add(FlexSizer,0,wxALL|wxEXPAND,0);
		
	wxStaticText *LabelColor = new wxStaticText(this,wxID_ANY,GetMsg(MSG_COLOR));
	FlexSizer->Add(LabelColor,0,wxALL|wxALIGN_CENTER_VERTICAL,1);
	wxColourPickerCtrl *ColorPicker = new wxColourPickerCtrl(this,wxID_ANY);
	FlexSizer->Add(ColorPicker,0,wxALL,1);

	wxStaticText *LabelCoverage = new wxStaticText(this,wxID_ANY,GetMsg(MSG_COVERAGE));
	FlexSizer->Add(LabelCoverage,0,wxALL|wxALIGN_CENTER_VERTICAL,1);
	m_CoverageText = new wxSpinCtrl(this,wxID_ANY);
	FlexSizer->Add(m_CoverageText,0,wxALL|wxEXPAND,1);
	
	//m_SectorSizer = new wxStaticBoxSizer(wxVERTICAL,this,GetMsg(MSG_SECTOR));
	//Sizer->Add(m_SectorSizer,0,wxALL|wxEXPAND,5);
	
	wxStaticText *LabelSectorFrom = new wxStaticText(this,wxID_ANY,GetMsg(MSG_SECTOR_FROM));
	FlexSizer->Add(LabelSectorFrom,0,wxALL|wxALIGN_CENTER_VERTICAL,1);
	m_SectorTextFrom = new wxSpinCtrl(this,wxID_ANY);
	FlexSizer->Add(m_SectorTextFrom,0,wxALL|wxEXPAND,1);
	
	wxStaticText *LabelSectorTo = new wxStaticText(this,wxID_ANY,GetMsg(MSG_SECTOR_TO));
	FlexSizer->Add(LabelSectorTo,0,wxALL|wxALIGN_CENTER_VERTICAL,1);
	m_SectorTextTo = new wxSpinCtrl(this,wxID_ANY);
	FlexSizer->Add(m_SectorTextTo,0,wxALL|wxEXPAND,1);
		
	//m_SectorSizer->Add(Sector,0,wxALL|wxEXPAND,2);
		
}

CLight::~CLight()
{

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
void CLight::OnNewSector(wxCommandEvent &event)
{
	CSectorPanel *Panel = new CSectorPanel(this);
	m_SectorSizer->Add(Panel,0,wxALL|wxEXPAND,2);
	m_ItemPanel->OnNewSector();

	m_Sectors.Add(Panel);
	
}

void CLight::OnDeleteSector(CSectorPanel *panel)
{
	this->GetSizer()->Detach(panel);
	delete panel;
	m_ItemPanel->OnDeleteSector();
	m_Sectors.Remove(panel);
}

//void CLight::OnNewSector(CSectorPanel *panel)
//{
//	this->GetSizer()->Add(panel,0,wxALL|wxEXPAND,5);
//}

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

wxColor CLight::GetColor()
{
	return GetBackgroundColour();
}

BEGIN_EVENT_TABLE(CColorLight, wxPanel)
	EVT_LEFT_DOWN(OnClick)
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

void CColorLight::OnClick(wxMouseEvent &event)
{
	wxColourDialog dialog(this);
	if (dialog.ShowModal() == wxID_OK)
	{
		wxColor color = dialog.GetColourData().GetColour();
		SetBackgroundColour(color);
		//SetFocus();
		Refresh();
	}

}

BEGIN_EVENT_TABLE(CSectorPanel, wxPanel)
	//EVT_BUTTON(ID_NEW,OnNew)
	EVT_BUTTON(ID_DELETE,OnDelete)
END_EVENT_TABLE()

CSectorPanel::CSectorPanel(CLight *parent, bool _add)
	:wxPanel(parent)
{
	m_Light = parent;
	wxFlexGridSizer *FlexSizer = new wxFlexGridSizer(5);
	this->SetSizer(FlexSizer);
		
	wxStaticText *LabelSectorFrom = new wxStaticText(this,wxID_ANY,GetMsg(MSG_SECTOR_FROM));
	FlexSizer->Add(LabelSectorFrom,0,wxALL|wxALIGN_CENTER_VERTICAL,1);
	m_SectorTextFrom = new wxSpinCtrl(this,wxID_ANY);
	FlexSizer->Add(m_SectorTextFrom,0,wxALL|wxEXPAND,1);
	
	wxStaticText *LabelSectorTo = new wxStaticText(this,wxID_ANY,GetMsg(MSG_SECTOR_TO));
	FlexSizer->Add(LabelSectorTo,0,wxALL|wxALIGN_CENTER_VERTICAL,1);
	m_SectorTextTo = new wxSpinCtrl(this,wxID_ANY);
	FlexSizer->Add(m_SectorTextTo,0,wxALL|wxEXPAND,1);

	if(!_add)
	{	
		wxMemoryInputStream in_1((const unsigned char*)del,del_size);
		wxImage myImage_1(in_1, wxBITMAP_TYPE_PNG);
		wxButton *Del = new wxBitmapButton(this,ID_DELETE,wxBitmap(myImage_1));
		FlexSizer->Add(Del,0,wxALL,1);
	}

}

//void CSectorPanel::OnDelete(wxCommandEvent &event)
//{
	//m_LightPanel->OnNewSector(this);
//}

void CSectorPanel::OnDelete(wxCommandEvent &event)
{
	m_Light->OnDeleteSector(this);

}

BEGIN_EVENT_TABLE(CLightDraw, wxPanel)
	//EVT_BUTTON(ID_NEW,OnNew)
	EVT_PAINT(OnPaint)
	EVT_SIZE(OnSize)
END_EVENT_TABLE()

CLightDraw::CLightDraw(CLightPanel *parent)
	:wxPanel(parent)
{
	SetBackgroundColour(*wxRED);
	//SetMinSize(wxSize(150,150));
	//m_Light = parent;
	m_Height = 150;
	m_Width = 150;
}

void CLightDraw::OnSize(wxSizeEvent &event)
{
	//GetClientSize(&m_Width, &m_Height);

}

void CLightDraw::OnPaint(wxPaintEvent &event)
{
	wxPaintDC dc(this);
	
	//wxSize s = GetSize();

	int r = (m_Width*m_Height)*2 / ((2*m_Width) + (2*m_Height)); 

	//dc.DrawAr

	dc.DrawCircle(m_Width/2,m_Height/2,r);
}