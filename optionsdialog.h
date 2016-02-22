#ifndef __OPTIONS_DIALOG
#define __OPTIONS_DIALOG

#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <wx/clrpicker.h>
#include "conf.h"

class COptionsDialog: public wxDialog
{
	wxSpinCtrl *m_NumberOfTries;
	wxSpinCtrl *m_SecondsBetweenTries;
	
	wxColourPickerCtrl *m_SymbolNormalColor;
	wxColourPickerCtrl *m_SymbolNoMonitorColor;
	wxColourPickerCtrl *m_SymbolErrorColor;
	wxColourPickerCtrl *m_SymbolLightOn;
	
	wxSlider *m_SymbolNormalColorAlpha;
	wxSlider *m_SymbolNoMonitorColorAlpha;
	wxSlider *m_SymbolErrorAlpha;
	wxSlider *m_SymbolLightOnAlpha;
	wxSlider *m_FontSize;
	wxSlider *m_ViewNameScale;
	wxSlider *m_ScaleFactor;
	
	wxTextCtrl *m_LowerThreshold;
	wxTextCtrl *m_UpperThreshold;
	wxTextCtrl *m_RestrictedArea;
	wxTextCtrl *m_OffPositionArea;
	wxTextCtrl *m_ReportTimeout;
	wxCheckBox *m_ShowNames;

	wxRadioButton *m_PositionFromGps;
	wxRadioButton *m_PositionFromSymbol;
	
	wxPanel *GetButtonPanel(wxWindow *parent);
	wxPanel *GetColorPanel(wxWindow *parent);
	wxPanel *GetFontPanel(wxWindow *Parent);
	wxPanel *GetPositionFromPanel(wxWindow *Parent);

	wxPanel *GetOtherPanel(wxWindow *Parent);
	wxPanel *GetGlobalOtherPanel(wxWindow *Parent);
	wxPanel *GetGlobalThresholdPanel(wxWindow *Parent);
	wxPanel *GetGlobalSunPanel(wxWindow *Parent);

	wxPanel *GetPage1(wxWindow *Parent);
	wxPanel *GetPage2(wxWindow *Parent);

	wxTextCtrl *m_TextLat;
	wxTextCtrl *m_TextLon;

	int m_DegreeFormat;
	bool m_LonValid;
	bool m_LatValid;
	double m_Lon;
	double m_Lat;
	

	void OnColorPicker(wxColourPickerEvent &event);
	void OnAlpha(wxCommandEvent &event);
	void OnNameScale(wxCommandEvent &event);
	void OnFontSize(wxCommandEvent &event);
	void OnScaleFactor(wxCommandEvent &event);
	void OnShowNames(wxCommandEvent &event);
	void OnRestrictedArea(wxCommandEvent &event);
	void OnLowerThreshold(wxCommandEvent &event);
	void OnUpperThreshold(wxCommandEvent &event);
	void OnOffPositionArea(wxCommandEvent &event);
	void OnLon(wxCommandEvent &event);
	void OnLat(wxCommandEvent &event);
	void OnPositionFromGps(wxCommandEvent &event);
	void OnPositionFromSymbol(wxCommandEvent &event);
	void OnReportTimeout(wxCommandEvent &event);
	void OnDbConfig(wxCommandEvent &event);


public:

	COptionsDialog();
	~COptionsDialog();
	

	enum
	{
		ID_SYMBOL_NORMAL_COLOR = 2300,
		ID_SYMBOL_NORMAL_ALPHA,
		ID_SYMBOL_NO_MONITOR_COLOR,
		ID_SYMBOL_NO_MONITOR_ALPHA,
		ID_SYMBOL_ERROR_COLOR,
		ID_SYMBOL_ERROR_ALPHA,
		ID_SYMBOL_LIGHT_ON_COLOR,
		ID_SYMBOL_LIGHT_ON_ALPHA,
		ID_SHOW_NAMES,
		ID_SCALE_FACTOR,
		ID_RESTRICTED_AREA,
		ID_LOWER_THRESHOLD,
		ID_UPPER_THRESHOLD,
		ID_OFF_POSITION_AREA,
		ID_SUN_LON,
		ID_SUN_LAT,
		ID_GPS,
		ID_SYMBOL,
		ID_REPORT_TIMEOUT,

		ID_FONT_SIZE,
		ID_VIEW_NAME_SCALE,
		ID_DB_CONFIG,
	
	};


	DECLARE_EVENT_TABLE();

};


#endif