#include "battery.h"
#include "conf.h"
#include "tools.h"
#include "listctrl.h"
#include "battery_new.h"
#include "db.h"
#include <wx/mstream.h>


extern unsigned int	add_size;
extern unsigned char add[];

CBatteryDialog::CBatteryDialog(int type)
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
	ButtonOk = NULL;

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
		PanelSizer->Add(ButtonClose,0,wxALL,5);
		SetLabel(GetMsg(MSG_BATTERY));
	
	}
		
	Center();
	
}

CBatteryDialog::~CBatteryDialog()
{

}

wxPanel *CBatteryDialog::GetPanel(wxWindow *Parent)
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxHORIZONTAL);
	wxPanel *Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition);
	Panel->SetSizer(Sizer);
	m_List = new CListCtrl(Panel,wxLC_REPORT |  wxLC_VIRTUAL );
	wxListItem item;
	item.SetWidth(150);	item.SetText(GetMsg(MSG_NAME));		m_List->InsertColumn(0,item);
	item.SetWidth(100);	item.SetText(GetMsg(MSG_TYPE));		m_List->InsertColumn(1,item);
	item.SetWidth(100);	item.SetText(GetMsg(MSG_CAPACITY));	m_List->InsertColumn(2,item);
	item.SetWidth(250);	item.SetText(GetMsg(MSG_INFO));		m_List->InsertColumn(3,item);

	m_List->_AddColumn(FID_BATTERY_NAME,FNAME_BATTERY_NAME);
	m_List->_AddColumn(FID_BATTERY_TYPE,FNAME_BATTERY_TYPE);
	m_List->_AddColumn(FID_BATTERY_CAPACITY,FNAME_BATTERY_CAPACITY);
	m_List->_AddColumn(FID_BATTERY_INFO,FNAME_BATTERY_INFO);
	
	m_List->_AddColumn(FID_AREA_ID,FNAME_AREA_ID);
	m_List->SetColumnWithId(BATTERY_COLUMN_WITH_ID); // id kolumny z id pól bazy danych
		
	m_List->InitColumns();
	Read();
	
	m_List->SetControlType(CONTROL_BATTERY,this);

	Sizer->Add(m_List,1,wxALL|wxEXPAND,0);

	return Panel;

}

void CBatteryDialog::Read()
{
	wxString sql;

	if(m_Field == wxEmptyString)		
		sql = wxString::Format(_("SELECT * FROM `%s`"),TABLE_BATTERY);
	else
		sql = wxString::Format(_("SELECT * FROM %s ORDER BY %s %s"),TABLE_BATTERY,m_Field,m_Order);

	m_List->Read(sql);
	m_List->Refresh(false);
}

void CBatteryDialog::Clear()
{
	m_List->Clear();
}
	
void CBatteryDialog::Select()
{
	m_List->Select();
}

void CBatteryDialog::OnNew()
{
	
	CBatteryNew *ptr = new CBatteryNew();
	if(ptr->ShowModal() == wxID_OK)
	{
		wxString sql = wxString::Format(_("INSERT INTO %s SET name='%s', info='%s', type='%s', capacity='%s'"),TABLE_BATTERY,ptr->GetName(),ptr->GetInfo(),ptr->GetType(),ptr->GetCapacity());
		
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

void CBatteryDialog::OnEdit(wxString id)
{
	wxString sql = wxString::Format(_("SELECT * FROM %s WHERE id = '%s'"),TABLE_BATTERY,id);
	
	if(!my_query(sql))
		return;
		
	CBatteryNew *ptr = new CBatteryNew();
	
	void *result = db_result();
	char **row = (char**)db_fetch_row(result);
	
	ptr->SetName(Convert(row[FID_BATTERY_NAME]));
	ptr->SetInfo(Convert(row[FID_BATTERY_INFO]));
	ptr->SetCapacity(Convert(row[FID_BATTERY_CAPACITY]));
	ptr->SetType(Convert(row[FID_BATTERY_TYPE]));
	
	db_free_result(result);

	if(ptr->ShowModal() == wxID_OK)
	{
		wxString sql = wxString::Format	(_("UPDATE %s SET name='%s', info ='%s', type ='%s', capacity='%s' WHERE id = '%s'"),TABLE_BATTERY,ptr->GetName(),ptr->GetInfo(),ptr->GetType(),ptr->GetCapacity(),id);
		my_query(sql);
		Clear();
		Read();
		Select();
	}

	delete ptr;
	
}

void CBatteryDialog::OnDelete(wxString id)
{
	wxMessageDialog *MessageDialog = new wxMessageDialog(this,GetMsg(MSG_DELETE_QUESTION),wxString::Format(wxT("%s %s"),wxT(PRODUCT_NAME),wxT(PRODUCT_VERSION)),wxYES_NO|wxICON_QUESTION);
    if(MessageDialog->ShowModal() == wxID_YES)
	{
		wxString sql = wxString::Format(_("DELETE FROM %s WHERE id = '%s'"),TABLE_BATTERY,id);
		my_query(sql);
		Clear();
		Read();
		Select();
	}

	delete MessageDialog;
}


void CBatteryDialog::OnColumnCLick(wxString field, int order)
{
	if(order == ORDER_ASC)
		m_Order = _("ASC");
	else
		m_Order = _("DESC");
	
	m_Field = field;
	Clear();
	Read();
}

void CBatteryDialog::OnSelect(wxString id,wxArrayString row)
{
	if(ButtonOk)
		ButtonOk->Enable();
	m_Id = row[BATTERY_COLUMN_WITH_ID];
	m_Name = row[BATTERY_COLUMN_WITH_NAME];
}

void CBatteryDialog::OnDeSelect()
{
	if(ButtonOk)
		ButtonOk->Disable();
}

wxString CBatteryDialog::GetBatteryId()
{
	return m_Id;
}

wxString CBatteryDialog::GetBatteryName()
{
	return m_Name;
}