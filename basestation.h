#ifndef __BASE_STATION
#define __BASE_STATION

#include "ticker.h"
#include <gl/gl.h>
#include "navibroker.h"
#include "tgamem.h"
#include "geometrytools.h"
#include "nvfastfont.h"
#include "nvtime.h"
#include "listItem.h"


class CBaseStation: public CListItem
{
	void *m_DB;
	CNaviBroker *m_Broker;
	//pozycja referencyjna
	double m_RLon, m_RLat, m_RLonMap, m_RLatMap;
	//pozycja GPS
	double m_GpsLon, m_GpsLat, m_GpsLonMap, m_GpsLatMap;
	//pozycja gps lub referencyjna
	double m_Lon, m_Lat, m_LonMap, m_LatMap;

	double m_Scale;
	double m_SmoothScaleFactor;
	double m_RectWidth;
	double m_RectHeight;
	double m_TranslationX;
	double m_TranslationY;
	double m_VisibleMap[4];
	wxString m_Name;
	bool m_Exists;
	bool m_Selected;
	
	void UpdateViewPort();
	void SetColor(int id);
	void SetValues();
	void SetSmoothScaleFactor(double v);
	//void Read();
	//void SetSymbolColor();
	void RenderSelected();
	void RenderBaseStation();
		
public:

	CBaseStation(CNaviBroker *broker);
	~CBaseStation();

	void OnTick(void *db);
	
	//SET
	void SetName(wxString v);
	void SetDB(void *db);
	void SetLon(double v);
	void SetLat(double v);
	void SetLonMap(double v);
	void SetLatMap(double v);
	
	
	void Render() override;
	void Mouse(int x, int y, bool lmb, bool mmb, bool rmb) override;

};

#endif