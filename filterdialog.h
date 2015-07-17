#ifndef __FILTER_H
#define __FILTER_H

#include "conf.h"

class CFilterDialog: public wxDialog
{
	wxButton *m_ButtonSelect;
	//wxCheckBox *m_CheckInMonitoring;
	wxComboBox *m_ComboGroup;
	wxComboBox *m_ComboArea;
	wxComboBox *m_ComboSeaway;
	wxComboBox *m_ComboInMonitoring;
	wxComboBox *m_ComboSymbolType;
	
	void Set(int id, bool checked);
	wxPanel *GetPanel(wxWindow *Parent);
	wxPanel *GetButtonPanel(wxWindow *parent);
	

public:

	CFilterDialog();
	~CFilterDialog();
	int GetAreaId();
	int GetSymbolTypeId();
	int GetSeawayId();
	int GetInMonitoring();
	int GetGroupId();

	void SetAreaId(int id);
	void SetSymbolTypeId(int id);
	void SetSeawayId(int id);
	void SetInMonitoring(int v);
	void SetGroupId(int id);


	DECLARE_EVENT_TABLE();

	enum
	{
		ID_FILTER_BEGIN = 1300,
		ID_SELECT_ALL,
		ID_DESELECT_ALL,
	};
	

};


#endif