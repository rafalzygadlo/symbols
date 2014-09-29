#include "communication.h"
#include "communication_new.h"
#include "conf.h"
#include "tools.h"
#include "listctrl.h"
#include "db.h"
#include <wx/mstream.h>


extern unsigned int	add_size;
extern unsigned char add[];

CCommunicationDialog::CCommunicationDialog(int type)
:wxDialog(NULL,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
	SetSize(DEFAULT_DIALOG_WIDTH,DEFAULT_DIALOG_HEIGHT);
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(Sizer);
	Sizer->Add(GetPanel(this),1,wxALL|wxEXPAND,0);

	wxPanel *Panel = new wxPanel(this);
	Sizer->Add(Panel,0,wxALL|wxEXPAND,5);
	wxBoxSizer *PanelSizer = new wxBoxSizer(wxHORIZONTAL);
	Panel->SetSizer(PanelSizer);
	
	if(type == 1)
	{
		PanelSizer->AddStretchSpacer();
		ButtonOk = new wxButton(Panel,wxID_OK,GetMsg(MSG_OK));
		ButtonOk->Disable();
		PanelSizer->Add(ButtonOk,0,wxALL,5);
		wxButton *ButtonClose = new wxButton(Panel,wxID_CANCEL,GetMsg(MSG_CANCEL));
		PanelSizer->Add(ButtonClose,0,wxALL,5);
		SetLabel(GetMsg(MSG_BATTERY));
	
	}else{
		wxButton *ButtonClose = new wxButton(Panel,wxID_CANCEL,GetMsg(MSG_CLOSE));
		PanelSizer->AddStretchSpacer();
		PanelSizer->Add(ButtonClose,0,wxALL,2);
		SetLabel(GetMsg(MSG_COMMUNICATION_TYPE));
	
	}
	
	Center();
}

CCommunicationDialog::~CCommunicationDialog()
{

}

wxPanel *CCommunicationDialog::GetPanel(wxWindow *Parent)
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxHORIZONTAL);
	wxPanel *Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition);
	Panel->SetSizer(Sizer);
	m_List = new CListCtrl(Panel,wxLC_REPORT |  wxLC_VIRTUAL );
	wxListItem item;
	item.SetWidth(150);	item.SetText(GetMsg(MSG_NAME));	m_List->InsertColumn(0,item);
	item.SetWidth(250);	item.SetText(GetMsg(MSG_INFO));	m_List->InsertColumn(1,item);

	m_List->_AddColumn(FID_COMMUNICATION_NAME,FNAME_COMMUNICATION_NAME);
	m_List->_AddColumn(FID_COMMUNICATION_INFO,FNAME_COMMUNICATION_INFO);
	
	m_List->_AddColumn(FID_AREA_ID,FNAME_AREA_ID);
	m_List->SetColumnWithId(2); // id kolumny z id pól bazy danych
	
	m_List->InitColumns();
	Read();
	
	m_List->SetControlType(CONTROL_COMMUNICATION,this);

	Sizer->Add(m_List,1,wxALL|wxEXPAND,0);

	return Panel;

}

void CCommunicationDialog::Read()
{
	wxString sql;

	if(m_Field == wxEmptyString)		
		sql = wxString::Format(_("SELECT * FROM `%s`"),TABLE_COMMUNICATION);
	else
		sql = wxString::Format(_("SELECT * FROM %s ORDER BY %s %s"),TABLE_COMMUNICATION,m_Field,m_Order);

	m_List->Read(sql);
	m_List->Refresh(false);
}

void CCommunicationDialog::Clear()
{
	m_List->Clear();
}
	
void CCommunicationDialog::Select()
{
	m_List->Select();
}

void CCommunicationDialog::OnNew()
{
	
	CCommunicationNew *ptr = new CCommunicationNew();
	if(ptr->ShowModal() == wxID_OK)
	{
		wxString sql = wxString::Format(_("INSERT INTO %s SET name='%s', info='%s'"),TABLE_COMMUNICATION,ptr->GetName(),ptr->GetInfo());
		
		if(!my_query(sql))
		{
			delete ptr;
			return;
		}
			
		Clear();
		Read();
		
	}
	
	delete ptr;
	
}

void CCommunicationDialog::OnEdit(wxString id)
{
	wxString sql = wxString::Format(_("SELECT * FROM %s WHERE id = '%s'"),TABLE_COMMUNICATION,id);
	
	if(!my_query(sql))
		return;
		
	CCommunicationNew *ptr = new CCommunicationNew();
	
	void *result = db_result();
	char **row = (char**)db_fetch_row(result);
	
	ptr->SetName(Convert(row[FID_COMMUNICATION_NAME]));
	ptr->SetInfo(Convert(row[FID_COMMUNICATION_INFO]));
	
	db_free_result(result);

	if(ptr->ShowModal() == wxID_OK)
	{
		wxString sql = wxString::Format	(_("UPDATE %s SET name='%s', info ='%s' WHERE id = '%s'"),TABLE_COMMUNICATION,ptr->GetName(),ptr->GetInfo(),id);
		my_query(sql);
		Clear();
		Read();
		Select();
	}

	delete ptr;
	
}

void CCommunicationDialog::OnDelete(wxString id)
{
	wxMessageDialog *MessageDialog = new wxMessageDialog(this,GetMsg(MSG_DELETE_QUESTION),wxString::Format(wxT("%s %s"),wxT(PRODUCT_NAME),wxT(PRODUCT_VERSION)),wxYES_NO|wxICON_QUESTION);
    if(MessageDialog->ShowModal() == wxID_YES)
	{
		wxString sql = wxString::Format(_("DELETE FROM %s WHERE id = '%s'"),TABLE_COMMUNICATION,id);
		my_query(sql);
		Clear();
		Read();
		Select();
	}

	delete MessageDialog;
}


void CCommunicationDialog::OnColumnCLick(wxString field, int order)
{
	if(order == ORDER_ASC)
		m_Order = _("ASC");
	else
		m_Order = _("DESC");
	
	m_Field = field;
	Clear();
	Read();
}

void CCommunicationDialog::OnSelect(wxString id, wxArrayString row)
{
	if(ButtonOk)
		ButtonOk->Enable();
	m_Id = row[COMMUNICATION_COLUMN_WITH_ID];
	m_Name = row[COMMUNICATION_COLUMN_WITH_NAME];
}


wxString CCommunicationDialog::GetCommunicationId()
{
	return m_Id;
}

wxString CCommunicationDialog::GetCommunicationName()
{
	return m_Name;
}

