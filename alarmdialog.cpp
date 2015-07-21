#include <wx/notebook.h>
#include <wx/filepicker.h>
#include "alarmdialog.h"
#include "conf.h"
#include "tools.h"
#include "options.h"

BEGIN_EVENT_TABLE(CAlarmDialog, wxDialog)
	//EVT_BUTTON(ID_EDIT,OnEdit)
	//EVT_LISTBOX(ID_LIST,OnListBox)
END_EVENT_TABLE()
CAlarmDialog::CAlarmDialog(void *db, wxString station)
	:wxDialog(NULL,wxID_ANY,_(PRODUCT_NAME),wxDefaultPosition,wxDefaultSize)
{
	m_DB = db;
	m_StationName = station;
	m_Validate = false;
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	
	//Sizer->Add(GetTitlePanel(this,station),0,wxALL|wxEXPAND,0);
	Sizer->Add(GetPanel(this),1,wxALL|wxEXPAND,0);
	
	wxBoxSizer *ButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	Sizer->Add(ButtonSizer,0,wxALL|wxEXPAND,5);
	wxStaticText *LabelProductInfo = new wxStaticText(this,wxID_ANY,GetProductInfo() ,wxDefaultPosition,wxDefaultSize);
	ButtonSizer->Add(LabelProductInfo,0,wxALL,5);
	ButtonSizer->AddStretchSpacer(1);
		
	wxButton *ButtonOk = new wxButton(this,wxID_OK,GetMsg(MSG_OK),wxDefaultPosition,wxDefaultSize);
	ButtonSizer->Add(ButtonOk,0,wxALL|wxALIGN_RIGHT,5);

	//wxButton *ButtonCancel = new wxButton(this,wxID_CANCEL,GetMsg(MSG_CANCEL),wxDefaultPosition,wxDefaultSize);
	//ButtonSizer->Add(ButtonCancel,0,wxALL|wxALIGN_RIGHT,5);

	SetSizer(Sizer);
	
	
}

CAlarmDialog::~CAlarmDialog()
{
	
}

bool CAlarmDialog::Validate()
{
	return true;
	m_Validate = true;

	for(size_t i = 0; i < m_Panels.size(); i++)
	{
		CAlarmPanel *ptr =  (CAlarmPanel*)m_Panels.Item(i);
		ptr->Confirm();
	}
	
	m_Panels.Clear();
	m_Validate = false;
	return true;
}

wxPanel *CAlarmDialog::GetPanel(wxWindow *parent)
{
	wxPanel *Panel = new wxPanel(parent);
	//Panel->SetBackgroundColour(*wxWHITE);
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	Panel->SetSizer(Sizer);
	wxBoxSizer *ScrollSizer = new wxBoxSizer(wxVERTICAL);
	m_Scroll = new wxScrolledWindow(Panel, wxID_ANY, wxDefaultPosition, wxSize(-1,200));
	Sizer->Add(m_Scroll,1,wxALL|wxEXPAND,5);
	m_Scroll->SetFocusIgnoringChildren();
	m_Scroll->SetSizer(ScrollSizer);
	m_Scroll->SetScrollbars(20, 20, 20, 20);

	return Panel;

}

bool CAlarmDialog::IsValidating()
{
	return m_Validate;
}

/*
void CAlarmDialog::Set(CData *v)
{
	m_Scroll->DestroyChildren();
	for(int i = 0; i < v->GetLength(); i++)
	{
		CAlertPanel *p = new CAlertPanel(m_DB,m_Scroll,(SAlert*)v->GetValue(i));
		m_Panels.Add(p);
		m_Scroll->GetSizer()->Add(p,0,wxALL|wxEXPAND,2);
		m_Scroll->Layout();
		m_Scroll->FitInside();
	}
		
	v->SetNewAlert(false);
	m_Scroll->SetFocusIgnoringChildren();
	Layout();
	Center();
	Show();
	
}
*/
void CAlarmDialog::ClearAlert()
{
	m_TextAlert->Clear();
}


BEGIN_EVENT_TABLE(CAlarmPanel, wxPanel)
	EVT_BUTTON(ID_CONFIRM,OnConfirm)
	//EVT_BUTTON(ID_EDIT,OnEdit)
	//EVT_LISTBOX(ID_LIST,OnListBox)
END_EVENT_TABLE()

CAlarmPanel::CAlarmPanel(void *db,wxWindow *parent, SAlert *v)
	:wxPanel(parent)
{
	m_DB = db;
	m_Alert = v;
			
	if(v->error > 0)
		SetForegroundColour(*wxRED);
	
	SetBackgroundColour(*wxWHITE);
	wxBoxSizer *Sizer = new wxBoxSizer(wxHORIZONTAL);
	SetSizer(Sizer);
	
	time_t t = v->gpstimestamp;
	wxDateTime time(t);
	time = time.ToUTC();
	wxFont font;
	font.SetPointSize(12);
	
	wxStaticText *TextLabel = new wxStaticText(this,wxID_ANY,wxEmptyString, wxDefaultPosition, wxDefaultSize);
	//TextLabel->SetFont(font);
//	TextLabel->SetLabel(wxString::Format(_("%s %s\n%s"),time.FormatISODate().wc_str(),time.FormatISOTime().wc_str(),GetStatusText(v->error)));
	Sizer->Add(TextLabel,1,wxALL|wxEXPAND,2);
	
	wxButton *Button = new wxButton(this,ID_CONFIRM ,GetMsg(MSG_CONFIRM));
	Sizer->Add(Button,0,wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL,2);

}

void CAlarmPanel::OnConfirm(wxCommandEvent &event)
{
	Confirm();
}

void CAlarmPanel::Confirm()
{
	//GetMutex()->Lock();
	//wxString sql = wxString::Format(_("UPDATE `%s` SET confirmed='%d',id_user='%d',confirmdate=utc_timestamp() WHERE gpstimestamp='%d'"),TABLE_ALERT,ALERT_CONFIRMED,_GetUID(),m_Alert->gpstimestamp);
	//my_query(m_DB,sql);
	//GetMutex()->Unlock();
}