#ifndef __GROUP
#define __GROUP

#include "conf.h"

class CGroup
{	
	int m_Id;
	int m_Type;
	wxString m_Name;
	bool m_New;
	bool m_Exists;
	bool m_Confirmed;

public:

	CGroup();
	//SET
	void SetId(int v);
	void SetName(wxString v);
	void SetNew(bool v);
	void SetExists(bool v);
			
	//GET
	int GetId();
	wxString GetName();
	bool GetNew();
	bool GetExists();

};


#endif