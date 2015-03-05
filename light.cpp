#include "light.h"
#include "conf.h"
#include "tools.h"
#include "db.h"
#include <wx/mstream.h>
#include <wx/colordlg.h>
#include <wx/dataview.h>
#include "images/del.img"
#include "images/add.img"
#include "geometrytools.h"
#include <wx/valnum.h>

extern unsigned int	add_size;
extern unsigned char add[]; 
extern unsigned int	del_size;
extern unsigned char del[]; 

BEGIN_EVENT_TABLE(CLightPanel, wxPanel)
	EVT_BUTTON(ID_NEW,CLightPanel::OnNew)
	EVT_SIZE(OnSize)
	EVT_PAINT(OnPaint)
END_EVENT_TABLE()
CLightPanel::CLightPanel(void *db,wxWindow *top, wxWindow *parent)
	:wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize)
{
	m_DB = db;
	m_Top = top;
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	SetSizer(Sizer);
	
	wxMemoryInputStream in_1((const unsigned char*)add,add_size);
    wxImage myImage_1(in_1, wxBITMAP_TYPE_PNG);
	//wxButton *New = new wxBitmapButton(this,ID_NEW,wxBitmap(myImage_1));
	//Sizer->Add(New,0,wxALL,1);

	m_Sizer = new wxWrapSizer(wxHORIZONTAL);
	Sizer->Add(m_Sizer,1,wxALL|wxEXPAND,0);
		
}

CLightPanel::~CLightPanel()
{
	
}

void CLightPanel::OnSize(wxSizeEvent &event)
{
	GetClientSize(&m_Width, &m_Height);

	m_CenterX = m_Width/2;
	m_CenterY = m_Height/2;
}

void CLightPanel::OnPaint(wxPaintEvent &event)
{
	wxPaintDC dc(this);
	
	//wxSize s = GetSize();

	int r = (m_Width*m_Height)*2 / ((2*m_Width) + (2*m_Height)); 
	r = m_Width/3;
	dc.DrawCircle(m_Width/2,m_Height/2,r);

	for(size_t i = 0; i < m_List.size();i++)
	{
		CLight *Light = (CLight*)m_List.Item(i);
		
		long from,to;
		
		wxPoint pt[3];
		Light->GetSectorFrom().ToLong(&from);
				
		wxPoint p1;
		p1.x = m_CenterX + (r * cos(nvToRad(from)));
		p1.y = m_CenterY + (r * sin(nvToRad(from)));
		dc.DrawLine(m_CenterX,m_CenterY, p1.x  , p1.y );
		
		wxPoint p2;		
		Light->GetSectorTo().ToLong(&to);
		p2.x = m_CenterX + (r * cos(nvToRad(to)));
		p2.y = m_CenterY + (r * sin(nvToRad(to)));
		dc.DrawLine(m_CenterX,m_CenterY, p2.x  , p2.y );
						
		wxBrush brush;
		brush.SetColour(wxColor(255,0,0));
		dc.SetBrush(brush);
		
		
		dc.DrawEllipticArc(p1,wxSize(100,100), from,to);
		
	
	}

	
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
	CLight *Light = new CLight(this);
	AppendPanel(Light);
}
void CLightPanel::OnDelete(CLight *panel)
{
	RemovePanel(panel);
}

void CLightPanel::AppendPanel(CLight *light)
{
	m_List.Add(light);
	//m_Sizer->Add(light,1,wxALL|wxEXPAND,1);
	//m_Top->Layout();
}

void CLightPanel::RemovePanel(CLight *panel)
{
	m_Sizer->Detach(panel);
	delete panel;
	m_List.Remove(panel);
	m_Top->Layout();
}

wxArrayPtrVoid CLightPanel::GetItems()
{
	return m_List;
}

void CLightPanel::Read(wxString query)
{
	if(!my_query(m_DB,query))
		return;
	
	int rows = 0;
	void *result = db_result(m_DB);
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
	EVT_BUTTON(ID_DELETE,CLight::OnDelete)
END_EVENT_TABLE()

CLight::CLight(CLightPanel *parent)
	:wxPanel(parent,wxID_ANY,wxDefaultPosition)
{
		
	wxFloatingPointValidator<float> CoverageValidator;
	CoverageValidator.SetStyle(wxFILTER_INCLUDE_CHAR_LIST);
	CoverageValidator.SetMin(COVERAGE_MIN);
	CoverageValidator.SetMax(COVERAGE_MAX);
	CoverageValidator.SetPrecision(COVERAGE_PRECISION);

	wxFloatingPointValidator<float> SectorValidator;
	SectorValidator.SetStyle(wxFILTER_INCLUDE_CHAR_LIST);
	SectorValidator.SetMin(SECTOR_MIN);
	SectorValidator.SetMax(SECTOR_MAX);
	SectorValidator.SetPrecision(COVERAGE_PRECISION);

	wxTextValidator TextValidator;
	TextValidator.SetStyle(wxFILTER_EXCLUDE_CHAR_LIST);
	TextValidator.SetCharExcludes(_("'\"\\;?"));

	m_ItemPanel = parent;
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	SetSizer(Sizer);
		
	wxMemoryInputStream in_1((const unsigned char*)del,del_size);
    wxImage myImage_1(in_1, wxBITMAP_TYPE_PNG);
	wxButton *Del = new wxBitmapButton(this,ID_DELETE,wxBitmap(myImage_1));
	Sizer->Add(Del,0,wxALL,0);
	
	wxFlexGridSizer *FlexSizer = new wxFlexGridSizer(2);
	Sizer->Add(FlexSizer,1,wxALL|wxEXPAND,0);
		
	wxStaticText *LabelColor = new wxStaticText(this,wxID_ANY,GetMsg(MSG_COLOR));
	FlexSizer->Add(LabelColor,0,wxALL|wxALIGN_CENTER_VERTICAL,1);
	FlexSizer->AddGrowableCol(1);
	m_ColorPicker = new wxColourPickerCtrl(this,wxID_ANY);
	FlexSizer->Add(m_ColorPicker,0,wxALL,1);
		
	wxStaticText *LabelCoverage = new wxStaticText(this,wxID_ANY,GetMsg(MSG_COVERAGE));
	FlexSizer->Add(LabelCoverage,0,wxALL|wxALIGN_CENTER_VERTICAL,1);
	m_CoverageText = new wxTextCtrl(this,wxID_ANY);
	m_CoverageText->SetSize(80,-1);
	m_CoverageText->SetValue(wxString::Format(_("%4.2f"),COVERAGE_DEFAULT_VALUE));
	m_CoverageText->SetValidator(CoverageValidator);
	FlexSizer->Add(m_CoverageText,0,wxALL,1);
		
	wxStaticText *LabelSectorFrom = new wxStaticText(this,wxID_ANY,GetMsg(MSG_SECTOR_FROM));
	FlexSizer->Add(LabelSectorFrom,0,wxALL|wxALIGN_CENTER_VERTICAL,1);
	m_SectorTextFrom = new wxTextCtrl(this,wxID_ANY);
	m_SectorTextFrom->SetValidator(SectorValidator);
	m_SectorTextFrom->SetValue(wxString::Format(_("%4.2f"),SECTOR_FROM_DEFAULT_VALUE));
	FlexSizer->Add(m_SectorTextFrom,0,wxALL,1);
	
	wxStaticText *LabelSectorTo = new wxStaticText(this,wxID_ANY,GetMsg(MSG_SECTOR_TO));
	FlexSizer->Add(LabelSectorTo,0,wxALL|wxALIGN_CENTER_VERTICAL,1);
	m_SectorTextTo = new wxTextCtrl(this,wxID_ANY);
	m_SectorTextTo->SetValue(wxString::Format(_("%4.2f"),SECTOR_TO_DEFAULT_VALUE));
	m_SectorTextTo->SetValidator(SectorValidator);
	FlexSizer->Add(m_SectorTextTo,0,wxALL,1);
		
		
}

CLight::~CLight()
{

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

void CLight::SetColor(wxColor color)
{
	m_ColorPicker->SetColour(color);
}

void CLight::SetCoverage(wxString v)
{
	m_CoverageText->SetValue(v);
}

void CLight::SetSectorFrom(wxString v)
{
	m_SectorTextFrom->SetValue(v);
}

void CLight::SetSectorTo(wxString v)
{
	m_SectorTextTo->SetValue(v);
}


wxColor CLight::GetColor()
{
	return m_ColorPicker->GetColour();
}

wxString CLight::GetCoverage()
{
	return m_CoverageText->GetValue();
}

wxString CLight::GetSectorFrom()
{
	return m_SectorTextFrom->GetValue();
}

wxString CLight::GetSectorTo()
{
	return m_SectorTextTo->GetValue();
}


BEGIN_EVENT_TABLE(CLightDraw, wxPanel)
	//EVT_BUTTON(ID_NEW,OnNew)
	EVT_PAINT(OnPaint)
	EVT_SIZE(OnSize)
END_EVENT_TABLE()

CLightDraw::CLightDraw(CLightPanel *parent)
	:wxPanel(parent)
{
	//SetBackgroundColour(*wxRED);
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
	
	dc.DrawCircle(m_Width/2,m_Height/2,r);
}