#include <wx/notebook.h>
#include <wx/filepicker.h>
#include "alarmdialog.h"
#include "conf.h"
#include "tools.h"
#include "options.h"

DEFINE_EVENT_TYPE(EVT_SET_ALARM)

BEGIN_EVENT_TABLE(CAlarmDialog, wxDialog)
	EVT_BUTTON(ID_OK,OnOk)
	//EVT_LISTBOX(ID_LIST,OnListBox)
END_EVENT_TABLE()
CAlarmDialog::CAlarmDialog()
	:wxDialog(NULL,wxID_ANY,GetMsg(MSG_ALARM),wxDefaultPosition,wxSize(500,400),wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER |wxMINIMIZE_BOX|wxMAXIMIZE_BOX| wxSTAY_ON_TOP)
{
	m_Count = 0;
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	
	//Sizer->Add(GetTitlePanel(this,station),0,wxALL|wxEXPAND,0);
	Sizer->Add(GetPanel(this),1,wxALL|wxEXPAND,0);
	
	wxBoxSizer *ButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	Sizer->Add(ButtonSizer,0,wxALL|wxEXPAND,5);
	wxStaticText *LabelProductInfo = new wxStaticText(this,wxID_ANY,GetProductInfo() ,wxDefaultPosition,wxDefaultSize);
	ButtonSizer->Add(LabelProductInfo,0,wxALL,5);
	ButtonSizer->AddStretchSpacer(1);
		
	wxButton *ButtonOk = new wxButton(this,ID_OK,GetMsg(MSG_OK),wxDefaultPosition,wxDefaultSize);
	ButtonSizer->Add(ButtonOk,0,wxALL|wxALIGN_RIGHT,5);

	//wxButton *ButtonCancel = new wxButton(this,wxID_CANCEL,GetMsg(MSG_CANCEL),wxDefaultPosition,wxDefaultSize);
	//ButtonSizer->Add(ButtonCancel,0,wxALL|wxALIGN_RIGHT,5);

	SetSizer(Sizer);
	Center();
	
}

CAlarmDialog::~CAlarmDialog()
{
	
}

void CAlarmDialog::OnOk(wxCommandEvent &event)
{
	wxMessageDialog *MessageDialog = new wxMessageDialog(this,GetMsg(MSG_CONFIRM_QUESTION),wxString::Format(wxT("%s %s"),wxT(PRODUCT_NAME),wxT(PRODUCT_VERSION)),wxYES_NO|wxICON_QUESTION);
    if(MessageDialog->ShowModal() == wxID_YES)
	{
		ConfirmAlarms();
		Hide();
	}

	delete MessageDialog;
}

wxPanel *CAlarmDialog::GetPanel(wxWindow *parent)
{
	wxPanel *Panel = new wxPanel(parent);
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	m_TextAlarm = new CAlarmList(Panel);
	Sizer->Add(m_TextAlarm,1,wxALL|wxEXPAND,5);

	Panel->SetSizer(Sizer);
	
	return Panel;
}

void CAlarmDialog::Set(wxArrayPtrVoid *v)
{
	m_TextAlarm->SetList(v);
}

void CAlarmDialog::ShowWindow()
{
	PlaySound();
	Show();
}

//void CAlarmDialog::SetNew(bool v)
//{
	//m_New = v;
//}

void CAlarmDialog::PlaySound()
{
	//wxSound snd(
}
