#ifndef __SYMBOLPANEL_H
#define __SYMBOLPANEL_H

#include <wx/html/htmlwin.h>
#include "symbolpanel.h"
#include "navibroker.h"
#include "tgamem.h"
#include "picture.h"
#include "grid.h"
#include "graph.h"
#include "light.h"
#include "symbol.h"
#include "graphdialog.h"
#include "icon.h"


class CSymbolPanel : public wxPanel
{
	CPicturePanel *m_PicturePanel;
	CSymbol *m_Symbol;	
	CGraphDialog *m_GraphDialog;
	wxHtmlWindow *m_Html;
	int m_IdSBMS;
	int m_IdBaseStation;
	int m_SBMSID;
	wxButton *m_ButtonManagement;
	wxButton *m_ButtonGraph;
	wxButton *m_ButtonAlarm;

	CMyIcon *m_Calibrated,*m_ForcedOff,*m_PhotoCellNightTime,*m_FaultOutput,*m_SolarCharger,*m_SyncMaster,*m_SeasonControl;

	void SetHeader();
	void SymbolInfo(void *db,CSymbol *ptr);
	void SBMSInfo(void *db,int id_sbms);
	void PictureInfo(void *db,CSymbol *ptr);
	void BaseStationInfo(void *db, int id_base_station);
	void SBMSLastRaport(void *db, int id_sbms, int id_base_station);
	void SetGraph(void *db, int id_sbms, int id_base_station);
	void OnManagement(wxCommandEvent &event);
	void OnGraph(wxCommandEvent &event);
	void OnAlarm(wxCommandEvent &event);
	void OnMenu(wxContextMenuEvent &event);
	void OnShowMenu(wxCommandEvent &event);
	void SetCalibrated(bool v);
	void SetForcedOff(bool v);
	void SetPhotoCellNightTime(bool v);
	void SetFaultOutput(bool v);
	void SetSolarCharger(bool v);
	void SetSyncMaster(bool v);
	void SetSeasonControl(bool v);


public:

	CSymbolPanel(wxWindow *parent);
	~CSymbolPanel();
	void GetPage1();	
	void SetPage1(CSymbol *ptr);
	void SetPageEmpty();
	void SetSBMS();
	
	enum
	{
		ID_MANAGEMENT = 2600,
		ID_GRAPH,
		ID_ALARM,
		ID_SHOW_PICTURE,
		ID_CALIBRATED,
		ID_FORCED_OFF,
		ID_PHOTOCELL_NIGHT_TIME,
		ID_FAULT_OUTPUT,
		ID_SOLAR_CHARGER,
		ID_SYNC_MASTER,
		ID_SEASON_CONTROL,

	};

	DECLARE_EVENT_TABLE();
	
};

#endif