#include "item.h"
#include "conf.h"
#include "tools.h"
#include "listctrl.h"
#include "db.h"
#include <wx/mstream.h>
#include <wx/dataview.h>
#include "images/del.img"

extern unsigned int	add_size;
extern unsigned char add[]; 

CItemPanel::CItemPanel(wxWindow *top, wxWindow *parent)
	:wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize)
{
	m_Top = top;
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
		
	wxString sql = wxString::Format(_("SELECT * FROM `%s` ORDER BY name"),TABLE_ITEM_TYPE);
	Read(sql);
			
	for(size_t i = 0; i < m_Items.size(); i++)
	{
		CItem *ptr = (CItem*)m_Items.Item(i);
		Sizer->Add(ptr,0,wxALL|wxEXPAND,1);

	}

	
	SetSizer(Sizer);
				
}

CItemPanel::~CItemPanel()
{
	
}

void CItemPanel::_Layout()
{
	m_Top->Layout();
}

wxArrayPtrVoid CItemPanel::GetItems()
{
	return m_Items;
}

void CItemPanel::Read(wxString query)
{
	if(!my_query(query))
		return;
	
	int rows = 0;
	void *result = db_result();
	char **row;
	
	while(row = (char**)db_fetch_row(result))
	{
		wxString str(row[0],wxConvUTF8);
		wxString name(row[1],wxConvUTF8);
		CItem *Item = new CItem(this,name);
		Item->_SetId(str);
		m_Items.Add(Item);
	}

	db_free_result(result);
	
}

BEGIN_EVENT_TABLE(CItem, wxPanel)
	EVT_BUTTON(ID_DELETE,CItem::OnDelete)
	EVT_BUTTON(ID_NEW,CItem::OnNew)
END_EVENT_TABLE()

CItem::CItem(CItemPanel *parent,wxString name)
	:wxPanel(parent,wxID_ANY,wxDefaultPosition)
{
	m_Counter = 1;
	m_ItemPanel = parent;
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	SetSizer(Sizer);
	
	this->SetWindowStyle(wxBORDER_SIMPLE);
	wxMemoryInputStream in_1((const unsigned char*)add,add_size);
    wxImage myImage_1(in_1, wxBITMAP_TYPE_PNG);

	wxBoxSizer *HSizer = new wxBoxSizer(wxHORIZONTAL);
	Sizer->Add(HSizer,0,wxALL|wxEXPAND,5);
	
	m_Name = new wxStaticText(this,wxID_ANY,wxEmptyString);
	m_Name->SetLabel(name);
	HSizer->Add(m_Name,0,wxALL,1);
	HSizer->AddStretchSpacer(1);
	wxButton *New = new wxBitmapButton(this,ID_NEW,wxBitmap(myImage_1));
	HSizer->Add(New,0,wxALL|wxALIGN_RIGHT,1);
	
	//AppendCombo();
}

CItem::~CItem()
{

}
void CItem::AppendCombo()
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxHORIZONTAL);
	this->GetSizer()->Add(Sizer,0,wxALL|wxEXPAND,2);
	
	wxStaticText *LabelNumber = new wxStaticText(this,wxID_ANY,wxString::Format(_("%d"),m_Counter));
	Sizer->Add(LabelNumber,0,wxALL,2);
	
	wxComboBox *Combo = new wxComboBox(this,wxID_ANY,wxEmptyString);
	Sizer->Add(Combo,1,wxALL,2);
	
	wxMemoryInputStream in_1((const unsigned char*)del,del_size);
    wxImage myImage_1(in_1, wxBITMAP_TYPE_PNG);

	wxButton *Delete = new wxBitmapButton(this,ID_DELETE,wxBitmap(myImage_1));
	Sizer->Add(Delete,0,wxALL,2);

	wxString sql = wxString::Format(_("SELECT * FROM `%s` WHERE id_type = '%s'"),TABLE_ITEM,m_Id);
	Read(sql,0,Combo);

	m_ItemPanel->_Layout();
	m_Counter++;

}

void CItem::Read(wxString query, int field, wxComboBox *combo)
{
	if(!my_query(query))
		return;
	
	int rows = 0;
	void *result = db_result();
	char **row;
	
	while(row = (char**)db_fetch_row(result))
	{
		wxString str(row[field],wxConvUTF8);
		combo->Append(str);
	}

	db_free_result(result);
	
}

void CItem::OnDelete(wxCommandEvent &event)
{
	m_Counter--;
}

void CItem::OnNew(wxCommandEvent &event)
{
	AppendCombo();
}

wxString CItem::_GetId()
{
	return m_Id;
}


void CItem::_SetId(wxString v)
{
	m_Id = v;
}

void CItem::_SetName(wxString v)
{
	m_Name->SetLabel(v);
}
