#include "conf.h"
#include "tools.h"
#include "datedialog.h"

CDateDialog::CDateDialog()
:wxDialog( NULL,wxID_ANY,_(PRODUCT_NAME), wxDefaultPosition,wxDefaultSize, wxDEFAULT_DIALOG_STYLE)
{

	wxBoxSizer *MainSizer = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer *CenterSizer = new wxBoxSizer(wxVERTICAL);
	MainSizer->Add(CenterSizer,1,wxALL|wxEXPAND,0);

    wxPanel *Panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	CenterSizer->Add(Panel,1,wxALL|wxEXPAND,0);
	Panel->SetBackgroundColour(*wxWHITE);
	wxBoxSizer *PanelSizer = new wxBoxSizer(wxVERTICAL);
	Panel->SetSizer(PanelSizer);

	wxFlexGridSizer *FlexSizer = new wxFlexGridSizer(2);
	PanelSizer->Add(FlexSizer,0,wxALL,5);

	wxStaticText *LabelFromTime = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_FROM));
	FlexSizer->Add(LabelFromTime,0,wxALL,10);
	m_From = new wxDatePickerCtrl(Panel,wxID_ANY);
	FlexSizer->Add(m_From,0,wxALL,10);

	wxStaticText *LabelToTime = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_TO));
	FlexSizer->Add(LabelToTime,0,wxALL,10);
	m_To = new wxDatePickerCtrl(Panel,wxID_ANY);
	FlexSizer->Add(m_To,0,wxALL,10);

	wxBoxSizer *PanelButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	wxPanel *PanelButton = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	PanelButton->SetSizer(PanelButtonSizer);

	//wxStaticText *LabelProductInfo = new wxStaticText(PanelButton,wxID_ANY,GetProductInfo() ,wxDefaultPosition,wxDefaultSize);
	//PanelButtonSizer->Add(LabelProductInfo,0,wxALL,5);

	PanelButtonSizer->AddStretchSpacer(1);
	
	wxButton *ButtonOk = new wxButton(PanelButton,wxID_OK,GetMsg(MSG_OK),wxDefaultPosition,wxDefaultSize);
	PanelButtonSizer->Add(ButtonOk,0,wxALL|wxALIGN_RIGHT,5);
		
	wxButton *ButtonCancel = new wxButton(PanelButton,wxID_CANCEL,GetMsg(MSG_CANCEL),wxDefaultPosition,wxDefaultSize);
	PanelButtonSizer->Add(ButtonCancel,0,wxALL|wxALIGN_RIGHT,5);
	
	MainSizer->Add(PanelButton,0,wxALL|wxEXPAND,5);
		
	this->SetSizer(MainSizer);
	GetSizer()->SetSizeHints(this);
	
	Center();
	
}

wxDateTime CDateDialog::GetFrom()
{
	return m_From->GetValue();
}

wxDateTime CDateDialog::GetTo()
{
	return m_To->GetValue();
}