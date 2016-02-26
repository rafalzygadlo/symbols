#ifndef __DRIVER
#define __DRIVER

#include <wx/wx.h>
#include "control.h"
#include "nvfastfont.h"

#define DRIVER_TYPE_SBMS	0
#define DRIVER_TYPE_GE64	1

class CDriver
{
	int m_Id;
	int m_Type;
	bool m_Exists;
	wxString m_Name;
	wxString m_SymbolName;

public:

	CDriver();
	virtual ~CDriver();
	//SET
	void SetName(wxString v);
	void SetSymbolName(wxString v);
	void SetType(int v);
	void SetId(int v);
	void SetExists(bool v);
	
	//GET
	wxString GetName();
	wxString GetSymbolName();
	int GetType();
	int GetId();
	bool GetExists();
	
	virtual void Read();
	virtual void Render();
	
	//SBMS
	//SET
	virtual void SetIdBaseStation(int v);
	virtual void SetMMSI(int v);
	virtual void SetForcedOff(int v);
	virtual void SetLightOn(int v);
	virtual void SetInputVolt(float v);
	virtual void SetIdSymbol(int v);
	virtual void SetFont(nvFastFont *v);
	virtual void SetSBMSID(int v);

	virtual void SetLon(double v);
	virtual void SetLat(double v);
	virtual void SetLonMap(double v);
	virtual void SetLatMap(double v);
	
	virtual void SetGpsLon(double v);
	virtual void SetGpsLat(double v);
	virtual void SetGpsLonMap(double v);
	virtual void SetGpsLatMap(double v);

	virtual void SetRLon(double v);
	virtual void SetRLat(double v);
	virtual void SetRLonMap(double v);
	virtual void SetRLatMap(double v);
		
	virtual void SetDB(void *v);
	virtual void SetAge(int v);
	virtual void SetAge(wxString v);
	virtual void SetTimestamp(int v);
	virtual void SetAuto(bool v);
	virtual void SetCharging(bool v);
	virtual void SetNewReport(bool v);
	virtual void UnsetNewReport();

	//GET
	virtual int GetBaseStationId();
	virtual wxString GetDriverHtml(int v);
	virtual wxString GetDriverFullHtml();
	virtual wxString GetAlarmHtml();
	
	virtual float GetInputVolt();
	virtual double GetGpsLon();
	virtual double GetGpsLat();
	virtual double GetGpsLonMap();
	virtual double GetGpsLatMap();
	virtual int GetMMSI();
	virtual int GetSBMSID();
	virtual int GetCharging();
	
		
	virtual void ShowGraph();
	virtual void ShowAction();
};

#endif