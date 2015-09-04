#ifndef __ALARM
#define __ALARM

#include "conf.h"

class CAlarm
{	
	int m_Id;
	wxString m_Name;
	
public:

	CAlarm();
	//SET
	void SetId(int v);
	void SetName(wxString v);

	//GET
	int GetId();
	wxString GetName();

};



#endif