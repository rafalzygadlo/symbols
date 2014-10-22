#ifndef __PICTURE_H
#define __PICTURE_H

#include <wx/wx.h>
#include <wx/wrapsizer.h>
#include <wx/grid.h>
#include <wx/hyperlink.h>
#include "conf.h"

class CPicturePanel: public wxPanel
{
	wxBoxSizer *m_PanelSizer;
	wxStaticBitmap *m_StaticPicture;
	wxImage m_Picture;
	wxString m_ID;
	wxStaticText *m_Info;
	
	void OnNew(wxHyperlinkEvent &event);
	void OnPick(wxHyperlinkEvent &event);
	void OnDelete(wxCommandEvent &event);
	void New();

public:

	CPicturePanel(wxWindow *parent, int type = -1);
	~CPicturePanel();
	wxImage GetPicture();
	void SetPictureId(wxString id);
	void _SetId(wxString id);
	void Read();
	void Clear();

	DECLARE_EVENT_TABLE();

	enum
	{
		ID_NEW = 8124,
		ID_DELETE,
		ID_PICK,
	};

};


#endif