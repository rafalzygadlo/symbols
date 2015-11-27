#include <wx/dateevt.h>
#include <wx/timectrl.h>
#include <wx/datectrl.h>
#include <wx/statline.h>
#include "commanddialog.h"
#include "commandpanel.h"
#include "conf.h"
#include "tools.h"
#include "db.h"

CCommandDialog::CCommandDialog(wxWindow *parent, CSymbol *ptr)
	:wxDialog(NULL,wxID_ANY, ptr->GetName())
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	m_CommandPanel = new CCommandPanel(this);
	m_CommandPanel->SetSelectedPtr(ptr);
	m_CommandPanel->Set();
	Sizer->Add(m_CommandPanel,1,wxALL|wxEXPAND,2);
	
	wxStaticLine *line = new wxStaticLine(this,wxID_ANY);
	Sizer->Add(line,0,wxALL|wxEXPAND,0);

	Sizer->Add(GetButtonPanel(this),0,wxALL|wxEXPAND,5);
	
	SetSizer(Sizer);
	Fit();
	Center();
}

CCommandDialog::~CCommandDialog()
{
	
}

CCommandPanel *CCommandDialog::GetCommandPanel()
{
	return m_CommandPanel;
}

wxPanel *CCommandDialog::GetButtonPanel(wxWindow *parent)
{

	wxPanel *Panel = new wxPanel(this);
	wxBoxSizer *Sizer = new wxBoxSizer(wxHORIZONTAL);
	Panel->SetSizer(Sizer);	
	
	wxStaticText *LabelProductInfo = new wxStaticText(Panel,wxID_ANY,GetProductInfo() ,wxDefaultPosition,wxDefaultSize);
	Sizer->Add(LabelProductInfo,0,wxALL,5);
	Sizer->AddStretchSpacer(1);
	
	wxButton *ButtonClose = new wxButton(Panel,wxID_CANCEL,GetMsg(MSG_CLOSE));
	Sizer->AddStretchSpacer();
	Sizer->Add(ButtonClose,0,wxALL,5);
	
	return Panel;
}
