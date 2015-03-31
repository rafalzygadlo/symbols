#ifndef __PICTURE_H
#define __PICTURE_H

#include <wx/wx.h>
#include <wx/wrapsizer.h>
#include <wx/grid.h>
#include <wx/hyperlink.h>
#include "conf.h"

class CPicturePanel: public wxPanel
{
	void *m_DB;
	wxBoxSizer *m_PanelSizer;
	wxStaticBitmap *m_StaticPicture;
	wxImage m_Picture;
	int m_ID;
	wxStaticText *m_Info;
		
	void OnNew(wxHyperlinkEvent &event);
	void OnPick(wxHyperlinkEvent &event);
	void OnDelete(wxCommandEvent &event);
	void New();

public:

	CPicturePanel(void *db, wxWindow *parent, int type = -1);
	~CPicturePanel();
	wxImage GetPicture();
	void SetPictureId(int id);
	int GetPictureId();
	int GetPictureType();
	void _SetId(int id);
	void Read();
	void Clear();
	void SetDB(void *db);
	
	DECLARE_EVENT_TABLE();

	enum
	{
		ID_NEW = 8124,
		ID_DELETE,
		ID_PICK,
	};

};


#endif