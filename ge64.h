#ifndef __GE64
#define __GE64

#include <gl/gl.h>
#include "geometrytools.h"
#include "nvfastfont.h"
#include "driver.h"
#include "navibroker.h"
#include "alarm.h"
#include "list.h"

class CGE64 :public CDriver
{
	CNaviBroker *m_Broker;
	void *m_DB;
	bool m_NightMode;
	bool m_MainLampOn;
	bool m_SecondLampOn;
	bool m_GeneratorOn;
	bool m_ManualOn;
	double m_Scale;
	double m_SmoothScaleFactor;
	double m_VisibleMap[4];
	double m_RectWidth;
	double m_RectHeight;
	double m_TranslationX;
	double m_TranslationY;
	bool m_AlarmOn;
	bool m_Alarm;
	//pozycja gps lub referencyjna
	double m_Lon, m_Lat, m_LonMap, m_LatMap;
	CList m_AlarmList;

	void ClearAlarms();
	bool CheckAlarm();
	void SetAlarms();
	void SetSmoothScaleFactor(double v);
	void SetValues();
	void SetColor(int id);
	void SetSymbolColor();
	
	void RenderAlarm();
	void RenderGE64();
	void Render() override;
	
public:

	CGE64(void *db,CNaviBroker *broker);
	~CGE64();

	void ShowAction() override;
	void Read() override;

	//GET
	bool GetNightMode();
	bool GetMainLampOn();
	bool GetSecondLampOn();
	bool GetGeneratorOn();
	bool GetManualOn();
	int GetAlarmCount();
	CAlarm *GetAlarm(int v);
	wxString GetDriverHtml(int v) override;
	wxString GetDriverFullHtml() override;
	wxString GetAlarmHtml() override;
	
	
	//SET
	void SetNightMode(bool v);
	void SetMainOn(bool v);
	void SetSecondLampOn(bool v);
	void SetGeneratorOn(bool v);
	void SetManualOn(bool v);
	//referencyjna lub Gps
	void SetLon(double v) override;		
	void SetLat(double v) override;		
	void SetLonMap(double v) override;		
	void SetLatMap(double v) override;
		

};

#endif