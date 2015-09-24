#ifndef __DATEDIALOG
#define __DATEDIALOG

#include <wx/wx.h>
#include <wx/datectrl.h>

class CDateDialog :public wxDialog
{
	wxDatePickerCtrl *m_From, *m_To;
		
public:
	
	CDateDialog();
	wxDateTime GetFrom();
	wxDateTime GetTo();
	

};

#endif
