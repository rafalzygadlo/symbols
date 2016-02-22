#ifndef __FILTER
#define __FILTER

#include "conf.h"

class CFilterDialog: public wxDialog
{
	wxButton *m_ButtonSelect;
	//wxCheckBox *m_CheckInMonitoring;
	//wxComboBox *m_ComboGroup;
	wxComboBox *m_ComboLight;
	wxComboBox *m_ComboArea;
	wxComboBox *m_ComboSeaway;
	wxComboBox *m_ComboMonitoring;
	wxComboBox *m_ComboBaseStation;
	wxComboBox *m_ComboSymbolType;
	wxComboBox *m_ComboAlarm;
	
	void Set(int id, bool checked);
	wxPanel *GetPanel(wxWindow *Parent);
	wxPanel *GetButtonPanel(wxWindow *parent);
	

public:

	CFilterDialog();
	~CFilterDialog();
	int GetAreaId();
	int GetSymbolTypeId();
	int GetSeawayId();
	int GetMonitoring();
	//int GetGroupId();
	int GetLight();
	int GetBaseStationId();
	int GetAlarmId();
	
	void SetAreaId(int v);
	void SetSymbolTypeId(int v);
	void SetSeawayId(int v);
	void SetBaseStationId(int v);
	void SetMonitoring(int v);
	void SetLight(int v);
	//void SetGroupId(int v);
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