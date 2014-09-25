#include "seaway.h"
#include "seaway_new.h"
#include "conf.h"
#include "tools.h"
#include "listctrl.h"
#include "db.h"

CSeawayDialog::CSeawayDialog()
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
	
	wxButton *ButtonClose = new wxButton(Panel,wxID_CANCEL,GetMsg(MSG_CLOSE));
	PanelSizer->AddStretchSpacer();
	PanelSizer->Add(ButtonClose,0,wxALL,5);
	SetLabel(GetMsg(MSG_SEAWAY));
	Center();
	
}

CSeawayDialog::~CSeawayDialog()
{

}

wxPanel *CSeawayDialog::GetPanel(wxWindow *Parent)
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxHORIZONTAL);
	wxPanel *Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition);
	Panel->SetSizer(Sizer);
	m_List = new CListCtrl(Panel,wxLC_REPORT |  wxLC_VIRTUAL );
	wxListItem item;
	item.SetWidth(150);	item.SetText(GetMsg(MSG_NAME));	m_List->InsertColumn(0,item);
	item.SetWidth(250);	item.SetText(GetMsg(MSG_INFO));	m_List->InsertColumn(1,item);

	m_List->_AddColumn(FID_SEAWAY_NAME,FNAME_SEAWAY_NAME);
	m_List->_AddColumn(FID_SEAWAY_INFO,FNAME_SEAWAY_INFO);
	
	m_List->_AddColumn(FID_SEAWAY_ID,FNAME_SEAWAY_ID);
	m_List->SetColumnWithId(2); // id kolumny z id pól bazy danych
	
	m_List->InitColumns();
	Read();
	
	m_List->SetControlType(CONTROL_SEAWAY,this);

	Sizer->Add(m_List,1,wxALL|wxEXPAND,0);

	return Panel;

}

void CSeawayDialog::Read()
{
	wxString sql;

	if(m_Field == wxEmptyString)		
		sql = wxString::Format(_("SELECT * FROM `%s`"),TABLE_SEAWAY);
	else
		sql = wxString::Format(_("SELECT * FROM %s ORDER BY %s %s"),TABLE_SEAWAY,m_Field,m_Order);

	m_List->Read(sql);
	m_List->Refresh(false);
}

void CSeawayDialog::Clear()
{
	m_List->Clear();
}
	
void CSeawayDialog::Select()
{
	m_List->Select();
}

void CSeawayDialog::OnNew()
{
	
	CSeawayNew *ptr = new CSeawayNew();
	if(ptr->ShowModal() == wxID_OK)
	{
		wxString sql = wxString::Format(_("INSERT INTO %s SET name='%s', info='%s'"),TABLE_SEAWAY,ptr->GetName(),ptr->GetInfo());
		
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

void CSeawayDialog::OnEdit(wxString id)
{
	wxString sql = wxString::Format(_("SELECT * FROM %s WHERE id = '%s'"),TABLE_SEAWAY,id);
	
	if(!my_query(sql))
		return;
		
	CSeawayNew *ptr = new CSeawayNew();
	
	void *result = db_result();
	char **row = (char**)db_fetch_row(result);
	
	ptr->SetName(Convert(row[FID_SEAWAY_NAME]));
	ptr->SetInfo(Convert(row[FID_SEAWAY_INFO]));
	
	db_free_result(result);

	if(ptr->ShowModal() == wxID_OK)
	{
		wxString sql = wxString::Format	(_("UPDATE %s SET name='%s', info ='%s' WHERE id = '%s'"),TABLE_SEAWAY,ptr->GetName(),ptr->GetInfo(),id);
		my_query(sql);
		Clear();
		Read();
		Select();
	}

	delete ptr;
	
}

void CSeawayDialog::OnDelete(wxString id)
{
	wxMessageDialog *MessageDialog = new wxMessageDialog(this,GetMsg(MSG_DELETE_SEAWAY),wxString::Format(wxT("%s %s"),wxT(PRODUCT_NAME),wxT(PRODUCT_VERSION)),wxYES_NO|wxICON_QUESTION);
    if(MessageDialog->ShowModal() == wxID_YES)
	{
		wxString sql = wxString::Format(_("DELETE FROM %s WHERE id = '%s'"),TABLE_SEAWAY,id);
		my_query(sql);
		Clear();
		Read();
		Select();
	}

	delete MessageDialog;
}


void CSeawayDialog::OnColumnCLick(wxString field, int order)
{
	if(order == ORDER_ASC)
		m_Order = _("ASC");
	else
		m_Order = _("DESC");
	
	m_Field = field;
	Clear();
	Read();
}