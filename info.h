#ifndef __INFO
#define __INFO

#include <wx/wx.h>
#include <vector>

class CMyInfo: public wxDialog
{
	wxStaticText *Text;
	void OnCloseButton(wxCommandEvent &event);
	void OnClose(wxCloseEvent &event);
					
public:

	CMyInfo(wxWindow *Parent, wxString text, bool center_on_screen);
	~CMyInfo();
	void SetText(wxString text);	
	
	
	
};

#endif