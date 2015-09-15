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
	EVT_COMMAND(ID_ALARM,EVT_SET_ALARM,OnSetAlarm)
END_EVENT_TABLE()
CAlarmDialog::CAlarmDialog()
	:wxDialog(NULL,wxID_ANY,GetMsg(MSG_ALARM),wxDefaultPosition,wxSize(500,400),wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER |wxMINIMIZE_BOX|wxMAXIMIZE_BOX| wxSTAY_ON_TOP)
{
	m_Counter = 0;
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
	ConfirmAlarms();
	Hide();
	m_Html = wxEmptyString;
	
}

void CAlarmDialog::OnSetAlarm(wxCommandEvent &event)
{
	m_TextAlarm->SetPage(m_Html);
}

bool CAlarmDialog::Validate()
{
	return true;
}

wxPanel *CAlarmDialog::GetPanel(wxWindow *parent)
{
	wxPanel *Panel = new wxPanel(parent);
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	m_TextAlarm = new wxHtmlWindow(Panel,wxID_ANY);
	Sizer->Add(m_TextAlarm,1,wxALL|wxEXPAND,5);

	Panel->SetSizer(Sizer);
	
	return Panel;

}


void CAlarmDialog::Set(CSymbol *v)
{
	if(v->GetNewAlarmCount() == 0)
		return;
	
	v->SetNewAlarmCount(0);
	
	for(int i = 0 ; i < v->GetAlarmCount();i++)
	{
		CAlarm *ptr = v->GetAlarm(i);
		if(ptr->GetNew() && !ptr->GetConfirmed())
		{
		
			m_Html << wxString::Format(_("<font size=3>%s</font>"),v->GetName());
			m_Html << wxString::Format(_("<br><font color=red>%s</font>"),ptr->GetName());
			m_Html << "<hr>";
			m_Counter++;
		}
		ptr->SetNew(false);
	}
		
	wxCommandEvent evt(EVT_SET_ALARM,ID_ALARM);
	wxPostEvent(this,evt);
	
}

void CAlarmDialog::ShowWindow()
{
	if(m_Counter)
		Show();

	m_Counter = 0;
}

void CAlarmDialog::ClearAlert()
{
	//m_TextAlert->Clear();
}

