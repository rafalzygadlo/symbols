#include "dialog.h"
#include "conf.h"
#include "tools.h"
#include "listctrl.h"
#include "new.h"
#include "db.h"


SHeader Header[] =
{
	{CONTROL_AREA,80,	{FID_AREA_ID ,	FNAME_AREA_ID, MSG_ID} },
	{CONTROL_AREA,100,	{FID_AREA_NAME , FNAME_AREA_NAME, MSG_NAME} },
	{CONTROL_AREA,250,	{FID_AREA_INFO , FNAME_AREA_INFO, MSG_INFO} },

	{CONTROL_BATTERY,80,  {FID_BATTERY_ID,	FNAME_BATTERY_ID, MSG_ID }},
	{CONTROL_BATTERY,100, {FID_BATTERY_TYPE, FNAME_BATTERY_TYPE, MSG_TYPE}},
	{CONTROL_BATTERY,100, {FID_BATTERY_CAPACITY, FNAME_BATTERY_CAPACITY,MSG_CAPACITY }},
	{CONTROL_BATTERY,250, {FID_BATTERY_INFO, FNAME_BATTERY_INFO,MSG_INFO}},
	
	{CONTROL_COMMUNICATION,80,	{FID_COMMUNICATION_ID ,	FNAME_COMMUNICATION_ID, MSG_ID} },
	{CONTROL_COMMUNICATION,100,	{FID_COMMUNICATION_NAME , FNAME_COMMUNICATION_NAME, MSG_NAME} },
	{CONTROL_COMMUNICATION,250,	{FID_COMMUNICATION_INFO , FNAME_COMMUNICATION_INFO, MSG_INFO} },
	
	{CONTROL_SEAWAY,80,	 {FID_SEAWAY_ID , FNAME_SEAWAY_ID, MSG_ID} },
	{CONTROL_SEAWAY,100, {FID_SEAWAY_NAME , FNAME_SEAWAY_NAME, MSG_NAME} },
	{CONTROL_SEAWAY,250, {FID_SEAWAY_INFO , FNAME_SEAWAY_INFO, MSG_INFO} },
	
	{CONTROL_LIGHT,80,	{FID_LIGHT_ID , FNAME_LIGHT_ID, MSG_ID} },
	{CONTROL_LIGHT,100,	{FID_LIGHT_NAME , FNAME_LIGHT_NAME, MSG_NAME} },
	{CONTROL_LIGHT,250,	{FID_LIGHT_INFO , FNAME_LIGHT_INFO, MSG_INFO} },

	{CONTROL_FLASH,80,  {FID_FLASH_ID , FNAME_FLASH_ID, MSG_ID}  },
	{CONTROL_FLASH,100, {FID_FLASH_TYPE , FNAME_FLASH_TYPE, MSG_TYPE}  },
	{CONTROL_FLASH,250, {FID_FLASH_INFO , FNAME_FLASH_INFO, MSG_INFO}  },
	
	{CONTROL_BULB,80,  {FID_BULB_ID , FNAME_BULB_ID, MSG_ID}  },
	{CONTROL_BULB,100, {FID_BULB_TYPE , FNAME_BULB_TYPE, MSG_TYPE}  },
	{CONTROL_BULB,100, {FID_BULB_VOLTAGE , FNAME_BULB_VOLTAGE, MSG_VOLTAGE}  },
	{CONTROL_BULB,100, {FID_BULB_POWER , FNAME_BULB_POWER, MSG_POWER}  },
	{CONTROL_BULB,250, {FID_BULB_INFO , FNAME_BULB_INFO, MSG_INFO}  },

	{CONTROL_SYMBOL_TYPE,80,	{FID_SYMBOL_TYPE_ID ,	FNAME_SYMBOL_TYPE_ID, MSG_ID} },
	{CONTROL_SYMBOL_TYPE,100,	{FID_SYMBOL_TYPE_NAME , FNAME_SYMBOL_TYPE_NAME, MSG_NAME} },
	{CONTROL_SYMBOL_TYPE,250,	{FID_SYMBOL_TYPE_INFO , FNAME_SYMBOL_TYPE_INFO, MSG_INFO} },
	
	{CONTROL_LANTERN,80,	{FID_LANTERN_ID ,	FNAME_LANTERN_ID, MSG_ID} },
	{CONTROL_LANTERN,100,	{FID_LANTERN_TYPE , FNAME_LANTERN_TYPE, MSG_TYPE} },
	{CONTROL_LANTERN,250,	{FID_LANTERN_INFO , FNAME_LANTERN_INFO, MSG_INFO} },
	
	{CONTROL_CHANGER,80,	{FID_CHANGER_ID ,	FNAME_CHANGER_ID, MSG_ID} },
	{CONTROL_CHANGER,100,	{FID_CHANGER_TYPE , FNAME_CHANGER_TYPE, MSG_TYPE} },
	{CONTROL_CHANGER,250,	{FID_CHANGER_INFO , FNAME_CHANGER_INFO, MSG_INFO} },

	{CONTROL_SOLAR,80,	{FID_CHANGER_ID ,	FNAME_CHANGER_ID, MSG_ID} },
	{CONTROL_SOLAR,100,	{FID_CHANGER_TYPE , FNAME_CHANGER_TYPE, MSG_TYPE} },
	{CONTROL_SOLAR,250,	{FID_CHANGER_INFO , FNAME_CHANGER_INFO, MSG_INFO} },

	{CONTROL_REGULATOR,80,	{FID_REGULATOR_ID ,	FNAME_REGULATOR_ID, MSG_ID} },
	{CONTROL_REGULATOR,100,	{FID_REGULATOR_TYPE , FNAME_REGULATOR_TYPE, MSG_TYPE} },
	{CONTROL_REGULATOR,250,	{FID_REGULATOR_INFO , FNAME_REGULATOR_INFO, MSG_INFO} },

	{CONTROL_AC_ADAPTER,80,	{FID_AC_ADAPTER_ID , FNAME_AC_ADAPTER_ID, MSG_ID} },
	{CONTROL_AC_ADAPTER,100,{FID_AC_ADAPTER_TYPE , FNAME_AC_ADAPTER_TYPE, MSG_TYPE} },
	{CONTROL_AC_ADAPTER,250,{FID_AC_ADAPTER_INFO , FNAME_AC_ADAPTER_INFO, MSG_INFO} },

	{CONTROL_SYNCHRONIZATION,80, {FID_SYNCHRONIZATION_ID , FNAME_SYNCHRONIZATION_ID, MSG_ID} },
	{CONTROL_SYNCHRONIZATION,100, {FID_SYNCHRONIZATION_TYPE , FNAME_SYNCHRONIZATION_TYPE, MSG_TYPE} },
	{CONTROL_SYNCHRONIZATION,250, {FID_SYNCHRONIZATION_INFO , FNAME_SYNCHRONIZATION_INFO, MSG_INFO} },

	{CONTROL_TELEMETRY,80, {FID_TELEMETRY_ID , FNAME_TELEMETRY_ID, MSG_ID} },
	{CONTROL_TELEMETRY,100, {FID_TELEMETRY_TYPE , FNAME_TELEMETRY_TYPE, MSG_TYPE} },
	{CONTROL_TELEMETRY,250, {FID_TELEMETRY_INFO , FNAME_TELEMETRY_INFO, MSG_INFO} },
	
	{CONTROL_COLLECTION,80, {FID_COLLECTION_ID , FNAME_COLLECTION_ID, MSG_ID} },
	{CONTROL_COLLECTION,100, {FID_COLLECTION_TYPE , FNAME_COLLECTION_TYPE, MSG_TYPE} },
	{CONTROL_COLLECTION,250, {FID_COLLECTION_INFO , FNAME_COLLECTION_INFO, MSG_INFO} },

	{CONTROL_ANTENNA,80, {FID_ANTENNA_ID , FNAME_ANTENNA_ID, MSG_ID} },
	{CONTROL_ANTENNA,100, {FID_ANTENNA_TYPE , FNAME_ANTENNA_TYPE, MSG_TYPE} },
	{CONTROL_ANTENNA,250, {FID_ANTENNA_INFO , FNAME_ANTENNA_INFO, MSG_INFO} },

	{CONTROL_LIGHTNING,80, {FID_LIGHTNING_ID , FNAME_LIGHTNING_ID, MSG_ID} },
	{CONTROL_LIGHTNING,100, {FID_LIGHTNING_TYPE , FNAME_LIGHTNING_TYPE, MSG_TYPE} },
	{CONTROL_LIGHTNING,250, {FID_LIGHTNING_INFO , FNAME_LIGHTNING_INFO, MSG_INFO} },
	
	{CONTROL_WIND_GENERATOR,80, {FID_WIND_GENERATOR_ID , FNAME_WIND_GENERATOR_ID, MSG_ID} },
	{CONTROL_WIND_GENERATOR,100, {FID_WIND_GENERATOR_TYPE , FNAME_WIND_GENERATOR_TYPE, MSG_TYPE} },
	{CONTROL_WIND_GENERATOR,250, {FID_WIND_GENERATOR_INFO , FNAME_WIND_GENERATOR_INFO, MSG_INFO} },

	{CONTROL_NAUTOFON,80, {FID_NAUTOFON_ID , FNAME_NAUTOFON_ID, MSG_ID} },
	{CONTROL_NAUTOFON,100, {FID_NAUTOFON_TYPE , FNAME_NAUTOFON_TYPE, MSG_TYPE} },
	{CONTROL_NAUTOFON,250, {FID_NAUTOFON_INFO , FNAME_NAUTOFON_INFO, MSG_INFO} },

	{-1},

};

SIds Id[] =
{
	{CONTROL_AREA, COLUMN_WITH_ID, COLUMN_WITH_NAME, MSG_AREA},
	{CONTROL_BATTERY, COLUMN_WITH_ID, COLUMN_WITH_NAME,MSG_BATTERY},
	{CONTROL_COMMUNICATION, COLUMN_WITH_ID, COLUMN_WITH_NAME,MSG_COMMUNICATION_TYPE},
	{CONTROL_SEAWAY, COLUMN_WITH_ID, COLUMN_WITH_NAME,MSG_SEAWAY},
	{CONTROL_LIGHT, COLUMN_WITH_ID, COLUMN_WITH_NAME,MSG_LIGHT},
	{CONTROL_FLASH, COLUMN_WITH_ID, COLUMN_WITH_NAME,MSG_FLASH},
	{CONTROL_BULB, COLUMN_WITH_ID, COLUMN_WITH_NAME,MSG_BULB},
	{CONTROL_SYMBOL_TYPE, COLUMN_WITH_ID, COLUMN_WITH_NAME,MSG_SYMBOL_TYPE},
	{CONTROL_LANTERN, COLUMN_WITH_ID, COLUMN_WITH_NAME,MSG_LANTERN},
	{CONTROL_CHANGER, COLUMN_WITH_ID, COLUMN_WITH_NAME,MSG_CHANGER},
	{CONTROL_SOLAR, COLUMN_WITH_ID, COLUMN_WITH_NAME, MSG_SOLAR},
	{CONTROL_REGULATOR, COLUMN_WITH_ID, COLUMN_WITH_NAME, MSG_REGULATOR},
	{CONTROL_AC_ADAPTER, COLUMN_WITH_ID, COLUMN_WITH_NAME, MSG_AC_ADAPTER},
	{CONTROL_SYNCHRONIZATION, COLUMN_WITH_ID, COLUMN_WITH_NAME, MSG_SYNCHRONIZATION},
	{CONTROL_TELEMETRY, COLUMN_WITH_ID, COLUMN_WITH_NAME, MSG_TELEMETRY_MODULE},
	{CONTROL_COLLECTION, COLUMN_WITH_ID, COLUMN_WITH_NAME, MSG_COLLECTION_MODULE},
	{CONTROL_ANTENNA, COLUMN_WITH_ID, COLUMN_WITH_NAME, MSG_ANTENNA},
	{CONTROL_LIGHTNING, COLUMN_WITH_ID, COLUMN_WITH_NAME, MSG_LIGHTNING},
	{CONTROL_WIND_GENERATOR, COLUMN_WITH_ID, COLUMN_WITH_NAME, MSG_WIND_GENERATOR},
	{CONTROL_NAUTOFON, COLUMN_WITH_ID, COLUMN_WITH_NAME, MSG_NAUTOFON},
	{-1},

};

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
	SetTable();
	
	SetSize(DEFAULT_DIALOG_WIDTH,DEFAULT_DIALOG_HEIGHT);
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(Sizer);
	
	wxPanel *TopPanel = new wxPanel(this);
	Sizer->Add(TopPanel,0,wxALL|wxEXPAND,5);
	wxBoxSizer *TopPanelSizer = new wxBoxSizer(wxHORIZONTAL);
	TopPanel->SetSizer(TopPanelSizer);

	m_TopLabel = new wxStaticText(TopPanel,wxID_ANY,wxEmptyString);
	TopPanelSizer->Add(m_TopLabel,0,wxALL,5);
	
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

	int id = 0;
	wxListItem item;
	int counter = 0;
	SHeader h;

	while(Header[id].id_control != -1)
	{
		h = Header[id];
		
		if(h.id_control == m_ControlType)
		{
			h = Header[id];
			item.SetWidth(h.width);	
			item.SetText(GetMsg(h.column.id_msg));	
			m_List->InsertColumn(counter,item);
			m_List->_AddColumn(h.column.id,h.column.name);
			counter++;
		}
	
		id++;
	}

	id = 0;
	
	while(Id[id].id_control != -1)
	{
		SIds i = Id[id];
		if(i.id_control == m_ControlType)
		{
			m_List->SetColumnWithId(i.col_with_id);
			m_List->SetColumnWithName(i.col_with_name);
			m_TopLabel->SetLabel(GetMsg(i.id_label));
			break;
		} 
	
		id++;
	}

	
	m_List->InitColumns();
	Read();
	
	m_List->SetControlType(m_ControlType,this);

	Sizer->Add(m_List,1,wxALL|wxEXPAND,0);

	return Panel;

}

void CDialog::SetTable()
{
	switch(m_ControlType)
	{
		case CONTROL_AREA:				m_Table = TABLE_AREA;				break;
		case CONTROL_BATTERY:			m_Table = TABLE_BATTERY;			break;
		case CONTROL_COMMUNICATION:		m_Table = TABLE_COMMUNICATION;		break;
		case CONTROL_SEAWAY:			m_Table = TABLE_SEAWAY;				break;
		case CONTROL_LIGHT:				m_Table = TABLE_LIGHT;				break;
		case CONTROL_FLASH:				m_Table = TABLE_FLASH;				break;
		case CONTROL_BULB:				m_Table = TABLE_BULB;				break;
		case CONTROL_SYMBOL_TYPE:		m_Table	= TABLE_SYMBOL_TYPE;		break;
		case CONTROL_LANTERN:			m_Table = TABLE_LANTERN;			break;
		case CONTROL_CHANGER:			m_Table = TABLE_CHANGER;			break;
		case CONTROL_SOLAR:				m_Table = TABLE_SOLAR;				break;
		case CONTROL_REGULATOR:			m_Table = TABLE_REGULATOR;			break;
		case CONTROL_AC_ADAPTER:		m_Table = TABLE_AC_ADAPTER;			break;
		case CONTROL_SYNCHRONIZATION:	m_Table = TABLE_SYNCHRONIZATION;	break;
		case CONTROL_TELEMETRY:			m_Table = TABLE_TELEMETRY;			break;
		case CONTROL_COLLECTION:		m_Table = TABLE_COLLECTION;			break;
		case CONTROL_ANTENNA:			m_Table = TABLE_ANTENNA;			break;
		case CONTROL_LIGHTNING:			m_Table = TABLE_LIGHTNING;			break;
		case CONTROL_WIND_GENERATOR:	m_Table = TABLE_WIND_GENERATOR;		break;
		case CONTROL_NAUTOFON:			m_Table = TABLE_NAUTOFON;			break;
	}
}

void CDialog::Read()
{	
	
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
			case CONTROL_COMMUNICATION:	
			case CONTROL_SEAWAY:		
			case CONTROL_SYMBOL_TYPE:
				sql = wxString::Format(_("INSERT INTO %s SET name='%s', info='%s'"),m_Table,ptr->GetName(),ptr->GetInfo());
			break;
			
			case CONTROL_BATTERY:		
				sql = wxString::Format(_("INSERT INTO %s SET info='%s', type='%s', capacity='%s'"),m_Table,ptr->GetInfo(),ptr->GetType(),ptr->GetCapacity());
			break;
			case CONTROL_LIGHT:			
				sql = wxString::Format(_("INSERT INTO %s SET name='%s', info='%s'"),m_Table,ptr->GetName(),ptr->GetInfo());
			break;
			
			case CONTROL_BULB:			
				sql = wxString::Format(_("INSERT INTO %s SET type ='%s',voltage='%s', power='%s', info='%s'"),m_Table,ptr->GetType(),ptr->GetVoltage(),ptr->GetPower(),ptr->GetInfo());
			break;
						
			case CONTROL_LANTERN:
			case CONTROL_CHANGER:
			case CONTROL_SOLAR:
			case CONTROL_REGULATOR:
			case CONTROL_AC_ADAPTER:
			case CONTROL_SYNCHRONIZATION:
			case CONTROL_TELEMETRY:
			case CONTROL_FLASH:
			case CONTROL_COLLECTION:
			case CONTROL_ANTENNA:
			case CONTROL_LIGHTNING:
			case CONTROL_WIND_GENERATOR:
			case CONTROL_NAUTOFON:
				sql = wxString::Format(_("INSERT INTO %s SET type ='%s', info='%s'"),m_Table,ptr->GetType(),ptr->GetInfo());
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
		
		case CONTROL_BATTERY:			EditBattery(id);					break;
		case CONTROL_LIGHT:				EditLight(id);						break;
		case CONTROL_BULB:				EditBulb(id);						break;
		
		case CONTROL_COMMUNICATION:		
		case CONTROL_AREA:				
		case CONTROL_SEAWAY:			
		case CONTROL_SYMBOL_TYPE:		
			EditName(id);		
		break;
		
		case CONTROL_FLASH:	
		case CONTROL_LANTERN:
		case CONTROL_CHANGER:
		case CONTROL_SOLAR:
		case CONTROL_REGULATOR:
		case CONTROL_AC_ADAPTER:
		case CONTROL_SYNCHRONIZATION:
		case CONTROL_TELEMETRY:
		case CONTROL_COLLECTION:
		case CONTROL_ANTENNA:
		case CONTROL_LIGHTNING:
		case CONTROL_WIND_GENERATOR:
		case CONTROL_NAUTOFON:
			EditType(id);
		break;
	}

}

void CDialog::EditName(wxString id)
{
	wxString sql = wxString::Format(_("SELECT * FROM %s WHERE id = '%s'"),m_Table,id);
	
	if(!my_query(sql))
		return;
		
	CNew *ptr = new CNew(m_ControlType);
	
	void *result = db_result();
	char **row = (char**)db_fetch_row(result);
	
	ptr->SetName(Convert(row[FID_NAME]));
	ptr->SetInfo(Convert(row[FID_INFO]));
	
	db_free_result(result);

	if(ptr->ShowModal() == wxID_OK)
	{
		wxString sql = wxString::Format	(_("UPDATE %s SET name='%s', info ='%s' WHERE id = '%s'"),m_Table,ptr->GetName(),ptr->GetInfo(),id);
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
	
	ptr->SetInfo(Convert(row[FID_BATTERY_INFO]));
	ptr->SetCapacity(Convert(row[FID_BATTERY_CAPACITY]));
	ptr->SetType(Convert(row[FID_BATTERY_TYPE]));
	
	db_free_result(result);

	if(ptr->ShowModal() == wxID_OK)
	{
		wxString sql = wxString::Format	(_("UPDATE %s SET info ='%s', type ='%s', capacity='%s' WHERE id = '%s'"),TABLE_BATTERY,ptr->GetInfo(),ptr->GetType(),ptr->GetCapacity(),id);
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
	
	ptr->SetInfo(Convert(row[FID_BULB_INFO]));
	ptr->SetPower(Convert(row[FID_BULB_POWER]));
	ptr->SetVoltage(Convert(row[FID_BULB_VOLTAGE]));
	ptr->SetType(Convert(row[FID_BULB_TYPE]));
	
	db_free_result(result);

	if(ptr->ShowModal() == wxID_OK)
	{
		wxString sql = wxString::Format	(_("UPDATE %s SET info ='%s', type ='%s', voltage='%s', power='%s' WHERE id = '%s'"),TABLE_BULB,ptr->GetInfo(),ptr->GetType(),ptr->GetVoltage(),ptr->GetPower(),id);
		my_query(sql);
		Clear();
		Read();
		Select();
	}

	delete ptr;
}


void CDialog::EditType(wxString id)
{
	wxString sql = wxString::Format(_("SELECT * FROM %s WHERE id = '%s'"),m_Table,id);
	
	if(!my_query(sql))
		return;
		
	CNew *ptr = new CNew(m_ControlType);
	
	void *result = db_result();
	char **row = (char**)db_fetch_row(result);
	
	ptr->SetType(Convert(row[FID_TYPE]));
	ptr->SetInfo(Convert(row[FID_INFO]));
	
	db_free_result(result);

	if(ptr->ShowModal() == wxID_OK)
	{
		wxString sql = wxString::Format	(_("UPDATE %s SET type= '%s', info ='%s' WHERE id = '%s'"),m_Table,ptr->GetType(),ptr->GetInfo(),id);
		my_query(sql);
		Clear();
		Read();
		Select();
	}

	delete ptr;
	
}


void CDialog::OnDelete(wxString id)
{
	

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