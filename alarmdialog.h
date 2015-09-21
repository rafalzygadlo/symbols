#ifndef __ALARMDIALOG
#define __ALARMDIALOG

#include <wx/wx.h>
#include <wx/htmllbox.h>
#include "conf.h"
#include "symbol.h"
#include "alarmlist.h"

class CSymbol;
class CAlarmList;
class CAlarmDialog: public wxDialog
{
	wxArrayPtrVoid *m_List;
	CAlarmList *m_TextAlarm;
	wxString m_Html;
	int m_Count;
	bool m_New;

	wxPanel *GetPanel(wxWindow *parent);
	void OnSetAlarm(wxCommandEvent &event);
	void OnOk(wxCommandEvent &event);
		
public:

	CAlarmDialog();
	~CAlarmDialog();
	void Set(wxArrayPtrVoid *v);
	void ShowWindow();
	void SetNew(bool v);
	
	DECLARE_EVENT_TABLE();
		
	enum
	{
		ID_CONFIRM = 3412,
		ID_ALARM,
		ID_OK,
	};

};



#endif