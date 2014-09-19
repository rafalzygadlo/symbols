#include "area.h"
#include "conf.h"
#include "tools.h"
#include "listctrl.h"
//#include "group_new.h"
//#include "group_right.h"
#include "db.h"

BEGIN_EVENT_TABLE(CArea, wxDialog)
//	EVT_RADIOBUTTON(ID_RADIO_COMPANY,CUser::OnCompanyRadio)
//	EVT_RADIOBUTTON(ID_RADIO_USER,CUser::OnUserRadio)
//	EVT_BUTTON(ID_REGISTER,CUser::OnRegister)
END_EVENT_TABLE()

CArea::CArea()
:wxDialog(NULL,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{

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
	SetLabel(GetMsg(MSG_AREA));
	Center();
	
}

CArea::~CArea()
{

}

wxPanel *CArea::GetPanel(wxWindow *Parent)
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxHORIZONTAL);
	wxPanel *Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition);
	Panel->SetSizer(Sizer);
	m_List = new CListCtrl(Panel,wxLC_REPORT |  wxLC_VIRTUAL );
	wxListItem item;
	item.SetWidth(150);	item.SetText(GetMsg(MSG_NAME));	m_List->InsertColumn(0,item);
			
	m_List->_AddColumn(FID_OBJECT_AREA_NAME,FNAME_OBJECT_AREA_NAME);
	m_List->_AddColumn(FID_GROUP_INFO,FNAME_GROUP_INFO);
	
	m_List->_AddColumn(FID_GROUP_ID,FNAME_GROUP_NAME);
	m_List->SetColumnWithId(2); // id kolumny z id pól bazy danych
	
	m_List->InitColumns();
	Read();
	
	m_List->SetControlType(CONTROL_AREA,this);

	Sizer->Add(m_List,1,wxALL|wxEXPAND,5);

	return Panel;

}

void CArea::Read()
{
	wxString sql;

	if(m_Field == wxEmptyString)		
		sql = wxString::Format(_("SELECT * FROM %s"),TABLE_GROUP);
	else
		sql = wxString::Format(_("SELECT * FROM %s ORDER BY %s %s"),TABLE_GROUP,m_Field,m_Order);

	m_List->Read(sql);
	m_List->Refresh(false);
}

void CArea::Clear()
{
	m_List->Clear();
}
	
void CArea::Select()
{
	m_List->Select();
}

void CArea::OnNew()
{
	/*
	CGroupNew *GroupNew = new CGroupNew();
	if(GroupNew->ShowModal() == wxID_OK)
	{
		wxDateTime time = wxDateTime::Now();
		wxString sql = wxString::Format(_("INSERT INTO %s SET name='%s', info='%s'"),TABLE_GROUP,GroupNew->GetName(),GroupNew->GetInfo());
		
		if(!my_query(sql))
		{
			delete GroupNew;
			return;
		}
			
		Clear();
		Read();
		
	}
	
	delete GroupNew;
	*/
}

void CArea::OnEdit(wxString id)
{
	wxString sql = wxString::Format(_("SELECT * FROM %s WHERE id = '%s'"),TABLE_GROUP,id);
	
	if(!my_query(sql))
		return;
	/*	
	CGroupNew *GroupNew = new CGroupNew();
	
	void *result = db_result();
	char **row = (char**)db_fetch_row(result);
	
	GroupNew->SetName(Convert(row[FID_GROUP_NAME]));
	GroupNew->SetInfo(Convert(row[FID_GROUP_INFO]));
	
	db_free_result(result);

	if(GroupNew->ShowModal() == wxID_OK)
	{

		wxDateTime time = wxDateTime::Now();
		wxString sql = wxString::Format	(_("UPDATE %s SET name='%s', info ='%s' WHERE id = '%s'"),TABLE_GROUP,GroupNew->GetName(),GroupNew->GetInfo(),id);
		my_query(sql);
		Clear();
		Read();
		Select();
	}

	delete GroupNew;
	*/

}

void CArea::OnDelete(wxString id)
{
	wxMessageDialog *MessageDialog = new wxMessageDialog(this,GetMsg(MSG_DELETE_AREA),wxString::Format(wxT("%s %s"),wxT(PRODUCT_NAME),wxT(PRODUCT_VERSION)),wxYES_NO|wxICON_QUESTION);
    if(MessageDialog->ShowModal() == wxID_YES)
	{
		wxString sql = wxString::Format(_("DELETE FROM %s WHERE id = '%s'"),TABLE_GROUP,id);
		my_query(sql);
		
		sql = wxString::Format(_("DELETE FROM %s WHERE id_group = '%s'"),TABLE_GROUP_RIGHT,id);
		my_query(sql);
		
		Clear();
		Read();
		Select();
	}

	delete MessageDialog;
}


void CArea::OnColumnCLick(wxString field, int order)
{
	if(order == ORDER_ASC)
		m_Order = _("ASC");
	else
		m_Order = _("DESC");
	
	m_Field = field;
	Clear();
	Read();
}