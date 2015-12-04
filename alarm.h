#ifndef __ALARM
#define __ALARM

#include "conf.h"

//definicja ALARMÓW
#define ALARM_OFFSET                            127     //dla alarmów z serwera
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


class CAlarm
{	
	int m_Id;
	int m_IdAlarm;
	int m_Type;
	wxString m_Name;
	wxString m_SymbolName;
	wxString m_AlarmOnDate;
	wxString m_AlarmOffDate;
	wxString m_UserFirstName;
	wxString m_UserLastName;
	bool m_New;
	bool m_Exists;
	bool m_Confirmed;

public:

	CAlarm();
	//SET
	void SetId(int v);
	void SetIdAlarm(int v);
	void SetName(wxString v);
	void SetSymbolName(wxString v);
	void SetNew(bool v);
	void SetExists(bool v);
	void SetConfirmed(bool v);
	void SetType(int v);
	void SetAlarmOnDate(wxString v);
	void SetUserFirstName(wxString v);
	void SetUserLastName(wxString v);
			
	//GET
	int GetId();
	int GetIdAlarm();
	wxString GetName();
	wxString GetSymbolName();
	bool GetNew();
	bool GetExists();
	bool GetConfirmed();
	int GetType();
	wxString GetAlarmOnDate();
	wxString GetUserFirstName();
	wxString GetUserLastName();
	

};



#endif