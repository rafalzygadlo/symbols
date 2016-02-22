#ifndef __POSITIONDIALOG
#define __POSITIONDIALOG

#include <wx/wx.h>
#include <vector>
#include <wx/spinctrl.h>
#include "dll.h"

class CMapPlugin;
class CPositionDialog: public wxDialog
{
	CMapPlugin *_Parent;
	wxTextCtrl *m_TextLon;
	wxTextCtrl *m_TextLat;
	wxTextCtrl *m_TextName;
	wxComboBox *m_TextArea;
	
	void OnLon(wxCommandEvent &event);
	void OnLat(wxCommandEvent &event);
	void OnOk(wxCommandEvent &event);
	void OnCancel(wxCommandEvent &event);
						
public:

	CPositionDialog(CMapPlugin *Parent);
	~CPositionDialog();
	void _SetPosition(double lon, double lat);
		
	DECLARE_EVENT_TABLE();
	enum
	{
		ID_CLOSE = 1234,
		ID_RADIO,
		ID_LON,
		ID_LAT,
		ID_OK,
		ID_CANCEL
		
	};
	
};

#endif