#ifndef __SECTOR_DIALOG
#define __SECTOR_DIALOG

#include <wx/wx.h>
#include <wx/clrpicker.h>
#include <wx/spinctrl.h>
#include "sector.h"

class CSectorDialog :public wxDialog
{
	wxString m_Id;
	wxString m_IdCharacteristic;
	
	wxSpinCtrlDouble *m_CoverageText;
	wxSpinCtrlDouble *m_SectorTextFrom;
	wxSpinCtrlDouble *m_SectorTextTo;
	wxColourPickerCtrl *m_ColorPicker;
	wxComboBox *m_Characteristic;
	CSector *m_Sector;
	wxWindow *m_Parent;
	

	void OnNewSector(wxCommandEvent &event);
	void OnDelete(wxCommandEvent &event);
	void OnSectorFrom(wxSpinDoubleEvent &event);
	void OnSectorTo(wxSpinDoubleEvent &event);
	void OnColor(wxColourPickerEvent &event);
	wxPanel *GetSectorPanel(wxWindow *parent, bool _add = true);
	wxPanel *GetButtonPanel(wxWindow *parent);

public:

	CSectorDialog(void *db, wxWindow *parent);
	~CSectorDialog();
		
	wxString _GetId();
	wxColor GetColor();
	double GetCoverage();
	double GetSectorFrom();
	double GetSectorTo();
	int GetIdCharacteristic();
	
	void _SetId(wxString v);
	void SetColor(wxColor color);
	void SetCoverage(wxString v);
	void SetSectorFrom(wxString v);
	void SetSectorTo(wxString v);
	void SetSector(CSector *v);
	void SetIdCharacteristic(wxString v);
	
	DECLARE_EVENT_TABLE();
	
	enum
	{
		ID_SECTOR_FROM = 2500,
		ID_SECTOR_TO,
		ID_SECTOR_COLOR,
	};

};

#endif