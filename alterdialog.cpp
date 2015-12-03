#include <wx/wx.h>
#include <wx/statline.h>
#include "alterdialog.h"
#include "tools.h"
#include "db.h"
#include "options.h"
#include "alter.h"
#include "conf.h"

BEGIN_EVENT_TABLE(CAlterDialog, wxDialog)
	EVT_BUTTON(ID_ALTER,OnAlter)
END_EVENT_TABLE()

CAlterDialog::CAlterDialog()
	:wxDialog(NULL,wxID_ANY,wxEmptyString)
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	Sizer->Add(GetPanel(this),1,wxALL|wxEXPAND,5);
	Sizer->Add(GetButtonPanel(this),0,wxALL|wxEXPAND,5);
	
	SetSizer(Sizer);
	Fit();
	Center();
}

CAlterDialog::~CAlterDialog()
{
	
}

wxPanel *CAlterDialog::GetPanel(wxWindow *parent)
{
	wxPanel *Panel = new wxPanel(parent);
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);

	wxStaticText *LabelText = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_DB_VERSION_MISMATCH));
	Sizer->Add(LabelText,0,wxALL|wxEXPAND,5);

	wxStaticLine *TopLine = new wxStaticLine(Panel,wxID_ANY);
	Sizer->Add(TopLine,0,wxALL|wxEXPAND,5);
	
	wxStaticText *LabelPassword = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_DB_ADMIN_PASSWORD));
	Sizer->Add(LabelPassword,0,wxALL|wxEXPAND,5);

	m_RootPassword = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_PASSWORD);
	Sizer->Add(m_RootPassword,0,wxALL|wxEXPAND,5);

	wxButton *ButtonAlter = new wxButton(Panel,ID_ALTER,GetMsg(MSG_ALTER));
	Sizer->Add(ButtonAlter,0,wxALL,5);
	
	m_Log = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString,wxDefaultPosition,wxSize(-1,150),wxTE_MULTILINE);
	Sizer->Add(m_Log,0,wxALL|wxEXPAND,5);

	wxStaticLine *BottomLine = new wxStaticLine(Panel,wxID_ANY);
	Sizer->Add(BottomLine,0,wxALL|wxEXPAND,5);

	Panel->SetSizer(Sizer);

	return Panel;
}

wxPanel *CAlterDialog::GetButtonPanel(wxWindow *parent)
{
	wxPanel *Panel = new wxPanel(this);
	wxBoxSizer *Sizer = new wxBoxSizer(wxHORIZONTAL);
	Panel->SetSizer(Sizer);	
	
	wxStaticText *LabelProductInfo = new wxStaticText(Panel,wxID_ANY,GetProductInfo() ,wxDefaultPosition,wxDefaultSize);
	Sizer->Add(LabelProductInfo,0,wxALL,5);
	Sizer->AddStretchSpacer(1);
	
	wxButton *ButtonClose = new wxButton(Panel,wxID_CANCEL,GetMsg(MSG_CLOSE));
	Sizer->AddStretchSpacer();
	Sizer->Add(ButtonClose,0,wxALL,5);
	
	return Panel;
}

void CAlterDialog::OnAlter(wxCommandEvent &event)
{
	
	CAlter Alter;
	Alter.SetLogCtrl(m_Log);
	Alter.Alter(m_RootPassword->GetValue(),GetDBName());

}
