#include "sectordialog.h"
#include "conf.h"
#include "tools.h"
#include "geometrytools.h"
#include <wx/valnum.h>


CSectorDialog::CSectorDialog()
	:wxDialog(NULL,wxID_ANY,wxEmptyString)
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

	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	SetSizer(Sizer);
		
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
	
	Sizer->Add(GetButtonPanel(this));
		
}

CSectorDialog::~CSectorDialog()
{

}

wxPanel *CSectorDialog::GetButtonPanel(wxWindow *parent)
{

	wxPanel *Panel = new wxPanel(this);
		
	wxBoxSizer *PanelSizer = new wxBoxSizer(wxHORIZONTAL);
	Panel->SetSizer(PanelSizer);	
	
	
	if(m_Picker)
	{
		PanelSizer->AddStretchSpacer();
		m_ButtonOk = new wxButton(Panel,wxID_OK,GetMsg(MSG_OK));
		PanelSizer->Add(m_ButtonOk,0,wxALL,5);
		wxButton *ButtonClose = new wxButton(Panel,wxID_CANCEL,GetMsg(MSG_CANCEL));
		PanelSizer->Add(ButtonClose,0,wxALL,5);
	}else{
	
		wxButton *ButtonClose = new wxButton(Panel,wxID_CANCEL,GetMsg(MSG_CLOSE));
		PanelSizer->AddStretchSpacer();
		PanelSizer->Add(ButtonClose,0,wxALL,2);
	
	}
	

	return Panel;
}

wxString CSectorDialog::_GetId()
{
	return m_Id;
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


wxColor CSectorDialog::GetColor()
{
	return m_ColorPicker->GetColour();
}

wxString CSectorDialog::GetCoverage()
{
	return m_CoverageText->GetValue();
}

wxString CSectorDialog::GetSectorFrom()
{
	return m_SectorTextFrom->GetValue();
}

wxString CSectorDialog::GetSectorTo()
{
	return m_SectorTextTo->GetValue();
}
