#include "light.h"
#include "conf.h"
#include "tools.h"
#include "listctrl.h"
#include "light_new.h"
#include "db.h"

CLightDialog::CLightDialog()
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
	SetLabel(GetMsg(MSG_LIGHT));
	Center();
	
}

CLightDialog::~CLightDialog()
{

}

wxPanel *CLightDialog::GetPanel(wxWindow *Parent)
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxHORIZONTAL);
	wxPanel *Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition);
	Panel->SetSizer(Sizer);
	m_List = new CListCtrl(Panel,wxLC_REPORT |  wxLC_VIRTUAL );
	wxListItem item;
	item.SetWidth(150);	item.SetText(GetMsg(MSG_NAME));	m_List->InsertColumn(0,item);
	item.SetWidth(250);	item.SetText(GetMsg(MSG_INFO));	m_List->InsertColumn(1,item);

	m_List->_AddColumn(FID_LIGHT_NAME,FNAME_LIGHT_NAME);
	m_List->_AddColumn(FID_LIGHT_INFO,FNAME_LIGHT_INFO);
	
	m_List->_AddColumn(FID_LIGHT_ID,FNAME_LIGHT_ID);
	m_List->SetColumnWithId(2); // id kolumny z id pól bazy danych
	
	m_List->InitColumns();
	Read();
	
	m_List->SetControlType(CONTROL_LIGHT,this);

	Sizer->Add(m_List,1,wxALL|wxEXPAND,0);

	return Panel;

}

void CLightDialog::Read()
{
	wxString sql;

	if(m_Field == wxEmptyString)		
		sql = wxString::Format(_("SELECT * FROM `%s`"),TABLE_LIGHT);
	else
		sql = wxString::Format(_("SELECT * FROM %s ORDER BY %s %s"),TABLE_LIGHT,m_Field,m_Order);

	m_List->Read(sql);
	m_List->Refresh(false);
}

void CLightDialog::Clear()
{
	m_List->Clear();
}
	
void CLightDialog::Select()
{
	m_List->Select();
}

void CLightDialog::OnNew()
{
	
	CLightNew *ptr = new CLightNew();
	if(ptr->ShowModal() == wxID_OK)
	{
		wxString sql = wxString::Format(_("INSERT INTO %s SET name='%s', info='%s'"),TABLE_LIGHT,ptr->GetName(),ptr->GetInfo());
		
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

void CLightDialog::OnEdit(wxString id)
{
	wxString sql = wxString::Format(_("SELECT * FROM %s WHERE id = '%s'"),TABLE_LIGHT,id);
	
	if(!my_query(sql))
		return;
		
	CLightNew *ptr = new CLightNew();
	
	void *result = db_result();
	char **row = (char**)db_fetch_row(result);
	
	ptr->SetName(Convert(row[FID_AREA_NAME]));
	ptr->SetInfo(Convert(row[FID_AREA_INFO]));
	
	db_free_result(result);

	if(ptr->ShowModal() == wxID_OK)
	{
		wxString sql = wxString::Format	(_("UPDATE %s SET name='%s', info ='%s' WHERE id = '%s'"),TABLE_LIGHT,ptr->GetName(),ptr->GetInfo(),id);
		my_query(sql);
		Clear();
		Read();
		Select();
	}

	delete ptr;
	
}

void CLightDialog::OnDelete(wxString id)
{
	wxMessageDialog *MessageDialog = new wxMessageDialog(this,GetMsg(MSG_DELETE_LIGHT),wxString::Format(wxT("%s %s"),wxT(PRODUCT_NAME),wxT(PRODUCT_VERSION)),wxYES_NO|wxICON_QUESTION);
    if(MessageDialog->ShowModal() == wxID_YES)
	{
		wxString sql = wxString::Format(_("DELETE FROM %s WHERE id = '%s'"),TABLE_LIGHT,id);
		my_query(sql);
		Clear();
		Read();
		Select();
	}

	delete MessageDialog;
}


void CLightDialog::OnColumnCLick(wxString field, int order)
{
	if(order == ORDER_ASC)
		m_Order = _("ASC");
	else
		m_Order = _("DESC");
	
	m_Field = field;
	Clear();
	Read();
}