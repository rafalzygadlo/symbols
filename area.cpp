#include "area.h"
#include "conf.h"
#include "tools.h"
#include "listctrl.h"
#include "area_new.h"
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
	SetLabel(GetMsg(MSG_OBJECT_AREA));
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
	item.SetWidth(250);	item.SetText(GetMsg(MSG_INFO));	m_List->InsertColumn(1,item);

	m_List->_AddColumn(FID_OBJECT_AREA_NAME,FNAME_OBJECT_AREA_NAME);
	m_List->_AddColumn(FID_OBJECT_AREA_INFO,FNAME_OBJECT_AREA_INFO);
	
	m_List->_AddColumn(FID_OBJECT_AREA_ID,FNAME_OBJECT_AREA_ID);
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
		sql = wxString::Format(_("SELECT * FROM `%s`"),TABLE_OBJECT_AREA);
	else
		sql = wxString::Format(_("SELECT * FROM %s ORDER BY %s %s"),TABLE_OBJECT_AREA,m_Field,m_Order);

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
	
	CAreaNew *ptr = new CAreaNew();
	if(ptr->ShowModal() == wxID_OK)
	{
		wxDateTime time = wxDateTime::Now();
		wxString sql = wxString::Format(_("INSERT INTO %s SET name='%s', info='%s'"),TABLE_OBJECT_AREA,ptr->GetName(),ptr->GetInfo());
		
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

void CArea::OnEdit(wxString id)
{
	wxString sql = wxString::Format(_("SELECT * FROM %s WHERE id = '%s'"),TABLE_OBJECT_AREA,id);
	
	if(!my_query(sql))
		return;
		
	CAreaNew *ptr = new CAreaNew();
	
	void *result = db_result();
	char **row = (char**)db_fetch_row(result);
	
	ptr->SetName(Convert(row[FID_OBJECT_AREA_NAME]));
	ptr->SetInfo(Convert(row[FID_OBJECT_AREA_INFO]));
	
	db_free_result(result);

	if(ptr->ShowModal() == wxID_OK)
	{

		wxDateTime time = wxDateTime::Now();
		wxString sql = wxString::Format	(_("UPDATE %s SET name='%s', info ='%s' WHERE id = '%s'"),TABLE_OBJECT_AREA,ptr->GetName(),ptr->GetInfo(),id);
		my_query(sql);
		Clear();
		Read();
		Select();
	}

	delete ptr;
	
}

void CArea::OnDelete(wxString id)
{
	wxMessageDialog *MessageDialog = new wxMessageDialog(this,GetMsg(MSG_DELETE_AREA),wxString::Format(wxT("%s %s"),wxT(PRODUCT_NAME),wxT(PRODUCT_VERSION)),wxYES_NO|wxICON_QUESTION);
    if(MessageDialog->ShowModal() == wxID_YES)
	{
		wxString sql = wxString::Format(_("DELETE FROM %s WHERE id = '%s'"),TABLE_OBJECT_AREA,id);
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