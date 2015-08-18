#ifndef __OPTIONS_DIALOG_H
#define __OPTIONS_DIALOG_H

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
	wxCheckBox *m_ShowNames;
	

	wxPanel *GetButtonPanel(wxWindow *parent);
	wxPanel *GetColorPanel(wxWindow *parent);
	wxPanel *GetFontPanel(wxWindow *Parent);
	wxPanel *GetOtherPanel(wxWindow *Parent);
	wxPanel *GetThresholdPanel(wxWindow *Parent);


	wxPanel *GetPage1(wxWindow *Parent);

	void OnColorPicker(wxColourPickerEvent &event);
	void OnAlpha(wxCommandEvent &event);
	void OnNameScale(wxCommandEvent &event);
	void OnFontSize(wxCommandEvent &event);
	void OnScaleFactor(wxCommandEvent &event);
	void OnShowNames(wxCommandEvent &event);

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

		ID_FONT_SIZE,
		ID_VIEW_NAME_SCALE,
	
	};


	DECLARE_EVENT_TABLE();

};


#endif