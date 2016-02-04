#ifndef __SECTOR
#define __SECTOR

#include <wx/wx.h>

class CSector
{
	int m_Id;
	float m_Coverage;
	float m_SectorFrom;
	float m_SectorTo;
	float m_Radius;
	wxColor m_Color;
	int m_IdCharacteristic;
		
public:

	CSector();
	~CSector();
		
	wxColor GetColor();
	float GetCoverage();
	float GetSectorFrom();
	float GetSectorTo();
	int GetId();
	int GetIdCharacteristic();
	
	void SetId(int v);
	void SetColor(wxColor color);
	void SetCoverage(float v);
	void SetSectorFrom(float v);
	void SetSectorTo(float v);
	void SetRadius(float v);
	void SetIdCharacteristic(int v);

	void RenderSelected();
	void Render();

};

#endif