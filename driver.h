#ifndef __DRIVER_H
#define __DRIVER_H
#include <wx/wx.h>
#include "nvfastfont.h"

#define DRIVER_TYPE_SBMS	0
#define DRIVER_TYPE_GE64	1

class CDriver
{
	int m_Id;
	int m_Type;
	bool m_Exists;
	wxString m_Name;

public:

	CDriver();
	virtual ~CDriver();
	//SET
	void SetName(wxString v);
	void SetType(int v);
	void SetId(int v);
	void SetExists(bool v);
	
	//GET
	wxString GetName();
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
	
	virtual void SetLon(double v);
	virtual void SetLat(double v);
	virtual void SetLonMap(double v);
	virtual void SetLatMap(double v);
	
	virtual void SetGpsLon(double v);
	virtual void SetGpsLat(double v);
	virtual void SetGpsLonMap(double v);
	virtual void SetGpsLatMap(double v);
	
	virtual void SetDB(void *v);

	//GET
	virtual int GetBaseStationId();
	virtual wxString GetText();
	virtual wxString GetFullText();
	virtual float GetInputVolt();
	virtual double GetGpsLon();
	virtual double GetGpsLat();
	virtual double GetGpsLonMap();
	virtual double GetGpsLatMap();
	
		
};

#endif