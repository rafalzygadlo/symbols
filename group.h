#ifndef __GROUP
#define __GROUP

#include "conf.h"
#include "listitem.h"

class CGroup : public CListItem
{	
	int m_Type;
	wxString m_Name;
	bool m_New;
	bool m_Exists;
	bool m_Confirmed;

public:

	CGroup();
	//SET
	void SetName(wxString v);
	void SetNew(bool v);
				
	//GET
	wxString GetName();
	bool GetNew();
	

};


#endif