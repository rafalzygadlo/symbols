#include <wx/statline.h>
#include "optionsdialog.h"
#include "conf.h"
#include "tools.h"
#include "db.h"

COptionsDialog::COptionsDialog()
	:wxDialog(NULL,wxID_ANY,wxEmptyString)
{
		
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	
	wxPanel *Panel = new wxPanel(this);
	Sizer->Add(Panel,1,wxALL|wxEXPAND,5);
	wxBoxSizer *PanelSizer = new wxBoxSizer(wxVERTICAL);
	Panel->SetSizer(PanelSizer);
	
	wxStaticBoxSizer *Box = new wxStaticBoxSizer(wxVERTICAL,Panel,GetMsg(MSG_OPTIONS));
	PanelSizer->Add(Box,0,wxALL|wxEXPAND,0);

	wxFlexGridSizer *FlexSizer = new wxFlexGridSizer(3);
	Box->Add(FlexSizer,1,wxALL|wxEXPAND,5);
		
	wxStaticText *TextNumberOfTries = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_NUMBER_OF_TRIES),wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(TextNumberOfTries,0,wxALL|wxALIGN_CENTER_VERTICAL,2);

	m_NumberOfTries = new wxSpinCtrl(Panel,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize);
	m_NumberOfTries->SetMin(1);
	m_NumberOfTries->SetMax(100);
	FlexSizer->Add(m_NumberOfTries,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	FlexSizer->AddSpacer(1);

	wxStaticText *TextSecondsBetweenTries = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_NUMBER_OF_TRIES),wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(TextSecondsBetweenTries,0,wxALL|wxALIGN_CENTER_VERTICAL,2);

	m_SecondsBetweenTries = new wxSpinCtrl(Panel,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize);
	m_SecondsBetweenTries->SetMin(1);
	m_SecondsBetweenTries->SetMax(60);
	FlexSizer->Add(m_SecondsBetweenTries,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
		


	wxStaticLine *line = new wxStaticLine(this,wxID_ANY);
	Sizer->Add(line,0,wxALL|wxEXPAND,0);
	
	Sizer->Add(GetButtonPanel(this),0,wxALL|wxEXPAND,10);
	
	SetSizer(Sizer);
	Fit();
	Center();
}

COptionsDialog::~COptionsDialog()
{
	
}

wxPanel *COptionsDialog::GetButtonPanel(wxWindow *parent)
{

	wxPanel *Panel = new wxPanel(this);
	wxBoxSizer *Sizer = new wxBoxSizer(wxHORIZONTAL);
	Panel->SetSizer(Sizer);	
	wxButton *ButtonOk = new wxButton(Panel,wxID_OK,GetMsg(MSG_OK));
	wxButton *ButtonClose = new wxButton(Panel,wxID_CANCEL,GetMsg(MSG_CANCEL));
	Sizer->AddStretchSpacer();
	Sizer->Add(ButtonOk,0,wxALL,2);
	Sizer->Add(ButtonClose,0,wxALL,2);
	
	return Panel;
}