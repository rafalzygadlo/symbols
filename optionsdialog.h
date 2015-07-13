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
	wxColourPickerCtrl *m_SymbolNormalColor,*m_SymbolNoMonitorColor,*m_SymbolErrorColor,*m_SymbolLightOn;
	wxSlider *m_SymbolNormalColorAlpha,*m_SymbolNoMonitorColorAlpha,*m_SymbolErrorAlpha,*m_SymbolLightOnAlpha;
	wxSlider *m_FontSize,*m_ViewNameScale;
	
	wxSpinCtrl *m_CommTimeout;

	
	wxPanel *GetButtonPanel(wxWindow *parent);
	wxPanel *GetColorPanel(wxWindow *parent);
	wxPanel *GetFontPanel(wxWindow *Parent);
	wxPanel *GetOtherPanel(wxWindow *Parent);

	wxPanel *GetPage1(wxWindow *Parent);

	void OnColorPicker(wxColourPickerEvent &event);
	void OnAlpha(wxCommandEvent &event);
	void OnNameScale(wxCommandEvent &event);
	void OnFontSize(wxCommandEvent &event);


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

		ID_FONT_SIZE,
		ID_VIEW_NAME_SCALE,
	
	};


	DECLARE_EVENT_TABLE();

};


#endif