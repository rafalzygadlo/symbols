#ifndef __ALARM
#define __ALARM

#include "conf.h"
#include "listItem.h"

//definicja ALARM�W
#define ALARM_OFFSET                            127     //dla alarm�w z serwera
//Alarmy SBMS
#define ALARM_OPENING_MAIN_FLAP			0
#define ALARM_POWER_SUPPLY_FAULT		1
#define ALARM_IMPACT_DETECTED			2

//alarmy tylko z SBMSA beda
//ALarmy Serwer
#define ALARM_OFF_POSITION                      ALARM_OFFSET + 1
#define ALARM_COMMUNICATION_TIMEOUT             ALARM_OFFSET + 2
#define ALARM_LOW_VOLTAGE                       ALARM_OFFSET + 3
#define ALARM_HIGH_VOLTAGE                      ALARM_OFFSET + 4

#define ALARM_TYPE_WARNING	0
#define ALARM_TYPE_ALARM	1


class CAlarm : public CListItem
{	
	int m_IdAlarm;
	int m_Type;
	wxString m_Name;
	wxString m_SymbolName;
	wxString m_AlarmOnDate;
	wxString m_AlarmOffDate;
	wxString m_UserFirstName;
	wxString m_UserLastName;
	bool m_New;
	bool m_Confirmed;
	int m_DriverType;

public:

	CAlarm();
	//SET
	void SetIdAlarm(int v);
	void SetName(wxString v);
	void SetSymbolName(wxString v);
	void SetNew(bool v);
	void SetDriverType(int v);
	void SetConfirmed(bool v);
	void SetType(int v);
	void SetAlarmOnDate(wxString v);
	void SetUserFirstName(wxString v);
	void SetUserLastName(wxString v);
			
	//GET
	int GetIdAlarm();
	wxString GetName();
	wxString GetSymbolName();
	bool GetNew();
	//bool GetExists();
	bool GetConfirmed();
	int GetType();
	int GetDriverType();
	wxString GetAlarmOnDate();
	wxString GetUserFirstName();
	wxString GetUserLastName();
	

};



#endif