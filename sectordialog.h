#ifndef __SECTOR_DIALOG_H
#define __SECTOR_DIALOG_H

#include <wx/wx.h>
#include <wx/clrpicker.h>

class CSectorDialog :public wxDialog
{
	wxString m_Id;
	wxTextCtrl *m_CoverageText;
	wxTextCtrl *m_SectorTextFrom;
	wxTextCtrl *m_SectorTextTo;
	wxColourPickerCtrl *m_ColorPicker;
	
	void OnNewSector(wxCommandEvent &event);
	void OnDelete(wxCommandEvent &event);
	wxPanel *GetSectorPanel(wxWindow *parent, bool _add = true);
	wxPanel *CSectorDialog::GetButtonPanel(wxWindow *parent);

public:

	CSectorDialog();
	~CSectorDialog();
		
	wxString _GetId();
	wxColor GetColor();
	wxString GetCoverage();
	wxString GetSectorFrom();
	wxString GetSectorTo();


	void _SetId(wxString v);
	void SetColor(wxColor color);
	void SetCoverage(wxString v);
	void SetSectorFrom(wxString v);
	void SetSectorTo(wxString v);
	
};

#endif