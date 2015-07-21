#include <wx/dateevt.h>
#include <wx/timectrl.h>
#include <wx/datectrl.h>
#include "graphdialog.h"
#include "conf.h"
#include "tools.h"
#include "db.h"

//BEGIN_EVENT_TABLE(CCommandDialog, wxDialog)
//END_EVENT_TABLE()

CGraphDialog::CGraphDialog(wxWindow *parent, CSymbol *ptr)
	:wxDialog(NULL,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	m_Graph = new CGraph(this);
	m_Graph->SetMinSize(wxSize(800,250));
	Sizer->Add(m_Graph,1,wxALL|wxEXPAND,5);
	Sizer->Add(GetButtonPanel(this),0,wxALL|wxEXPAND,5);
	SetSizer(Sizer);
	Fit();	
}

CGraphDialog::~CGraphDialog()
{
	
}

CGraph *CGraphDialog::GetGraph()
{
	return m_Graph;
}

wxPanel *CGraphDialog::GetButtonPanel(wxWindow *parent)
{

	wxPanel *Panel = new wxPanel(this);
	wxBoxSizer *Sizer = new wxBoxSizer(wxHORIZONTAL);
	Panel->SetSizer(Sizer);

	wxStaticText *LabelProductInfo = new wxStaticText(Panel,wxID_ANY,GetProductInfo() ,wxDefaultPosition,wxDefaultSize);
	Sizer->Add(LabelProductInfo,0,wxALL,5);
	Sizer->AddStretchSpacer(1);

	wxButton *ButtonClose = new wxButton(Panel,wxID_CANCEL,GetMsg(MSG_CLOSE));
	Sizer->AddStretchSpacer();
	Sizer->Add(ButtonClose,0,wxALL,2);
	
	return Panel;
}
