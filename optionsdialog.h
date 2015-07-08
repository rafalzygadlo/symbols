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
		
	wxPanel *GetButtonPanel(wxWindow *parent);
	wxPanel *GetColorPanel(wxWindow *parent);
	void OnColorPicker(wxColourPickerEvent &event);
	void OnAlpha(wxCommandEvent &event);

public:

	COptionsDialog();
	~COptionsDialog();
	

	enum
	{
		ID_SYMBOL_NORMAL_COLOR,
		ID_SYMBOL_NORMAL_ALPHA,
		
		ID_SYMBOL_NO_MONITOR_COLOR,
		ID_SYMBOL_NO_MONITOR_ALPHA,

		ID_SYMBOL_ERROR_COLOR,
		ID_SYMBOL_ERROR_ALPHA,

		ID_SYMBOL_LIGHT_ON_COLOR,
		ID_SYMBOL_LIGHT_ON_ALPHA,
	
	};


	DECLARE_EVENT_TABLE();

};


#endif