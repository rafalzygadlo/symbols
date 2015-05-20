#include <wx/dateevt.h>
#include <wx/timectrl.h>
#include <wx/datectrl.h>
#include "commanddialog.h"
#include "commandpanel.h"
#include "conf.h"
#include "tools.h"
#include "db.h"

//BEGIN_EVENT_TABLE(CCommandDialog, wxDialog)
//END_EVENT_TABLE()

CCommandDialog::CCommandDialog(wxWindow *parent, CSymbol *ptr)
	:wxDialog(NULL,wxID_ANY,wxEmptyString)
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	CCommandPanel *CommandPanel = new CCommandPanel(this);
	CommandPanel->SetSelectedPtr(ptr);
	Sizer->Add(CommandPanel,1,wxALL|wxEXPAND,5);
	
	Sizer->Add(GetButtonPanel(this),0,wxALL|wxEXPAND,5);
		

	SetSizer(Sizer);
	Fit();	
}

CCommandDialog::~CCommandDialog()
{
	
}

wxPanel *CCommandDialog::GetButtonPanel(wxWindow *parent)
{

	wxPanel *Panel = new wxPanel(this);
	wxBoxSizer *Sizer = new wxBoxSizer(wxHORIZONTAL);
	Panel->SetSizer(Sizer);	
	wxButton *ButtonClose = new wxButton(Panel,wxID_CANCEL,GetMsg(MSG_CLOSE));
	Sizer->AddStretchSpacer();
	Sizer->Add(ButtonClose,0,wxALL,2);
	
	return Panel;
}
