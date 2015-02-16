#include "command.h"
#include "conf.h"
#include "tools.h"
#include "db.h"

BEGIN_EVENT_TABLE(CCommandPanel, wxPanel)
	//EVT_HYPERLINK(ID_NEW,CCommandPanel::OnNew)
	//EVT_HYPERLINK(ID_PICK,CCommandPanel::OnPick)
END_EVENT_TABLE()

CCommandPanel::CCommandPanel(void *db,wxWindow *parent)
	:wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize)
{
	m_DB = db;
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	m_Sizer = new wxStaticBoxSizer(wxVERTICAL,this,GetMsg(MSG_COMMAND));
	Sizer->Add(m_Sizer,1,wxALL|wxEXPAND,5);
	SetSizer(m_Sizer);
	SetGui();
	Refresh();
	Layout();
}

CCommandPanel::~CCommandPanel()
{

}

void CCommandPanel::SetGui()
{
	
	wxFlexGridSizer *FlexSizer = new wxFlexGridSizer(2);
	FlexSizer->AddGrowableCol(1,1);
	m_Sizer->Add(FlexSizer,1,wxALL|wxEXPAND,5);
	
	wxStaticText *LabelPowerOfLight = new wxStaticText(this,wxID_ANY,GetMsg(MSG_POWER_OF_LIGHT));
	FlexSizer->Add(LabelPowerOfLight,0,wxALL,2);
	
	m_PowerOfLight = new wxSlider(this,wxID_ANY,0,0,1,wxDefaultPosition,wxDefaultSize);
	FlexSizer->Add(m_PowerOfLight,0,wxALL,2);
	m_PowerOfLight->SetMin(50);
	m_PowerOfLight->SetMax(200);
	//m_FontSize->SetValue(GetFontSize() * 10);
		
}