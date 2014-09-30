#include "dialog.h"
#include "conf.h"
#include "tools.h"
#include "listctrl.h"
#include "new.h"
#include "db.h"

CDialog::CDialog(int control_type)
{

}

CDialog::CDialog(int control_type, bool picker)
:wxDialog(NULL,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
	m_Picker = picker;
	m_ButtonOk = NULL;
	m_Table = wxEmptyString;
	m_ControlType = control_type;
	SetSize(DEFAULT_DIALOG_WIDTH,DEFAULT_DIALOG_HEIGHT);
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(Sizer);
	Sizer->Add(GetPanel(this),1,wxALL|wxEXPAND,0);

	wxPanel *Panel = new wxPanel(this);
	Sizer->Add(Panel,0,wxALL|wxEXPAND,5);
	wxBoxSizer *PanelSizer = new wxBoxSizer(wxHORIZONTAL);
	Panel->SetSizer(PanelSizer);
	
	//wxButton *ButtonNew = new wxButton(Panel,wxID_CANCEL,GetMsg(MSG_NEW));
	//PanelSizer->Add(ButtonNew,0,wxALL,2);
	//wxButton *ButtonEdit = new wxButton(Panel,wxID_CANCEL,GetMsg(MSG_EDIT));
	//PanelSizer->Add(ButtonEdit,0,wxALL,2);
	//wxButton *ButtonDelete = new wxButton(Panel,wxID_CANCEL,GetMsg(MSG_DELETE));
	//PanelSizer->Add(ButtonDelete,0,wxALL,2);
	
	if(picker)
	{
		PanelSizer->AddStretchSpacer();
		m_ButtonOk = new wxButton(Panel,wxID_OK,GetMsg(MSG_OK));
		m_ButtonOk->Disable();
		PanelSizer->Add(m_ButtonOk,0,wxALL,5);
		wxButton *ButtonClose = new wxButton(Panel,wxID_CANCEL,GetMsg(MSG_CANCEL));
		PanelSizer->Add(ButtonClose,0,wxALL,5);
		SetLabel(GetMsg(MSG_BATTERY));
	
	}else{
			
		wxButton *ButtonClose = new wxButton(Panel,wxID_CANCEL,GetMsg(MSG_CLOSE));
		PanelSizer->AddStretchSpacer();
		PanelSizer->Add(ButtonClose,0,wxALL,2);
		
	}
	
	Center();
	
}

CDialog::~CDialog()
{

}

wxPanel *CDialog::GetPanel(wxWindow *Parent)
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxHORIZONTAL);
	wxPanel *Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition);
	Panel->SetSizer(Sizer);
	m_List = new CListCtrl(Panel,wxLC_REPORT |  wxLC_VIRTUAL | wxLC_SINGLE_SEL | wxLC_ALIGN_LEFT );

	switch(m_ControlType)
	{
	
		case CONTROL_AREA:			ControlArea();				break;
		case CONTROL_BATTERY:		ControlBattery();			break;
		case CONTROL_COMMUNICATION:	ControlCommunication();		break;
		case CONTROL_SEAWAY:		ControlSeaway();			break;
		case CONTROL_LIGHT:			ControlLight();				break;
		case CONTROL_BULB:			ControlBulb();				break;
		case CONTROL_FLASH:			ControlFlash();				break;
	}
	

	m_List->InitColumns();
	Read();
	
	m_List->SetControlType(m_ControlType,this);

	Sizer->Add(m_List,1,wxALL|wxEXPAND,0);

	return Panel;

}

void CDialog::ControlArea()
{
	wxListItem item;
	item.SetWidth(150);	item.SetText(GetMsg(MSG_NAME));	m_List->InsertColumn(0,item);
	item.SetWidth(250);	item.SetText(GetMsg(MSG_INFO));	m_List->InsertColumn(1,item);
		
	m_List->_AddColumn(FID_AREA_NAME,FNAME_AREA_NAME);
	m_List->_AddColumn(FID_AREA_INFO,FNAME_AREA_INFO);
	
	m_List->_AddColumn(FID_AREA_ID,FNAME_AREA_ID);
	m_List->SetColumnWithId(AREA_COLUMN_WITH_ID); // id kolumny z id pól bazy danych
	m_List->SetColumnWithName(AREA_COLUMN_WITH_NAME);
	SetLabel(GetMsg(MSG_AREA));

}

void CDialog::ControlBattery()
{
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
	m_List->SetColumnWithName(BATTERY_COLUMN_WITH_NAME);
	
	SetLabel(GetMsg(MSG_BATTERY));
}

void CDialog::ControlCommunication()
{
	wxListItem item;
	item.SetWidth(150);	item.SetText(GetMsg(MSG_NAME));	m_List->InsertColumn(0,item);
	item.SetWidth(250);	item.SetText(GetMsg(MSG_INFO));	m_List->InsertColumn(1,item);

	m_List->_AddColumn(FID_COMMUNICATION_NAME,FNAME_COMMUNICATION_NAME);
	m_List->_AddColumn(FID_COMMUNICATION_INFO,FNAME_COMMUNICATION_INFO);
	
	m_List->_AddColumn(FID_AREA_ID,FNAME_AREA_ID);
	m_List->SetColumnWithId(COMMUNICATION_COLUMN_WITH_ID); // id kolumny z id pól bazy danych
	m_List->SetColumnWithName(COMMUNICATION_COLUMN_WITH_NAME);
	
	SetLabel(GetMsg(MSG_COMMUNICATION_TYPE));
	
}


void CDialog::ControlSeaway()
{
	wxListItem item;
	item.SetWidth(150);	item.SetText(GetMsg(MSG_NAME));	m_List->InsertColumn(0,item);
	item.SetWidth(250);	item.SetText(GetMsg(MSG_INFO));	m_List->InsertColumn(1,item);

	m_List->_AddColumn(FID_SEAWAY_NAME,FNAME_SEAWAY_NAME);
	m_List->_AddColumn(FID_SEAWAY_INFO,FNAME_SEAWAY_INFO);
	
	m_List->_AddColumn(FID_SEAWAY_ID,FNAME_SEAWAY_ID);
	m_List->SetColumnWithId(SEAWAY_COLUMN_WITH_ID);		// id kolumny z id pól bazy danych
	m_List->SetColumnWithName(SEAWAY_COLUMN_WITH_NAME);
	
	SetLabel(GetMsg(MSG_SEAWAY));
}


void CDialog::ControlLight()
{
	wxListItem item;
	item.SetWidth(150);	item.SetText(GetMsg(MSG_NAME));	m_List->InsertColumn(0,item);
	item.SetWidth(250);	item.SetText(GetMsg(MSG_INFO));	m_List->InsertColumn(1,item);

	m_List->_AddColumn(FID_LIGHT_NAME,FNAME_LIGHT_NAME);
	m_List->_AddColumn(FID_LIGHT_INFO,FNAME_LIGHT_INFO);
	
	m_List->_AddColumn(FID_LIGHT_ID,FNAME_LIGHT_ID);
	m_List->SetColumnWithId(LIGHT_COLUMN_WITH_ID); // id kolumny z id pól bazy danych
	m_List->SetColumnWithName(LIGHT_COLUMN_WITH_NAME);
	
	SetLabel(GetMsg(MSG_LIGHT));
}


void CDialog::ControlFlash()
{
	wxListItem item;
	item.SetWidth(150);	item.SetText(GetMsg(MSG_NAME));		m_List->InsertColumn(0,item);
	item.SetWidth(100);	item.SetText(GetMsg(MSG_TYPE));		m_List->InsertColumn(1,item);
	item.SetWidth(250);	item.SetText(GetMsg(MSG_INFO));		m_List->InsertColumn(2,item);

	m_List->_AddColumn(FID_FLASH_NAME,FNAME_FLASH_NAME);
	m_List->_AddColumn(FID_FLASH_TYPE,FNAME_FLASH_TYPE);
	m_List->_AddColumn(FID_FLASH_INFO,FNAME_FLASH_INFO);
	
	m_List->_AddColumn(FID_FLASH_ID,FNAME_FLASH_ID);
	m_List->SetColumnWithId(FLASH_COLUMN_WITH_ID); // id kolumny z id pól bazy danych
	m_List->SetColumnWithName(FLASH_COLUMN_WITH_NAME);
	
	SetLabel(GetMsg(MSG_FLASH));
}



void CDialog::ControlBulb()
{
	wxListItem item;
	item.SetWidth(150);	item.SetText(GetMsg(MSG_NAME));		m_List->InsertColumn(0,item);
	item.SetWidth(100);	item.SetText(GetMsg(MSG_TYPE));		m_List->InsertColumn(1,item);
	item.SetWidth(100);	item.SetText(GetMsg(MSG_VOLTAGE));	m_List->InsertColumn(2,item);
	item.SetWidth(100);	item.SetText(GetMsg(MSG_POWER));	m_List->InsertColumn(3,item);
	item.SetWidth(250);	item.SetText(GetMsg(MSG_INFO));		m_List->InsertColumn(4,item);

	m_List->_AddColumn(FID_BULB_NAME,FNAME_BULB_NAME);
	m_List->_AddColumn(FID_BULB_TYPE,FNAME_BULB_TYPE);
	m_List->_AddColumn(FID_BULB_VOLTAGE,FNAME_BULB_VOLTAGE);
	m_List->_AddColumn(FID_BULB_POWER,FNAME_BULB_POWER);
	m_List->_AddColumn(FID_BULB_INFO,FNAME_BULB_INFO);
	
	m_List->_AddColumn(FID_BULB_ID,FNAME_BULB_ID);
	m_List->SetColumnWithId(BULB_COLUMN_WITH_ID); // id kolumny z id pól bazy danych
	m_List->SetColumnWithName(BULB_COLUMN_WITH_NAME);
	
	SetLabel(GetMsg(MSG_BULB));
}

void CDialog::SetTable()
{
	switch(m_ControlType)
	{
		case CONTROL_AREA:			m_Table = TABLE_AREA;			break;
		case CONTROL_BATTERY:		m_Table = TABLE_BATTERY;		break;
		case CONTROL_COMMUNICATION:	m_Table = TABLE_COMMUNICATION;	break;
		case CONTROL_SEAWAY:		m_Table = TABLE_SEAWAY;			break;
		case CONTROL_LIGHT:			m_Table = TABLE_LIGHT;			break;
		case CONTROL_FLASH:			m_Table = TABLE_FLASH;			break;
		case CONTROL_BULB:			m_Table = TABLE_BULB;			break;
		//case CONTROL_SYMBOL:		table = TABLE_t
	}
}

void CDialog::Read()
{	
	SetTable();
	wxString sql;

	if(m_Field == wxEmptyString)		
		sql = wxString::Format(_("SELECT * FROM `%s`"),m_Table);
	else
		sql = wxString::Format(_("SELECT * FROM %s ORDER BY %s %s"),m_Table,m_Field,m_Order);

	m_List->Read(sql);
	m_List->Refresh(false);

}

void CDialog::Clear()
{
	m_List->Clear();
}
	
void CDialog::Select()
{
	m_List->Select();
}

void CDialog::OnNew()
{
	New();
}

void CDialog::New()
{
	CNew *ptr = new CNew(m_ControlType);
	if(ptr->ShowModal() == wxID_OK)
	{
		wxString sql; 

		switch(m_ControlType)
		{
			case CONTROL_AREA:			
				sql = wxString::Format(_("INSERT INTO %s SET name='%s', info='%s'"),TABLE_AREA,ptr->GetName(),ptr->GetInfo());
			break;
			case CONTROL_BATTERY:		
				sql = wxString::Format(_("INSERT INTO %s SET name='%s', info='%s', type='%s', capacity='%s'"),TABLE_BATTERY,ptr->GetName(),ptr->GetInfo(),ptr->GetType(),ptr->GetCapacity());
			break;
			case CONTROL_COMMUNICATION:	
				sql = wxString::Format(_("INSERT INTO %s SET name='%s', info='%s'"),TABLE_COMMUNICATION,ptr->GetName(),ptr->GetInfo());
			break;
			case CONTROL_SEAWAY:		
				sql = wxString::Format(_("INSERT INTO %s SET name='%s', info='%s'"),TABLE_SEAWAY,ptr->GetName(),ptr->GetInfo());
			break;
			case CONTROL_LIGHT:			
				sql = wxString::Format(_("INSERT INTO %s SET name='%s', info='%s'"),TABLE_LIGHT,ptr->GetName(),ptr->GetInfo());
			break;
			case CONTROL_FLASH:			
				sql = wxString::Format(_("INSERT INTO %s SET name='%s', type ='%s', info='%s'"),TABLE_FLASH,ptr->GetName(),ptr->GetType(),ptr->GetInfo());
			break;
			case CONTROL_BULB:			
				sql = wxString::Format(_("INSERT INTO %s SET name='%s', type ='%s',voltage='%s', power='%s', info='%s'"),TABLE_BULB,ptr->GetName(),ptr->GetType(),ptr->GetVoltage(),ptr->GetPower(),ptr->GetInfo());
			break;

		}
				
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




void CDialog::OnEdit(wxString id)
{
	switch(m_ControlType)
	{
		case CONTROL_AREA:			EditArea(id);			break;
		case CONTROL_BATTERY:		EditBattery(id);		break;
		case CONTROL_COMMUNICATION:	EditCommunication(id);	break;
		case CONTROL_SEAWAY:		EditSeaway(id);			break;
		case CONTROL_LIGHT:			EditLight(id);			break;
		case CONTROL_BULB:			EditBulb(id);			break;
	}

}

void CDialog::EditArea(wxString id)
{
	wxString sql = wxString::Format(_("SELECT * FROM %s WHERE id = '%s'"),TABLE_AREA,id);
	
	if(!my_query(sql))
		return;
		
	CNew *ptr = new CNew(CONTROL_AREA);
	
	void *result = db_result();
	char **row = (char**)db_fetch_row(result);
	
	ptr->SetName(Convert(row[FID_AREA_NAME]));
	ptr->SetInfo(Convert(row[FID_AREA_INFO]));
	
	db_free_result(result);

	if(ptr->ShowModal() == wxID_OK)
	{
		wxString sql = wxString::Format	(_("UPDATE %s SET name='%s', info ='%s' WHERE id = '%s'"),TABLE_AREA,ptr->GetName(),ptr->GetInfo(),id);
		my_query(sql);
		Clear();
		Read();
		Select();
	}

	delete ptr;
	
}

void CDialog::EditBattery(wxString id)
{
	wxString sql = wxString::Format(_("SELECT * FROM %s WHERE id = '%s'"),TABLE_BATTERY,id);
	
	if(!my_query(sql))
		return;
		
	CNew *ptr = new CNew(CONTROL_BATTERY);
	
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

void CDialog::EditCommunication(wxString id)
{
	wxString sql = wxString::Format(_("SELECT * FROM %s WHERE id = '%s'"),TABLE_COMMUNICATION,id);
	
	if(!my_query(sql))
		return;
		
	CNew *ptr = new CNew(CONTROL_COMMUNICATION);
	
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

void CDialog::EditSeaway(wxString id)
{
	wxString sql = wxString::Format(_("SELECT * FROM %s WHERE id = '%s'"),TABLE_SEAWAY,id);
	
	if(!my_query(sql))
		return;
		
	CNew *ptr = new CNew(CONTROL_SEAWAY);
	
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

void CDialog::EditLight(wxString id)
{
	wxString sql = wxString::Format(_("SELECT * FROM %s WHERE id = '%s'"),TABLE_LIGHT,id);
	
	if(!my_query(sql))
		return;
		
	CNew *ptr = new CNew(CONTROL_LIGHT);
	
	void *result = db_result();
	char **row = (char**)db_fetch_row(result);
	
	ptr->SetName(Convert(row[FID_LIGHT_NAME]));
	ptr->SetInfo(Convert(row[FID_LIGHT_INFO]));
	
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

void CDialog::EditBulb(wxString id)
{

	wxString sql = wxString::Format(_("SELECT * FROM %s WHERE id = '%s'"),TABLE_BULB,id);
	
	if(!my_query(sql))
		return;
		
	CNew *ptr = new CNew(CONTROL_BULB);
	
	void *result = db_result();
	char **row = (char**)db_fetch_row(result);
	
	ptr->SetName(Convert(row[FID_BULB_NAME]));
	ptr->SetInfo(Convert(row[FID_BULB_INFO]));
	ptr->SetPower(Convert(row[FID_BULB_POWER]));
	ptr->SetVoltage(Convert(row[FID_BULB_VOLTAGE]));
	ptr->SetType(Convert(row[FID_BULB_TYPE]));
	
	db_free_result(result);

	if(ptr->ShowModal() == wxID_OK)
	{
		wxString sql = wxString::Format	(_("UPDATE %s SET name='%s', info ='%s', type ='%s', voltage='%s', power='%s' WHERE id = '%s'"),TABLE_BULB,ptr->GetName(),ptr->GetInfo(),ptr->GetType(),ptr->GetVoltage(),ptr->GetPower(),id);
		my_query(sql);
		Clear();
		Read();
		Select();
	}

	delete ptr;
}

void CDialog::OnDelete(wxString id)
{
	SetTable();

	wxMessageDialog *MessageDialog = new wxMessageDialog(this,GetMsg(MSG_DELETE_QUESTION),wxString::Format(wxT("%s %s"),wxT(PRODUCT_NAME),wxT(PRODUCT_VERSION)),wxYES_NO|wxICON_QUESTION);
    if(MessageDialog->ShowModal() == wxID_YES)
	{
		wxString sql = wxString::Format(_("DELETE FROM %s WHERE id = '%s'"),m_Table,id);
		my_query(sql);
		Clear();
		Read();
		
		if(m_Picker)
			m_ButtonOk->Disable();
		
	}

	delete MessageDialog;
}




void CDialog::OnColumnCLick(wxString field, int order)
{
	if(order == ORDER_ASC)
		m_Order = _("ASC");
	else
		m_Order = _("DESC");
	
	m_Field = field;
	Clear();
	Read();
}

void CDialog::OnSelect(wxString id, wxString name)
{
	if(m_ButtonOk)
		m_ButtonOk->Enable();
	m_Id = id;
	m_Name = name;

}

wxString CDialog::_GetId()
{
	return m_Id;
}

wxString  CDialog::_GetName()
{
	return m_Name;
}