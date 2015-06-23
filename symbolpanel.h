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

class CSymbolPanel : public wxPanel
{
	CPicturePanel *m_PicturePanel;
	CSymbol *m_Symbol;	
	CLightPanel *m_LightPanel;
	CGraphDialog *m_GraphDialog;
	wxHtmlWindow *m_Html;
	int m_IdSBMS;
	int m_IdBaseStation;
	int m_SBMSID;
	wxButton *m_ButtonManagement;
	wxButton *m_ButtonGraph;
	wxButton *m_ButtonAlert;

	void SetHeader();
	void SymbolInfo(void *db,CSymbol *ptr);
	void SBMSInfo(void *db,int id_sbms);
	void PictureInfo(void *db,CSymbol *ptr);
	void BaseStationInfo(void *db, int id_base_station);
	void SBMSLastRaport(void *db, int id_sbms, int id_base_station);
	void SetGraph(void *db, int id_sbms, int id_base_station);
	void OnManagement(wxCommandEvent &event);
	void OnGraph(wxCommandEvent &event);

public:

	CSymbolPanel(wxWindow *parent);
	~CSymbolPanel();
	void GetPage1();	
	void SetPage1(CSymbol *ptr);
	void SetPageEmpty();
	void SetSBMS();
	
	enum
	{
		ID_MANAGEMENT = 7000,
		ID_GRAPH,
		ID_ALERT,
	};

	DECLARE_EVENT_TABLE();
	
};

#endif