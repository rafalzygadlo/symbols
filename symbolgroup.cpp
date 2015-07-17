#include "symbolgroup.h"
#include "conf.h"
#include "tools.h"
#include "db.h"


BEGIN_EVENT_TABLE(CSymbolGroup, wxDialog)
	EVT_CHECKLISTBOX(ID_LIST, OnCheck)
END_EVENT_TABLE()

CSymbolGroup::CSymbolGroup(void *db, int id)
:wxDialog(NULL,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize)
{
	m_DB = db;
	m_ID = id;
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(Sizer);
		
	wxPanel *Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition);
	Sizer->Add(Panel,1,wxALL|wxEXPAND,5);
	wxBoxSizer *PanelSizer = new wxBoxSizer(wxVERTICAL);
	Panel->SetSizer(PanelSizer);
		
	m_List = new wxCheckListBox(Panel,ID_LIST);
	PanelSizer->Add(m_List,1,wxALL|wxEXPAND,0);
	
	wxPanel *Panel1 = new wxPanel(this);
	Sizer->Add(Panel1,0,wxALL|wxEXPAND,5);
	wxBoxSizer *Panel1Sizer = new wxBoxSizer(wxHORIZONTAL);
	Panel1->SetSizer(Panel1Sizer);

	Panel1Sizer->AddStretchSpacer();
		
	wxButton *ButtonClose = new wxButton(Panel1,wxID_OK,GetMsg(MSG_CLOSE));
	Panel1Sizer->Add(ButtonClose,0,wxALL,5);
			
	
	SetData();
	Center();
	
}

CSymbolGroup::~CSymbolGroup()
{

}


void CSymbolGroup::InitColumns()
{

/*	if(m_ColumnArray.size() == 0)
	{
		for(size_t i = 0; i < m_ColumnIds.size(); i++)
		{
			wxArrayString *Data = new wxArrayString();
			m_ColumnArray.Add(Data);
		}
	}
	*/
}

void CSymbolGroup::SetData()
{
	m_Id.Clear();
	
	wxString sql = wxString::Format(_("SELECT *FROM `%s`"),TABLE_SYMBOL_GROUP);

	if(!my_query(m_DB,sql))
		return;
	
	//int fields = db_field_count();
	void *result = db_result(m_DB);
	char **row;
	
	while(row = (char**)db_fetch_row(result))
	{
		wxString str(row[FI_SYMBOL_GROUP_NAME],wxConvUTF8);
		m_List->Append(str);
		m_Id.Add(row[FI_SYMBOL_GROUP_ID]);
		
	}
	
	db_free_result(result);


	sql = wxString::Format(_("SELECT *FROM `%s` WHERE id_symbol ='%d'"),TABLE_SYMBOL_TO_GROUP,m_ID);

	if(!my_query(m_DB,sql))
		return;
		
	result = db_result(m_DB);
	//char **row;
	
	while(row = (char**)db_fetch_row(result))
	{
		int gid = atoi(row[FI_SYMBOL_TO_GROUP_ID_GROUP]);
		
		for(size_t i = 0; i < m_Id.size(); i++)
		{
			long b;
			wxString a = m_Id.Item(i);
			a.ToLong(&b);
			if(gid == b)
				m_List->Check(i,true);
		}
				
	}
	db_free_result(result);

	
}

void CSymbolGroup::OnCheck(wxCommandEvent &event)
{
	//int event.gets
	wxString group_id = m_Id.Item(event.GetInt());
	wxString sql;
	if(m_List->IsChecked(event.GetInt()))
		sql = wxString::Format(_("INSERT INTO `%s` SET id_symbol = '%d', id_group = '%s'"),TABLE_SYMBOL_TO_GROUP, m_ID,group_id);
	else
		sql = wxString::Format(_("DELETE FROM `%s` WHERE id_symbol = '%d' AND id_group = '%s'"),TABLE_SYMBOL_TO_GROUP, m_ID,group_id);
	
	my_query(m_DB,sql);
		
}