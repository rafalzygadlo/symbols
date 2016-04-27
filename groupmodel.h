#ifndef __GROUPMODEL
#define __GROUPMODEL

#include "conf.h"
#include "listitem.h"

class CGroupModel : public CListItem
{	
	int m_Type;
	int m_Count;
	int m_ItemCount;
	wxString m_Name;
	bool m_New;
	bool m_Exists;
	bool m_Confirmed;
	wxString m_Code;


public:

	CGroupModel();
	//SET
	void SetName(wxString v);
	void SetNew(bool v);
	void SetItemCount(int v);
	void SetCode(wxString v);
				
	//GET
	wxString GetName();
	bool GetNew();
	int GetItemCount();
	wxString GetCode();
	

};


#endif