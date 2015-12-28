#ifndef __COMMAND_DIALOG_H
#define __COMMAND_DIALOG_H

#include <wx/wx.h>
#include <wx/hyperlink.h>
#include "conf.h"
#include "symbol.h"
#include "commandpanel.h"

class CCommandDialog: public wxDialog
{
	CCommandPanel *m_CommandPanel;
	wxPanel *GetButtonPanel(wxWindow *parent);

public:

	CCommandDialog(void *db,wxWindow *parent,CSymbol *ptr);
	~CCommandDialog();
	CCommandPanel *GetCommandPanel();
	
};


#endif