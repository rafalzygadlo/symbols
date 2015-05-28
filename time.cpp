#include "time.h"
#include "conf.h"
#include "tools.h"
#include "db.h"
#include "images/del.img"
#include "images/add.img"
#include <wx/mstream.h>
#include <wx/valnum.h>

extern unsigned int	add_size;
extern unsigned char add[]; 
extern unsigned int	del_size;
extern unsigned char del[]; 

BEGIN_EVENT_TABLE(CTimePanel, wxPanel)
	EVT_BUTTON(ID_NEW,CTimePanel::OnNew)
END_EVENT_TABLE()
CTimePanel::CTimePanel(void *db,wxWindow *top, wxWindow *parent)
	:wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize)
{
	m_DB = db;
	m_Top = top;
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	SetSizer(Sizer);
	
	wxMemoryInputStream in_1((const unsigned char*)add,add_size);
    wxImage myImage_1(in_1, wxBITMAP_TYPE_PNG);
	wxButton *New = new wxBitmapButton(this,ID_NEW,wxBitmap(myImage_1));
	Sizer->Add(New,0,wxALL,1);

	m_Sizer = new wxBoxSizer(wxVERTICAL);
	Sizer->Add(m_Sizer,1,wxALL|wxEXPAND,0);
			
}

CTimePanel::~CTimePanel()
{
	
}

size_t CTimePanel::GetCount()
{
	return m_List.size();
}

CTime *CTimePanel::GetTime(int id)
{
	return (CTime*)m_List.Item(id);
}

void CTimePanel::OnNew(wxCommandEvent &event)
{
	CTime *ptr = new CTime(this);
	AppendPanel(ptr);
}
void CTimePanel::OnDelete(CTime *panel)
{
	RemovePanel(panel);
}

void CTimePanel::AppendPanel(CTime *light)
{
	m_List.Add(light);
	m_Sizer->Add(light,1,wxALL|wxEXPAND,1);
	m_Top->Layout();
}

void CTimePanel::RemovePanel(CTime *panel)
{
	m_Sizer->Detach(panel);
	delete panel;
	m_List.Remove(panel);
	m_Top->Layout();
}

wxArrayPtrVoid CTimePanel::GetItems()
{
	return m_List;
}

void CTimePanel::Read(wxString query)
{
	if(!my_query(m_DB,query))
		return;
	
	int rows = 0;
	void *result = db_result(m_DB);
	char **row;
	
	while(row = (char**)db_fetch_row(result))
	{
		wxString str(row[0],wxConvUTF8);
		wxString name(row[1],wxConvUTF8);
		//CItem *Item = new CItem(this,name);
		//Item->_SetId(str);
		//m_Items.Add(Item);
	}

	db_free_result(result);
	
}

BEGIN_EVENT_TABLE(CTime, wxPanel)
	EVT_BUTTON(ID_DELETE,CTime::OnDelete)
END_EVENT_TABLE()

CTime::CTime(CTimePanel *parent)
	:wxPanel(parent,wxID_ANY,wxDefaultPosition)
{
	m_Panel = parent;

	wxFloatingPointValidator<float> Validator;
	Validator.SetStyle(wxFILTER_INCLUDE_CHAR_LIST);
	Validator.SetMin(CHARACTERISTIC_MIN);
	Validator.SetMax(CHARACTERISTIC_MAX);
	Validator.SetPrecision(CHARACTERISTIC_PRECISION);
	
	wxTextValidator TextValidator;
	TextValidator.SetStyle(wxFILTER_EXCLUDE_CHAR_LIST);
	TextValidator.SetCharExcludes(_("'\"\\;?"));
		
	wxStaticBoxSizer *Sizer = new wxStaticBoxSizer(wxVERTICAL,this,GetMsg(MSG_TIME));
	SetSizer(Sizer);

	//wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	//SetSizer(Sizer);
		
	wxMemoryInputStream in_1((const unsigned char*)del,del_size);
    wxImage myImage_1(in_1, wxBITMAP_TYPE_PNG);
	wxFlexGridSizer *FlexSizer = new wxFlexGridSizer(5);
	Sizer->Add(FlexSizer,1,wxALL|wxEXPAND,0);
					
	wxStaticText *LabelFrom = new wxStaticText(this,wxID_ANY,GetMsg(MSG_TIME_ON));
	FlexSizer->Add(LabelFrom,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	m_TextOn = new wxTextCtrl(this,wxID_ANY);
	m_TextOn->SetValidator(Validator);
	m_TextOn->SetValue(wxString::Format(_("%4.2f"),CHRACTERISTIC_ON_DEFAULT_VALUE));
	FlexSizer->Add(m_TextOn,0,wxALL,2);
	
	wxStaticText *LabelSectorTo = new wxStaticText(this,wxID_ANY,GetMsg(MSG_TIME_OFF));
	FlexSizer->Add(LabelSectorTo,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	m_TextOff = new wxTextCtrl(this,wxID_ANY);
	m_TextOff->SetValue(wxString::Format(_("%4.2f"),CHRACTERISTIC_OFF_DEFAULT_VALUE));
	m_TextOff->SetValidator(Validator);
	FlexSizer->Add(m_TextOff,0,wxALL,2);
	
	wxButton *Del = new wxBitmapButton(this,ID_DELETE,wxBitmap(myImage_1));
	FlexSizer->Add(Del,0,wxALL,2);
		
}

CTime::~CTime()
{

}

void CTime::OnDelete(wxCommandEvent &event)
{
	m_Panel->OnDelete(this);
}

wxString CTime::_GetId()
{
	return m_Id;
}

void CTime::_SetId(wxString v)
{
	m_Id = v;
}

void CTime::SetOn(float v)
{
	m_TextOn->SetValue(wxString::Format(_("%4.2f"),v));
}

void CTime::SetOff(float v)
{
	m_TextOff->SetValue(wxString::Format(_("%4.2f"),v));
}

float CTime::GetOn()
{
	double v;
	m_TextOn->GetValue().ToCDouble(&v);
	return v;
}

float CTime::GetOff()
{
	double v;
	m_TextOff->GetValue().ToCDouble(&v);
	return v;
}
