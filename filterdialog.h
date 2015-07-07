#ifndef __FILTER_H
#define __FILTER_H

#include "conf.h"

class CFilterDialog: public wxDialog
{
	wxButton *m_ButtonSelect;
	void Set(int id, bool checked);
	wxPanel *GetPanel(wxWindow *Parent);
	wxComboBox *m_ComboArea;
	wxComboBox *m_ComboSeaway;
	wxComboBox *m_ComboSymbolType;

public:

	CFilterDialog();
	~CFilterDialog();
	int GetAreaId();
	int GetSymbolTypeId();
	int GetSeawayId();

	DECLARE_EVENT_TABLE();

	enum
	{
		ID_FILTER_BEGIN = 5213,
		ID_SELECT_ALL,
		ID_DESELECT_ALL,
	};
	

};


#endif