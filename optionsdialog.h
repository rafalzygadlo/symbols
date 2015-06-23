#ifndef __OPTIONS_DIALOG_H
#define __OPTIONS_DIALOG_H

#include <wx/wx.h>
#include <wx/spinctrl.h>
#include "conf.h"

class COptionsDialog: public wxDialog
{

	wxSpinCtrl *m_NumberOfTries;
	wxSpinCtrl *m_SecondsBetweenTries;
	wxPanel *GetButtonPanel(wxWindow *parent);

public:

	COptionsDialog();
	~COptionsDialog();
	
};


#endif