#ifndef __FILTER_H
#define __FILTER_H

#include "conf.h"

class CFilterDialog: public wxDialog
{
	wxButton *m_ButtonSelect;
	//wxCheckBox *m_CheckInMonitoring;
	wxComboBox *m_ComboLight;
	wxComboBox *m_ComboInMonitoring;
	
	wxCheckListBox *m_ComboArea;
	wxCheckListBox *m_ComboSeaway;
	wxCheckListBox *m_ComboSymbolType;
	wxCheckListBox *m_ComboGroup;
	wxCheckListBox *m_ComboAlarm;
	
	wxCheckListBox *m_ComboBaseStation;

	void SetGui();
	void Set(int id, bool checked);
	wxPanel *GetPanel(void *db,wxWindow *Parent);
	wxPanel *GetAlarmPanel(void *db,wxWindow *Parent);
	wxPanel *GetGroupPanel(void *db,wxWindow *Parent);
	wxPanel *GetButtonPanel(wxWindow *parent);
	

public:

	CFilterDialog();
	~CFilterDialog();
	int GetAreaId();
	int GetSymbolTypeId();
	int GetSeawayId();
	int GetInMonitoring();
	int GetGroupId();
	int GetLight();
	int GetBaseStationId();
	int GetAlarmId();
	
	void SetAreaId(int v);
	void SetSymbolTypeId(int v);
	void SetSeawayId(int v);
	void SetBaseStationId(int v);
	void SetInMonitoring(int v);
	void SetLight(int v);
	void SetGroupId(int v);
	void SetAlarmId(int v);
	
	DECLARE_EVENT_TABLE();

	enum
	{
		ID_FILTER_BEGIN = 1300,
		ID_SELECT_ALL,
		ID_DESELECT_ALL,
	};
	

};


#endif