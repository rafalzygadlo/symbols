#ifndef __DRIVER_H
#define __DRIVER_H
#include <wx/wx.h>

#define DRIVER_TYPE_SBMS	0
#define DRIVER_TYPE_GE64	1

class CDriver
{
	int m_Id;
	int m_Type;
	wxString m_Name;

public:

	CDriver();
	virtual ~CDriver();
	//SET
	void SetName(wxString v);
	void SetType(int v);
	void SetId(int v);
	
	//GET
	wxString GetName();
	int GetType();
	int GetId();
	
	void Render();
	
	//SBMS
	//SET
	virtual void SetIdBaseStation(int v);
	virtual void SetMMSI(int v);
	virtual void SetForcedOff(int v);
	virtual void SetInputVolt(float v);

	//GET
	virtual int GetBaseStationId();
	virtual wxString GetText();
	virtual float GetInputVolt();
		
};

#endif