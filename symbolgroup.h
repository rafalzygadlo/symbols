#ifndef __USER_GROUP_H
#define __USER_GROUP_H

#include <wx/wx.h>


class CSymbolGroup: public wxDialog
{
	void *m_DB;
	wxTextCtrl *m_TextInfo;
	int m_ID;

	wxArrayString m_Id;
	wxCheckListBox *m_List;

	void InitColumns();
	void SetData();
	void OnCheck(wxCommandEvent &event);

public:

	CSymbolGroup(void *db,int id);
	~CSymbolGroup();
	
	
	enum
	{
		ID_LIST

	};
	
	DECLARE_EVENT_TABLE()

};

#endif