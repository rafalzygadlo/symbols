#ifndef __SYMBOL_H
#define __SYMBOL_H

#include <wx/html/htmlwin.h>
#include "ticker.h"
#include <gl/gl.h>
#include "navibroker.h"
#include "tgamem.h"
#include "picture.h"
#include "geometrytools.h"
#include "nvfastfont.h"
#include "nvtime.h"

class CSymbol
{
	void *m_DB;
	nvCircle m_Circle;
	CNaviBroker *m_Broker;
	CNaviArray <SOnOff> m_OnList;
	CNaviArray <nvPoint3f> m_PosBuffer;

	TTexture *m_TextureTGA_0;
	GLuint m_TextureID_0;
	nvFastFont *m_Font;
	bool m_FirstTime;
	int m_Step;
	bool m_Begin;
	int m_Id;
	bool m_LightOn;
	bool m_BusyOn;
	bool m_Busy;
	bool m_Alarm;
	bool m_AlarmOn;
	//pozycja referencyjna
	double m_RLon, m_RLat, m_RLonMap, m_RLatMap;
	//pozycja GPS
	double m_Lon, m_Lat, m_LonMap, m_LatMap;
	double m_Scale;
	double m_SmoothScaleFactor;
	double m_RectWidth;
	double m_RectHeight;
	double m_TranslationX;
	double m_TranslationY;
	double m_VisibleMap[4];
	bool m_TickExit;
	int m_CommandTick;
	int	m_CommandTickOn;
	int m_PositionsTick;
	int m_ReportTick;
	int m_ReadTick;
	int m_CollisionTick;
	int m_AlarmTick,m_AlarmTickOn;
	int m_IdSBMS;
	int m_SBMSID;
	int m_IdBaseStation;
	bool m_RenderRestricted;
	bool m_Selected;
	int m_AlarmCount;
	int m_ReportCount;
	wxString m_Name;
	wxString m_Number;
	bool m_Exists;
	bool m_ForcedOff;
	bool m_PhotoCellNightTime;
	int m_CommandCount;
	int m_MMSI;
	nvtime_t m_nvTime;
	int m_Timestamp;
	int m_Age;
	wxString m_AgeString;
	bool m_InMonitoring;
		
	void CSymbol::SetColor(int id);
	void CreateSymbol(void *MemoryBlock,long MemoryBlockSize);
	void CreateTexture(TTexture *Texture, GLuint *TextureID);
	void CreateTextures(void);
	bool CheckCommand();
	bool CheckAlarm();
	bool CheckCollision();
	bool CheckReport();
	bool SetPositions();
	void SetValues();
	void SetSmoothScaleFactor(double v);
	void Read();
	void RenderSymbol();
	void RenderLightOn();
	void RenderBusy();
	void RenderRestricted();
	void RenderAlarm();
	void RenderGPS();		//real position
	void RenderPositions();
	void RenderSelected();
			
public:

	CSymbol(CNaviBroker *broker,nvFastFont *font);
	~CSymbol();

	void OnTick(void *db);
	void OnTickExit();
	void SetId(int v);
	//pozycja referencyjna
	void SetRLon(double v);	void SetRLat(double v);	void SetRLonMap(double v);	void SetRLatMap(double v);
	
	void SetIdSBMS(int v);
	void SetSBMSID(int v);
	//void SetBaseStationId();
	void SetNumber(wxString v);
	void SetInMonitoring(bool v);
	void SetName(wxString v);
	void SetRemove(bool v);
	void SetDB(void *db);
	void SetForcedOff(bool v);
	void SetPhotoCellNightTime(bool v);
	void SetLightOn(bool v);
	void SetMMSI(int v);
	void SetNvTime(nvtime_t dt);
	void SetLon(double v);
	void SetLat(double v);
	void SetLonMap(double v);
	void SetLatMap(double v);
	void SetTimestamp(int v);
	void SetAge(int v);
	void SetAge(wxString v);
	
	int GetId();
	int GetIdSBMS();
	int GetSBMSID();
	int GetBaseStationId();
	//pozycja referencyjna
	double GetRLon();	double GetRLat();	double GetRLonMap();	double GetRLatMap();
	bool GetBusy();					//zajêty komendami
	int GetAlarmCount();
	wxString GetName();
	wxString GetNumber();
	bool GetExists();
	bool GetLightOn();
	int GetMMSI();
	nvtime_t GetNvTime();
	int GetAge();
	wxString GetAgeAsString();
	wxString GetReportCountAsString();
	wxString GetCommandCountAsString();
	
	
	void Render();

};

#endif