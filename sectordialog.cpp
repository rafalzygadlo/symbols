#include "sectordialog.h"
#include "conf.h"
#include "tools.h"
#include "geometrytools.h"
#include <wx/valnum.h>


BEGIN_EVENT_TABLE(CSectorDialog,wxDialog)
	EVT_SPINCTRLDOUBLE(ID_SECTOR_FROM,OnSectorFrom)
	EVT_SPINCTRLDOUBLE(ID_SECTOR_TO,OnSectorTo)
	EVT_COLOURPICKER_CHANGED(ID_SECTOR_COLOR,OnColor)
END_EVENT_TABLE()

CSectorDialog::CSectorDialog(void *db,wxWindow *parent)
	:wxDialog(parent,wxID_ANY,wxEmptyString)
{	
	m_Parent = parent;
	m_Sector = NULL;
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	SetSizer(Sizer);

	wxFlexGridSizer *FlexSizer = new wxFlexGridSizer(2);
	Sizer->Add(FlexSizer,1,wxALL|wxEXPAND,0);

	wxStaticText *LabelColor = new wxStaticText(this,wxID_ANY,GetMsg(MSG_COLOR));
	FlexSizer->Add(LabelColor,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_ColorPicker = new wxColourPickerCtrl(this,ID_SECTOR_COLOR);
	m_ColorPicker->SetColour(SECTOR_DEFAULT_COLOR);
	FlexSizer->Add(m_ColorPicker,0,wxALL,5);

	wxStaticText *LabelCharacteristic = new wxStaticText(this,wxID_ANY,GetMsg(MSG_CHARACTERISTIC));
	FlexSizer->Add(LabelCharacteristic,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_Characteristic = GetCombo(db,this,TABLE_CHARACTERISTIC,m_IdCharacteristic,FI_CHARACTERISTIC_ID,FI_CHARACTERISTIC_NAME,false,false);
	m_Characteristic->SetSize(200,-1);
	//m_ColorPicker->SetColour(SECTOR_DEFAULT_COLOR);
	FlexSizer->Add(m_Characteristic,0,wxALL,5);
		
	wxStaticText *LabelCoverage = new wxStaticText(this,wxID_ANY,GetMsg(MSG_COVERAGE));
	FlexSizer->Add(LabelCoverage,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_CoverageText = new wxSpinCtrlDouble(this,wxID_ANY);
	m_CoverageText->SetMinSize(wxSize(220,-1));
	m_CoverageText->SetValue(wxString::Format(_("%4.2f"),COVERAGE_DEFAULT_VALUE));
	FlexSizer->Add(m_CoverageText,0,wxALL,5);

	wxStaticText *LabelSectorFrom = new wxStaticText(this,wxID_ANY,GetMsg(MSG_SECTOR_FROM));
	FlexSizer->Add(LabelSectorFrom,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_SectorTextFrom = new wxSpinCtrlDouble(this,ID_SECTOR_FROM);
	m_SectorTextFrom->SetRange(SECTOR_MIN,SECTOR_MAX);
	m_SectorTextFrom->SetValue(wxString::Format(_("%4.2f"),SECTOR_FROM_DEFAULT_VALUE));
	FlexSizer->Add(m_SectorTextFrom,0,wxALL,5);

	wxStaticText *LabelSectorTo = new wxStaticText(this,wxID_ANY,GetMsg(MSG_SECTOR_TO));
	FlexSizer->Add(LabelSectorTo,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_SectorTextTo = new wxSpinCtrlDouble(this,ID_SECTOR_TO);
	m_SectorTextTo->SetRange(SECTOR_MIN,SECTOR_MAX);
	m_SectorTextTo->SetValue(wxString::Format(_("%4.2f"),SECTOR_TO_DEFAULT_VALUE));
	FlexSizer->Add(m_SectorTextTo,0,wxALL,5);

	Sizer->Add(GetButtonPanel(this),0,wxALL|wxEXPAND,5);
	Fit();
	Center();	
}


CSectorDialog::~CSectorDialog()
{

}

wxPanel *CSectorDialog::GetButtonPanel(wxWindow *parent)
{
	wxPanel *Panel = new wxPanel(this);
	wxBoxSizer *Sizer = new wxBoxSizer(wxHORIZONTAL);
	Panel->SetSizer(Sizer);	
	
	wxStaticText *LabelProductInfo = new wxStaticText(Panel,wxID_ANY,GetProductInfo() ,wxDefaultPosition,wxDefaultSize);
	Sizer->Add(LabelProductInfo,0,wxALL,5);
	Sizer->AddStretchSpacer(1);
		
	wxButton *ButtonOk = new wxButton(Panel,wxID_OK,GetMsg(MSG_OK));
	Sizer->Add(ButtonOk,0,wxALL,5);
	wxButton *ButtonClose = new wxButton(Panel,wxID_CANCEL,GetMsg(MSG_CANCEL));
	Sizer->Add(ButtonClose,0,wxALL,5);
	
	return Panel;
}

void CSectorDialog::OnSectorFrom(wxSpinDoubleEvent &event)
{
	m_Sector->SetSectorFrom(event.GetValue());
	m_Parent->Refresh();
}

void CSectorDialog::OnSectorTo(wxSpinDoubleEvent &event)
{
	m_Sector->SetSectorTo(event.GetValue());
	m_Parent->Refresh();
}

void CSectorDialog::OnColor(wxColourPickerEvent &event)
{
	m_Sector->SetColor(event.GetColour());
	m_Parent->Refresh();
}

void CSectorDialog::_SetId(wxString v)
{
	m_Id = v;
}

void CSectorDialog::SetColor(wxColor color)
{
	m_ColorPicker->SetColour(color);
}

void CSectorDialog::SetCoverage(wxString v)
{
	m_CoverageText->SetValue(v);
}

void CSectorDialog::SetSectorFrom(wxString v)
{
	m_SectorTextFrom->SetValue(v);
}

void CSectorDialog::SetSectorTo(wxString v)
{
	m_SectorTextTo->SetValue(v);
}

void CSectorDialog::SetSector(CSector *v)
{
	m_Sector = v;

}

void CSectorDialog::SetIdCharacteristic(wxString v)
{
	long _v;
	v.ToLong(&_v);
	ComboSetSelection(m_Characteristic,_v);
	m_IdCharacteristic = v;
}

//GET
wxString CSectorDialog::_GetId()
{
	return m_Id;
}

wxColor CSectorDialog::GetColor()
{
	return m_ColorPicker->GetColour();
}

double CSectorDialog::GetCoverage()
{
	return m_CoverageText->GetValue();
}

double CSectorDialog::GetSectorFrom()
{
	return m_SectorTextFrom->GetValue();
}

double CSectorDialog::GetSectorTo()
{
	return m_SectorTextTo->GetValue();
}

int CSectorDialog::GetIdCharacteristic()
{
	int id = m_Characteristic->GetSelection();
	if(id < 0)
		return 0;
	
	return (int)m_Characteristic->GetClientData(m_Characteristic->GetSelection());
	
}