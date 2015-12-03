#ifndef __ALTERDIALOG
#define __ALTERDIALOG

#include "conf.h"

class CAlterDialog: public wxDialog
{
	wxTextCtrl *m_RootPassword;
	wxTextCtrl *m_Log;

	wxPanel *GetButtonPanel(wxWindow *parent);
	wxPanel *GetPanel(wxWindow *parent);
	void OnAlter(wxCommandEvent &event);

public:

	CAlterDialog();
	~CAlterDialog();
	
	DECLARE_EVENT_TABLE();

	enum
	{
		ID_ALTER = 1000	
	};
		
};


#endif
